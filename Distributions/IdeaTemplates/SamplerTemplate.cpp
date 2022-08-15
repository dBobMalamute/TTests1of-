#include "SamplerTemplate.h"
#include <QJsonArray>
#include <QRandomGenerator>

#include "../Common/DistributionCommonFunctions.h"

SamplerTemplate::SamplerTemplate() :
    m_samples(QList<QVariant>()),
    m_samplingSize(1),
    m_totalSamples(0),
    m_animationSpeed(1.0)
{
    m_samplesInImplicitBin.reserve(80);
    for(int i = 0; i < 80; i++)
        m_samplesInImplicitBin.push_back(0);
}

void SamplerTemplate::onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber)
{
    m_input = std::dynamic_pointer_cast<DistributionDataType>(dataType);

    validate();
}

QJsonObject SamplerTemplate::save() const
{
    QJsonObject saveJson = DistributionTemplate::save();
    saveJson["s"] = m_samplingSize;
    saveJson["n"] = m_totalSamples;
    saveJson["as"] = m_animationSpeed;

    return saveJson;
}

void SamplerTemplate::load(const QJsonObject &p)
{
    DistributionTemplate::load(p);
    QJsonValue v = p["s"];
    if(!v.isUndefined())
    {
        m_samplingSize = v.toInt();
        emit samplingSizeChanged(m_samplingSize);
    }
    v = p["as"];
    if(!v.isUndefined())
    {
        m_animationSpeed = v.toDouble();
        emit animationSpeedChanged(m_animationSpeed);
    }

    v = p["n"];
    if(!v.isUndefined())
    {
        m_totalSamples = v.toInt();
        emit totalSamplesChanged(m_totalSamples);
        resetSamples();
        if(valid())
            sample();
    }

}

void SamplerTemplate::resetDisplay()
{
    if(valid())
    {
        plot();
        for(int i = 0; i < 80; i++)
            m_samplesInImplicitBin[i] = 0;

        emit samplesChanged(m_samples);
        emit startAnimation();
    }
}

QList<QVariant> SamplerTemplate::samples() const
{
    return m_samples;
}

int SamplerTemplate::samplingSize() const
{
    return m_samplingSize;
}

double SamplerTemplate::animationSpeed() const
{
    return m_animationSpeed;
}

int SamplerTemplate::totalSamples() const
{
    return m_totalSamples;
}

void SamplerTemplate::validate()
{
    resetSamples();

    auto v_distribution = m_input.lock();
    if(v_distribution)
    {
        setStatus(IdeaStatus::Working, "Ready to Sample", "Ready to sample a distribution.");
        m_distribution = v_distribution;
        if(!minimized())
            plot();

        if(m_distribution->distType() == DistributionDataType::Continuous)
            prepareSampleContinous();

        sample();
    }
    else
    {
        setDefaultStatus();
    }
}

void SamplerTemplate::prepareSampleContinous()
{
    m_distributionSections = DistributionCommonFunctions::visualBoundDistributionSectionsContinuous(m_distribution, 100);
}

void SamplerTemplate::prepareSampleDiscrete()
{


}

void SamplerTemplate::setTotalSamples(int totalSamples)
{
    if (m_totalSamples == totalSamples)
        return;

    QJsonObject oldParams = Idea::save();
    oldParams["n"] = m_totalSamples;

    m_totalSamples = totalSamples;
    emit totalSamplesChanged(m_totalSamples);

    QJsonObject newParams = Idea::save();
    newParams["n"] = m_totalSamples;

    emit reportParamsChanged(oldParams, newParams);

    if(valid())
        sample();
}

void SamplerTemplate::setSamples(QList<QVariant> samples)
{
    if (m_samples == samples)
        return;

    m_samples = samples;
    emit samplesChanged(m_samples);
}

void SamplerTemplate::setSamplingSize(int samplingSize)
{
    if (m_samplingSize == samplingSize)
        return;

    QJsonObject oldParams = Idea::save();
    oldParams["s"] = m_samplingSize;

    m_samplingSize = samplingSize;
    emit samplingSizeChanged(m_samplingSize);

    QJsonObject newParams = Idea::save();
    newParams["s"] = m_samplingSize;
    emit reportParamsChanged(oldParams, newParams);
}

void SamplerTemplate::sampleButtonPressed()
{
    setTotalSamples(m_totalSamples + m_samplingSize);
}

void SamplerTemplate::resampleButtonPressed()
{
    resetSamples();
    if(valid())
        sample();
}

void SamplerTemplate::totalSamplesTextEdited(int samples)
{
    if(m_totalSamples == samples)
        return;

    resetSamples();
    setTotalSamples(samples);
}

void SamplerTemplate::sample()
{
    if(m_distribution->distType() == DistributionDataType::Continuous)
        sampleContinuous();
    else
        sampleDiscrete();
}

double SamplerTemplate::getIndividualXValueContinuous()
{
    double random = QRandomGenerator::global()->generateDouble();

    int low = std::floor(100 * random);
    return DistributionCommonFunctions::findPointForValueContinuous(m_distribution, random,
                                                                    m_distributionSections.at(low), low/100.0,
                                                                    m_distributionSections.at(low+1), (low + 1) /100.0);
}

void SamplerTemplate::resetSamples()
{
    m_currentSamples = 0;

    for(int i = 0; i < 80; i++)
        m_samplesInImplicitBin[i] = 0;

    m_samples.clear();
    emit samplesChanged(m_samples);
    m_samplesDoubles.clear();

    emit resetAnimation();

    m_output = std::make_shared<NumbersDataType>(m_samplesDoubles);
    emit newData(0);
}

std::shared_ptr<DataType> SamplerTemplate::dataOut(PlugNumber)
{
    return std::static_pointer_cast<DataType>(m_output);
}

QPointF SamplerTemplate::getPositionForDot(int i)
{
    //450 is the width. Position is percentage.
    double xValue = 450 * (m_samplesDoubles[i] - xLow())/
            (xHigh() - xLow());
    int implicitBinIndex = std::floor((80 * xValue / 450.00001));

    if(implicitBinIndex >= 80 || implicitBinIndex < 0)
        return QPointF(xValue, 290);

    double yValue = 290 - 2.0 * m_samplesInImplicitBin.at(implicitBinIndex);
    m_samplesInImplicitBin[implicitBinIndex]++;

    return QPointF(xValue, yValue);
}

void SamplerTemplate::setAnimationSpeed(double animationSpeed)
{
    if (qFuzzyCompare(m_animationSpeed, animationSpeed))
        return;

    m_animationSpeed = animationSpeed;
    emit animationSpeedChanged(m_animationSpeed);
}


void SamplerTemplate::boundsChanged()
{
    if(valid())
    {
        for(int i = 0; i < 80; i++)
            m_samplesInImplicitBin[i] = 0;

        emit samplesChanged(m_samples);
        emit resetAnimation();
        emit startAnimation();
    }
}
