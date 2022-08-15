#include "DistributionCommonFunctions.h"

double DistributionCommonFunctions::lnGamma(double v)
{
    // Lanczos C. 1964. A precision approximation of the gamma function.
    double temp; double y; double ser;

    static const double cof[14] = {57.1562356658629235, -59.5979603554754912,
                                  14.1360979747417471, -0.491913816097620199, .339946499848118887e-4,
                                  .465236289270485756e-4, -.983744753048795646e-4, .158088703224912494e-3,
                                  -.210264441724104883e-3, .21743961811521264e-3, -.164318106536762890e-3,
                                  .844182239838527433e-4, -.261908384015814087e-4, .368991826595316234e-5};
    y = v;
    temp = v + 5.2421875;
    temp = (0.5 + v) * std::log(temp) - temp;
    ser = 0.99999999999999702;
    for(int i = 0; i < 14; i++)
        ser += cof[i] / (y + i + 1);

    return temp + std::log(2.5066282746310005 * ser / v);
}

double DistributionCommonFunctions::findPointForValueContinuous(std::shared_ptr<DistributionDataType> ddt, double goalValue, double low, double high)
{
    double lowBound = low;
    double highBound = high;
    double lowValue = ddt->cdf()->evaluate(lowBound);
    double highValue = ddt->cdf()->evaluate(highBound);

    if(goalValue < lowValue)
        return lowValue;
    if(goalValue > highValue)
        return highValue;

    double tolerance = 1e-10;

    double slope = (highValue - lowValue) / (highBound - lowBound);
    double searchPoint = (goalValue - lowValue) / slope;
    double searchValue = ddt->cdf()->evaluate(searchPoint);

    int loopMax = 500;
    int numLoops = 0;
    while(qAbs(searchValue - goalValue) > tolerance)
    {
        numLoops++;
        if(numLoops > loopMax)
            break;
        if(searchValue < goalValue)
        {
            lowBound = searchPoint;
            lowValue = searchValue;
        }
        else
        {
            highBound = searchPoint;
            highValue = searchValue;
        }

        searchPoint = (lowBound+highBound) / 2.0;
        searchValue = ddt->cdf()->evaluate(searchPoint);
    }

    return searchPoint;
}

double DistributionCommonFunctions::findPointForValueContinuous(std::shared_ptr<DistributionDataType> ddt, double goalValue, double low, double lowCDFVal, double high, double highCDFVal)
{
    double lowBound = low;
    double highBound = high;
    double lowValue = lowCDFVal;
    double highValue = highCDFVal;

    if(goalValue < lowValue)
        return lowValue;
    if(goalValue > highValue)
        return highValue;

    double tolerance = 1e-10;

    double slope = (highValue - lowValue) / (highBound - lowBound);
    double searchPoint = (goalValue - lowValue) / slope;
    double searchValue = ddt->cdf()->evaluate(searchPoint);

    int loopMax = 500;
    int numLoops = 0;
    while(qAbs(searchValue - goalValue) > tolerance)
    {
        numLoops++;
        if(numLoops > loopMax)
            break;
        if(searchValue < goalValue)
        {
            lowBound = searchPoint;
            lowValue = searchValue;
        }
        else
        {
            highBound = searchPoint;
            highValue = searchValue;
        }

        searchPoint = (lowBound+highBound) / 2.0;
        searchValue = ddt->cdf()->evaluate(searchPoint);
    }

    return searchPoint;
}

std::vector<double> DistributionCommonFunctions::distributionSectionsContinuous(std::shared_ptr<DistributionDataType> dfs, int numSections, double low, double high)
{
    std::vector<double> goals;
    goals.reserve(numSections - 1);

    for(int i = 1; i < numSections ; i++)
        goals.push_back(1.0*i / numSections);

    std::vector<double> sectionPoints;
    sectionPoints.reserve(numSections - 1);
    sectionPoints.push_back(findPointForValueContinuous(dfs, goals.at(0), low, high));

    for(int i = 1; i < numSections - 1; i++)
        sectionPoints.push_back(findPointForValueContinuous(dfs, goals.at(i), sectionPoints.at(i-1), high));

    return sectionPoints;
}

