#ifndef MULTIPLICATIONIDEA_H
#define MULTIPLICATIONIDEA_H

#include "IdeaTemplates/TwoToOneIdeaTemplate.h"

struct MultiplicationAttributes : public IdeaAttributes
{
    MultiplicationAttributes();
};

class MultiplicationIdea : public TwoToOneIdeaTemplate
{
    Q_OBJECT

public:
    MultiplicationIdea();
    const IdeaAttributes attributes() override;

    void resetDisplay() override;

private:
    void validate() override;
    void compute(double n1, double n2);
};

#endif // MULTIPLICATIONIDEA_H
