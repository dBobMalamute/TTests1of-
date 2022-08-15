#ifndef NUMBERSVARIANCEIDEA_H
#define NUMBERSVARIANCEIDEA_H

#include "IdeaTemplates/NumbersToNumberTemplate.h"
#include <cmath>

struct NumbersVarianceAttributes : public IdeaAttributes
{
    NumbersVarianceAttributes();
};

class NumbersVarianceIdea : public NumbersToNumberTemplate
{
    Q_OBJECT

public:
    explicit NumbersVarianceIdea();
    const IdeaAttributes attributes() override;

signals:
    void startVarianceAnimation(std::vector<double> dotPositions, double meanPosition, double stdevLength);
    void clearDisplay();

public slots:
    void playAnimation() override;

protected:
    void validate() override;
    void compute() override;
    void prepareVisuals() override;

    double m_mean;
    std::vector<double> m_dotPostions;
    double m_meanPosition;
    double m_stdevLength;
};

#endif // NUMBERSVARIANCEIDEA_H
