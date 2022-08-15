#ifndef SAMPLERTEMPLATE_H
#define SAMPLERTEMPLATE_H

#include <QPointF>
#include "../../DataTypes/NumbersDataType.h"
#include "DistributionTemplate.h"

class SamplerTemplate : public DistributionTemplate
{
    Q_OBJECT

    Q_PROPERTY(QList<QVariant> samples READ samples WRITE setSamples NOTIFY samplesChanged)
    Q_PROPERTY(int totalSamples READ totalSamples WRITE setTotalSamples NOTIFY totalSamplesChanged)
    Q_PROPERTY(int samplingSize READ samplingSize WRITE setSamplingSize NOTIFY samplingSizeChanged)

    Q_PROPERTY(double animationSpeed READ animationSpeed WRITE setAnimationSpeed NOTIFY animationSpeedChanged)

public:
    explicit SamplerTemplate();

    void onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber plugNumber) override;
    std::shared_ptr<DataType> dataOut(PlugNumber plugNumber) override;

    QJsonObject save() const override;
    void load(const QJsonObject &) override;

    void resetDisplay() override;

    QList<QVariant> samples() const;
    int totalSamples() const;
    int samplingSize() const;

    double animationSpeed() const;

signals:
    void samplesChanged(QList<QVariant> samples);
    void samplingSizeChanged(int samplingSize);
    void totalSamplesChanged(int totalSamples);

    void startAnimation();
    void resetAnimation();

    void animationSpeedChanged(double animationSpeed);

public slots:
    void setSamples(QList<QVariant> samples);
    void setTotalSamples(int totalSamples);
    void setSamplingSize(int samplingSize);

    void sampleButtonPressed();
    void resampleButtonPressed();
    void totalSamplesTextEdited(int samples);

    QPointF getPositionForDot(int i);

    void setAnimationSpeed(double animationSpeed);

protected:
    std::weak_ptr<DistributionDataType> m_input;
    std::shared_ptr<NumbersDataType> m_output;

    void validate() override;
    void boundsChanged() override;

    void prepareSampleContinous();
    void prepareSampleDiscrete();
    std::vector<double> m_distributionSections;

    void sample();
    virtual void sampleContinuous() = 0;
    double getIndividualXValueContinuous();
    virtual void sampleDiscrete() = 0;
    virtual void resetSamples();

    QList<QVariant> m_samples;
    std::vector<int> m_samplesInImplicitBin;
    std::vector<double> m_samplesDoubles;
    int m_samplingSize;
    int m_currentSamples;
    int m_totalSamples;

    double m_animationSpeed;

};

#endif // SAMPLERTEMPLATE_H