std::vector<double> DistributionCommonFunctions::visualBoundDistributionSectionsContinuous(std::shared_ptr<DistributionDataType> ddt, int numSections)
{
    std::vector<double> result;
    result.reserve(numSections+1);

    double stdev = std::sqrt(ddt->getVariance());
    double mean = ddt->getMean();

    double visualLow;
    double visualHigh;

    if(ddt->getSupportMinSet())
        visualLow = ddt->getSupportMin();
    else
    {
        if(ddt->getFlags() & VARIANCEUNDEFINED || !qIsFinite(stdev))
            visualLow = 10.0 * DistributionCommonFunctions::findPointBelowPercentileContinuous(ddt, 1.0/numSections, -1.0);
        else
            visualLow = mean - 15*stdev;
    }
    if(ddt->getSupportMaxSet())
        visualHigh = ddt->getSupportMax();
    else
    {
        if(ddt->getFlags() & VARIANCEUNDEFINED || !qIsFinite(stdev))
            visualHigh = 10.0 * DistributionCommonFunctions::findPointAbovePercentileContinuous(ddt, (numSections - 1.0) / numSections, 1.0);
        else
            visualHigh = mean + 15*stdev;
    }

    result.push_back(visualLow);
    std::vector<double> temp = distributionSectionsContinuous(ddt, numSections, visualLow, visualHigh);
    result.insert(result.end(), temp.begin(), temp.end());
    result.push_back(visualHigh);

    return result;
}

double DistributionCommonFunctions::findPointAbovePercentileContinuous(std::shared_ptr<DistributionDataType> ddt, double percentile, double start)
{
    if(start < 0.0)
        qFatal("findPointAbovePercentile, guess is below 0");

    double guess = start;
    while(ddt->cdf()->evaluate(guess) < percentile)
        guess *= 2.0;

    return guess;
}

double DistributionCommonFunctions::findPointBelowPercentileContinuous(std::shared_ptr<DistributionDataType> ddt, double percentile, double start)
{
    if(start > 0.0)
        qFatal("findPointBelowPercentile, guess is above 0");

    double guess = start;
    while(ddt->cdf()->evaluate(guess) > percentile)
        guess *= 2.0;

    return guess;
}

double DistributionCommonFunctions::findPointForValueDiscrete(std::shared_ptr<DistributionDataType> ddt, double goalValue, int low, int high)
{
    int lowBound = low;
    int highBound = high;
    double lowValue = ddt->cdf()->evaluate(lowBound);
    double highValue = ddt->cdf()->evaluate(highBound);

    if(goalValue < lowValue)
        return lowValue;
    if(goalValue > highValue)
        return highValue;

    double slope = (highValue - lowValue) / (highBound - lowBound);
    int searchPoint = std::floor((goalValue - lowValue) / slope);
    double searchValueBelow = ddt->cdf()->evaluate(searchPoint);
    double searchValueAbove = ddt->cdf()->evaluate(searchPoint + 1);

    int loopMax = 500;
    int numLoops = 0;
    while(!(searchValueBelow < goalValue && searchValueAbove >= goalValue))
    {
        numLoops++;
        if(numLoops > loopMax)
            break;
        if(searchValueBelow < goalValue)
        {
            lowBound = searchPoint;
            lowValue = searchValueBelow;
        }
        else
        {
            highBound = searchPoint;
            highValue = searchValueBelow;
        }

        searchPoint = std::floor((lowBound+highBound) / 2.0);
        searchValueBelow = ddt->cdf()->evaluate(searchPoint);
        searchValueAbove = ddt->cdf()->evaluate(searchPoint + 1);
    }

    return searchPoint;
}

