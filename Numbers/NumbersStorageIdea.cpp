#include "NumbersStorageIdea.h"
#include <QJsonArray>

NumbersStorageAttributes::NumbersStorageAttributes()
{
    m_listName = "Numbers Storage";
    m_displayName = "";
    m_authors << "dBob";
    m_description = "This box stores and displays a list of numbers.";
    m_iconPath = "qrc:/Icons/NumbersStorage.png";

    m_dataTypesIn.push_back(Magic<NumbersDataTypeAttributes>::cast().id());
    m_labelsIn << "";
    m_dataTypesOut.push_back(Magic<NumbersDataTypeAttributes>::cast().id());
    m_labelsOut << "";
    m_customLabels = true;

    m_embeddedQMLPath = ":/QML/NumbersStorageIdea.qml";
}

const IdeaAttributes NumbersStorageIdea::attributes()
{
    return Magic<NumbersStorageAttributes>::cast();
}

NumbersStorageIdea::NumbersStorageIdea()
{
    setStatus(IdeaStatus::StandBy, "Awaiting Data","Not currently storing any numbers");
}

QJsonObject NumbersStorageIdea::save() const
{
    QJsonObject saveJson;
    QJsonArray numsArray;
    for(size_t i = 0; i < m_nums.size(); i++)
        numsArray.append(m_nums.at(i));

    saveJson["ns"] = numsArray;

    return saveJson;
}

void NumbersStorageIdea::load(const QJsonObject &obj)
{
    QJsonValue v = obj["ns"];
    if(!v.isUndefined())
    {
        m_nums.clear();
        QJsonArray numsArray = v.toArray();
        if(numsArray.size() >= 1)
        {
            for(int i = 0; i < numsArray.size(); i++)
                m_nums.push_back(numsArray.at(i).toDouble());

            //Set up the new output;
            setStatus(IdeaStatus::Working, "Storing Numbers","Storing Numbers");
            m_output = std::make_shared<NumbersDataType>(m_nums);
            emit newData(0);

            setupDisplay();
        }

    }
}

void NumbersStorageIdea::onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber)
{
    m_input = std::dynamic_pointer_cast<NumbersDataType>(dataType);

    validate();
}

std::shared_ptr<DataType> NumbersStorageIdea::dataOut(PlugNumber)
{
    return std::static_pointer_cast<DataType>(m_output);
}

QList<QVariant> NumbersStorageIdea::numbersVariant() const
{
    return m_numbersVariant;
}

void NumbersStorageIdea::clear()
{
    setStatus(IdeaStatus::StandBy, "Awaiting Data","Not currently storing any numbers");
    m_nums.clear();
    m_numbersVariant.clear();
    emit numbersVariantChanged(m_numbersVariant);
}

void NumbersStorageIdea::validate()
{
    auto n = m_input.lock();
    if(n)
    {
        m_nums = n->numbers();
        if(m_nums.size() == 0)
        {
            //I don't want to propogate an empty list of numbers. Might happen, but I hope it doesn't.
            //This might be unnecessary
            setStatus(IdeaStatus::StandBy, "Awaiting Data","Not currently storing any numbers");
        }
        else
        {
            setStatus(IdeaStatus::Working, "Storing Numbers","Storing Numbers");
            m_output = std::make_shared<NumbersDataType>(m_nums);
            emit newData(0);

            setupDisplay();
        }
    }
}

void NumbersStorageIdea::setupDisplay()
{
    //Prepare variant list for qml. Let QML know.
    QList<QVariant> numbersVariant;
    numbersVariant.reserve(m_nums.size());
    for(size_t i = 0; i < m_nums.size(); i++)
        numbersVariant.push_back(QVariant(m_nums.at(i)));
    m_numbersVariant = numbersVariant;
    emit numbersVariantChanged(m_numbersVariant);
}
