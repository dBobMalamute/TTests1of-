#ifndef NUMBERSSTANDARDDEVIATIONFIXEDMEANIDEA_H
#define NUMBERSSTANDARDDEVIATIONFIXEDMEANIDEA_H

#include "IdeaTemplates/NumbersToNumberTemplate.h"
#include <cmath>

struct NumbersStandardDeviationFixedMeanAttributes : public IdeaAttributes
{
    NumbersStandardDeviationFixedMeanAttributes();
};

class NumbersStandardDeviationFixedMeanIdea : public NumbersToNumberTemplate
{
    Q_OBJECT

public:
    explicit NumbersStandardDeviationFixedMeanIdea();

    const IdeaAttributes attributes() override;

    void onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber plugNumber) override;

signals:
    void startStandardDeviationAnimation(std::vector<double> dotPositions, double meanPosition, double stdevLength);
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
    std::vector<double> m_dotPostions;
    double m_meanPosition;
    double m_stdevLength;
};

#endif // NUMBERSSTANDARDDEVIATIONFIXEDMEANIDEA_H