ConnectedPlot DistributionCommonFunctions::makeContinuousConnectedPlot(std::shared_ptr<DistributionDataType> distribution, double gridWidth, double gridHeight,
                                                             double displayXLow, double displayXHigh,
                                                             double displayYLow, double displayYHigh,
                                                             double plotXLow, double plotXHigh)
{
    double displayXLength = displayXHigh - displayXLow;

    double low = plotXLow;
    if(low < displayXLow) //Don't plot if the area isn't visible.
        low = displayXLow - 0.01*displayXLength;
    if(distribution->getSupportMinSet()) //Don't plot below the minimum of the support
        low = qMax(distribution->getSupportMin(), low);

    double high = plotXHigh;
    if(high > displayXHigh)
        high = displayXHigh + 0.01*displayXLength;
    if(distribution->getSupportMaxSet()) //Don't plot above the max of the support.
        high = qMin(distribution->getSupportMax(), high);

    int pointsDrawn = std::ceil(450 * (high - low) / displayXLength);
    if(pointsDrawn <= 0)
    {
        return ConnectedPlot(std::vector<double>(), std::vector<double>());
    }

    double plotXLength = high - low;

    // Get raw yVectors.
    std::vector<double> yRaw;
    yRaw.reserve(pointsDrawn);
    for(int i = 0; i < pointsDrawn; i++)
    {
        double x = low + plotXLength * i / (pointsDrawn - 1.0);
        yRaw.push_back(distribution->pdf()->evaluate(x));
    }

    double displayYLength = displayYHigh - displayYLow;

    //Prepare export containers.
    std::vector<double> xPos;
    std::vector<double> yPos;
    if(distribution->getSupportMaxSet())
    {
        xPos.reserve(pointsDrawn + 2);
        yPos.reserve(pointsDrawn + 2);
    }
    else
    {
        xPos.reserve(pointsDrawn + 1);
        yPos.reserve(pointsDrawn + 1);
    }

    double xStart = (low - displayXLow) / displayXLength;
    double xEnd = (high - displayXLow) / displayXLength;
    double xLen = xEnd - xStart;
    for(int i = 0; i < pointsDrawn; i++)
    {
        xPos.push_back(gridWidth * (xStart + xLen * i / (pointsDrawn - 1)));
        yPos.push_back(gridHeight - (gridHeight * (yRaw.at(i) - displayYLow) / displayYLength));
    }
    if(distribution->getSupportMaxSet())
    {
        xPos.push_back(gridWidth * (xStart + xLen));
        yPos.push_back(gridHeight);
    }

    //Add a point for the mode if the mode is defined.
    if(!(distribution->getFlags() & MODEUNDEFINED))
    {
        double mode = distribution->getMode();
        double xPosMode = gridWidth * (mode - displayXLow) / (displayXLength);

        // See if the mode is within the range.
        if(xPosMode > xPos[0] && xPosMode < xPos.back())
        {
            double yValueAtMode = gridHeight - gridHeight * (distribution->pdf()->evaluate(mode) - displayYLow)
                    / displayYLength;

            auto indexToAddAt = std::lower_bound(xPos.begin(), xPos.end(), xPosMode);
            xPos.insert(indexToAddAt, xPosMode);
            yPos.insert(yPos.begin() + std::distance(xPos.begin(), indexToAddAt), yValueAtMode);
        }
    }

    return ConnectedPlot(xPos, yPos);
}

ConnectedPlot DistributionCommonFunctions::makeContinuousConnectedCDFPlot(std::shared_ptr<DistributionDataType> distribution, double gridWidth, double gridHeight, double displayXLow, double displayXHigh, double displayYLow, double displayYHigh, double plotXLow, double plotXHigh)
{
    double displayXLength = displayXHigh - displayXLow;

    double low = plotXLow;
    if(low < displayXLow) //Don't plot if the area isn't visible.
        low = displayXLow - 0.01*displayXLength;
    if(distribution->getSupportMinSet()) //Don't plot below the minimum of the support
        low = qMax(distribution->getSupportMin(), low);

    double high = plotXHigh;
    if(high > displayXHigh)
        high = displayXHigh + 0.01*displayXLength;
    if(distribution->getSupportMaxSet()) //Don't plot above the max of the support.
        high = qMin(distribution->getSupportMax(), high);

    int pointsDrawn = std::ceil(450 * (high - low) / displayXLength);
    if(pointsDrawn <= 0)
    {
        return ConnectedPlot(std::vector<double>(), std::vector<double>());
    }

    double plotXLength = high - low;

    // Get raw yVectors.
    std::vector<double> yRaw;
    yRaw.reserve(pointsDrawn);
    for(int i = 0; i < pointsDrawn; i++)
    {
        double x = low + plotXLength * i / (pointsDrawn - 1.0);
        yRaw.push_back(distribution->cdf()->evaluate(x));
    }

    double displayYLength = displayYHigh - displayYLow;

    //Prepare export containers.
    std::vector<double> xPos;
    std::vector<double> yPos;
    xPos.reserve(pointsDrawn + 1);
    yPos.reserve(pointsDrawn + 1);

    double xStart = (low - displayXLow) / displayXLength;
    double xEnd = (high - displayXLow) / displayXLength;
    double xLen = xEnd - xStart;
    for(int i = 0; i < pointsDrawn; i++)
    {
        xPos.push_back(gridWidth * (xStart + xLen * i / (pointsDrawn - 1)));
        yPos.push_back(gridHeight - (gridHeight * (yRaw.at(i) - displayYLow) / displayYLength));
    }

    return ConnectedPlot(xPos, yPos);
}

