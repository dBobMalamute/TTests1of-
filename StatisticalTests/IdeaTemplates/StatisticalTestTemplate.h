#ifndef STATISTICALTESTTEMPLATE_H
#define STATISTICALTESTTEMPLATE_H

#include "../../MalamuteCore/InheritedClasses/Idea.h"
#include "../../DataTypes/NumbersDataType.h"
#include "../../DataTypes/NumberDataType.h"
#include "../../DataTypes/DistributionDataType.h"
#include "../../Distributions/Common/DistributionCommonFunctions.h"

class StatisticalTestTemplate : public Idea
{
    Q_OBJECT

    Q_PROPERTY(double xLowData READ xLowData WRITE setXLowData NOTIFY xLowDataChanged)
    Q_PROPERTY(double xHighData READ xHighData WRITE setXHighData NOTIFY xHighDataChanged)
    Q_PROPERTY(bool autoFitData READ autoFitData WRITE setAutoFitData NOTIFY autoFitDataChanged)

    Q_PROPERTY(double xLowDist READ xLowDist WRITE setXLowDist NOTIFY xLowDistChanged)
    Q_PROPERTY(double xHighDist READ xHighDist WRITE setXHighDist NOTIFY xHighDistChanged)
    Q_PROPERTY(bool autoFitDist READ autoFitDist WRITE setAutoFitDist NOTIFY autoFitDistChanged)

    Q_PROPERTY(double animationSpeed READ animationSpeed WRITE setAnimationSpeed NOTIFY animationSpeedChanged)

    Q_PROPERTY(double statisticalTestValue READ statisticalTestValue WRITE setStatisticalTestValue NOTIFY statisticalTestValueChanged)
    Q_PROPERTY(double alpha READ alpha WRITE setAlpha NOTIFY alphaChanged)
    Q_PROPERTY(double xValueForAlpha READ xValueForAlpha WRITE setXValueForAlpha NOTIFY xValueForAlphaChanged)
    Q_PROPERTY(double pValue READ pValue WRITE setPValue NOTIFY pValueChanged)


public:
    StatisticalTestTemplate();

    QJsonObject save() const override;
    void load(const QJsonObject &obj) override;

    void resetDisplay() override;

    std::shared_ptr<DataType> dataOut(PlugNumber plugNumber) override;

    double xLowData() const;
    double xHighData() const;
    bool autoFitData() const;

    double xLowDist() const;
    double xHighDist() const;
    bool autoFitDist() const;

    double animationSpeed() const;

    double statisticalTestValue() const;
    double alpha() const;
    double xValueForAlpha() const;
    double pValue() const;

signals:
    void xLowDataChanged(double xLowData);
    void xHighDataChanged(double xHighData);
    void autoFitDataChanged(bool autoFitData);

    void xLowDistChanged(double xLowDist);
    void xHighDistChanged(double xHighDist);
    void autoFitDistChanged(bool autoFitDist);

    void animationSpeedChanged(double animationSpeed);

    void statisticalTestValueChanged(double statisticalTestValue);
    void alphaChanged(double alpha);
    void xValueForAlphaChanged(double xValueForAlpha);
    void pValueChanged(double pValue);

    void plotDistribution(std::vector<double> xValues, std::vector<double> yValues);

public slots:
    void setXLowData(double xLowData);
    void setXHighData(double xHighData);
    void setAutoFitData(bool autoFitData);

    void setXLowDist(double xLowDist);
    void setXHighDist(double xHighDist);
    void setAutoFitDist(bool autoFitDist);

    void setAnimationSpeed(double animationSpeed);

    void setStatisticalTestValue(double statisticalTestValue);
    void setAlpha(double alpha);
    void setXValueForAlpha(double xValueForAlpha);
    void setPValue(double pValue);

protected:
    std::shared_ptr<NumberDataType> m_pValueOutput;
    std::shared_ptr<NumberDataType> m_statisticalTestValueOutput;

    std::shared_ptr<DistributionDataType> m_distribution;

    virtual void validate() = 0;
    void compute();
    virtual void computeTestStatistic() = 0;
    virtual void prepareTestStatisticVisuals() = 0;
    virtual void makeDistribution() = 0;
    virtual void computePValue() = 0;
    virtual void preparePValueVisuals() = 0;

    double m_xLowData;
    double m_xHighData;
    bool m_autoFitData;

    double m_xLowDist;
    double m_xHighDist;
    double m_yLowDist;
    double m_yHighDist;
    bool m_autoFitDist;

    double m_animationSpeed;

    double m_statisticalTestValue;
    double m_alpha;
    double m_xValueForAlpha;
    double m_pValue;
};

#endif // STATISTICALTESTTEMPLATE_H
