#include "DistributionTemplate.h"
#include <QJsonArray>

DistributionTemplate::DistributionTemplate() :
    m_xLow(-1.0),
    m_xHigh(1.0),
    m_yLow(0.0),
    m_yHigh(1.0),
    m_autoFit(true)
{

}

void DistributionTemplate::setAutoFit(bool autoFit)
{
    if (m_autoFit == autoFit)
        return;

    QJsonObject oldParams = save();

    m_autoFit = autoFit;
    emit autoFitChanged(m_autoFit);

    QJsonObject newParams;
    newParams["a"] = m_autoFit;
    reportParamsChanged(oldParams, newParams);

    if(valid())
    {
        plot();
        boundsChanged();
    }
}

QJsonObject DistributionTemplate::save() const
{
    QJsonObject saveJson;
    saveJson["xl"] = xLow();
    saveJson["xh"] = xHigh();
    saveJson["yl"] = yLow();
    saveJson["yh"] = yHigh();
    saveJson["a"] = autoFit();

    return saveJson;
}

void DistributionTemplate::load(const QJsonObject &obj)
{
    bool replotNeeded = false;

    QJsonValue v = obj["xl"];
    if(!v.isUndefined())
    {
        replotNeeded = true;
        m_xLow = v.toDouble();
        emit xLowChanged(m_xLow);
    }

    v = obj["xh"];
    if(!v.isUndefined())
    {
        replotNeeded = true;
        m_xHigh = v.toDouble();
        emit xHighChanged(m_xHigh);
    }

    v = obj["yl"];
    if(!v.isUndefined())
    {
        replotNeeded = true;
        m_yLow = v.toDouble();
        emit yLowChanged(m_yLow);
    }

    v = obj["yh"];
    if(!v.isUndefined())
    {
        replotNeeded = true;
        m_yHigh = v.toDouble();
        emit yHighChanged(m_yHigh);
    }

    v = obj["a"];
    if(!v.isUndefined())
    {
        replotNeeded = true;
        m_autoFit = v.toBool();
        emit autoFitChanged(m_autoFit);
    }

    if(replotNeeded && valid() && !minimized())
    {
        plot();
        boundsChanged();
    }
}

double DistributionTemplate::xLow() const
{
    return m_xLow;
}

double DistributionTemplate::xHigh() const
{
    return m_xHigh;
}

double DistributionTemplate::yLow() const
{
    return m_yLow;
}

double DistributionTemplate::yHigh() const
{
    return m_yHigh;
}

bool DistributionTemplate::autoFit() const
{
    return m_autoFit;
}


void DistributionTemplate::setXLow(double xLow)
{
    if (qFuzzyCompare(m_xLow, xLow))
        return;

    if(xLow > m_xHigh)
        return;

    QJsonObject oldParams;
    oldParams["xl"] = m_xLow;
    oldParams["a"] = m_autoFit;

    m_xLow = xLow;
    emit xLowChanged(m_xLow);
    m_autoFit = false;
    emit autoFitChanged(m_autoFit);

    QJsonObject newParams;
    newParams["xl"] = m_xLow;
    newParams["a"] = m_autoFit;
    reportParamsChanged(oldParams, newParams);
    if(valid())
    {
        plot();
        boundsChanged();
    }
}

void DistributionTemplate::setXHigh(double xHigh)
{
    if (qFuzzyCompare(m_xHigh, xHigh))
        return;

    if(xHigh < m_xLow)
        return;

    QJsonObject oldParams;
    oldParams["xh"] = m_xHigh;
    oldParams["a"] = m_autoFit;

    m_xHigh = xHigh;
    emit xHighChanged(m_xHigh);
    m_autoFit = false;
    emit autoFitChanged(m_autoFit);

    QJsonObject newParams;
    newParams["xh"] = m_xHigh;
    newParams["a"] = m_autoFit;
    reportParamsChanged(oldParams, newParams);
    if(valid())
    {
        plot();
        boundsChanged();
    }
}

