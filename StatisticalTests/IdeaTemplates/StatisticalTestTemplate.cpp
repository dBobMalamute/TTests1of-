#include "StatisticalTestTemplate.h"

StatisticalTestTemplate::StatisticalTestTemplate() :
    m_xLowData(-1.0),
    m_xHighData(1.0),
    m_autoFitData(true),
    m_xLowDist(-1.0),
    m_xHighDist(1.0),
    m_autoFitDist(true),
    m_animationSpeed(1.0),
    m_alpha(0.05)
{

}

QJsonObject StatisticalTestTemplate::save() const
{
    QJsonObject saveJson = Idea::save();
    saveJson["xld"] = m_xLowData;
    saveJson["xhd"] = m_xHighData;
    saveJson["ad"] = m_autoFitData;
    saveJson["xls"] = m_xLowDist;
    saveJson["xhs"] = m_xHighDist;
    saveJson["as"] = m_autoFitDist;
    saveJson["s"] = m_animationSpeed;
    saveJson["al"] = m_alpha;

    return saveJson;
}

void StatisticalTestTemplate::load(const QJsonObject &obj)
{
    bool redrawTestStatisticVisuals = false;
    bool redrawPValueVisuals = false;

    QJsonValue v = obj["xld"];
    if(!v.isUndefined())
    {
        m_xLowData = v.toDouble();
        emit xLowDataChanged(m_xLowData);
        redrawTestStatisticVisuals = true;
    }
    v = obj["xhd"];
    if(!v.isUndefined())
    {
        m_xHighData = v.toDouble();
        emit xHighDataChanged(m_xHighData);
        redrawTestStatisticVisuals = true;
    }
    v = obj["ad"];
    if(!v.isUndefined())
    {
        m_autoFitData = v.toBool();
        emit autoFitDataChanged(m_autoFitData);
        redrawTestStatisticVisuals = true;
    }

    v = obj["xls"];
    if(!v.isUndefined())
    {
        m_xLowDist = v.toDouble();
        emit xLowDistChanged(m_xLowDist);
        redrawPValueVisuals = true;
    }
    v = obj["xhs"];
    if(!v.isUndefined())
    {
        m_xHighDist = v.toDouble();
        emit xHighDistChanged(m_xHighDist);
        redrawPValueVisuals = true;
    }
    v = obj["as"];
    if(!v.isUndefined())
    {
        m_autoFitDist = v.toBool();
        emit autoFitDistChanged(m_autoFitDist);
        redrawPValueVisuals = true;
    }
    v = obj["s"];
    if(!v.isUndefined())
    {
        m_animationSpeed = v.toDouble();
        emit animationSpeedChanged(m_animationSpeed);
    }

    v = obj["al"];
    if(!v.isUndefined())
    {
        m_alpha = v.toDouble();
        emit alphaChanged(m_alpha);
        redrawPValueVisuals = true;
    }

    if(valid())
    {
        if(redrawTestStatisticVisuals)
            prepareTestStatisticVisuals();
        if(redrawPValueVisuals)
            preparePValueVisuals();
    }
}

std::shared_ptr<DataType> StatisticalTestTemplate::dataOut(PlugNumber plugNumber)
{
    if(plugNumber == 0)
        return std::static_pointer_cast<DataType>(m_statisticalTestValueOutput);
    else
        return std::static_pointer_cast<DataType>(m_pValueOutput);
}

double StatisticalTestTemplate::pValue() const
{
    return m_pValue;
}

double StatisticalTestTemplate::xValueForAlpha() const
{
    return m_xValueForAlpha;
}

double StatisticalTestTemplate::alpha() const
{
    return m_alpha;
}

double StatisticalTestTemplate::xLowData() const
{
    return m_xLowData;
}

double StatisticalTestTemplate::xHighData() const
{
    return m_xHighData;
}

bool StatisticalTestTemplate::autoFitData() const
{
    return m_autoFitData;
}

double StatisticalTestTemplate::xLowDist() const
{
    return m_xLowDist;
}

double StatisticalTestTemplate::xHighDist() const
{
    return m_xHighDist;
}

bool StatisticalTestTemplate::autoFitDist() const
{
    return m_autoFitDist;
}

double StatisticalTestTemplate::statisticalTestValue() const
{
    return m_statisticalTestValue;
}

double StatisticalTestTemplate::animationSpeed() const
{
    return m_animationSpeed;
}

void StatisticalTestTemplate::setPValue(double pValue)
{
    if (qFuzzyCompare(m_pValue, pValue))
        return;

    m_pValue = pValue;
    emit pValueChanged(m_pValue);
}

void StatisticalTestTemplate::setXValueForAlpha(double xValueForAlpha)
{
    if (qFuzzyCompare(m_xValueForAlpha, xValueForAlpha))
        return;

    m_xValueForAlpha = xValueForAlpha;
    emit xValueForAlphaChanged(m_xValueForAlpha);
}

void StatisticalTestTemplate::compute()
{
    emit startSpinningGear();
    computeTestStatistic();
    if(!minimized())
    {
        prepareTestStatisticVisuals();
    }

    makeDistribution();
    computePValue();

    if(!minimized())
    {
        preparePValueVisuals();
    }

    emit stopSpinningGear();
}

void StatisticalTestTemplate::setAlpha(double alpha)
{
    if (qFuzzyCompare(m_alpha, alpha))
        return;

    if(qFuzzyCompare(alpha, 1.0) || qFuzzyIsNull(alpha))
    {
        emit alphaChanged(m_alpha); // Dot not let alpha be 0 or 1. Validator doesn't check for that.
        return;
    }

    QJsonObject oldParams;
    oldParams["al"] = m_alpha;

    m_alpha = alpha;
    emit alphaChanged(m_alpha);

    QJsonObject newParams;
    newParams["al"] = m_alpha;
    reportParamsChanged(oldParams, newParams);

    preparePValueVisuals();
}

