#include "MultiplicationIdea.h"

MultiplicationAttributes::MultiplicationAttributes()
{
    m_listName = "Multiplication";
    m_displayName = "Multiplication";
    m_authors << "dBob";
    m_description = "This idea represents multiplication of two decimal-type numbers.";
    m_iconPath = "qrc:/Icons/Multiplication.png";

    m_dataTypesIn.push_back(Magic<NumberDataTypeAttributes>::cast().id());
    m_dataTypesIn.push_back(Magic<NumberDataTypeAttributes>::cast().id());
    m_dataTypesOut.push_back(Magic<NumberDataTypeAttributes>::cast().id());

    m_gear = true;

    m_embeddedQMLPath = ":/QML/MultiplicationIdea.qml";
    m_minimizedQMLPath = ":/QML/MultiplicationMinimized.qml";
    m_minimizable = true;
}

MultiplicationIdea::MultiplicationIdea()
{

}

const IdeaAttributes MultiplicationIdea::attributes()
{
    return Magic<MultiplicationAttributes>::cast();
}

void MultiplicationIdea::validate()
{
    auto n1 = m_input1.lock();
    auto n2 = m_input2.lock();
    if(n1 && n2)
    {
        setStatus(IdeaStatus::Working, "Multiplying", "Multiplying " + QString::number(n1->number()) + " * " + QString::number(n2->number()));
        compute(n1->number(),n2->number());
    }
    else
    {
        setDefaultStatus();
        emit clear();
    }
}

void MultiplicationIdea::compute(double n1, double n2)
{
    emit startSpinningGear();

    m_result = std::make_shared<NumberDataType>(n1*n2);
    emit newData(0);

    emit display(n1, n2, n1*n2);

    emit stopSpinningGear();
}


void MultiplicationIdea::resetDisplay()
{
    if(valid())
    {
        double n1 = m_input1.lock()->number();
        double n2 = m_input2.lock()->number();
        emit display(n1, n2, n1*n2);
    }
}
