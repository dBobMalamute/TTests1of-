#include "GaussianDistributionBuilder.h"


std::shared_ptr<DistributionDataType> GaussianDistributionBuilder::makeGaussian(double mean, double stdev)
{
    std::shared_ptr<DistributionDataType> gaussianDist =
            std::make_shared<DistributionDataType>(DistributionDataType::Continuous, "Gaussian");

    gaussianDist->setMean(mean);
    gaussianDist->setMedian(mean);
    gaussianDist->setMode(mean);
    gaussianDist->setVariance(stdev * stdev);
    gaussianDist->setSkew(0.0);
    gaussianDist->setKurtosis(3.0);
    gaussianDist->setDefaultXLow(mean - 6.0 * stdev);
    gaussianDist->setDefaultXHigh(mean + 6.0 * stdev);

    gaussianDist->setPdf(std::make_shared<GaussianPDF>(mean, stdev));
    gaussianDist->setCdf(std::make_shared<GaussianCDF>(mean, stdev));
    gaussianDist->setSampler(std::make_shared<GaussianSampler>(mean, stdev));

    return gaussianDist;
}
