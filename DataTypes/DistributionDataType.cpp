#include "DistributionDataType.h"

DistributionDataTypeAttributes::DistributionDataTypeAttributes()
{
    m_name = "Continuous Distribution";
    m_color = "#095bb5";
    m_abbreviation = "Dist";
    m_description = "This data types holds a continuous distribution represented as a two dimensional set of numbers.";
    m_authors << "dBob";

    m_defaultDisplay = "Distribution Display";
    m_defaultSource = "Gaussian Distribution";
}

DataTypeAttributes DistributionDataType::getAttributes()
{
    return Magic<DistributionDataTypeAttributes>::cast();
}

DistributionDataType::DistributionDataType(DistributionType distType, QString distributionName) :
    m_distributionName(distributionName),
    m_distType(distType),
    m_flags(0)
{

}

DistributionDataType::DistributionType DistributionDataType::distType() const
{
    return m_distType;
}

long long DistributionDataType::getFlags() const
{
    return m_flags;
}

void DistributionDataType::setFlags(long long newFlags)
{
    m_flags |= newFlags;
}

bool DistributionDataType::meanUndefined()
{
    return m_flags & MEANUNDEFINED;
}

double DistributionDataType::getMean() const
{
    return mean;
}

void DistributionDataType::setMean(double value)
{
    mean = value;
}

bool DistributionDataType::medianUndefined()
{
    return m_flags & MEDIANUNDEFINED;
}

double DistributionDataType::getMedian() const
{
    return median;
}

void DistributionDataType::setMedian(double value)
{
    median = value;
}

bool DistributionDataType::modeUndefined()
{
    return m_flags & MODEUNDEFINED;
}

double DistributionDataType::getMode() const
{
    return mode;
}

void DistributionDataType::setMode(double value)
{
    mode = value;
}

bool DistributionDataType::varianceUndefined()
{
    return m_flags & VARIANCEUNDEFINED;
}

double DistributionDataType::getVariance() const
{
    return variance;
}

void DistributionDataType::setVariance(double value)
{
    variance = value;
}

bool DistributionDataType::skewUndefined()
{
    return m_flags & SKEWUNDEFINED;
}

double DistributionDataType::getSkew() const
{
    return skew;
}

void DistributionDataType::setSkew(double value)
{
    skew = value;
}

bool DistributionDataType::kurtosisUndefined()
{
    return m_flags & KURTOSISUNDEFINED;
}

double DistributionDataType::getKurtosis() const
{
    return kurtosis;
}

void DistributionDataType::setKurtosis(double value)
{
    kurtosis = value;
}

double DistributionDataType::getDefaultXLow() const
{
    return defaultXLow;
}

void DistributionDataType::setDefaultXLow(double value)
{
    defaultXLow = value;
}

double DistributionDataType::getDefaultXHigh() const
{
    return defaultXHigh;
}

void DistributionDataType::setDefaultXHigh(double value)
{
    defaultXHigh = value;
}

double DistributionDataType::getSupportMin() const
{
    return supportMin;
}

void DistributionDataType::setSupportMin(double value)
{
    supportMinSet = true;
    supportMin = value;
}

double DistributionDataType::getSupportMax() const
{
    return supportMax;
}

void DistributionDataType::setSupportMax(double value)
{
    supportMaxSet = true;
    supportMax = value;
}

bool DistributionDataType::getSupportMinSet() const
{
    return supportMinSet;
}

bool DistributionDataType::getSupportMaxSet() const
{
    return supportMaxSet;
}

std::shared_ptr<DistributionPDF> DistributionDataType::pdf() const
{
    return m_pdf;
}

void DistributionDataType::setPdf(const std::shared_ptr<DistributionPDF> &pdf)
{
    m_pdf = pdf;
}

std::shared_ptr<DistributionCDF> DistributionDataType::cdf() const
{
    return m_cdf;
}

void DistributionDataType::setCdf(const std::shared_ptr<DistributionCDF> &cdf)
{
    m_cdf = cdf;
}

std::shared_ptr<DistributionSampler> DistributionDataType::sampler() const
{
    return m_sampler;
}

void DistributionDataType::setSampler(const std::shared_ptr<DistributionSampler> &sampler)
{
    m_flags |= SAMPLERSET;
    m_sampler = sampler;
}

