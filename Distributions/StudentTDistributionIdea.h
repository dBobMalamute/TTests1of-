#ifndef STUDENTTDISTRIBUTIONIDEA_H
#define STUDENTTDISTRIBUTIONIDEA_H

#include "IdeaTemplates/DistributionTemplate.h"

struct StudentTDistributionAttributes : public IdeaAttributes
{
    StudentTDistributionAttributes();
};

class StudentTDistributionIdea : public DistributionTemplate
{
    Q_OBJECT

public:
    explicit StudentTDistributionIdea();
    const IdeaAttributes attributes() override;

    void onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber plugNumber) override;
    std::shared_ptr<DataType> dataOut(PlugNumber plugNumber) override;

    void resetDisplay() override;

private:
    std::weak_ptr<NumberDataType> m_inputDoF;

    void validate() override;
    void compute(double dof);
};

#endif // STUDENTTDISTRIBUTIONIDEA_H
