#include "TTestTemplate.h"

TTestTemplate::TTestTemplate() :
    m_lowBound(0.0),
    m_upBound(1.0),
    m_autoFit(true),
    m_animationSpeed(1.0),
    m_tValue(0.0),
    m_pValue(0.0)
{

}

QJsonObject TTestTemplate::save() const
{
    QJsonObject saveJson = Idea::save();

    saveJson["l"] = m_lowBound;
    saveJson["u"] = m_upBound;
    saveJson["a"] = m_autoFit;
    saveJson["s"] = m_animationSpeed;

    return saveJson;
}

void TTestTemplate::load(const QJsonObject &obj)
{
    QJsonValue v = obj["l"];
    if(!v.isUndefined())
    {
        m_lowBound = v.toDouble();
        emit lowBoundChanged(m_lowBound);
    }

    v = obj["u"];
    if(!v.isUndefined())
    {
        m_upBound = v.toDouble();
        emit upBoundChanged(m_upBound);
    }

    v = obj["a"];
    if(!v.isUndefined())
    {
        m_autoFit = v.toBool();
        emit autoFitChanged(m_autoFit);
    }

    v = obj["s"];
    if(!v.isUndefined())
    {
        m_animationSpeed = v.toDouble();
        emit animationSpeedChanged(m_animationSpeed);
    }
}

std::shared_ptr<DataType> TTestTemplate::dataOut(PlugNumber plugNumber)
{
    if(plugNumber == 0)
        return std::static_pointer_cast<DataType>(m_pValueOutput);
    else
        return std::static_pointer_cast<DataType>(m_tValueOutput);
}

double TTestTemplate::lowBound() const
{
    return m_lowBound;
}

double TTestTemplate::upBound() const
{
    return m_upBound;
}

bool TTestTemplate::autoFit() const
{
    return m_autoFit;
}

double TTestTemplate::tValue() const
{
    return m_tValue;
}

double TTestTemplate::pValue() const
{
    return m_pValue;
}

double TTestTemplate::animationSpeed() const
{
    return m_animationSpeed;
}

void TTestTemplate::setLowBound(double lowBound)
{
    if (qFuzzyCompare(m_lowBound, lowBound))
        return;

    QJsonObject oldParams = Idea::save();
    oldParams["l"] = m_lowBound;
    oldParams["a"] = m_autoFit;

    m_lowBound = lowBound;
    emit lowBoundChanged(m_lowBound);

    m_autoFit = false;
    emit autoFitChanged(m_autoFit);

    QJsonObject newParams = Idea::save();
    newParams["l"] = m_lowBound;
    newParams["a"] = false;
    emit reportParamsChanged(oldParams, newParams);

    validate();
}

void TTestTemplate::setUpBound(double upBound)
{
    if (qFuzzyCompare(m_upBound, upBound))
        return;

    QJsonObject oldParams = Idea::save();
    oldParams["u"] = m_upBound;
    oldParams["a"] = m_autoFit;

    m_upBound = upBound;
    emit upBoundChanged(m_upBound);

    m_autoFit = false;
    emit autoFitChanged(m_autoFit);

    QJsonObject newParams = Idea::save();
    newParams["u"] = m_upBound;
    newParams["a"] = false;
    emit reportParamsChanged(oldParams, newParams);

    validate();
}

void TTestTemplate::setAutoFit(bool autoFit)
{
    if (m_autoFit == autoFit)
        return;

    QJsonObject oldParams = save();

    m_autoFit = autoFit;
    emit autoFitChanged(m_autoFit);
    if(m_autoFit == true)
    {
        //Make validate work
        m_lowBound = 0.0;
        m_upBound = 1.0;
        validate();
    }
    QJsonObject newParams = Idea::save();
    newParams["a"] = m_autoFit;
    emit reportParamsChanged(oldParams, newParams);
}

void TTestTemplate::setTValue(double tValue)
{
    if (qFuzzyCompare(m_tValue, tValue))
        return;

    m_tValue = tValue;
    emit tValueChanged(m_tValue);
}

void TTestTemplate::setPValue(double pValue)
{
    if (qFuzzyCompare(m_pValue, pValue))
        return;

    m_pValue = pValue;
    emit pValueChanged(m_pValue);
}

void TTestTemplate::setAnimationSpeed(double animationSpeed)
{
    if (qFuzzyCompare(m_animationSpeed, animationSpeed))
        return;

    m_animationSpeed = animationSpeed;
    emit animationSpeedChanged(m_animationSpeed);
}

void TTestTemplate::resetDisplay()
{
    validate();
}
