#ifndef NUMBERSVARIANCEFIXEDMEANIDEA_H
#define NUMBERSVARIANCEFIXEDMEANIDEA_H

#include "IdeaTemplates/NumbersToNumberTemplate.h"
#include <cmath>

struct NumbersVarianceFixedMeanAttributes : public IdeaAttributes
{
    NumbersVarianceFixedMeanAttributes();
};

class NumbersVarianceFixedMeanIdea : public NumbersToNumberTemplate
{
    Q_OBJECT

public:
    explicit NumbersVarianceFixedMeanIdea();

    const IdeaAttributes attributes() override;

    void onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber plugNumber) override;

signals:
    void startVarianceAnimation(std::vector<double> dotPositions, double meanPosition, double stdevLength);
    void clearDisplay();

public slots:
    void playAnimation() override;

private:
    std::weak_ptr<NumberDataType> m_input2;

    void validate() override;
    void compute() override;
    void prepareVisuals() override;

    double m_mean;
    double m_sampleMean;
    double m_variance;
    std::vector<double> m_dotPostions;
    double m_meanPosition;
    double m_stdevLength;
};

#endif // NUMBERSVARIANCEFIXEDMEANIDEA_H
