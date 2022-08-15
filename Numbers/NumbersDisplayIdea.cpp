#include "NumbersDisplayIdea.h"

NumbersDisplayAttributes::NumbersDisplayAttributes()
{
    m_listName = "Numbers Display";
    m_displayName = "";
    m_authors << "dBob";
    m_description = "This box displays a list of numbers.";
    m_iconPath = "qrc:/Icons/NumbersDisplay.png";

    m_dataTypesIn.push_back(Magic<NumbersDataTypeAttributes>::cast().id());
    m_labelsIn << "";
    m_customLabels = true;

    m_embeddedQMLPath = ":/QML/NumbersDisplayIdea.qml";
}

const IdeaAttributes NumbersDisplayIdea::attributes()
{
    return Magic<NumbersDisplayAttributes>::cast();
}

NumbersDisplayIdea::NumbersDisplayIdea()
{

}

void NumbersDisplayIdea::onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber)
{
    m_input = std::dynamic_pointer_cast<NumbersDataType>(dataType);

    validate();
}

QList<QVariant> NumbersDisplayIdea::numbersVariant() const
{
    return m_numbersVariant;
}

void NumbersDisplayIdea::validate()
{
    auto n = m_input.lock();
    if(n)
    {
        m_nums = n->numbers();
        if(m_nums.size() == 0)
        {
            setDefaultStatus();
        }
        else
        {
            setStatus(IdeaStatus::Working, "Displaying Numbers","Displaying Numbers");
            setupDisplay();
        }
    }
}

void NumbersDisplayIdea::setupDisplay()
{
    //Prepare variant list for qml. Let QML know.
    QList<QVariant> numbersVariant;
    numbersVariant.reserve(m_nums.size());
    for(size_t i = 0; i < m_nums.size(); i++)
        numbersVariant.push_back(QVariant(m_nums.at(i)));
    m_numbersVariant = numbersVariant;
    emit numbersVariantChanged(m_numbersVariant);
}



