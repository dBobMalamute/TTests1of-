#ifndef NUMBERSKURTOSISIDEA_H
#define NUMBERSKURTOSISIDEA_H

#include "IdeaTemplates/NumbersToNumberTemplate.h"

struct NumbersKurtosisIdeaAttributes : public IdeaAttributes
{
    NumbersKurtosisIdeaAttributes();
};

class NumbersKurtosisIdea : public NumbersToNumberTemplate
{
    Q_OBJECT
    Q_PROPERTY(double mean READ mean WRITE setMean NOTIFY meanChanged)

public:
    explicit NumbersKurtosisIdea();

    const IdeaAttributes attributes() override;

    void load(const QJsonObject &) override;

    double mean() const;

signals:
    void meanChanged(double mean);
    void kurtosisChanged(double skew);

public slots:
    void setMean(double mean);

private:
    void validate() override;
    void compute() override;
    void prepareVisuals() override;

    double m_mean;
};

#endif // NUMBERSKURTOSISIDEA_H
