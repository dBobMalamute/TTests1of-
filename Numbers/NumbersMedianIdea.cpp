#include "NumbersMedianIdea.h"

NumbersMedianAttributes::NumbersMedianAttributes()
{
    m_listName = "Numbers Median";
    m_displayName = "Median";
    m_authors << "dBob";
    m_description = "Takes in a list of numbers and calculates the mean. Contains a display to show"
                    " what's going on inside.";
    m_iconPath = "qrc:/Icons/NumbersMedian.png";

    m_dataTypesIn.push_back(Magic<NumbersDataTypeAttributes>::cast().id());
    m_dataTypesOut.push_back(Magic<NumberDataTypeAttributes>::cast().id());

    m_gear = true;

    m_embeddedQMLPath = ":/QML/NumbersMedianIdea.qml";
    m_minimizable = true;
    m_minimizedQMLPath = ":/QML/NumbersStatistic.qml";

    m_externalQMLPaths << ":/QML/SpeedControl.qml";
    m_externalQMLLocations.push_back({true, false, 10,0});
}

const IdeaAttributes NumbersMedianIdea::attributes()
{
    return Magic<NumbersMedianAttributes>::cast();
}

NumbersMedianIdea::NumbersMedianIdea()
{

}

void NumbersMedianIdea::validate()
{
    auto v_nums = m_input.lock();
    if(v_nums)
    {
        if(v_nums->numbers().size() == 0)
        {
            setStatus(IdeaStatus::Error, "No Input", "The input contains no numbers. It isn't possible to calculate the "
                                                     "median of nothing");
        }
        else if(v_nums->numbers().size() <= 1)
        {
            setStatus(IdeaStatus::Warning, "Only One Number", "The input has only one number. Taking the median of a "
                                                              "single number is technically something you can do, but"
                                                              " this is probably a mistake.");
            m_nums = v_nums->numbers();
            compute();
        }
        else
        {
            setStatus(IdeaStatus::Working, "Calculating the median", "Currently calucating the median of the input numbers");
            m_nums = v_nums->numbers();
            compute();
        }
    }
    else
    {
        setDefaultStatus();
    }
}

void NumbersMedianIdea::compute()
{
    emit startSpinningGear();

    int length = m_nums.size();
    double median;
    std::sort(m_nums.begin(), m_nums.end());

    if(length % 2 == 1)
        median = m_nums.at((length - 1) / 2);
    else
        median = 0.5 * (m_nums.at(length / 2) + m_nums.at((length / 2) - 1));

    setStatistic(median);
    m_output = std::make_shared<NumberDataType>(median);
    emit newData(0);
    emit stopSpinningGear();

    if(!minimized())
        prepareVisuals();
}

void NumbersMedianIdea::prepareVisuals()
{
    //Autofit if necessary.
    int length = m_nums.size();

    if(m_autoFit)
    {

        double lowBound = m_nums[0];
        double upBound = m_nums[0];
        for (int i = 1; i < length; i++)
        {
            if(m_nums[i] < lowBound)
                lowBound = m_nums[i];
            if(m_nums[i] > upBound)
                upBound = m_nums[i];
        }

        m_lowBound = (1.01 * lowBound - 0.01 *upBound);
        emit lowBoundChanged(m_lowBound);
        m_upBound = (1.01 * upBound - 0.01 * lowBound);
        emit upBoundChanged(m_upBound);
    }

    //Let the display know there are new dots, as well as how many there are.
    m_dotPositions.clear();
    m_dotPositions.reserve(length);
    for(int i = 0; i < length; i++)
        m_dotPositions.push_back(450 * (m_nums[i] - m_lowBound) / (m_upBound - m_lowBound));

    m_medianPosition = 450 * (m_statistic - m_lowBound) / (m_upBound - m_lowBound);

    double totalDelay = 1500 * std::log2(1.0*length);

    m_medianDelay = totalDelay + 2000;

    m_delays.clear();
    m_delays.reserve(length);
    if(length % 2 == 1)
    {
        for(int i = 0; i < (length - 1) / 2; i++)
            m_delays.push_back(totalDelay * i / ((length - 1) / 2));

        m_delays.push_back(totalDelay);

        for(int i = (length + 1) / 2; i < length; i++)
            m_delays.push_back(totalDelay * (length - 1 - i) / ((length - 1) / 2));
    }
    else
    {
        for(int i = 0; i < (length - 2) / 2; i++)
            m_delays.push_back(totalDelay * i / ((length - 2) / 2));

        m_delays.push_back(totalDelay);
        m_delays.push_back(totalDelay);

        for(int i = (length + 2) / 2; i < length; i++)
            m_delays.push_back(totalDelay * (length - 1 - i) / ((length - 2) / 2));
    }

    playAnimation();
}

void NumbersMedianIdea::playAnimation()
{
    emit startMedianAnimation(m_dotPositions, m_delays,
                              m_medianPosition, m_medianDelay);
}
