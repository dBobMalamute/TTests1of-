#ifndef ADDITIONIDEA_H
#define ADDITIONIDEA_H

#include "IdeaTemplates/TwoToOneIdeaTemplate.h"

struct AdditionAttributes : public IdeaAttributes
{
    AdditionAttributes();
};

class AdditionIdea : public TwoToOneIdeaTemplate
{
    Q_OBJECT

public:
    AdditionIdea();
    const IdeaAttributes attributes() override;

    void resetDisplay() override;

private:
    void validate() override;
    void compute(double n1, double n2);
};

#endif // ADDITIONIDEA_H
