#ifndef NUMBERSCORRECTEDSTANDARDDEVIATIONIDEA_H
#define NUMBERSCORRECTEDSTANDARDDEVIATIONIDEA_H

#include "NumbersStandardDeviationIdea.h"
#include <cmath>

struct NumbersCorrectedStandardDeviationAttributes : public IdeaAttributes
{
    NumbersCorrectedStandardDeviationAttributes();
};

class NumbersCorrectedStandardDeviationIdea : public NumbersToNumberTemplate
{
    Q_OBJECT


public:
    explicit NumbersCorrectedStandardDeviationIdea();

    const IdeaAttributes attributes() override;

signals:
    void startCorrectedStandardDeviationAnimation(std::vector<double> dotPositions, double meanPosition,
                                                  double stdevLength, double correctedLength);
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

#endif // NUMBERSCORRECTEDSTANDARDDEVIATIONIDEA_H
