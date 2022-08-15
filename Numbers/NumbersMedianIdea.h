#ifndef NUMBERSMEDIANIDEA_H
#define NUMBERSMEDIANIDEA_H

#include "IdeaTemplates/NumbersToNumberTemplate.h"
#include <cmath>

struct NumbersMedianAttributes : public IdeaAttributes
{
    NumbersMedianAttributes();
};

class NumbersMedianIdea : public NumbersToNumberTemplate
{
    Q_OBJECT

public:
    explicit NumbersMedianIdea();
    const IdeaAttributes attributes() override;

signals:
    void startMedianAnimation(std::vector<double> positions, std::vector<int> delay,
                              double medianPosition, double medianDelay);
    void clearDisplay();

public slots:
    void playAnimation() override;

private:
    void validate() override;
    void compute() override;
    void prepareVisuals() override;

    std::vector<double> m_dotPositions;
    std::vector<int> m_delays;
    double m_medianPosition;
    double m_medianDelay;
};

#endif // NUMBERSMEDIANIDEA_H
