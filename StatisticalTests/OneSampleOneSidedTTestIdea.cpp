#include "OneSampleOneSidedTTestIdea.h"

OneSampleOneSidedTTestAttributes::OneSampleOneSidedTTestAttributes()
{
    m_listName = "One Sample One Sided T Test";
    m_displayName = "One Sample One Sided T Test";
    m_authors << "dBob";
    m_description = "This box calculates a one sample T Test";
    m_iconPath = "qrc:/Icons/OneSampleOneSidedTTest.png";

    m_customLabels = true;

    m_dataTypesIn.push_back(Magic<NumbersDataTypeAttributes>::cast().id());
    m_dataTypesIn.push_back(Magic<NumberDataTypeAttributes>::cast().id());
    m_labelsIn << "Data" << "Null";
    m_dataTypesOut.push_back(Magic<NumberDataTypeAttributes>::cast().id());
    m_dataTypesOut.push_back(Magic<NumberDataTypeAttributes>::cast().id());
    m_labelsOut << "t" << "p";

    m_gear = true;

    m_embeddedQMLPath = ":/QML/OneSampleOneSidedTTest.qml";
    m_minimizable = true;
    m_minimizedQMLPath = ":/QML/TTestMinimized.qml";
    m_differentNameOnMinimized = true;
    m_minimizedName = "One Sample One\nSided T Test";

    m_externalQMLPaths << ":/QML/TTestSpeedControl.qml";
    m_externalQMLLocations.push_back({true, false, 10,0});
}

const IdeaAttributes OneSampleOneSidedTTestIdea::attributes()
{
    return Magic<OneSampleOneSidedTTestAttributes>::cast();
}

OneSampleOneSidedTTestIdea::OneSampleOneSidedTTestIdea() :
    m_nullValue(0.0),
    m_showNull(false),
    m_sideIsRight(true)
{
    m_inPortLabelColors = {QColor("#26d326"), QColor("#0bafd1")};
    m_outPortLabelColors = {QColor("#1dc78c"), QColor("#18b4c1")};
}

QJsonObject OneSampleOneSidedTTestIdea::save() const
{
    QJsonObject saveJson = StatisticalTestTemplate::save();
    saveJson["sr"] = m_sideIsRight;

    return saveJson;
}

void OneSampleOneSidedTTestIdea::load(const QJsonObject &obj)
{
    StatisticalTestTemplate::load(obj);

    QJsonValue v = obj["sr"];
    if(!v.isUndefined())
    {
        m_sideIsRight = v.toBool();
        emit sideIsRightChanged(m_sideIsRight);
        if(valid())
        {
            computePValue();
            if(!minimized())
                preparePValueVisuals();
        }
    }
}

void OneSampleOneSidedTTestIdea::onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber plugNumber)
{
    if(plugNumber == 0)
    {
        m_dataInput = std::dynamic_pointer_cast<NumbersDataType>(dataType);
    }
    else
    {
        m_nullValueInput = std::dynamic_pointer_cast<NumberDataType>(dataType);
    }

    validate();
}


double OneSampleOneSidedTTestIdea::nullValue() const
{
    return m_nullValue;
}

double OneSampleOneSidedTTestIdea::mean() const
{
    return m_mean;
}

double OneSampleOneSidedTTestIdea::variance() const
{
    return m_variance;
}

bool OneSampleOneSidedTTestIdea::sideIsRight() const
{
    return m_sideIsRight;
}

double OneSampleOneSidedTTestIdea::degreesOfFreedom() const
{
    return m_degreesOfFreedom;
}

bool OneSampleOneSidedTTestIdea::showNull() const
{
    return m_showNull;
}

void OneSampleOneSidedTTestIdea::setNullValue(double nullValue)
{
    if (qFuzzyCompare(m_nullValue, nullValue))
        return;

    m_nullValue = nullValue;
    emit nullValueChanged(m_nullValue);
}

void OneSampleOneSidedTTestIdea::setMean(double mean)
{
    if (qFuzzyCompare(m_mean, mean))
        return;

    m_mean = mean;
    emit meanChanged(m_mean);
}

