#include "LabelStyle.h"

LabelStyle::LabelStyle()
{
    m_colorList << QColor("#d4985d") << QColor("#b14343") << QColor("#a942ea");
}

QColor LabelStyle::defaultColor()
{
    return QColor("#a6b0cb");
}

QColor LabelStyle::getColor()
{
    colorListIndex++;
    if(colorListIndex == m_colorList.length())
        colorListIndex = 0;

    return m_colorList.at(colorListIndex);
}
