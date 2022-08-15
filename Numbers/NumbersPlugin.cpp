#include "NumbersPlugin.h"

#include "NumbersInputIdea.h"
#include "NumbersDisplayIdea.h"
#include "NumbersMeanIdea.h"
#include "NumbersVarianceIdea.h"
#include "../DataTypes/NumbersDataType.h"
#include "../DataTypes/NumberDataType.h"

QString NumbersPlugin::PluginName()
{
    return "Numbers";
}

QStringList NumbersPlugin::authors()
{
    return QStringList("dBob");
}

QString NumbersPlugin::PluginDescription()
{
    return "This plugin holds the ideas usually used when analyzing numbers";
}

void NumbersPlugin::registerIdeas(std::shared_ptr<IdeaRegistry> ideaRegistry)
{
    ideaRegistry->registerIdea<NumbersInputIdea>();
    ideaRegistry->registerIdea<NumbersDisplayIdea>();
    ideaRegistry->registerIdea<NumbersMeanIdea>();
    ideaRegistry->registerIdea<NumbersVarianceIdea>();

    qmlRegisterType(QUrl("qrc:/QML/QMLTemplates/StatisticTemplate.qml"), "com.malamute.numbers", 1, 0, "StatisticTemplate");
}

void NumbersPlugin::registerDataTypeAttributes(std::shared_ptr<DataTypeRegistry> dataTypeRegistry)
{
    dataTypeRegistry->registerDataTypeAttributes<NumberDataTypeAttributes>();
    dataTypeRegistry->registerDataTypeAttributes<NumbersDataTypeAttributes>();
}

void NumbersPlugin::registerToolbars(std::shared_ptr<ToolbarRegistry> toolbarRegistry)
{
    QStringList orderList;
    orderList << Magic<NumbersInputAttributes>::cast().listName();
    orderList << Magic<NumbersDisplayAttributes>::cast().listName();
    orderList << Magic<NumbersMeanAttributes>::cast().listName();
    orderList << Magic<NumbersVarianceAttributes>::cast().listName();

    toolbarRegistry->registerToolbar("List of Numbers", orderList);
}
