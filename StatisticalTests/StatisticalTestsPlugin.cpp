#include "StatisticalTestsPlugin.h"

#include "OneSampleOneSidedTTestIdea.h"

#include "../DataTypes/NumbersDataType.h"
#include "../DataTypes/NumberDataType.h"

QString StatisticalTestsPlugin::PluginName()
{
    return "Statistical Tests";
}

QStringList StatisticalTestsPlugin::authors()
{
    return QStringList("dBob");
}

QString StatisticalTestsPlugin::PluginDescription()
{
    return "This plugin holds statistical tests";
}

void StatisticalTestsPlugin::registerIdeas(std::shared_ptr<IdeaRegistry> ideaRegistry)
{
    ideaRegistry->registerIdea<OneSampleOneSidedTTestIdea>();

    qmlRegisterType(QUrl("qrc:/QML/QMLTemplates/StatisticalTestTemplate.qml"), "com.malamute.statisticaltests",
                    1, 0, "StatisticalTestTemplate");
    qmlRegisterType(QUrl("qrc:/QML/QMLTemplates/BridgeRailings.qml"), "com.malamute.statisticaltests",
                    1, 0, "BridgeRailings");
    qmlRegisterType(QUrl("qrc:/QML/QMLTemplates/StatisticalTestMinimized.qml"), "com.malamute.statisticaltests",
                    1, 0, "StatisticalTestMinimized");
}

void StatisticalTestsPlugin::registerDataTypeAttributes(std::shared_ptr<DataTypeRegistry> dataTypeRegistry)
{
    dataTypeRegistry->registerDataTypeAttributes<NumberDataTypeAttributes>();
    dataTypeRegistry->registerDataTypeAttributes<NumbersDataTypeAttributes>();
}

void StatisticalTestsPlugin::registerToolbars(std::shared_ptr<ToolbarRegistry> toolbarRegistry)
{
    QStringList orderList;
    orderList << Magic<OneSampleOneSidedTTestAttributes>::cast().listName();

    toolbarRegistry->registerToolbar("Statistical Tests", orderList);
}
