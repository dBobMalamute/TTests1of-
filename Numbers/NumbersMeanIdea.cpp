#include "NumbersMeanIdea.h"

NumbersMeanAttributes::NumbersMeanAttributes()
{
    m_listName = "Numbers Mean";
    m_displayName = "Mean";
    m_authors << "dBob";
    m_description = "Takes in a list of numbers and calculates the mean. Contains a display to show"
                    " what's going on inside.";
    m_iconPath = "qrc:/Icons/NumbersMean.png";

    m_dataTypesIn.push_back(Magic<NumbersDataTypeAttributes>::cast().id());
    m_dataTypesOut.push_back(Magic<NumberDataTypeAttributes>::cast().id());

    m_gear = true;

    m_embeddedQMLPath = ":/QML/NumbersMeanIdea.qml";
    m_minimizable = true;
    m_minimizedQMLPath = ":/QML/NumbersStatistic.qml";

    m_externalQMLPaths << ":/QML/SpeedControl.qml";
    m_externalQMLLocations.push_back({true, false, 10,0});
}

const IdeaAttributes NumbersMeanIdea::attributes()
{
    return Magic<NumbersMeanAttributes>::cast();
}

void NumbersMeanIdea::playAnimation()
{
    emit startMeanAnimation(m_dotPostions, m_meanPosition);
}

NumbersMeanIdea::NumbersMeanIdea()
{

}

void NumbersMeanIdea::validate()
{
    auto v_nums = m_input.lock();
    if(v_nums)
    {
        if(v_nums->numbers().size() == 0)
        {
            setStatus(IdeaStatus::Error, "No Input", "The input contains no numbers. It isn't possible to calculate the "
                                                     "mean of nothing");
        }
        else if(v_nums->numbers().size() <= 1)
        {
            setStatus(IdeaStatus::Warning, "Only One Number", "The input has only one number. Taking the mean of a "
                                                              "single number is technically something you can do, but"
                                                              " this is probably a mistake.");
            m_nums = v_nums->numbers();
            compute();
        }
        else
        {
            setStatus(IdeaStatus::Working, "Calculating the mean", "Currently displaying the numbers: " + v_nums->toString());
            m_nums = v_nums->numbers();
            compute();
        }
    }
    else
    {
        setDefaultStatus();
    }
}

void NumbersMeanIdea::compute()
{
    emit startSpinningGear();

    double mean = m_nums[0];
    int length = m_nums.size();

    for (int i = 1; i < length; i++)
    {
        mean += m_nums[i];
    }
    mean /= length;

    setStatistic(mean);

    if(!minimized())
        prepareVisuals();

    m_output = std::make_shared<NumberDataType>(mean);
    emit newData(0);
    emit stopSpinningGear();
}

void NumbersMeanIdea::prepareVisuals()
{
    int length = m_nums.size();

    if(m_lowBound >= m_upBound) // User set bounds make the thing backwards.
    {
        setStatus(IdeaStatus::DisplayWarning, "Grid bounds Error", "The lower bound is greater than the upper bound");
        emit clearDisplay();
        return;
    }

    m_dotPostions.clear();
    m_dotPostions.reserve(length);

    m_meanPosition = 450.0 * (m_statistic - m_lowBound) / (m_upBound - m_lowBound);

    if(length == 1) // One dot edge case.
    {
        if(m_autoFit)
        {
            m_lowBound = m_statistic - 1;
            emit lowBoundChanged(m_lowBound);
            m_upBound = m_statistic + 1;
            emit upBoundChanged(m_upBound);
        }
        m_dotPostions.push_back(m_meanPosition);
    }
    else
    {
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

            m_lowBound = lowBound;
            emit lowBoundChanged(m_lowBound);
            m_upBound = upBound;
            emit upBoundChanged(m_upBound);
        }

        //Setup properties for the animation. Start the animation.
        double intervalLen = m_upBound - m_lowBound;
        for(int i = 0; i < length; i++)
            m_dotPostions.push_back(450 * (m_nums[i] - m_lowBound) / intervalLen);
        m_meanPosition = 450.0 * (m_statistic - m_lowBound) / intervalLen;
    }

    playAnimation();
}
