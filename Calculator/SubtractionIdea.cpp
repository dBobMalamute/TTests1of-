#include "SubtractionIdea.h"

SubtractionAttributes::SubtractionAttributes()
{
    m_listName = "Subtraction";
    m_displayName = "Subtraction";
    m_authors << "dBob";
    m_description = "This idea represents subtraction of one decimal type number from another.";
    m_iconPath = "qrc:/Icons/Subtraction.png";

    m_dataTypesIn.push_back(Magic<NumberDataTypeAttributes>::cast().id());
    m_dataTypesIn.push_back(Magic<NumberDataTypeAttributes>::cast().id());
    m_dataTypesOut.push_back(Magic<NumberDataTypeAttributes>::cast().id());

    m_gear = true;

    m_embeddedQMLPath = ":/QML/SubtractionIdea.qml";
}

SubtractionIdea::SubtractionIdea()
{

}

const IdeaAttributes SubtractionIdea::attributes()
{
    return Magic<SubtractionAttributes>::cast();
}


void SubtractionIdea::validate()
{
    auto n1 = m_input1.lock();
    auto n2 = m_input2.lock();
    if(n1 && n2)
    {
        setStatus(IdeaStatus::Working, "Subtracting", "Subtracting " + QString::number(n1->number()) + " - " + QString::number(n2->number()));
        compute(n1->number(),n2->number());
        emit display(n1->number(), n2->number(), n1->number() - n2->number());
    }
    else
    {
        setDefaultStatus();
        emit clear();
    }
}

void SubtractionIdea::compute(double n1, double n2)
{
    emit startSpinningGear();
    m_result = std::make_shared<NumberDataType>(n1-n2);
    emit newData(0);
    emit stopSpinningGear();
}