void StatisticalTestTemplate::setXLowData(double xLowData)
{
    if (qFuzzyCompare(m_xLowData, xLowData))
        return;
    if(xLowData > m_xHighData)
    {
        emit xLowDataChanged(m_xLowData);
        return;
    }

    QJsonObject oldParams;
    QJsonObject newParams;

    if(m_autoFitData)
    {
        oldParams["ad"] = true;
        m_autoFitData = false;
        newParams["ad"] = false;
        emit autoFitDataChanged(m_autoFitData);
    }

    oldParams["xld"] = m_xLowData;

    m_xLowData = xLowData;
    emit xLowDataChanged(m_xLowData);

    newParams["xld"] = m_xLowData;
    reportParamsChanged(oldParams, newParams);

    prepareTestStatisticVisuals();
}

void StatisticalTestTemplate::setXHighData(double xHighData)
{
    if (qFuzzyCompare(m_xHighData, xHighData))
        return;
    if(xHighData < m_xLowData)
    {
        emit xHighDataChanged(m_xHighData);
        return;
    }

    QJsonObject oldParams;
    QJsonObject newParams;

    if(m_autoFitData)
    {
        oldParams["ad"] = true;
        m_autoFitData = false;
        newParams["ad"] = false;
        emit autoFitDataChanged(m_autoFitData);
    }

    oldParams["xhd"] = m_xHighData;

    m_xHighData = xHighData;
    emit xHighDataChanged(m_xHighData);

    newParams["xhd"] = m_xHighData;
    reportParamsChanged(oldParams, newParams);

    prepareTestStatisticVisuals();
}

void StatisticalTestTemplate::setAutoFitData(bool autoFitData)
{
    if (m_autoFitData == autoFitData)
        return;

    QJsonObject oldParams;
    QJsonObject newParams;
    if(!m_autoFitData)
    {
        oldParams["xld"] = m_xLowData;
        oldParams["xhd"] = m_xHighData;
    }
    oldParams["ad"] = m_autoFitData;

    m_autoFitData = autoFitData;
    emit autoFitDataChanged(m_autoFitData);

    newParams["ad"] = m_autoFitData;
    reportParamsChanged(oldParams, newParams);

    if(autoFitData) //Turning off autofitting does not require updating visuals
        prepareTestStatisticVisuals();
}

void StatisticalTestTemplate::setXLowDist(double xLowDist)
{
    if (qFuzzyCompare(m_xLowDist, xLowDist))
        return;

    if(xLowDist > m_xHighDist)
    {
        emit xLowDistChanged(m_xLowDist);
        return;
    }

    QJsonObject oldParams;
    QJsonObject newParams;

    if(m_autoFitDist)
    {
        oldParams["as"] = m_autoFitDist;
        m_autoFitDist = false;
        newParams["as"] = m_autoFitDist;
        emit autoFitDistChanged(m_autoFitDist);
    }

    oldParams["xls"] = m_xLowDist;
    m_xLowDist = xLowDist;
    emit xLowDistChanged(m_xLowDist);

    newParams["xls"] = m_xLowDist;
    reportParamsChanged(oldParams, newParams);

    preparePValueVisuals();
}

void StatisticalTestTemplate::setXHighDist(double xHighDist)
{
    if (qFuzzyCompare(m_xHighDist, xHighDist))
        return;

    if(xHighDist < m_xLowDist)
    {
        emit xHighDistChanged(m_xHighDist);
        return;
    }

    QJsonObject oldParams;
    QJsonObject newParams;

    if(m_autoFitDist)
    {
        oldParams["as"] = m_autoFitDist;
        m_autoFitDist = false;
        newParams["as"] = m_autoFitDist;
        emit autoFitDistChanged(m_autoFitDist);
    }

    oldParams["xhs"] = m_xHighDist;

    m_xHighDist = xHighDist;
    emit xHighDistChanged(m_xHighDist);

    newParams["xhs"] = m_xHighDist;
    reportParamsChanged(oldParams, newParams);

    preparePValueVisuals();
}

void StatisticalTestTemplate::setAutoFitDist(bool autoFitDist)
{
    if (m_autoFitDist == autoFitDist)
        return;

    QJsonObject oldParams;
    QJsonObject newParams;
    if(!m_autoFitData)
    {
        oldParams["xls"] = m_xLowDist;
        oldParams["xhs"] = m_xHighDist;
    }
    oldParams["as"] = m_autoFitDist;

    m_autoFitDist = autoFitDist;
    emit autoFitDistChanged(m_autoFitDist);

    newParams["as"] = m_autoFitDist;
    reportParamsChanged(oldParams, newParams);

    if(autoFitDist) // Turning off autofitting doesn't require redrawing visuals.
        preparePValueVisuals();
}

void StatisticalTestTemplate::setStatisticalTestValue(double statisticalTestValue)
{
    if (qFuzzyCompare(m_statisticalTestValue, statisticalTestValue))
        return;

    m_statisticalTestValue = statisticalTestValue;
    emit statisticalTestValueChanged(m_statisticalTestValue);
}

void StatisticalTestTemplate::setAnimationSpeed(double animationSpeed)
{
    if (qFuzzyCompare(m_animationSpeed, animationSpeed))
        return;

    m_animationSpeed = animationSpeed;
    emit animationSpeedChanged(m_animationSpeed);
}

void StatisticalTestTemplate::resetDisplay()
{
    if(valid())
    {
        prepareTestStatisticVisuals();
        preparePValueVisuals();
    }
}
