#ifndef GAUSSIANDISTRIBUTIONIDEA_H
#define GAUSSIANDISTRIBUTIONIDEA_H

#include "IdeaTemplates/DistributionTemplate.h"

struct GaussianDistributionAttributes : public IdeaAttributes
{
    GaussianDistributionAttributes();
};

class GaussianDistributionIdea : public DistributionTemplate
{
    Q_OBJECT

    Q_PROPERTY(double mean READ mean WRITE setMean NOTIFY meanChanged)
    Q_PROPERTY(bool meanVisible READ meanVisible WRITE setMeanVisible NOTIFY meanVisibleChanged)
    Q_PROPERTY(double stdev READ stdev WRITE setStdev NOTIFY stdevChanged)
    Q_PROPERTY(bool stdevVisible READ stdevVisible WRITE setStdevVisible NOTIFY stdevVisibleChanged)

public:
    explicit GaussianDistributionIdea();
    const IdeaAttributes attributes() override;

    QJsonObject save() const override;
    void load(const QJsonObject &) override;

    void onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber plugNumber) override;
    std::shared_ptr<DataType> dataOut(PlugNumber plugNumber) override;

    void resetDisplay() override;

    double mean() const;
    bool meanVisible() const;
    double stdev() const;
    bool stdevVisible() const;

public slots:
    void setMean(double mean);
    void setMeanVisible(bool meanVisible);
    void setStdev(double stdev);   
    void setStdevVisible(bool stdevVisible);

signals:
    void meanChanged(double mean);
    void meanVisibleChanged(bool meanVisible);
    void stdevChanged(double stdev);   
    void stdevVisibleChanged(bool stdevVisible);

private:
    std::weak_ptr<NumberDataType> m_meanInput;
    std::weak_ptr<NumberDataType> m_stdevInput;

    void validate() override;
    void compute(double mean, double stdev);

    double m_mean;
    bool m_meanVisible;
    double m_stdev;
    bool m_stdevVisible;
};

#endif // GAUSSIANIDEA_H
