#ifndef DISTRIBUTIONTEMPLATE_H
#define DISTRIBUTIONTEMPLATE_H

#include "../../MalamuteCore/InheritedClasses/Idea.h"
#include "../../DataTypes/NumberDataType.h"
#include "../../DataTypes/DistributionDataType.h"
#include "../Common/DistributionCommonFunctions.h"

class DistributionTemplate : public Idea
{
    Q_OBJECT

    Q_PROPERTY(double xLow READ xLow WRITE setXLow NOTIFY xLowChanged)
    Q_PROPERTY(double xHigh READ xHigh WRITE setXHigh NOTIFY xHighChanged)
    Q_PROPERTY(double yLow READ yLow WRITE setYLow NOTIFY yLowChanged)
    Q_PROPERTY(double yHigh READ yHigh WRITE setYHigh NOTIFY yHighChanged)

    Q_PROPERTY(bool autoFit READ autoFit WRITE setAutoFit NOTIFY autoFitChanged)

public:
    explicit DistributionTemplate();

    QJsonObject save() const override;
    void load(const QJsonObject &) override;

    double xLow() const;
    double xHigh() const;
    double yLow() const;
    double yHigh() const;
    bool autoFit() const;

signals:
    void xLowChanged(double xLow);
    void xHighChanged(double xHigh);
    void yLowChanged(double yLow);
    void yHighChanged(double yHigh);
    void autoFitChanged(bool autoFit);

    void displayContinuousDistribution(std::vector<double> xValues, std::vector<double> yValues);
    void displayDiscreteDistribution(std::vector<double> xValues, std::vector<double> yValues);

public slots:    
    void setXLow(double xLow);
    void setXHigh(double xHigh);
    void setYLow(double yLow);
    void setYHigh(double yHigh);

    void setAutoFit(bool autoFit);

protected:
    std::shared_ptr<DistributionDataType> m_distribution;
    virtual void validate() = 0;

    void plot();
    void plotContinuous();
    void plotDiscrete();
    virtual void boundsChanged();

    std::vector<double> m_xValues;
    std::vector<double> m_yValues;

    double m_xLow;
    double m_xHigh;
    double m_yLow;
    double m_yHigh;
    bool m_autoFit;
};

#endif // DISTRIBUTIONTEMPLATE_H
