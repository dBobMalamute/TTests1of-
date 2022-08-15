#ifndef ONESAMPLEONESIDEDTTESTIDEA_H
#define ONESAMPLEONESIDEDTTESTIDEA_H

#include "IdeaTemplates/StatisticalTestTemplate.h"
#include "../Distributions/DistributionMakers/StudentTDistributionBuilder.h"

struct OneSampleOneSidedTTestAttributes : public IdeaAttributes
{
    OneSampleOneSidedTTestAttributes();
};

class OneSampleOneSidedTTestIdea : public StatisticalTestTemplate
{
    Q_OBJECT

    Q_PROPERTY(double nullValue READ nullValue WRITE setNullValue NOTIFY nullValueChanged)
    Q_PROPERTY(bool showNull READ showNull WRITE setShowNull NOTIFY showNullChanged)
    Q_PROPERTY(double mean READ mean WRITE setMean NOTIFY meanChanged)
    Q_PROPERTY(double variance READ variance WRITE setVariance NOTIFY varianceChanged)

    Q_PROPERTY(double degreesOfFreedom READ degreesOfFreedom WRITE setDegreesOfFreedom NOTIFY degreesOfFreedomChanged)
    Q_PROPERTY(bool sideIsRight READ sideIsRight WRITE setSideIsRight NOTIFY sideIsRightChanged)

public:
    OneSampleOneSidedTTestIdea();

    const IdeaAttributes attributes() override;

    QJsonObject save() const override;
    void load(const QJsonObject &obj) override;

    void onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber plugNumber) override;

    double nullValue() const;
    bool showNull() const;
    double mean() const;
    double variance() const;

    double degreesOfFreedom() const;
    bool sideIsRight() const;

signals:
    void nullValueChanged(double nullValue);
    void showNullChanged(bool showNull);
    void meanChanged(double mean);
    void varianceChanged(double variance);

    void degreesOfFreedomChanged(double degreesOfFreedom);
    void sideIsRightChanged(bool sideIsRight);

    void displayNewData(std::vector<double> positions);
    void displayAlphaFillArea(std::vector<double> xValues, std::vector<double> yValues);
    void displayTestStatisticFillArea(std::vector<double> xValues, std::vector<double> yValues);


public slots:
    void setNullValue(double nullValue);
    void setShowNull(bool showNull);
    void setMean(double mean);
    void setVariance(double variance);

    void setDegreesOfFreedom(double degreesOfFreedom);
    void setSideIsRight(bool sideIsRight);

private:
    std::weak_ptr<NumbersDataType> m_dataInput;
    std::weak_ptr<NumberDataType> m_nullValueInput;

    void validate() override;

    void computeTestStatistic() override;
    void prepareTestStatisticVisuals() override;
    void makeDistribution() override;
    void computePValue() override;
    void preparePValueVisuals() override;

    double m_nullValue;
    bool m_showNull;
    double m_mean;
    double m_variance;
    double m_stderr;

    double m_degreesOfFreedom;
    bool m_sideIsRight;
};


#endif // ONESAMPLEONESIDEDTTESTIDEA_H
