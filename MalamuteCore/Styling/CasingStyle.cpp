#include "CasingStyle.h"

CasingStyle::CasingStyle(QObject *parent) : QObject(parent)
{
    m_gradientTopColors = {QColor("#338347"), QColor("#6b8333"), QColor("#33836c"),
                           QColor("#337b83"), QColor("#5b3383"), QColor("#836a33"),
                           QColor("#a11212"), QColor("#eae9cc"), QColor("#1c132b")};

    m_gradientBottomColors = {QColor("#71A67B"), QColor("#96a671"), QColor("#71a696"),
                              QColor("#71a0a6"), QColor("#8b71a6"), QColor("#a69571"),
                              QColor("#e63c10"), QColor("#d7d7cf"), QColor("#0a080d")};

    m_nameFont = QFont("inconsolata", 14,QFont::ExtraBold);
    m_portLabelsFont = QFont("inconsolata", 11, QFont::Bold);
    m_validationTextFont = QFont("inconsolata", 14,QFont::Bold);
}

double CasingStyle::bordersWidth() const
{
    return m_bordersWidth;
}

QColor CasingStyle::borderColor() const
{
    return m_borderColor;
}

QColor CasingStyle::borderSelectedColor() const
{
    return m_borderSelectedColor;
}

QColor CasingStyle::gradientTopColor(int i)
{
    return m_gradientTopColors.at(i);
}

QColor CasingStyle::gradientBottomColor(int i)
{
    return m_gradientBottomColors.at(i);
}

int CasingStyle::glowRadius() const
{
    return m_glowRadius;
}

double CasingStyle::glowSpread() const
{
    return m_glowSpread;
}

QColor CasingStyle::glowColor() const
{
    return m_glowColor;
}

double CasingStyle::portSize() const
{
    return m_portSize;
}

double CasingStyle::portSpacing() const
{
    return m_portSpacing;
}

double CasingStyle::portBorderWidth() const
{
    return m_portBorderWidth;
}

QColor CasingStyle::nameColor() const
{
    return m_nameColor;
}

QFont CasingStyle::nameFont() const
{
    return m_nameFont;
}

QFont CasingStyle::portLabelsFont() const
{
    return m_portLabelsFont;
}

QFont CasingStyle::validationTextFont() const
{
    return m_validationTextFont;
}

QColor CasingStyle::validationTextColor() const
{
    return m_validationTextColor;
}

double CasingStyle::buttonSize() const
{
    return m_buttonSize;
}

QColor CasingStyle::buttonColor() const
{
    return m_buttonColor;
}

double CasingStyle::buttonHoverDarkenFactor() const
{
    return m_buttonHoverDarkenFactor;
}

QColor CasingStyle::resizerColor() const
{
    return m_resizerColor;
}

QColor CasingStyle::resizerBorderColor() const
{
    return m_resizerBorderColor;
}

double CasingStyle::frameRadius() const
{
    return m_frameRadius;
}

double CasingStyle::resizerSize() const
{
    return m_resizerSize;
}
