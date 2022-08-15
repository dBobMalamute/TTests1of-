#ifndef DATATYPEREGISTRY_H
#define DATATYPEREGISTRY_H

#include <unordered_map>

#include <QString>
#include <QColor>
#include "../InheritedClasses/Magic.h"

class DataTypeRegistry
{

public:
    template<typename DataTypeTemplate> void registerDataTypeAttributes()
    {
        if(Magic<DataTypeTemplate>::cast().id() != -1)
        {   //Data type registered multiple times.
            return;
        }

        Magic<DataTypeTemplate>::cast().setID(m_idCounter);
        m_idCounter++;

        QString name = Magic<DataTypeTemplate>::cast().name();
        m_dataTypeNames.push_back(name);

        QString colorString = Magic<DataTypeTemplate>::cast().color();
        m_dataTypeColors.push_back(QColor(colorString));

        QString abbreviation = Magic<DataTypeTemplate>::cast().abbreviation();
        m_dataTypeAbbreviations.push_back(abbreviation);

        QString description = Magic<DataTypeTemplate>::cast().description();
        m_dataTypeDescriptions.push_back(description);

        QString defaultDisplay = Magic<DataTypeTemplate>::cast().defaultDisplay();
        m_defaultDisplays.push_back(defaultDisplay);

        QString defaultSource = Magic<DataTypeTemplate>::cast().defaultSource();
        m_defaultSources.push_back(defaultSource);
    }

    QColor dataTypeColor(int id);
    QString dataTypeAbbreviation(int id);
    QString dataTypeDescription(int id);
    QString defaultDisplay(int id);
    QString defaultSource(int id);

private:
    std::vector<QString> m_dataTypeNames;
    std::vector<QColor> m_dataTypeColors;
    std::vector<QString> m_dataTypeAbbreviations;
    std::vector<QString> m_dataTypeDescriptions;
    std::vector<QString> m_defaultDisplays;
    std::vector<QString> m_defaultSources;

    int m_idCounter = 0;
};

#endif // DATATYPEREGISTRY_H
