#include "DistributionDisplayIdea.h"

DistributionDisplayAttributes::DistributionDisplayAttributes()
{
    m_listName = "Distribution Display";
    m_displayName = "";
    m_authors << "dBob";
    m_description = "This box displays a distribution.";
    m_iconPath = "qrc:/Icons/DistributionDisplay.png";

    m_dataTypesIn.push_back(Magic<DistributionDataTypeAttributes>::cast().id());

    m_embeddedQMLPath = ":/QML/DistributionDisplayIdea.qml";
}

const IdeaAttributes DistributionDisplayIdea::attributes()
{
    return Magic<DistributionDisplayAttributes>::cast();
}

DistributionDisplayIdea::DistributionDisplayIdea()
{

}

void DistributionDisplayIdea::onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber)
{
    auto distribution = std::dynamic_pointer_cast<DistributionDataType>(dataType);
    m_input = distribution;

    validate();
}

void DistributionDisplayIdea::validate()
{
    auto v_distribution = m_input.lock();
    if(v_distribution)
    {
        setStatus(IdeaStatus::Working, "Plotting", "This idea box is currently plotting the input distribution.");
        m_distribution = v_distribution;
        plot();
    }
    else
    {
        setDefaultStatus();
    }
}
