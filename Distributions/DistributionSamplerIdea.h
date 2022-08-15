#ifndef DISTRIBUTIONSAMPLERIDEA_H
#define DISTRIBUTIONSAMPLERIDEA_H

#include <QPointF>
#include "../DataTypes/NumbersDataType.h"
#include "IdeaTemplates/SamplerTemplate.h"

struct DistributionSamplerAttributes : public IdeaAttributes
{
    DistributionSamplerAttributes();
};

class DistributionSamplerIdea : public SamplerTemplate
{
    Q_OBJECT

public:
    explicit DistributionSamplerIdea();
    const IdeaAttributes attributes() override;

signals:

public slots:
    QPointF getPositionForDot(int i);

private:
    void sampleContinuous() override;
    void sampleDiscrete() override;
};

#endif // DISTRIBUTIONDISPLAYIDEA_H
