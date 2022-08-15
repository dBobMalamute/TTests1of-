#ifndef NUMBERSDATATYPE_H
#define NUMBERSDATATYPE_H

#include "../MalamuteCore/InheritedClasses/DataType.h"

struct NumbersDataTypeAttributes : public DataTypeAttributes
{
    NumbersDataTypeAttributes();
};

class NumbersDataType : public DataType
{
public:
    NumbersDataType(std::vector<double> numbers);

    DataTypeAttributes getAttributes() override;

    std::vector<double> numbers();
    QString toString();

private:
    std::vector<double> m_numbers;
};

#endif
