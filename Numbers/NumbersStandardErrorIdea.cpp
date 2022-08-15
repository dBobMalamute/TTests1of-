#include "NumbersStandardErrorIdea.h"

NumbersStandardErrorAttributes::NumbersStandardErrorAttributes()
{
    m_listName = "Numbers Standard Error";
    m_displayName = "Standard Error\nof Mean";
    m_authors << "dBob";
    m_description = "Takes in a list of numbers and calculates the standard error.";
    m_iconPath = "qrc:/Icons/NumbersStandardError.png";

    m_dataTypesIn.push_back(Magic<NumbersDataTypeAttributes>::cast().id());
    m_dataTypesOut.push_back(Magic<NumberDataTypeAttributes>::cast().id());

    m_gear = true;

    m_embeddedQMLPath = ":/QML/NumbersStatistic.qml";

}

const IdeaAttributes NumbersStandardErrorIdea::attributes()
{
    return Magic<NumbersStandardErrorAttributes>::cast();
}

NumbersStandardErrorIdea::NumbersStandardErrorIdea()
{

}

void NumbersStandardErrorIdea::validate()
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
            setStatus(IdeaStatus::Working, "Calculating", "Currently calculating the standard error");
            m_nums = v_nums->numbers();
            compute();
        }
    }
    else
    {
        setDefaultStatus();
   }
}

void NumbersStandardErrorIdea::compute()
{
    emit startSpinningGear();

    double e_x = 0.0;
    double e_x2 = 0.0;

    int length = m_nums.size();

    for (int i = 0; i < length; i++)
    {
        e_x += m_nums[i];
        e_x2 += m_nums[i] * m_nums[i];
    }
    e_x /= length;
    e_x2 /= length;

    double stdError = std::sqrt((e_x2 - e_x * e_x) / length);
    setStatistic(stdError);

    m_output = std::make_shared<NumberDataType>(stdError);
    emit newData(0);
    emit stopSpinningGear();
}

void NumbersStandardErrorIdea::prepareVisuals()
{

}
