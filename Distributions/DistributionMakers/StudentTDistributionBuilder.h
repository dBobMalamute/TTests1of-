#ifndef STUDENTTDISTRIBUTIONBUILDER_H
#define STUDENTTDISTRIBUTIONBUILDER_H

#include <cmath>
#include <memory>
#include "../../DataTypes/DistributionDataType.h"

#include "../Common/DistributionCommonFunctions.h"
#include <QRandomGenerator>
#include "../Common/BoostIncludes.h"

class StudentTPDF : public DistributionPDF
{
public:
    StudentTPDF(double dof):
        m_dof(dof)
    {
        m_pdfCommon = std::exp(DistributionCommonFunctions::lnGamma((dof + 1.0) / 2.0) -
                                 DistributionCommonFunctions::lnGamma(dof / 2.0)) / std::sqrt(dof * M_PI);
    }
    double evaluate(double x) override
    {
        return m_pdfCommon * std::pow((1.0 + x*x/m_dof), -0.5*(m_dof + 1));
    }

private:
    double m_pdfCommon;
    double m_dof;
};

class StudentTCDF : public DistributionCDF
{
public:
    StudentTCDF(double dof):
        m_dof(dof)
    {

    }
    double evaluate(double t) override
    {
        if(t > 0)
        {
            double x = m_dof / (t*t + m_dof);
            return 1.0 - 0.5 * incompleteBeta(m_dof/2.0, 0.5, x);
        }
        else
        {
            double x = m_dof / (t*t + m_dof);
            return 0.5 * incompleteBeta(m_dof/2.0, 0.5, x);
        }
    }

private:
    double m_dof;
};

class StudentTDistributionBuilder
{
public:
    static std::shared_ptr<DistributionDataType> makeStudentT(double dof);
};

#endif // STUDENTTDISTRIBUTIONBUILDER_H
