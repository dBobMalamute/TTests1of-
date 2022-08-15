#ifndef DIVISIONIDEA_H
#define DIVISIONIDEA_H

#include "IdeaTemplates/TwoToOneIdeaTemplate.h"

struct DivisionAttributes : public IdeaAttributes
{
    DivisionAttributes();
};

class DivisionIdea : public TwoToOneIdeaTemplate
{
    Q_OBJECT
public:
    DivisionIdea();
    const IdeaAttributes attributes() override;

private:
    void validate() override;
    void compute(double n1, double n2);
};

#endif // DIVISIONIDEA_H
