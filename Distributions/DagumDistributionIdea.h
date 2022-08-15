#ifndef DAGUMDISTRIBUTIONIDEA_H
#define DAGUMDISTRIBUTIONIDEA_H

#include "IdeaTemplates/DistributionTemplate.h"
#include "Common/BoostIncludes.h"

struct DagumDistributionAttributes : public IdeaAttributes
{
    DagumDistributionAttributes();
};

class DagumDistributionIdea : public DistributionTemplate
{
    Q_OBJECT

public:
    explicit DagumDistributionIdea();
    const IdeaAttributes attributes() override;

    QJsonObject save() const override;
    void load(const QJsonObject &) override;

    void onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber plugNumber) override;
    std::shared_ptr<DataType> dataOut(PlugNumber plugNumber) override;

    void resetDisplay() override;

public slots:

signals:

private:
    std::weak_ptr<NumberDataType> m_shapeInput1;
    std::weak_ptr<NumberDataType> m_shapeInput2;
    std::weak_ptr<NumberDataType> m_scaleInput;

    void validate() override;
    void compute(double shape1, double shape2, double scale);
};

#endif // DAGUMDISTRIBUTIONIDEA_H
