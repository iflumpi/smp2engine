
#pragma once

#include "Smp/IModel.h"
#include "Smp/IRequest.h"
#include "Smp/Services/ILogger.h"
#include "Smp/Services/IScheduler.h"
#include "Smp/Services/IEventManager.h"
#include "Smp/Services/ITimeKeeper.h"


namespace Adcs
{

class Model : virtual public Smp::IModel
{

public:
    Model(Smp::String8 name, Smp::IComposite* parent)
    {
        this->name = name;
        this->parent = parent;

        this->state = Smp::MSK_Created;
    }

    virtual ~Model()
    {
    }

    virtual Smp::String8 GetName() const;
    virtual Smp::String8 GetDescription() const;
    virtual Smp::IComposite* GetParent() const;
    virtual Smp::ModelStateKind GetState() const;
    virtual void Publish(Smp::IPublication* receiver);
    virtual void Configure(Smp::Services::ILogger* logger);
    virtual void Connect(Smp::ISimulator* simulator);

protected:
    Smp::String8 name; // Name of Model
    Smp::ModelStateKind state; // Model state
    Smp::IComposite* parent; // Parent component
    Smp::Services::ILogger* logger = nullptr; // Logger service
    Smp::Services::IScheduler* scheduler = nullptr; // Scheduler service
    Smp::Services::IEventManager* eventManager = nullptr; // EventManager service
    Smp::Services::ITimeKeeper* timeKeeper = nullptr; // TimeKeeper service
    Smp::IPublication *publication = nullptr; // Publication service

};

}
