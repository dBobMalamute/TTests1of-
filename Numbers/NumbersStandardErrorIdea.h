#ifndef NUMBERSSTANDARDERRORIDEA_H
#define NUMBERSSTANDARDERRORIDEA_H

#include "IdeaTemplates/NumbersToNumberTemplate.h"
#include <cmath>

struct NumbersStandardErrorAttributes : public IdeaAttributes
{
    NumbersStandardErrorAttributes();
};

class NumbersStandardErrorIdea : public NumbersToNumberTemplate
{
    Q_OBJECT

public:
    explicit NumbersStandardErrorIdea();

    const IdeaAttributes attributes() override;

private:
    void validate() override;
    void compute() override;
    void prepareVisuals() override;
};

#endif // NUMBERSSTANDARDDEVIATIONIDEA_H
