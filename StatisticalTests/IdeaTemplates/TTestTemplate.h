#ifndef TTESTTEMPLATE_H
#define TTESTTEMPLATE_H

#include "../../MalamuteCore/InheritedClasses/Idea.h"
#include "../../DataTypes/NumbersDataType.h"
#include "../../DataTypes/NumberDataType.h"

class TTestTemplate : public Idea
{
    Q_OBJECT
    Q_PROPERTY(double lowBound READ lowBound WRITE setLowBound NOTIFY lowBoundChanged)
    Q_PROPERTY(double upBound READ upBound WRITE setUpBound NOTIFY upBoundChanged)
    Q_PROPERTY(bool autoFit READ autoFit WRITE setAutoFit NOTIFY autoFitChanged)
    Q_PROPERTY(double animationSpeed READ animationSpeed WRITE setAnimationSpeed NOTIFY animationSpeedChanged)

    Q_PROPERTY(double tValue READ tValue WRITE setTValue NOTIFY tValueChanged)
    Q_PROPERTY(double pValue READ pValue WRITE setPValue NOTIFY pValueChanged)

public:
    TTestTemplate();

    QJsonObject save() const override;
    void load(const QJsonObject &obj) override;

    void resetDisplay() override;

    std::shared_ptr<DataType> dataOut(PlugNumber plugNumber) override;

    double lowBound() const;
    double upBound() const;
    bool autoFit() const;
    double animationSpeed() const;

    double tValue() const;
    double pValue() const;

signals:
    void lowBoundChanged(double lowBound);
    void upBoundChanged(double upBound);
    void autoFitChanged(bool autoFit);
    void animationSpeedChanged(double animationSpeed);

    void tValueChanged(double tValue);
    void pValueChanged(double pValue);

    void clearDisplay();
    void displayNewTDistribution(std::vector<double> xValues, std::vector<double> yValues);
    void setPValueTextPosition(double xVal, double yVal);

public slots:
    void setLowBound(double lowBound);
    void setUpBound(double upBound);
    void setAutoFit(bool autoFit);
    void setAnimationSpeed(double animationSpeed);

    void setTValue(double tValue);
    void setPValue(double pValue);

protected:
    std::shared_ptr<NumberDataType> m_pValueOutput;
    std::shared_ptr<NumberDataType> m_tValueOutput;

    virtual void validate() = 0;

    double m_lowBound;
    double m_upBound;
    bool m_autoFit;
    double m_animationSpeed;

    double m_tValue;
    double m_pValue;
};

#endif // TTESTTEMPLATE_H
