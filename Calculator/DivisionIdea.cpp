#include "DivisionIdea.h"

DivisionAttributes::DivisionAttributes()
{
    m_listName = "Division";
    m_displayName = "Division";
    m_authors << "dBob";
    m_description = "This idea represents the division of one number by another";
    m_iconPath = "qrc:/Icons/Division.png";

    m_dataTypesIn.push_back(Magic<NumberDataTypeAttributes>::cast().id());
    m_dataTypesIn.push_back(Magic<NumberDataTypeAttributes>::cast().id());
    m_dataTypesOut.push_back(Magic<NumberDataTypeAttributes>::cast().id());

    m_gear = true;

    m_embeddedQMLPath = ":/QML/DivisionIdea.qml";
}

const IdeaAttributes DivisionIdea::attributes()
{
    return Magic<DivisionAttributes>::cast();
}

DivisionIdea::DivisionIdea()
{

}

void DivisionIdea::validate()
{
    auto n1 = m_input1.lock();
    auto n2 = m_input2.lock();
    if(n1 && n2)
    {
        if(qFuzzyCompare(n2->number(),0))
        {
            setStatus(IdeaStatus::Error, "Division by 0", "Division by 0 is not supported. In many cases where this comes up L'hopitals rule can help.");
            emit clear();
        }
        else
        {
            setStatus(IdeaStatus::Working, "Dividing", "Dividing " + QString::number(n1->number()) + " / " + QString::number(n2->number()));
            compute(n1->number(),n2->number());
            emit display(n1->number(), n2->number(), n1->number() / n2->number());
        }
    }
    else
    {
        setDefaultStatus();
        emit clear();
    }
}

void DivisionIdea::compute(double n1, double n2)
{
    emit startSpinningGear();
    m_result = std::make_shared<NumberDataType>(n1/n2);
    emit newData(0);
    emit stopSpinningGear();
}


