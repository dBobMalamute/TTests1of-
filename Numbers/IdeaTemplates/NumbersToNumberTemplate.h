#ifndef NUMBERSTONUMBERTEMPLATE_H
#define NUMBERSTONUMBERTEMPLATE_H

#include "../../MalamuteCore/InheritedClasses/Idea.h"
#include "../../DataTypes/NumberDataType.h"
#include "../../DataTypes/NumbersDataType.h"

class NumbersToNumberTemplate : public Idea
{
    Q_OBJECT

    Q_PROPERTY(double statistic READ statistic WRITE setStatistic NOTIFY statisticChanged)

    Q_PROPERTY(double lowBound READ lowBound WRITE setLowBound NOTIFY lowBoundChanged)
    Q_PROPERTY(double upBound READ upBound WRITE setUpBound NOTIFY upBoundChanged)
    Q_PROPERTY(bool autoFit READ autoFit WRITE setAutoFit NOTIFY autoFitChanged)
    Q_PROPERTY(double animationSpeed READ animationSpeed WRITE setAnimationSpeed NOTIFY animationSpeedChanged)


public:
    explicit NumbersToNumberTemplate();

    QJsonObject save() const override;
    void load(const QJsonObject &) override;

    void onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber plugNumber) override;
    std::shared_ptr<DataType> dataOut(PlugNumber plugNumber) override;

    void resetDisplay() override;

    double lowBound() const;
    double upBound() const;
    bool autoFit() const;

    double animationSpeed() const;

    double statistic() const;

signals:
    void lowBoundChanged(double lowBound);
    void upBoundChanged(double upBound);
    void autoFitChanged(bool autoFit);
    void animationSpeedChanged(double animationSpeed);

    void statisticChanged(double statistic);

public slots:
    void setLowBound(double lowBound);
    void setUpBound(double upBound);
    void setAutoFit(bool autoFit);
    void setAnimationSpeed(double animationSpeed);

    virtual void playAnimation();

    void setStatistic(double statistic);

protected:
    std::weak_ptr<NumbersDataType> m_input;
    std::shared_ptr<NumberDataType> m_output;

    virtual void validate() = 0;
    virtual void compute() = 0;
    virtual void prepareVisuals() = 0;

    double m_statistic;

    double m_lowBound;
    double m_upBound;
    bool m_autoFit;
    double m_animationSpeed;

    std::vector<double> m_nums;
};

#endif // NUMBERSTONUMBERTEMPLATE_H
