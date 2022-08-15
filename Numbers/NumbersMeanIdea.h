#ifndef NUMBERSMEANIDEA_H
#define NUMBERSMEANIDEA_H

#include "IdeaTemplates/NumbersToNumberTemplate.h"

struct NumbersMeanAttributes : public IdeaAttributes
{
    NumbersMeanAttributes();
};

class NumbersMeanIdea : public NumbersToNumberTemplate
{
    Q_OBJECT

public:
    explicit NumbersMeanIdea();
    const IdeaAttributes attributes() override;

signals:
    void startMeanAnimation(std::vector<double> dotPositions, double meanPosition);
    void clearDisplay();

public slots:
    void playAnimation() override;

private:
    void validate() override;
    void compute() override;
    void prepareVisuals() override;

    std::vector<double> m_dotPostions;
    double m_meanPosition;
};

#endif // NUMBERSMEANIDEA_H
