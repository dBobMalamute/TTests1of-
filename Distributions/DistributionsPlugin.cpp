#include "DistributionsPlugin.h"

#include "GaussianDistributionIdea.h"
#include "DistributionDisplayIdea.h"
#include "DistributionSamplerIdea.h"
#include "StudentTDistributionIdea.h"
#include "DagumDistributionIdea.h"

#include "../DataTypes/NumberDataType.h"
#include "../DataTypes/DistributionDataType.h"

#include <QQmlEngine>

QString DistributionsPlugin::PluginName()
{
    return "Distribution";
}

QStringList DistributionsPlugin::authors()
{
    return QStringList("dBob");
}

QString DistributionsPlugin::PluginDescription()
{
    return "This plugin holds mathematical distributions";
}

void DistributionsPlugin::registerIdeas(std::shared_ptr<IdeaRegistry> ideaRegistry)
{
    ideaRegistry->registerIdea<GaussianDistributionIdea>();
    ideaRegistry->registerIdea<DistributionDisplayIdea>();
    ideaRegistry->registerIdea<DistributionSamplerIdea>();
    ideaRegistry->registerIdea<StudentTDistributionIdea>();
    ideaRegistry->registerIdea<DagumDistributionIdea>();

    qmlRegisterType(QUrl("qrc:/QML/QMLTemplates/DistributionDisplay.qml"),
                    "com.malamute.distributions", 1, 0, "DistributionDisplay");
    qmlRegisterType(QUrl("qrc:/QML/QMLTemplates/SamplerTemplate.qml"),
                    "com.malamute.distributions", 1, 0, "SamplerTemplate");
    qmlRegisterType(QUrl("qrc:/QML/QMLTemplates/UpDownButton.qml"),
                    "com.malamute.distributions", 1, 0, "UpDownButton");
}

void DistributionsPlugin::registerDataTypeAttributes(std::shared_ptr<DataTypeRegistry> dataTypeRegistry)
{
    dataTypeRegistry->registerDataTypeAttributes<NumberDataTypeAttributes>();
    dataTypeRegistry->registerDataTypeAttributes<DistributionDataTypeAttributes>();
    dataTypeRegistry->registerDataTypeAttributes<NumbersDataTypeAttributes>();
}

void DistributionsPlugin::registerToolbars(std::shared_ptr<ToolbarRegistry> toolbarRegistry)
{
    QStringList distributionList;
    distributionList << Magic<DistributionDisplayAttributes>::cast().listName();
    distributionList << Magic<GaussianDistributionAttributes>::cast().listName();
    distributionList << Magic<StudentTDistributionAttributes>::cast().listName();
    distributionList << Magic<DagumDistributionAttributes>::cast().listName();
    toolbarRegistry->registerToolbar("Distributions", distributionList);

    QStringList distributionUtilitiesList;
    distributionUtilitiesList << Magic<DistributionSamplerAttributes>::cast().listName();

    toolbarRegistry->registerToolbar("Distribution Utilities", distributionUtilitiesList);
}