void OneSampleOneSidedTTestIdea::setVariance(double variance)
{
    if (qFuzzyCompare(m_variance, variance))
        return;

    m_variance = variance;
    emit varianceChanged(m_variance);
}

void OneSampleOneSidedTTestIdea::setShowNull(bool showNull)
{
    if (m_showNull == showNull)
        return;

    m_showNull = showNull;
    emit showNullChanged(m_showNull);
}

void OneSampleOneSidedTTestIdea::setSideIsRight(bool sideIsRight)
{
    if (m_sideIsRight == sideIsRight)
        return;

    QJsonObject oldParams = Idea::save();
    oldParams["sr"] = m_sideIsRight;

    m_sideIsRight = sideIsRight;
    emit sideIsRightChanged(m_sideIsRight);

    QJsonObject newParams = Idea::save();
    newParams["sr"] = m_sideIsRight;
    reportParamsChanged(oldParams, newParams);

    if(valid())
    {
        computePValue();
        if(!minimized())
            preparePValueVisuals();
    }
}

void OneSampleOneSidedTTestIdea::setDegreesOfFreedom(double degreesOfFreedom)
{
    if (qFuzzyCompare(m_degreesOfFreedom, degreesOfFreedom))
        return;

    m_degreesOfFreedom = degreesOfFreedom;
    emit degreesOfFreedomChanged(m_degreesOfFreedom);
}

void OneSampleOneSidedTTestIdea::validate()
{
    auto n1 = m_dataInput.lock();
    auto n2 = m_nullValueInput.lock();

    if(n2)
    {
        setShowNull(true);
        setNullValue(n2->number());
    }
    else
        setShowNull(false);

    if(n1 && n2)
    {
        if(n1->numbers().size() < 2)
        {
            setStatus(IdeaStatus::Error, "Insufficient data", "Not enough data points to do a t-test");
        }
        else
        {
            setStatus(IdeaStatus::Working, "Calculating", "Currently calculating the p value from the "
                                                          "given input");

            compute();
        }
    }
    else
    {
        setDefaultStatus();
    }
}

void OneSampleOneSidedTTestIdea::computeTestStatistic()
{
    auto n1 = m_dataInput.lock();
    auto n2 = m_nullValueInput.lock();

    std::vector<double> m_samples = n1->numbers();

    double e_x = 0.0;
    double e_x2 = 0.0;
    int sampleSize = m_samples.size();
    setDegreesOfFreedom(sampleSize - 1);

    //Calculate sample mean, variance and Bessel corrected standard deviation.
    for(int i = 0; i < sampleSize; i++)
    {
        e_x += m_samples[i];
        e_x2 += m_samples[i]*m_samples[i];
    }
    e_x /= sampleSize;
    e_x2 /= sampleSize;

    double uncorrectedVariance = e_x2 - e_x * e_x;
    double sampleStandardDeviation = std::sqrt(uncorrectedVariance * 1.0 * sampleSize / (sampleSize - 1.0));
    m_stderr = (sampleStandardDeviation / std::sqrt(1.0*sampleSize));
    //Calculate the test statistic.
    double t = (e_x - n2->number()) / m_stderr;

    setMean(e_x);
    setVariance(uncorrectedVariance);
    setStatisticalTestValue(t);
    m_statisticalTestValueOutput = std::make_shared<NumberDataType>(t);
    emit newData(0);
}

void OneSampleOneSidedTTestIdea::prepareTestStatisticVisuals()
{
    auto n1 = m_dataInput.lock();
    auto n2 = m_nullValueInput.lock();

    std::vector<double> samples = n1->numbers();

    if(autoFitData())
    {
        //Find autofit if necessary, set the bounds. Draw the dots

        double lowBound = samples[0];
        double upBound = samples[0];

        for(size_t i = 1; i < samples.size(); i++)
        {
            if(samples.at(i) < lowBound)
                lowBound = samples.at(i);
            if(samples.at(i) > upBound)
                upBound = samples.at(i);
        }
        double stdev = std::sqrt(variance());
        if(nullValue() - 2.0*stdev < lowBound)
            lowBound = nullValue() - 2.0*stdev;
        if(nullValue() + 2.0*stdev > upBound)
            upBound = nullValue() + 2.0*stdev;

        m_xLowData = lowBound;
        m_xHighData = upBound;
        emit xLowDataChanged(m_xLowData);
        emit xHighDataChanged(m_xHighData);
    }

    std::vector<double> dotPositions;
    dotPositions.reserve(samples.size());
    for(size_t i = 0; i < samples.size(); i++)
    {
        dotPositions.push_back(450.0 * (samples.at(i) - m_xLowData) / (m_xHighData - m_xLowData));
    }
    emit displayNewData(dotPositions);
}

