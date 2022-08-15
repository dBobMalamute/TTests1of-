#ifndef DISTRIBUTIONDATATYPES_H
#define DISTRIBUTIONDATATYPES_H

#include <memory>

#include "../MalamuteCore/InheritedClasses/DataType.h"

#define MEANUNDEFINED 1
#define MEDIANUNDEFINED 2
#define MODEUNDEFINED 4
#define VARIANCEUNDEFINED 8
#define SKEWUNDEFINED 16
#define KURTOSISUNDEFINED 32
#define SAMPLERSET 64
#define MEANUNSET 128
#define MEDIANUNSET 256
#define MODEUNSET 512
#define VARIANCEUNSET 1024
#define SKEWUNSET 2048
#define KURTOSISUNSET 4096

class DistributionPDF
{
public:
    virtual double evaluate(double x) = 0;
};

class DistributionCDF
{
public:
    virtual double evaluate(double x) = 0;
};

class DistributionSampler
{
public:
    virtual std::vector<double> getSamples(int n) = 0;
};

struct DistributionDataTypeAttributes : public DataTypeAttributes
{
    DistributionDataTypeAttributes();
};

class DistributionDataType : public DataType
{
public:

     enum DistributionType
     {
         Continuous,
         Discrete
     };

    DistributionDataType(DistributionType distType, QString distributionName);

    DataTypeAttributes getAttributes() override;
    DistributionType distType() const;

    long long getFlags() const;
    void setFlags(long long newFlags);

    bool meanUndefined();
    double getMean() const;
    void setMean(double value);

    bool medianUndefined();
    double getMedian() const;
    void setMedian(double value);

    bool modeUndefined();
    double getMode() const;
    void setMode(double value);

    bool varianceUndefined();
    double getVariance() const;
    void setVariance(double value);

    bool skewUndefined();
    double getSkew() const;
    void setSkew(double value);

    bool kurtosisUndefined();
    double getKurtosis() const;
    void setKurtosis(double value);

    double getDefaultXLow() const;
    void setDefaultXLow(double value);

    double getDefaultXHigh() const;
    void setDefaultXHigh(double value);

    double getSupportMin() const;
    void setSupportMin(double value);

    double getSupportMax() const;
    void setSupportMax(double value);

    bool getSupportMinSet() const;
    bool getSupportMaxSet() const;

    std::shared_ptr<DistributionPDF> pdf() const;
    void setPdf(const std::shared_ptr<DistributionPDF> &pdf);

    std::shared_ptr<DistributionCDF> cdf() const;
    void setCdf(const std::shared_ptr<DistributionCDF> &cdf);

    std::shared_ptr<DistributionSampler> sampler() const;
    void setSampler(const std::shared_ptr<DistributionSampler> &sampler);

private:
    QString m_distributionName;
    DistributionType m_distType;

    std::shared_ptr<DistributionPDF> m_pdf;
    std::shared_ptr<DistributionCDF> m_cdf;
    std::shared_ptr<DistributionSampler> m_sampler;

    long long m_flags;
    double mean;
    double median;
    double mode;
    double variance;
    double skew;
    double kurtosis;

    double defaultXLow;
    double defaultXHigh;

    double supportMin;
    double supportMax;

    bool supportMinSet = false;
    bool supportMaxSet = false;
};

#endif
