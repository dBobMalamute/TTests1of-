#include "GaussianDistributionIdea.h"
#include "DistributionMakers/GaussianDistributionBuilder.h"

GaussianDistributionAttributes::GaussianDistributionAttributes()
{
    m_listName = "Gaussian Distribution";
    m_displayName = "Gaussian Distribution";
    m_authors << "dBob";
    m_description = "This box creates a Gaussian distribution. The Gaussian or normal distribution is usually used "
                    "when you have limited information. It is the best distribution to use when you have a rough idea"
                    " of the mean and standard deviation, and don't want to claim anything else.";
    m_iconPath = "qrc:/Icons/GaussianDistribution.png";

    m_dataTypesIn.push_back(Magic<NumberDataTypeAttributes>::cast().id());
    m_dataTypesIn.push_back(Magic<NumberDataTypeAttributes>::cast().id());
    m_labelsIn << "Mean" << "Stdev";

    m_dataTypesOut.push_back(Magic<DistributionDataTypeAttributes>::cast().id());
    m_labelsOut << "Dist";
    m_customLabels = true;

    m_embeddedQMLPath = ":/QML/GaussianDistributionIdea.qml";
    m_minimizable = true;
    m_minimizedName = "Gaussian\nDistribution";
    m_differentNameOnMinimized = true;

    m_gear = true;

}

const IdeaAttributes GaussianDistributionIdea::attributes()
{
    return Magic<GaussianDistributionAttributes>::cast();
}

GaussianDistributionIdea::GaussianDistributionIdea() :
    m_meanVisible(false),
    m_stdevVisible(false)
{

}

void GaussianDistributionIdea::onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber plugNumber)
{
    auto number = std::dynamic_pointer_cast<NumberDataType>(dataType);
    if(plugNumber == 0)
        m_meanInput = number;
    else
        m_stdevInput = number;

    validate();
}

std::shared_ptr<DataType> GaussianDistributionIdea::dataOut(PlugNumber)
{
    return std::static_pointer_cast<DataType>(m_distribution);
}


double GaussianDistributionIdea::mean() const
{
    return m_mean;
}

double GaussianDistributionIdea::stdev() const
{
    return m_stdev;
}

bool GaussianDistributionIdea::meanVisible() const
{
    return m_meanVisible;
}

bool GaussianDistributionIdea::stdevVisible() const
{
    return m_stdevVisible;
}

void GaussianDistributionIdea::setMean(double mean)
{
    if (qFuzzyCompare(m_mean, mean))
        return;

    m_mean = mean;
    emit meanChanged(m_mean);
}

void GaussianDistributionIdea::setStdev(double stdev)
{
    if (qFuzzyCompare(m_stdev, stdev))
        return;

    m_stdev = stdev;
    emit stdevChanged(m_stdev);
}

void GaussianDistributionIdea::setMeanVisible(bool meanVisible)
{
    if (m_meanVisible == meanVisible)
        return;

    QJsonObject oldParams;
    oldParams["mv"] = m_meanVisible;

    m_meanVisible = meanVisible;
    emit meanVisibleChanged(m_meanVisible);

    QJsonObject newParams;
    newParams["mv"] = m_meanVisible;
    reportParamsChanged(oldParams, newParams);
}

void GaussianDistributionIdea::setStdevVisible(bool stdevVisible)
{
    if (m_stdevVisible == stdevVisible)
        return;

    QJsonObject oldParams;
    oldParams["sv"] = m_stdevVisible;

    m_stdevVisible = stdevVisible;
    emit stdevVisibleChanged(m_stdevVisible);

    QJsonObject newParams;
    newParams["sv"] = m_stdevVisible;
    reportParamsChanged(oldParams, newParams);
}

void GaussianDistributionIdea::validate()
{
    auto v_mean = m_meanInput.lock();
    auto v_stdev = m_stdevInput.lock();

    if(v_mean && v_stdev)
    {
        if(v_stdev->number() <= 0.0)
        {
            setStatus(IdeaStatus::Error, "Stdev <= 0", "The input standard deviation " + QString::number(v_stdev->number()) +
                      " is less than 0. ");
        }
        else
        {
            setStatus(IdeaStatus::Working, "Calculating a Gaussian", "Currently creating a Gaussian distribution with a mean of "
                      + QString::number(v_mean->number()) + " and a standard deviation of " + QString::number(v_stdev->number()));

            setMean(v_mean->number());
            setStdev(v_stdev->number());
            compute(v_mean->number(), v_stdev->number());
        }
    }
    else
    {
        setDefaultStatus();
    }
}

void GaussianDistributionIdea::compute(double mean, double stdev)
{
    emit startSpinningGear();

    m_distribution = GaussianDistributionBuilder::makeGaussian(mean, stdev);
    emit newData(0);
    if(!minimized())
        plot();

    emit stopSpinningGear();
}

QJsonObject GaussianDistributionIdea::save() const
{
    QJsonObject saveJson = DistributionTemplate::save();
    saveJson["mv"] = m_meanVisible;
    saveJson["sv"] = m_stdevVisible;

    return saveJson;
}

void GaussianDistributionIdea::load(const QJsonObject &obj)
{ 
    DistributionTemplate::load(obj);
    QJsonValue v = obj["mv"];
    if(!v.isUndefined())
    {
        m_meanVisible = v.toBool();
        emit meanVisibleChanged(m_meanVisible);
    }

    v = obj["sv"];
    if(!v.isUndefined())
    {
        m_stdevVisible = v.toBool();
        emit stdevVisibleChanged(m_stdevVisible);
    }
}

void GaussianDistributionIdea::resetDisplay()
{
    if(valid())
        plot();
}