ConnectedPlot DistributionCommonFunctions::makeDiscretePDFConnectedPlot(std::shared_ptr<DistributionDataType> distribution, double gridWidth, double gridHeight, double displayXLow, double displayXHigh, double displayYLow, double displayYHigh, double plotXLow, double plotXHigh)
{
    double displayXLength = displayXHigh - displayXLow;

    double low = plotXLow;
    if(low < displayXLow) //Don't plot if the area isn't visible.
        low = displayXLow - 0.01*displayXLength;
    if(distribution->getSupportMinSet()) //Don't plot below the minimum of the support
        low = qMax(distribution->getSupportMin(), low);

    double high = plotXHigh;
    if(high > displayXHigh)
        high = displayXHigh + 0.01*displayXLength;
    if(distribution->getSupportMaxSet()) //Don't plot above the max of the support.
        high = qMin(distribution->getSupportMax(), high);

    //Make sure the plot bounds are integers.
    low = std::floor(low);
    high = std::ceil(high);

    int pointsDrawn = static_cast<int>(high - low) + 1;
    if(pointsDrawn <= 0)
    {
        return ConnectedPlot(std::vector<double>(), std::vector<double>());
    }

    //Convenience.
    double xLength = high - low;

    // Get raw yVectors.
    std::vector<double> yRaw;
    yRaw.reserve(pointsDrawn);
    for(int i = 0; i < pointsDrawn; i++)
    {
        double x = low + xLength * i / (pointsDrawn - 1.0);
        yRaw.push_back(distribution->pdf()->evaluate(x));
    }

    double yLength = displayYHigh - displayYLow;
    //Prepare temporary containers.
    std::vector<double> xPos;
    std::vector<double> yPos;
    xPos.reserve(pointsDrawn);
    yPos.reserve(pointsDrawn);

    double xStart = (low - displayXLow) / displayXLength;
    double xEnd = (high - displayXLow) / displayXLength;
    double xLen = xEnd - xStart;

    for(int i = 0; i < pointsDrawn; i++)
    {
        xPos.push_back(gridWidth * (xStart + xLen * i / (pointsDrawn - 1)));
        yPos.push_back(gridHeight - (gridHeight * (yRaw.at(i) - displayYLow) / yLength));
    }
    return ConnectedPlot(xPos, yPos);
}

ConnectedPlot DistributionCommonFunctions::makeDiscreteCDFConnectedPlot(std::shared_ptr<DistributionDataType> distribution, double gridWidth, double gridHeight,
                                                                     double displayXLow, double displayXHigh, double displayYLow, double displayYHigh, double plotXLow, double plotXHigh)
{
    double low = plotXLow;
    if(low < displayXLow) //Don't plot if the area isn't visible.
        low = displayXLow - 0.5;
    if(distribution->getSupportMinSet()) //Don't plot below the minimum of the support
        low = qMax(distribution->getSupportMin() - 0.5, low);
    low = std::floor(low + 1.0);

    double high = plotXHigh;
    if(high > displayXHigh)
        high = displayXHigh;
    if(distribution->getSupportMaxSet()) //Don't plot above the max of the support.
        high = qMin(distribution->getSupportMax(), high);
    high = std::floor(high + 1.0);

    int pointsDrawn = static_cast<int>(high - low);
    //Convenience.
    double xLength = high - low;

    // Get raw yVectors.
    std::vector<double> yRaw;
    yRaw.reserve(pointsDrawn);

    //Edge case to avoid div by 0 if only one point.
    if(pointsDrawn == 1)
        yRaw.push_back(distribution->pdf()->evaluate(low));
    else
    {
        for(int i = 0; i < pointsDrawn; i++)
        {
            double x = low + xLength * i / (pointsDrawn);
            yRaw.push_back(distribution->pdf()->evaluate(x));
        }
    }

    double displayYLength = displayYHigh - displayYLow;
    double displayXLength = displayXHigh - displayXLow;

    //Prepare temporary containers.
    std::vector<double> xPos;
    std::vector<double> yPos;
    xPos.reserve(2*pointsDrawn);
    yPos.reserve(2*pointsDrawn);

    double xStart = (low - displayXLow) / displayXLength;
    double xEnd = (high - displayXLow) / displayXLength;
    double xLen = xEnd - xStart;

    if(pointsDrawn == 1) // Edge case only one point.
    {
        xPos.push_back(gridWidth * (xStart));
        xPos.push_back(gridWidth * (xStart + 1.0/displayXLength));
        yPos.push_back(gridHeight - (gridHeight * (yRaw.at(0) - displayYLow) / displayYLength));
        yPos.push_back(gridHeight - (gridHeight * (yRaw.at(0) - displayYLow) / displayYLength));
    }
    else
    {
        for(int i = 0; i < pointsDrawn; i++)
        {
            xPos.push_back(gridWidth * (xStart + xLen * i / (1.0*pointsDrawn)));
            xPos.push_back(gridWidth * (xStart + xLen * (i+1) / (1.0*pointsDrawn)));
            yPos.push_back(gridHeight - (gridHeight * (yRaw.at(i) - displayYLow) / displayYLength));
            yPos.push_back(gridHeight - (gridHeight * (yRaw.at(i) - displayYLow) / displayYLength));
        }
    }
    return ConnectedPlot(xPos, yPos);
}

