#include "AdditionIdea.h"

AdditionAttributes::AdditionAttributes()
{
    m_listName = "Addition";
    m_displayName = "Addition";
    m_authors << "dBob";
    m_description = "Addition of two decimal-type numbers";
    m_iconPath = "qrc:/Icons/Addition.png";

    m_dataTypesIn.push_back(Magic<NumberDataTypeAttributes>::cast().id());
    m_dataTypesIn.push_back(Magic<NumberDataTypeAttributes>::cast().id());
    m_dataTypesOut.push_back(Magic<NumberDataTypeAttributes>::cast().id());

    m_gear = true;

    m_embeddedQMLPath = ":/QML/AdditionIdea.qml";
    m_minimizedQMLPath = ":/QML/AdditionMinimized.qml";
    m_minimizable = true;
}

AdditionIdea::AdditionIdea()
{

}

const IdeaAttributes AdditionIdea::attributes()
{
    return Magic<AdditionAttributes>::cast();
}


void AdditionIdea::validate()
{
    auto n1 = m_input1.lock();
    auto n2 = m_input2.lock();

    if(n1 && n2)
    {
        setStatus(IdeaStatus::Working, "Adding", "Adding " + QString::number(n1->number()) + " + " + QString::number(n2->number()));
        compute(n1->number(),n2->number());
    }
    else
    {
        setDefaultStatus();
        emit clear();
    }
}

void AdditionIdea::compute(double n1, double n2)
{
    emit startSpinningGear();

    m_result = std::make_shared<NumberDataType>(n1 + n2);
    emit newData(0);

    emit display(n1, n2, n1 + n2);

    emit stopSpinningGear();
}

void AdditionIdea::resetDisplay()
{
    if(valid())
    {
        double n1 = m_input1.lock()->number();
        double n2 = m_input2.lock()->number();
        emit display(n1, n2, n1+n2);
    }
}
