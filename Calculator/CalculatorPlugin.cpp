#include <QQmlEngine>

#include "CalculatorPlugin.h"

#include "AdditionIdea.h"
#include "SubtractionIdea.h"
#include "MultiplicationIdea.h"
#include "DivisionIdea.h"
#include "NumberDisplayIdea.h"
#include "NumberInputIdea.h"
#include "LabeledNumberInputIdea.h"
#include "LabeledNumberDisplayIdea.h"

QString CalculatorPlugin::PluginName()
{
    return "Calculator";
}

QString CalculatorPlugin::PluginDescription()
{
    return "This library is designed to look like a calculator";
}

QStringList CalculatorPlugin::authors()
{
    return QStringList("dBob");
}

void CalculatorPlugin::registerIdeas(std::shared_ptr<IdeaRegistry> ideaRegistry)
{

    ideaRegistry->registerIdea<LabeledNumberDisplayIdea>();
    ideaRegistry->registerIdea<LabeledNumberInputIdea>();
    ideaRegistry->registerIdea<DivisionIdea>();
    ideaRegistry->registerIdea<MultiplicationIdea>();
    ideaRegistry->registerIdea<SubtractionIdea>();
    ideaRegistry->registerIdea<AdditionIdea>();
    ideaRegistry->registerIdea<NumberDisplayIdea>();
    ideaRegistry->registerIdea<NumberInputIdea>();

    qmlRegisterType(QUrl("qrc:/QML/QMLTemplates/TwoToOneTemplate.qml"), "com.malamute.calculator", 1, 0, "TwoToOneTemplate");
    qmlRegisterType(QUrl("qrc:/QML/QMLTemplates/OneToOneTemplate.qml"), "com.malamute.calculator", 1, 0, "OneToOneTemplate");
}

void CalculatorPlugin::registerDataTypeAttributes(std::shared_ptr<DataTypeRegistry> dataTypeRegistry)
{
    dataTypeRegistry->registerDataTypeAttributes<NumberDataTypeAttributes>();
}

void CalculatorPlugin::registerToolbars(std::shared_ptr<ToolbarRegistry> toolbarRegistry)
{
    QStringList orderList;
    orderList << Magic<NumberInputAttributes>::cast().listName();
    orderList << Magic<LabeledNumberInputAttributes>::cast().listName();
    orderList << Magic<NumberDisplayAttributes>::cast().listName();
    orderList << Magic<LabeledNumberDisplayAttributes>::cast().listName();
    orderList << Magic<AdditionAttributes>::cast().listName();
    orderList << Magic<SubtractionAttributes>::cast().listName();
    orderList << Magic<MultiplicationAttributes>::cast().listName();
    orderList << Magic<DivisionAttributes>::cast().listName();

    toolbarRegistry->registerToolbar(PluginName(),orderList);
}
