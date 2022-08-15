#ifndef GAUSSIANDISTRIBUTIONBUILDER_H
#define GAUSSIANDISTRIBUTIONBUILDER_H

#include <cmath>
#include <memory>
#include "../../DataTypes/DistributionDataType.h"
#include <QRandomGenerator>
#include "../Common/BoostIncludes.h"

class GaussianPDF : public DistributionPDF
{
public:
    GaussianPDF(double mean, double stdev):
        m_mean(mean),
        m_stdev(stdev)
    {

    }
    double evaluate(double x) override
    {
        double temp = (x-m_mean) / m_stdev;
        return  std::exp(-0.5 * temp * temp) / (m_stdev * std::sqrt(2.0 * M_PI));
    }

private:
    double m_mean;
    double m_stdev;
};

class GaussianCDF : public DistributionCDF
{
public:
    GaussianCDF(double mean, double stdev):
        m_mean(mean),
        m_stdev(stdev)
    {

    }
    double evaluate(double x) override
    {
        return 0.5 * (1.0 + errorFunction((x - m_mean) / m_stdev / M_SQRT2));
    }

private:
    double m_mean;
    double m_stdev;
};

class GaussianSampler : public DistributionSampler
{
public:
    GaussianSampler(double mean, double stdev) :
        m_mean(mean),
        m_stdev(stdev)
    {

    }
    std::vector<double> getSamples(int n) override
    {
        std::vector<double> samples;
        samples.reserve(n);

        for(int i = 0; i < n; i++)
        {
            double rand = QRandomGenerator::global()->generateDouble();
            samples.push_back(-1.0*M_SQRT2 * m_stdev *inverseErrorFunction(2.0 * rand - 1.0) + m_mean);
        }
        return samples;
    }

private:
    double m_mean;
    double m_stdev;
};

class GaussianDistributionBuilder
{
public:
    static std::shared_ptr<DistributionDataType> makeGaussian(double mean, double stdev);
};

#endif // GAUSSIANDISTRIBUTIONBUILDER_H
