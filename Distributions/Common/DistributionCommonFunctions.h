#ifndef DISTRIBUTIONCOMMONFUNCTIONS_H
#define DISTRIBUTIONCOMMONFUNCTIONS_H

#include "../../DataTypes/DistributionDataType.h"
#include <cmath>

struct ConnectedPlot
{
public:
    ConnectedPlot()
    {

    }
    ConnectedPlot(std::vector<double> xValues, std::vector<double> yValues) :
        m_xValues(xValues),
        m_yValues(yValues)
    {

    }
    std::vector<double> xValues() const;
    std::vector<double> yValues() const;

private:
    std::vector<double> m_xValues;
    std::vector<double> m_yValues;
};

class DistributionCommonFunctions
{
public:
    static double lnGamma(double v);

    static double findPointForValueContinuous(std::shared_ptr<DistributionDataType>, double goalValue,
                                              double low, double high);
    static double findPointForValueContinuous(std::shared_ptr<DistributionDataType>, double goalValue,
                                              double low, double lowCDFVal, double high, double highCDFVal);

    static std::vector<double> distributionSectionsContinuous(std::shared_ptr<DistributionDataType>, int numSections, double low, double high);
    static std::vector<double> visualBoundDistributionSectionsContinuous(std::shared_ptr<DistributionDataType>, int numSections);

    static double findPointAbovePercentileContinuous(std::shared_ptr<DistributionDataType>, double percentile, double start);
    static double findPointBelowPercentileContinuous(std::shared_ptr<DistributionDataType>, double percentile, double start);

    static double findPointForValueDiscrete(std::shared_ptr<DistributionDataType>, double goalValue, int low, int high);

    static ConnectedPlot makeContinuousConnectedPlot(std::shared_ptr<DistributionDataType> distribution,
                                                     double gridWidth, double gridHeight,
                                                     double displayXLow, double displayXHigh,
                                                     double displayYLow, double displayYHigh,
                                                     double plotXLow, double plotXHigh);

    static ConnectedPlot makeContinuousConnectedCDFPlot(std::shared_ptr<DistributionDataType> distribution,
                                                     double gridWidth, double gridHeight,
                                                     double displayXLow, double displayXHigh,
                                                     double displayYLow, double displayYHigh,
                                                     double plotXLow, double plotXHigh);

    static ConnectedPlot makeDiscretePDFConnectedPlot(std::shared_ptr<DistributionDataType> distribution,
                                                   double gridWidth, double gridHeight,
                                                   double displayXLow, double displayXHigh,
                                                   double displayYLow, double displayYHigh,
                                                   double plotXLow, double plotXHigh);

    static ConnectedPlot makeDiscreteCDFConnectedPlot(std::shared_ptr<DistributionDataType> distribution,
                                                   double gridWidth, double gridHeight,
                                                   double displayXLow, double displayXHigh,
                                                   double displayYLow, double displayYHigh,
                                                   double plotXLow, double plotXHigh);

    static ConnectedPlot makeDiscreteConnectedCDFPlot(std::shared_ptr<DistributionDataType> distribution,
                                                     double gridWidth, double gridHeight,
                                                     double displayXLow, double displayXHigh,
                                                     double displayYLow, double displayYHigh,
                                                     double plotXLow, double plotXHigh);

    static double findYMax (std::shared_ptr<DistributionDataType> distribution,
                            double displayXLow, double displayXHigh);
};

#endif // DISTRIBUTIONCOMMONFUNCTIONS_H
