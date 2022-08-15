#include "NumbersKurtosisIdea.h"

NumbersKurtosisIdeaAttributes::NumbersKurtosisIdeaAttributes()
{
    m_listName = "Numbers Kurtosis";
    m_displayName = "Kurtosis";
    m_authors << "dBob";
    m_description = "Takes in a list of numbers and calculates the kurtosis. Contains a display to show"
                    " what's going on inside.";
    m_iconPath = "qrc:/Icons/NumbersKurtosis.png";

    m_dataTypesIn.push_back(Magic<NumbersDataTypeAttributes>::cast().id());
    m_dataTypesOut.push_back(Magic<NumberDataTypeAttributes>::cast().id());

    m_gear = true;

    m_embeddedQMLPath = ":/QML/NumbersStatistic.qml";
}

const IdeaAttributes NumbersKurtosisIdea::attributes()
{
    return Magic<NumbersKurtosisIdeaAttributes>::cast();
}

NumbersKurtosisIdea::NumbersKurtosisIdea() :
    m_mean(0)
{

}

void NumbersKurtosisIdea::load(const QJsonObject &obj)
{
    NumbersToNumberTemplate::load(obj);

    validate();
}

double NumbersKurtosisIdea::mean() const
{
    return m_mean;
}

void NumbersKurtosisIdea::setMean(double mean)
{
    if (qFuzzyCompare(m_mean, mean))
        return;

    m_mean = mean;
    emit meanChanged(m_mean);
}

void NumbersKurtosisIdea::validate()
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
                                                     "kurtosis of nothing");
        }
        else if(v_nums->numbers().size() <= 3)
        {
            setStatus(IdeaStatus::Error, "Not enough Numbers", "The input has less than 4 numbers. Kurtosis"
                                                                 " is not defined.");
        }
        else
        {
            setStatus(IdeaStatus::Working, "Calculating the Kurtosis", "Calculating the Kurtosis");
            m_nums = v_nums->numbers();
            compute();
        }
    }
    else
    {
        setDefaultStatus();
    }
}

void NumbersKurtosisIdea::compute()
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
    double kurtosis = 0.0;
    for(int i = 0; i < length; i++)
    {
        double temp = m_nums[i] - mean;
        variance += temp*temp;
        kurtosis += temp*temp*temp*temp;
    }
    if(variance == 0)
    {
        setStatus(IdeaStatus::Error, "Stdev = 0", "The skew is undefined if the standard deviation is 0");
        emit stopSpinningGear();
        return;
    }

    kurtosis /= length;
    variance /= length;

    kurtosis /= variance*variance;

    setStatistic(kurtosis);
    m_output = std::make_shared<NumberDataType>(kurtosis);
    emit newData(0);
    emit stopSpinningGear();
}

void NumbersKurtosisIdea::prepareVisuals()
{

}

