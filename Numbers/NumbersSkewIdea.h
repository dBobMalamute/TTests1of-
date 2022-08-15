#ifndef NUMBERSSKEWIDEA_H
#define NUMBERSSKEWIDEA_H

#include "IdeaTemplates/NumbersToNumberTemplate.h"
#include <cmath>

struct NumbersSkewIdeaAttributes : public IdeaAttributes
{
    NumbersSkewIdeaAttributes();
};

class NumbersSkewIdea : public NumbersToNumberTemplate
{
    Q_OBJECT
    Q_PROPERTY(double mean READ mean WRITE setMean NOTIFY meanChanged)
    Q_PROPERTY(double skew READ skew WRITE setSkew NOTIFY skewChanged)

public:
    explicit NumbersSkewIdea();

    const IdeaAttributes attributes() override;

    void load(const QJsonObject &) override;

    double mean() const;
    double skew() const;

signals:
    void meanChanged(double mean);
    void skewChanged(double skew);

public slots:
    void setMean(double mean);
    void setSkew(double skew);

private:
    void validate() override;
    void compute() override;
    void prepareVisuals() override;

    double m_mean;
    double m_skew;
};

#endif // NUMBERSSKEWIDEA_H
