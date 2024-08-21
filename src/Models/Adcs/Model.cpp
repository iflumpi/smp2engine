
#include <Models/Adcs/Model.h>
#include "Smp/ISimulator.h"
#include "Smp/IPublication.h"


namespace Adcs
{

Smp::String8 Model::GetName() const
{
    return this->name;
}

Smp::String8 Model::GetDescription() const
{
    return "";
}

Smp::IComposite* Model::GetParent() const
{
    return this->parent;
}

Smp::ModelStateKind Model::GetState() const
{
    return this->state;
}

void Model::Publish(Smp::IPublication* receiver)
{
    if (state != Smp::MSK_Created)
        throw Smp::IModel::InvalidModelState(this->state, Smp::MSK_Created);
    this->state = Smp::MSK_Publishing;

    this->publication = receiver;
}

void Model::Configure(Smp::Services::ILogger* logger)
{
    if (state != Smp::MSK_Publishing)
        throw Smp::IModel::InvalidModelState(this->state, Smp::MSK_Publishing);
    this->state = Smp::MSK_Configured;
}

void Model::Connect(Smp::ISimulator* simulator)
{
    if (state != Smp::MSK_Configured)
        throw Smp::IModel::InvalidModelState(this->state, Smp::MSK_Configured);
    this->state = Smp::MSK_Connected;

    this->logger = simulator->GetLogger();
    this->scheduler = simulator->GetScheduler();
    this->eventManager = simulator->GetEventManager();
    this->timeKeeper = simulator->GetTimeKeeper();
}

}
