#include "NumbersSkewIdea.h"

NumbersSkewIdeaAttributes::NumbersSkewIdeaAttributes()
{
    m_listName = "Numbers Skew";
    m_displayName = "Skew";
    m_authors << "dBob";
    m_description = "Takes in a list of numbers and calculates the skew. Contains a display to show"
                    " what's going on inside.";
    m_iconPath = "qrc:/Icons/NumbersSkew.png";

    m_dataTypesIn.push_back(Magic<NumbersDataTypeAttributes>::cast().id());
    m_dataTypesOut.push_back(Magic<NumberDataTypeAttributes>::cast().id());

    m_gear = true;

    m_embeddedQMLPath = ":/QML/NumbersSkew.qml";
}

const IdeaAttributes NumbersSkewIdea::attributes()
{
    return Magic<NumbersSkewIdeaAttributes>::cast();
}

NumbersSkewIdea::NumbersSkewIdea() :
    m_mean(0),
    m_skew(0)
{

}

void NumbersSkewIdea::load(const QJsonObject &obj)
{
    NumbersToNumberTemplate::load(obj);

    validate();
}

double NumbersSkewIdea::mean() const
{
    return m_mean;
}

double NumbersSkewIdea::skew() const
{
    return m_skew;
}

void NumbersSkewIdea::setMean(double mean)
{
    if (qFuzzyCompare(m_mean, mean))
        return;

    m_mean = mean;
    emit meanChanged(m_mean);
}

void NumbersSkewIdea::setSkew(double skew)
{
    if (qFuzzyCompare(m_skew, skew))
        return;

    m_skew = skew;
    emit skewChanged(m_skew);
}

void NumbersSkewIdea::validate()
{
    auto v_nums = m_input.lock();
    if(v_nums)
    {
        if(m_lowBound >= m_upBound)
        {
            setStatus(IdeaStatus::Error, "Invalid Bounds", "The lower bound is greater than or equal to the upper bound."
                                                           " Please change the bounds or set autofit to true");
        }
        else if(v_nums->numbers().size() == 0)
        {
            setStatus(IdeaStatus::Error, "No Input", "The input contains no numbers. It isn't possible to calculate the "
                                                     "skew of nothing");
        }
        else if(v_nums->numbers().size() <= 2)
        {
            setStatus(IdeaStatus::Error, "Not enough Numbers", "The input has less than 3 numbers. Skew"
                                                                 " is not defined.");
        }
        else
        {
            setStatus(IdeaStatus::Working, "Calculating the Skew", "Calculating the skew");
            m_nums = v_nums->numbers();
            compute();
        }
    }
    else
    {
        setDefaultStatus();
    }
}

void NumbersSkewIdea::compute()
{
    emit startSpinningGear();

    double mean = m_nums[0];
    int length = m_nums.size();

    for (int i = 1; i < length; i++)
    {
        mean += m_nums[i];
    }
    mean /= length;

    double variance = 0.0;
    double skew = 0.0;

    for(int i = 0; i < length; i++)
    {
        double temp = m_nums[i] - mean;
        variance += temp*temp;
        skew += temp*temp*temp;
    }
    if(variance == 0)
    {
        setStatus(IdeaStatus::Error, "Stdev = 0", "The skew is undefined if the standard deviation is 0");
        emit stopSpinningGear();
        return;
    }
    variance = variance / length;
    skew /= length;
    skew /= std::pow(variance,1.5);

    setMean(mean);
    setSkew(skew);

    m_output = std::make_shared<NumberDataType>(skew);
    emit newData(0);
    emit stopSpinningGear();
}

void NumbersSkewIdea::prepareVisuals()
{

}

