#include "NumbersToNumberTemplate.h"


NumbersToNumberTemplate::NumbersToNumberTemplate() :
    m_statistic(0.0),
    m_lowBound(0.0),
    m_upBound(1.0),
    m_autoFit(true),
    m_animationSpeed(1.0)

{

}


QJsonObject NumbersToNumberTemplate::save() const
{
    QJsonObject saveJson = Idea::save();

    saveJson["l"] = m_lowBound;
    saveJson["u"] = m_upBound;
    saveJson["a"] = m_autoFit;
    saveJson["s"] = m_animationSpeed;

    return saveJson;
}

void NumbersToNumberTemplate::load(const QJsonObject &obj)
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

    if(valid())
        prepareVisuals();
}

void NumbersToNumberTemplate::onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber)
{
    m_input = std::dynamic_pointer_cast<NumbersDataType>(dataType);

    validate();
}

std::shared_ptr<DataType> NumbersToNumberTemplate::dataOut(PlugNumber)
{
    return std::static_pointer_cast<DataType>(m_output);
}

void NumbersToNumberTemplate::resetDisplay()
{
    if(valid())
        prepareVisuals();
}

double NumbersToNumberTemplate::lowBound() const
{
    return m_lowBound;
}

double NumbersToNumberTemplate::upBound() const
{
    return m_upBound;
}

bool NumbersToNumberTemplate::autoFit() const
{
    return m_autoFit;
}

double NumbersToNumberTemplate::animationSpeed() const
{
    return m_animationSpeed;
}

double NumbersToNumberTemplate::statistic() const
{
    return m_statistic;
}

void NumbersToNumberTemplate::setLowBound(double lowBound)
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

void NumbersToNumberTemplate::setUpBound(double upBound)
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

void NumbersToNumberTemplate::setAutoFit(bool autoFit)
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

void NumbersToNumberTemplate::playAnimation()
{
    resetDisplay();
}

void NumbersToNumberTemplate::setStatistic(double statistic)
{
    if (qFuzzyCompare(m_statistic, statistic))
        return;

    m_statistic = statistic;
    emit statisticChanged(m_statistic);
}


void NumbersToNumberTemplate::setAnimationSpeed(double animationSpeed)
{
    if (qFuzzyCompare(m_animationSpeed, animationSpeed))
        return;

    m_animationSpeed = animationSpeed;
    emit animationSpeedChanged(m_animationSpeed);
}