void OneSampleOneSidedTTestIdea::makeDistribution()
{
    m_distribution = StudentTDistributionBuilder::makeStudentT(degreesOfFreedom());
}

void OneSampleOneSidedTTestIdea::computePValue()
{
    double pValue = m_distribution->cdf()->evaluate(m_statisticalTestValue);
    if(m_sideIsRight)
        pValue = 1.0 - pValue;
    setPValue(pValue);
    m_pValueOutput = std::make_shared<NumberDataType>(pValue);
    emit newData(1);
}

void OneSampleOneSidedTTestIdea::preparePValueVisuals()
{
    double xValueForAlpha;

    if(m_sideIsRight)
    {
        xValueForAlpha = DistributionCommonFunctions::findPointForValueContinuous(
                    m_distribution, 1.0-m_alpha, -1000, 1000);
    }
    else
    {
        xValueForAlpha = DistributionCommonFunctions::findPointForValueContinuous(
                    m_distribution, m_alpha, -1000, 1000);
    }
    setXValueForAlpha(xValueForAlpha);

    //There is no user option to set y values. So always do this.
    m_yLowDist = 0.0;
    m_yHighDist = m_distribution->pdf()->evaluate(0.0);

    if(m_autoFitDist)
    {
        double low = -4.0;
        double up = 4.0;
        if(xValueForAlpha > up)
            up = xValueForAlpha + 1;
        if(xValueForAlpha < low)
            low = xValueForAlpha - 1;
        if(m_statisticalTestValue > up)
            up = m_statisticalTestValue + 1;
        if(m_statisticalTestValue < low)
            low = m_statisticalTestValue - 1;
        m_xLowDist = low;
        m_xHighDist = up;

        emit xLowDistChanged(m_xLowDist);
        emit xHighDistChanged(m_xHighDist);
    }

    ConnectedPlot distPlot = DistributionCommonFunctions::makeContinuousConnectedPlot(m_distribution, 450, 150,
                                                                                      m_xLowDist, m_xHighDist,
                                                                                      m_yLowDist, m_yHighDist,
                                                                                      m_xLowDist, m_xHighDist);
    ConnectedPlot alphaPlot;
    if(m_sideIsRight)
    {
        alphaPlot = DistributionCommonFunctions::makeContinuousConnectedPlot(m_distribution, 450, 150,
                                                                             m_xLowDist, m_xHighDist,
                                                                             m_yLowDist, m_yHighDist,
                                                                             xValueForAlpha, m_xHighDist);
    }
    else
    {
        alphaPlot = DistributionCommonFunctions::makeContinuousConnectedPlot(m_distribution, 450, 150,
                                                                             m_xLowDist, m_xHighDist,
                                                                             m_yLowDist, m_yHighDist,
                                                                             m_xLowDist, xValueForAlpha);
    }

    ConnectedPlot tPlot;
    if(m_sideIsRight)
    {
        tPlot = DistributionCommonFunctions::makeContinuousConnectedPlot(m_distribution, 450, 150,
                                                                             m_xLowDist, m_xHighDist,
                                                                             m_yLowDist, m_yHighDist,
                                                                             statisticalTestValue(), m_xHighDist);
    }
    else
    {
        tPlot = DistributionCommonFunctions::makeContinuousConnectedPlot(m_distribution, 450, 150,
                                                                             m_xLowDist, m_xHighDist,
                                                                             m_yLowDist, m_yHighDist,
                                                                             m_xLowDist, statisticalTestValue());
    }

    emit plotDistribution(distPlot.xValues(), distPlot.yValues());
    emit displayAlphaFillArea(alphaPlot.xValues(), alphaPlot.yValues());
    emit displayTestStatisticFillArea(tPlot.xValues(), tPlot.yValues());
}
