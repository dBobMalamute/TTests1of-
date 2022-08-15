#ifndef DISTRIBUTIONDISPLAYIDEA_H
#define DISTRIBUTIONDISPLAYIDEA_H

#include "IdeaTemplates/DistributionTemplate.h"

struct DistributionDisplayAttributes : public IdeaAttributes
{
    DistributionDisplayAttributes();
};

class DistributionDisplayIdea : public DistributionTemplate
{
    Q_OBJECT

public:
    explicit DistributionDisplayIdea();
    const IdeaAttributes attributes() override;

    void onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber plugNumber) override;

protected:
    std::weak_ptr<DistributionDataType> m_input;
    void validate() override;
};

#endif // DISTRIBUTIONDISPLAYIDEA_H
