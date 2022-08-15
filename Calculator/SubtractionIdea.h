#ifndef SUBTRACTIONIDEA_H
#define SUBTRACTIONIDEA_H

#include "IdeaTemplates/TwoToOneIdeaTemplate.h"

struct SubtractionAttributes : public IdeaAttributes
{
    SubtractionAttributes();
};

class SubtractionIdea : public TwoToOneIdeaTemplate
{
    Q_OBJECT

public:
    SubtractionIdea();
    const IdeaAttributes attributes() override;

private:
    void validate() override;
    void compute(double n1, double n2);
};

#endif // ADDITIONIDEA_H
