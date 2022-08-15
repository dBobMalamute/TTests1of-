#ifndef NUMBERSSTANDARDDEVIATIONIDEA_H
#define NUMBERSSTANDARDDEVIATIONIDEA_H

#include "IdeaTemplates/NumbersToNumberTemplate.h"
#include <cmath>
struct NumbersStandardDeviationAttributes : public IdeaAttributes
{
    NumbersStandardDeviationAttributes();
};

class NumbersStandardDeviationIdea : public NumbersToNumberTemplate
{
    Q_OBJECT

public:
    explicit NumbersStandardDeviationIdea();

    const IdeaAttributes attributes() override;

signals:
    void startStandardDeviationAnimation(std::vector<double> dotPositions, double meanPosition, double stdevLength);
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

#endif // NUMBERSSTANDARDDEVIATIONIDEA_H
