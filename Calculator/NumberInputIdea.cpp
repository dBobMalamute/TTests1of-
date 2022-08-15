#include "NumberInputIdea.h"

#include <QJsonValue>

NumberInputAttributes::NumberInputAttributes()
{
    m_listName = "Number Input";
    m_displayName = "";
    m_authors << "dBob";
    m_description = "This idea allows the user to enter a number. When selected, press enter to update the number"
                  " and propogate the change to other ideas.";
    m_iconPath = "qrc:/Icons/NumberInput.png";

    m_dataTypesOut.push_back(Magic<NumberDataTypeAttributes>::cast().id());
    m_labelsOut << "";
    m_customLabels = true;

    m_embeddedQMLPath = ":/QML/NumberInputIdea.qml";
}

NumberInputIdea::NumberInputIdea() :
    m_number(0.0)
{
    m_numberOutput = std::make_shared<NumberDataType>(m_number);
    setStatus(IdeaStatus::Working, "Sourcing: 0", "");
}

const IdeaAttributes NumberInputIdea::attributes()
{
    return Magic<NumberInputAttributes>::cast();
}

QJsonObject NumberInputIdea::save() const
{
    QJsonObject ideaJson;
    ideaJson["n"] = m_number;
    return ideaJson;
}

void NumberInputIdea::load(QJsonObject const &p)
{
    QJsonValue v = p["n"];

    if (!v.isUndefined())
    {
        m_number = v.toDouble();
        emit numberChanged(m_number);

        compute();
    }
}

std::shared_ptr<DataType> NumberInputIdea::dataOut(PlugNumber)
{
    return m_numberOutput;
}

double NumberInputIdea::number() const
{
    return m_number;
}

void NumberInputIdea::setNumber(double number)
{
    if(!qFuzzyCompare(m_number,number))
    {
        QJsonObject oldParams = this->save();

        m_number = number;
        emit numberChanged(m_number);

        QJsonObject newParams = this->save();
        emit reportParamsChanged(oldParams,newParams);

        compute();
    }
}

void NumberInputIdea::compute()
{
    m_numberOutput = std::make_shared<NumberDataType>(m_number);
    emit newData(0);
}
