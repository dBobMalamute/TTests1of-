#ifndef LABELSTYLE_H
#define LABELSTYLE_H

#include <QColor>
#include <QDebug>

class LabelStyle
{
public:
    LabelStyle();

    static QColor defaultColor();
    QColor getColor();

private:
    QList<QColor> m_colorList;
    int colorListIndex = 0;
};

#endif // LABELSTYLE_H
