#ifndef NUMBERSDISPLAYIDEA_H
#define NUMBERSDISPLAYIDEA_H

#include "../MalamuteCore/InheritedClasses/Idea.h"
#include "../DataTypes/NumbersDataType.h"

struct NumbersDisplayAttributes : public IdeaAttributes
{
    NumbersDisplayAttributes();
};

class NumbersDisplayIdea : public Idea
{
    Q_OBJECT

    Q_PROPERTY(QList<QVariant> numbersVariant READ numbersVariant NOTIFY numbersVariantChanged)

public:
    explicit NumbersDisplayIdea();

    const IdeaAttributes attributes() override;

    void onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber plugNumber) override;

    QList<QVariant> numbersVariant() const;

signals:
    void numbersVariantChanged(QList<QVariant> numbersVariant);

public slots:

private:
    std::weak_ptr<NumbersDataType> m_input;

    void validate();
    void setupDisplay();

    std::vector<double> m_nums;
    QList<QVariant> m_numbersVariant;
};

#endif // NUMBERSDISPLAYIDEA_H
