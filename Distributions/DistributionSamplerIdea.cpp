#include "DistributionSamplerIdea.h"
#include <QJsonArray>
#include <QRandomGenerator>

DistributionSamplerAttributes::DistributionSamplerAttributes()
{
    m_listName = "Distribution Sampler";
    m_displayName = "Distribution Sampler";
    m_authors << "dBob";
    m_description = "This box takes in a distribution and samples number from it. It features a nice visual when maximized";
    m_iconPath = "qrc:/Icons/DistributionSampler.png";

    m_dataTypesIn.push_back(Magic<DistributionDataTypeAttributes>::cast().id());
    m_dataTypesOut.push_back(Magic<NumbersDataTypeAttributes>::cast().id());

    m_gear = true;

    m_embeddedQMLPath = ":/QML/DistributionSamplerIdea.qml";
    m_minimizable = true;
    m_startMinimized = true;
    m_minimizedQMLPath = ":/QML/DistributionSamplerMinimized.qml";

    m_externalQMLPaths << ":/QML/SpeedControl.qml";
    m_externalQMLLocations.push_back({true, false, 10,0});
}

DistributionSamplerIdea::DistributionSamplerIdea()
{

}

const IdeaAttributes DistributionSamplerIdea::attributes()
{
    return Magic<DistributionSamplerAttributes>::cast();
}


void DistributionSamplerIdea::sampleContinuous()
{
    emit startSpinningGear();

    if(m_distribution->getFlags() & SAMPLERSET)
    {
        int numNewSamples = m_totalSamples - m_currentSamples;
        std::vector<double> newSamples = m_distribution->sampler()->getSamples(numNewSamples);

        for(int i = 0; i < numNewSamples; i++)
        {
            m_samples.push_back(newSamples.at(i));
            m_samplesDoubles.push_back(newSamples.at(i));
        }
        m_currentSamples = m_totalSamples;
    }
    else
    {
        while(m_currentSamples < m_totalSamples)
        {
            double xVal = getIndividualXValueContinuous();
            m_samples.push_back(xVal);
            m_samplesDoubles.push_back(xVal);
            m_currentSamples++;
        }
    }

    emit startAnimation();
    emit samplesChanged(m_samples);

    m_output = std::make_shared<NumbersDataType>(m_samplesDoubles);
    emit newData(0);
    emit stopSpinningGear();
}

void DistributionSamplerIdea::sampleDiscrete()
{
    emit startSpinningGear();

    int numNewSamples = m_totalSamples - m_currentSamples;
    std::vector<double> samples;
    if(m_distribution->getFlags() & SAMPLERSET)
    {
        samples = m_distribution->sampler()->getSamples(numNewSamples);
    }
    else
    {
        qFatal("Sampler not set");
    }

    for(int i = 0; i < numNewSamples; i++)
    {
        double xVal = samples.at(i);
        m_samples.push_back(xVal);
        m_samplesDoubles.push_back(xVal);
        m_currentSamples++;
    }

    emit startAnimation();
    emit samplesChanged(m_samples);

    m_output = std::make_shared<NumbersDataType>(m_samplesDoubles);
    emit newData(0);
    emit stopSpinningGear();
}


QPointF DistributionSamplerIdea::getPositionForDot(int i)
{
    //450 is the width. Position is percentage.
    double xValue = 450 * (m_samplesDoubles[i] - xLow())/
            (xHigh() - xLow());
    int implicitBinIndex = std::floor((80 * xValue / 450.00001));

    if(implicitBinIndex >= 80 || implicitBinIndex < 0)
        return QPointF(xValue, 296);

    double yValue = 296 - 2.0 * m_samplesInImplicitBin.at(implicitBinIndex);
    m_samplesInImplicitBin[implicitBinIndex]++;

    return QPointF(xValue, yValue);
}