ConnectedPlot DistributionCommonFunctions::makeDiscreteConnectedCDFPlot(std::shared_ptr<DistributionDataType> distribution, double gridWidth, double gridHeight, double displayXLow, double displayXHigh, double displayYLow, double displayYHigh, double plotXLow, double plotXHigh)
{
    double displayXLength = displayXHigh - displayXLow;

    double low = plotXLow;
    if(low < displayXLow) //Don't plot if the area isn't visible.
        low = displayXLow - 0.01*displayXLength;
    if(distribution->getSupportMinSet()) //Don't plot below the minimum of the support
        low = qMax(distribution->getSupportMin(), low);

    double high = plotXHigh;
    if(high > displayXHigh)
        high = displayXHigh + 0.01*displayXLength;
    if(distribution->getSupportMaxSet()) //Don't plot above the max of the support.
        high = qMin(distribution->getSupportMax(), high);

    //Make sure the plot bounds are integers.
    low = std::floor(low);
    high = std::ceil(high);

    int pointsDrawn = static_cast<int>(high - low) + 1;
    if(pointsDrawn <= 0)
    {
        return ConnectedPlot(std::vector<double>(), std::vector<double>());
    }

    //Convenience.
    double xLength = high - low;

    // Get raw yVectors.
    std::vector<double> yRaw;
    yRaw.reserve(pointsDrawn);
    for(int i = 0; i < pointsDrawn; i++)
    {
        double x = low + xLength * i / (pointsDrawn - 1.0);
        yRaw.push_back(distribution->cdf()->evaluate(x));
    }

    double yLength = displayYHigh - displayYLow;
    //Prepare temporary containers.
    std::vector<double> xPos;
    std::vector<double> yPos;
    xPos.reserve(pointsDrawn);
    yPos.reserve(pointsDrawn);

    double xStart = (low - displayXLow) / displayXLength;
    double xEnd = (high - displayXLow) / displayXLength;
    double xLen = xEnd - xStart;

    for(int i = 0; i < pointsDrawn; i++)
    {
        xPos.push_back(gridWidth * (xStart + xLen * i / (pointsDrawn - 1)));
        yPos.push_back(gridHeight - (gridHeight * (yRaw.at(i) - displayYLow) / yLength));
    }
    return ConnectedPlot(xPos, yPos);
}

double DistributionCommonFunctions::findYMax(std::shared_ptr<DistributionDataType> distribution, double displayXLow, double displayXHigh)
{
    double displayXLength = displayXHigh - displayXLow;

    double low = displayXLow - 0.01*displayXLength;
    if(distribution->getSupportMinSet()) //Don't plot below the minimum of the support
        low = qMax(distribution->getSupportMin(), low);

    double high = displayXHigh + 0.01*displayXLength;
    if(distribution->getSupportMaxSet()) //Don't plot above the max of the support.
        high = qMin(distribution->getSupportMax(), high);

    int pointsDrawn = std::ceil(450 * (high - low) / displayXLength);
    double plotXLength = high - low;

    // Get raw yVectors.
    std::vector<double> yRaw;
    yRaw.reserve(pointsDrawn);
    for(int i = 0; i < pointsDrawn; i++)
    {
        double x = low + plotXLength * i / (pointsDrawn - 1.0);
        yRaw.push_back(distribution->pdf()->evaluate(x));
    }

    double yMax = -1.0;
    for(size_t i = 0; i < yRaw.size(); i++)
    {
        if(yRaw.at(i) > yMax && qIsFinite(yRaw.at(i)))
            yMax = yRaw.at(i);
    }
    return yMax;
}

std::vector<double> ConnectedPlot::xValues() const
{
    return m_xValues;
}


std::vector<double> ConnectedPlot::yValues() const
{
    return m_yValues;
}
