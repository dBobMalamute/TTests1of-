#include "NumbersStandardDeviationIdea.h"

NumbersStandardDeviationAttributes::NumbersStandardDeviationAttributes()
{
    m_listName = "Numbers Standard Deviation";
    m_displayName = "Standard Deviation";
    m_authors << "dBob";
    m_description = "Takes in a list of numbers and calculates the standard deviation. Contains a display to show"
                    " what's going on inside.";
    m_iconPath = "qrc:/Icons/NumbersStandardDeviation.png";

    m_dataTypesIn.push_back(Magic<NumbersDataTypeAttributes>::cast().id());
    m_dataTypesOut.push_back(Magic<NumberDataTypeAttributes>::cast().id());

    m_gear = true;

    m_embeddedQMLPath = ":/QML/NumbersStandardDeviationIdea.qml";
    m_minimizable = true;
    m_minimizedQMLPath = ":/QML/NumbersStatistic.qml";
    m_minimizedName = "Stdev";
    m_differentNameOnMinimized = true;

    m_externalQMLPaths << ":/QML/SpeedControl.qml";
    m_externalQMLLocations.push_back({true, false, 10,0});
}

const IdeaAttributes NumbersStandardDeviationIdea::attributes()
{
    return Magic<NumbersStandardDeviationAttributes>::cast();
}

NumbersStandardDeviationIdea::NumbersStandardDeviationIdea() :
    m_mean(0)
{

}


void NumbersStandardDeviationIdea::validate()
{
    auto v_nums = m_input.lock();
    if(v_nums)
    {
        if(v_nums->numbers().size() == 0)
        {
            setStatus(IdeaStatus::Error, "No Input", "The input contains no numbers. It isn't possible to calculate the "
                                                     "standard deviation of nothing");
        }
        else if(v_nums->numbers().size() == 1)
        {
            setStatus(IdeaStatus::Error, "Only One Number", "The input has only one number. This is not allowed");
        }
        else
        {
            setStatus(IdeaStatus::Working, "Calculating", "Currently calculating the standard"
                                                                                  "deviation of the numbers: " + v_nums->toString());
            m_nums = v_nums->numbers();
            compute();
        }
    }
    else
    {
        setDefaultStatus();
    }
}

void NumbersStandardDeviationIdea::compute()
{
    emit startSpinningGear();

    int length = m_nums.size();
    double e_x = 0.0;
    double e_x2 = 0.0;

    for (int i = 0; i < length; i++)
    {
        e_x += m_nums[i];
        e_x2 += m_nums[i] * m_nums[i];

    }
    e_x /= length;
    e_x2 /= length;

    double stdev = std::sqrt(e_x2 - e_x * e_x);
    m_mean = e_x;
    setStatistic(stdev);

    if(!minimized())
        prepareVisuals();

    m_output = std::make_shared<NumberDataType>(stdev);
    emit newData(0);
    emit stopSpinningGear();
}

void NumbersStandardDeviationIdea::prepareVisuals()
{
    int length = m_nums.size();

    if(m_autoFit)
    {
        double lowBound = m_nums[0];
        double upBound = m_nums[0];

        for (int i = 0; i < length; i++)
        {
            if(m_nums[i] < lowBound)
                lowBound = m_nums[i];
            if(m_nums[i] > upBound)
                upBound = m_nums[i];
        }
        double len = 1.05*qMax(m_mean - lowBound, upBound - m_mean);
        m_lowBound = m_mean - len;
        emit lowBoundChanged(m_lowBound);
        m_upBound = m_mean + len;
        emit upBoundChanged(m_upBound);
    }

    //Let the display know there are new dots, as well as how many there are.
    m_dotPostions.clear();
    m_dotPostions.reserve(length);
    for(int i = 0; i < length; i++)
        m_dotPostions.push_back(450.0 * (m_nums[i] - m_lowBound) / (m_upBound - m_lowBound));

    m_meanPosition = 450.0 * (m_mean - m_lowBound) / (m_upBound - m_lowBound);
    m_stdevLength = 450.0 * m_statistic / (m_upBound - m_lowBound);

    playAnimation();
}

void NumbersStandardDeviationIdea::playAnimation()
{
    emit startStandardDeviationAnimation(m_dotPostions, m_meanPosition, m_stdevLength);
}
