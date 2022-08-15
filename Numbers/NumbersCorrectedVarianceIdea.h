#ifndef NUMBERSCORRECTEDVARIANCEIDEA_H
#define NUMBERSCORRECTEDVARIANCEIDEA_H

#include "NumbersVarianceIdea.h"
#include <cmath>

struct NumbersCorrectedVarianceAttributes : public IdeaAttributes
{
    NumbersCorrectedVarianceAttributes();
};

class NumbersCorrectedVarianceIdea : public NumbersToNumberTemplate
{
    Q_OBJECT

public:
    explicit NumbersCorrectedVarianceIdea();

    const IdeaAttributes attributes() override;

signals:
    void startCorrectedVarianceAnimation(std::vector<double> dotPositions, double meanPosition, double stdevLength, double correctedLength);
    void clearDisplay();

public slots:
    void playAnimation() override;

protected:
    void validate() override;
    void compute() override;
    void prepareVisuals() override;

    double m_mean;
    double m_stdev;
    std::vector<double> m_dotPostions;
    double m_meanPosition;
    double m_stdevLength;
    double m_correctedLength;
};

#endif // NUMBERSCORRECTEDVARIANCEIDEA_H