void DistributionTemplate::setYLow(double yLow)
{
    if (qFuzzyCompare(m_yLow, yLow))
        return;

    if(yLow > m_yHigh)
        return;

    QJsonObject oldParams;
    oldParams["yl"] = m_yLow;
    oldParams["a"] = m_autoFit;

    m_yLow = yLow;
    emit yLowChanged(m_yLow);
    m_autoFit = false;
    emit autoFitChanged(m_autoFit);

    QJsonObject newParams;
    newParams["yl"] = m_yLow;
    newParams["a"] = m_autoFit;
    reportParamsChanged(oldParams, newParams);
    if(valid())
    {
        plot();
        boundsChanged();
    }
}

void DistributionTemplate::setYHigh(double yHigh)
{
    if (qFuzzyCompare(m_yHigh, yHigh))
        return;

    if(yHigh < m_yLow)
        return;

    QJsonObject oldParams;
    oldParams["yh"] = m_yHigh;
    oldParams["a"] = m_autoFit;

    m_yHigh = yHigh;
    emit yHighChanged(m_yHigh);
    m_autoFit = false;
    emit autoFitChanged(m_autoFit);

    QJsonObject newParams;
    newParams["yl"] = m_yHigh;
    newParams["a"] = m_autoFit;
    reportParamsChanged(oldParams, newParams);
    if(valid())
    {
        plot();
        boundsChanged();
    }
}

void DistributionTemplate::plot()
{
    if(m_autoFit)
    {
        m_xLow = m_distribution->getDefaultXLow();
        emit xLowChanged(m_xLow);
        m_xHigh = m_distribution->getDefaultXHigh();
        emit xHighChanged(m_xHigh);
    }

    if(m_distribution->distType() == DistributionDataType::Continuous)
        plotContinuous();
    else
        plotDiscrete();
}

void DistributionTemplate::plotContinuous()
{
    if(m_autoFit)
    {
        m_yLow = 0.0;
        emit yLowChanged(m_yLow);

        if(m_distribution->getFlags() & MODEUNDEFINED)
        {
            m_yHigh = 1.015 * DistributionCommonFunctions::findYMax(m_distribution, m_xLow, m_xHigh);
            emit yHighChanged(m_yHigh);
        }
        else
        {
            m_yHigh = 1.015 * m_distribution->pdf()->evaluate(m_distribution->getMode());
            emit yHighChanged(m_yHigh);
        }
    }

    ConnectedPlot plot = DistributionCommonFunctions::makeContinuousConnectedPlot(m_distribution, 450, 300,
                                                                                  m_xLow, m_xHigh, m_yLow, m_yHigh,
                                                                                  m_xLow, m_xHigh);

    m_xValues = plot.xValues();
    m_yValues = plot.yValues();

    emit displayContinuousDistribution(m_xValues, m_yValues);
}

void DistributionTemplate::plotDiscrete()
{
    if(m_autoFit)
    {
        m_yLow = 0.0;
        emit yLowChanged(m_yLow);

        if(m_distribution->getFlags() & MODEUNDEFINED)
        {
            m_yHigh = 1.015 * DistributionCommonFunctions::findYMax(m_distribution, m_xLow, m_xHigh);
            emit yHighChanged(m_yHigh);
        }
        else
        {
            m_yHigh = 1.015 * m_distribution->pdf()->evaluate(m_distribution->getMode());
            emit yHighChanged(m_yHigh);
        }
    }

    ConnectedPlot plot = DistributionCommonFunctions::makeDiscretePDFConnectedPlot(m_distribution, 450, 300,
                                                                                   m_xLow, m_xHigh, m_yLow, m_yHigh,
                                                                                   m_xLow, m_xHigh);

    m_xValues = plot.xValues();
    m_yValues = plot.yValues();

    emit displayDiscreteDistribution(m_xValues, m_yValues);
}

void DistributionTemplate::boundsChanged()
{

}

