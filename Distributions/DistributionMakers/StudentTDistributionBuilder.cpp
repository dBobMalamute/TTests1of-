#include "StudentTDistributionBuilder.h"


std::shared_ptr<DistributionDataType> StudentTDistributionBuilder::makeStudentT(double dof)
{
    std::shared_ptr<DistributionDataType> studentTDist =
            std::make_shared<DistributionDataType>(DistributionDataType::Continuous, "StudentT");

    studentTDist->setMean(0);
    studentTDist->setMedian(0);
    studentTDist->setMode(0);
    if(dof > 2)
        studentTDist->setVariance(dof / (dof - 2.0));
    else
        studentTDist->setFlags(VARIANCEUNDEFINED);
    if(dof > 3)
        studentTDist->setSkew(0.0);
    else
        studentTDist->setFlags(SKEWUNDEFINED);
    if(dof > 4)
        studentTDist->setKurtosis(3.0 + 6.0 / (dof - 4.0));
    else
        studentTDist->setFlags(KURTOSISUNDEFINED);
    studentTDist->setDefaultXLow(-5);
    studentTDist->setDefaultXHigh(5);

    studentTDist->setPdf(std::make_shared<StudentTPDF>(dof));;
    studentTDist->setCdf(std::make_shared<StudentTCDF>(dof));;

    return studentTDist;
}
