#include "StudentTDistributionIdea.h"
#include "DistributionMakers/StudentTDistributionBuilder.h"

StudentTDistributionAttributes::StudentTDistributionAttributes()
{
    m_listName = "Student T Distribution";
    m_displayName = "Student T Distribution";
    m_authors << "dBob";
    m_description = "This box creates a student T distribution.";
    m_iconPath = "qrc:/Icons/StudentT.png";

    m_dataTypesIn.push_back(Magic<NumberDataTypeAttributes>::cast().id());
    m_labelsIn << "DoF";

    m_dataTypesOut.push_back(Magic<DistributionDataTypeAttributes>::cast().id());
    m_labelsOut << "Dist";
    m_customLabels = true;

    m_embeddedQMLPath = ":/QML/StudentTDistributionIdea.qml";
    m_minimizable = true;
    m_minimizedName = "Student T\nDistribution";
    m_differentNameOnMinimized = true;

    m_gear = true;

}

StudentTDistributionIdea::StudentTDistributionIdea()
{

}

const IdeaAttributes StudentTDistributionIdea::attributes()
{
    return Magic<StudentTDistributionAttributes>::cast();
}

void StudentTDistributionIdea::onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber)
{
    m_inputDoF = std::dynamic_pointer_cast<NumberDataType>(dataType);

    validate();
}

std::shared_ptr<DataType> StudentTDistributionIdea::dataOut(PlugNumber)
{
    return std::static_pointer_cast<DataType>(m_distribution);
}

void StudentTDistributionIdea::resetDisplay()
{
    if(valid())
        plot();
}

void StudentTDistributionIdea::validate()
{
    auto v_dof = m_inputDoF.lock();

    if(v_dof)
    {
        if(v_dof->number() <= 0.0)
        {
            setStatus(IdeaStatus::Error, "Dof <= 0", "The input degrees of freedom " + QString::number(v_dof->number()) +
                      " is less than 0. ");
        }
        else
        {
            setStatus(IdeaStatus::Working, "Creating Distribution", "Creating a student-t distribution");
            compute(v_dof->number());
        }
    }
    else
    {
        setDefaultStatus();
    }
}

void StudentTDistributionIdea::compute(double dof)
{
    emit startSpinningGear();

    m_distribution = StudentTDistributionBuilder::makeStudentT(dof);
    emit newData(0);
    if(!minimized())
        plot();

    emit stopSpinningGear();
}
