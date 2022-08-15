#include "NumbersInputIdea.h"

NumbersInputAttributes::NumbersInputAttributes()
{
    m_listName = "Numbers Input";
    m_displayName = "";
    m_authors << "dBob";
    m_description = "This box allows the user to enter a list of numbers.";
    m_iconPath = "qrc:/Icons/NumbersInput.png";

    m_dataTypesOut.push_back(Magic<NumbersDataTypeAttributes>::cast().id());
    m_labelsOut << "";
    m_customLabels = true;
    m_resizeable = true;

    m_embeddedQMLPath = ":/QML/NumbersInputIdea.qml";
}

const IdeaAttributes NumbersInputIdea::attributes()
{
    return Magic<NumbersInputAttributes>::cast();
}

std::shared_ptr<DataType> NumbersInputIdea::dataOut(PlugNumber)
{
    return std::static_pointer_cast<DataType>(m_nums);
}

NumbersInputIdea::NumbersInputIdea()
{
    m_rx = QRegExp("(-?\\d+(?:[\\.,]\\d+(?:e\\d+)?)?)");

    std::vector<double> tempList;
    tempList.push_back(1.0);
    tempList.push_back(2.0);
    tempList.push_back(3.0);
    m_nums = std::make_shared<NumbersDataType>(tempList);
    setStatus(IdeaStatus::Working,"Sourcing","Sourcing 1.0, 2.0, 3.0");
}

void NumbersInputIdea::setNums(QString nums)
{
    nums.replace(",", " ");
    QStringList list;
    int pos = 0;

    while((pos = m_rx.indexIn(nums, pos)) != -1)
    {
        list << m_rx.cap(1);
        pos += m_rx.matchedLength();
    }
    std::vector<double> numsVector;
    numsVector.reserve(list.length());

    bool ok = true;
    for(int i = 0; i < list.length(); i++)
    {
        double num = list.at(i).toDouble(&ok);
        if(ok)
            numsVector.push_back(num);
        else
            break;
    }
    if(!ok)
    {
        setStatus(IdeaStatus::Error, "Read Error",
                  "Could not parse the input string");
        return;
    }

    if(numsVector == m_nums->numbers())
        return;

    //Record the change for the undo/redo framework
    QJsonObject oldParams = this->save();
    m_nums = std::make_shared<NumbersDataType>(numsVector);

    QJsonObject newParams = this->save();
    emit reportParamsChanged(oldParams,newParams);

    setStatus(IdeaStatus::Working, "Creating bins", "The idea is currently sourcing the numbers: " + m_nums->toString());
    emit newData(0);

}

QString NumbersInputIdea::getNums()
{
    return m_nums->toString();
}


QJsonObject NumbersInputIdea::save() const
{
    QJsonObject modelJson = Idea::save();
    modelJson["ns"] = m_nums->toString();

    return modelJson;
}

void NumbersInputIdea::load(const QJsonObject &p)
{
    QJsonValue v = p["ns"];

    if (!v.isUndefined())
    {
        QString numsString = v.toString();
        numsString = numsString.simplified();
        QStringList numsStringList = numsString.split(",");
        std::vector<double> numsVector;
        for (int i = 0; i < numsStringList.size(); i++)
        {
            numsVector.push_back(numsStringList[i].simplified().toDouble());
        }
        m_nums = std::make_shared<NumbersDataType>(numsVector);
        emit numsChanged();
        emit newData(0);
    }
}


