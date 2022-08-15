#include "DagumDistributionIdea.h"

class DagumPDF : public DistributionPDF
{
public:
    DagumPDF(double shape1, double shape2, double scale):
        m_shape1(shape1),
        m_shape2(shape2),
        m_scale(scale)
    {

    }
    double evaluate(double x) override
    {
        if(x < 0)
            return 0;

        return m_shape1*m_shape2 / x * (std::pow(x/m_scale, m_shape1*m_shape2)) /
                std::pow(std::pow(x/m_scale, m_shape2) + 1.0 , m_shape1 + 1.0);
    }
private:
    double m_shape1;
    double m_shape2;
    double m_scale;
};

class DagumCDF : public DistributionCDF
{
public:
    DagumCDF(double shape1, double shape2, double scale):
        m_shape1(shape1),
        m_shape2(shape2),
        m_scale(scale)
    {

    }

    double evaluate(double x) override
    {
        if(x < 0)
            return 0;

        return std::pow(1.0 + std::pow(x/m_scale, -1.0*m_shape2) , -1.0*m_shape1);
    }

private:
    double m_shape1;
    double m_shape2;
    double m_scale;
};

DagumDistributionAttributes::DagumDistributionAttributes()
{
    m_listName = "Dagum Distribution";
    m_displayName = "Dagum Distribution";
    m_authors << "dBob";
    m_description = "This box creates a Dagum distribution.";
    m_iconPath = "qrc:/Icons/DagumDistribution.png";

    m_dataTypesIn.push_back(Magic<NumberDataTypeAttributes>::cast().id());
    m_dataTypesIn.push_back(Magic<NumberDataTypeAttributes>::cast().id());
    m_dataTypesIn.push_back(Magic<NumberDataTypeAttributes>::cast().id());
    m_labelsIn << "Shape1" << "Shape2" << "Rate";

    m_dataTypesOut.push_back(Magic<DistributionDataTypeAttributes>::cast().id());
    m_labelsOut << "Dist";
    m_customLabels = true;

    m_embeddedQMLPath = ":/QML/DagumDistributionIdea.qml";
    m_minimizable = true;
    m_differentNameOnMinimized = true;
    m_minimizedName = "Dagum\nDistribution";

    m_gear = true;
}

const IdeaAttributes DagumDistributionIdea::attributes()
{
    return Magic<DagumDistributionAttributes>::cast();
}

DagumDistributionIdea::DagumDistributionIdea()

{
}

void DagumDistributionIdea::onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber plugNumber)
{
    auto number = std::dynamic_pointer_cast<NumberDataType>(dataType);
    if(plugNumber == 0)
        m_shapeInput1 = number;
    else if(plugNumber == 1)
        m_shapeInput2 = number;
    else
        m_scaleInput = number;

    validate();
}

std::shared_ptr<DataType> DagumDistributionIdea::dataOut(PlugNumber)
{
    return std::static_pointer_cast<DataType>(m_distribution);
}

void DagumDistributionIdea::resetDisplay()
{
    if(valid())
        plot();
}

void DagumDistributionIdea::validate()
{
    auto v_shape1 = m_shapeInput1.lock();
    auto v_shape2 = m_shapeInput2.lock();
    auto v_scale = m_scaleInput.lock();

    if(v_shape1 && v_shape2 && v_scale)
    {
        if(v_shape1->number() <= 0.0)
        {
            setStatus(IdeaStatus::Error, "Shape1 <= 0", "The input shape1 " + QString::number(v_shape1->number()) + " is less than 0. This is undefined");

        }
        else if(v_shape2->number() <= 0.0)
        {
            setStatus(IdeaStatus::Error, "Shape2 <= 0", "The input shape2 " + QString::number(v_shape2->number()) + " is less than 0. This is undefined");

        }
        else if(v_scale->number() <= 0.0)
        {
            setStatus(IdeaStatus::Error, "Scale <= 0", "The input scale " + QString::number(v_scale->number()) + " is less than 0. This is undefined");
        }
        else
        {
            setStatus(IdeaStatus::Working, "Calculating a Dagum Distribution", "Currently creating a Dagum distribution");

            compute(v_shape1->number(), v_shape2->number(), v_scale->number());
        }
    }
    else
    {
        setDefaultStatus();
    }
}

void DagumDistributionIdea::compute(double shape1, double shape2, double scale)
{
    emit startSpinningGear();

    m_distribution = std::make_shared<DistributionDataType>(DistributionDataType::Continuous, "Dagum");

    if(shape2 > 1.0)
    {
        m_distribution->setMean(-scale/shape2 * gammaFunction(-1.0/shape2) * gammaFunction(1.0/shape2 + shape1)
                                / gammaFunction(shape1));
        m_distribution->setDefaultXHigh(2.0 * m_distribution->getMean() + 5);

    }
    else
    {
        m_distribution->setFlags(MEANUNDEFINED);
        m_distribution->setDefaultXHigh(5);
    }
    m_distribution->setMedian(scale * std::pow(-1.0 + std::pow(2.0, 1.0/shape1), -1.0/shape2));
    double mode = scale * std::pow((shape2*shape1 - 1.0)/(shape2 + 1.0), 1.0/shape2);
    if(!qFuzzyIsNull(mode))
        m_distribution->setMode(mode);
    else
        m_distribution->setMode(1e-20);

    if(shape2 > 2.0)
    {
        m_distribution->setVariance(-scale*scale/shape2/shape2 * (
                                        2.0 * shape2 * gammaFunction(-2.0/shape2) * gammaFunction(2.0/shape2 + shape1)
                                        / gammaFunction(shape1) +
                                        std::pow(gammaFunction(-1.0/shape2) * gammaFunction(1.0/shape2 + shape1)
                                             / gammaFunction(shape1), 2.0)));
    }
    else
        m_distribution->setFlags(VARIANCEUNDEFINED);

    m_distribution->setFlags(SKEWUNSET & KURTOSISUNSET);

    m_distribution->setDefaultXLow(0);
    m_distribution->setSupportMin(0.0);

    m_distribution->setPdf(std::make_shared<DagumPDF>(shape1, shape2, scale));
    m_distribution->setCdf(std::make_shared<DagumCDF>(shape1, shape2, scale));

    emit newData(0);
    if(!minimized())
        plot();

    emit stopSpinningGear();
}

QJsonObject DagumDistributionIdea::save() const
{
    QJsonObject saveJson = DistributionTemplate::save();

    return saveJson;
}

void DagumDistributionIdea::load(const QJsonObject &obj)
{
    DistributionTemplate::load(obj);
}
