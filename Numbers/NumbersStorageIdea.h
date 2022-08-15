#ifndef NUMBERSSTORAGEIDEA_H
#define NUMBERSSTORAGEIDEA_H

#include "../MalamuteCore/InheritedClasses/Idea.h"
#include "../DataTypes/NumbersDataType.h"

struct NumbersStorageAttributes : public IdeaAttributes
{
    NumbersStorageAttributes();
};

class NumbersStorageIdea : public Idea
{
    Q_OBJECT
    Q_PROPERTY(QList<QVariant> numbersVariant READ numbersVariant NOTIFY numbersVariantChanged)

public:
    explicit NumbersStorageIdea();

    const IdeaAttributes attributes() override;

    QJsonObject save() const override;
    void load(const QJsonObject &) override;

    void onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber plugNumber) override;
    std::shared_ptr<DataType> dataOut(PlugNumber plugNumber) override;

    QList<QVariant> numbersVariant() const;

signals:
    void numbersVariantChanged(QList<QVariant> numbersVariant);

public slots:
    void clear();

private:
    std::weak_ptr<NumbersDataType> m_input;
    std::shared_ptr<NumbersDataType> m_output;

    void validate();
    void setupDisplay();

    std::vector<double> m_nums;
    QList<QVariant> m_numbersVariant;
};

#endif // NUMBERSSTORAGEIDEA_H
