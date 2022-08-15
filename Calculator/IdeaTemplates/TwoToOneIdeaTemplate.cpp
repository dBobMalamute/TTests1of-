#include "TwoToOneIdeaTemplate.h"

TwoToOneIdeaTemplate::TwoToOneIdeaTemplate()
{

}

void TwoToOneIdeaTemplate::onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber plugNumber)
{
    auto number = std::dynamic_pointer_cast<NumberDataType>(dataType);
    if(plugNumber == 0)
        m_input1 = number;
    else
        m_input2 = number;

    validate();
}

std::shared_ptr<DataType> TwoToOneIdeaTemplate::dataOut(PlugNumber)
{
    return std::static_pointer_cast<DataType>(m_result);
}



