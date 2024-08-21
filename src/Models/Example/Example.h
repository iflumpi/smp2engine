#include "Smp/IModel.h"
#include "Smp/IEntryPoint.h"
#include "Smp/IDynamicInvocation.h"
#include "Smp/IRequest.h"
#include "Smp/Services/ILogger.h"
#include "Smp/Services/IScheduler.h"
#include "Smp/Services/IEventManager.h"
#include "Smp/Services/ITimeKeeper.h"


/*
 * ArrayBufferTimes type
 */

struct ArrayBufferTimes
{
    Smp::Duration internalArray[80];
};


/*
 * Example class
 */

class Example : virtual public Smp::IModel,
                virtual public ::Smp::IDynamicInvocation
{

private:

    /*
     * ExampleEntryPoint class
     */

    class ExampleEntryPoint : public Smp::IEntryPoint
    {

    private:
        Smp::String8 name; // Name of entry point.
        Smp::String8 description; // Description.
        Example* publisher; // Entry point publisher.
        void (Example::*entryPoint)(void); // Instance method.

    public:
        ExampleEntryPoint(
            Smp::String8 name,
            Smp::String8 description,
            Example* publisher,
            void (Example::*entryPoint)(void))
        {
            this->name = name;
            this->description = description;
            this->publisher = publisher;
            this->entryPoint = entryPoint;
        }

        virtual Smp::String8 GetName() const
        {
            return this->name;
        }
        virtual Smp::String8 GetDescription() const
        {
            return this->description;
        }
        virtual Smp::IComponent* GetOwner() const
        {
            return publisher;
        }

        void Execute() const
        {
            (publisher->*entryPoint)();
        }
    };


public:
    Example(Smp::String8 name, Smp::IComposite* parent)
    {
        this->counter = 0;
        this->lastSimulationTime = 0;
        this->indexBufferTimes = 0;
        this->name = name;
        this->state = Smp::MSK_Created;
        this->parent = parent;
        this->eventCounterId = -1;

        // Initialization of entry points
        this->entryPointCounter = new ExampleEntryPoint("Count", "Increment Counter", this,
                                                        &Example::Count);
        this->entryPointReset = new ExampleEntryPoint("Reset", "Reset Counter", this,
                                                      &Example::Reset);
    }

    virtual ~Example()
    {
    }

    virtual void Count(void);
    virtual void Reset(void);
    void SetCounter(Smp::Int64 value);
    void SetPeriodTime(Smp::Duration value);


    // IModel methods
    virtual Smp::String8 GetName() const
    {
        return name;
    }
    virtual Smp::String8 GetDescription() const
    {
        return "";
    }
    virtual Smp::IComposite* GetParent() const
    {
        return parent;
    }
    virtual Smp::ModelStateKind GetState() const
    {
        return state;
    }
    virtual void Publish(Smp::IPublication* receiver);
    virtual void Configure(Smp::Services::ILogger* logger);
    virtual void Connect(Smp::ISimulator* simulator);

    // IDynamicInvocation methods
    virtual Smp::IRequest* CreateRequest(Smp::String8 operationName);
    virtual void Invoke(Smp::IRequest* request);
    virtual void DeleteRequest(Smp::IRequest* request);


private:
    Smp::String8 name; // Name of model
    Smp::IComposite* parent; // Parent component
    Smp::ModelStateKind state; // Model state

    Smp::Int64 counter; // Counter field
    Smp::Duration lastSimulationTime; // Store the last simulation time in which the counter was updated
    ArrayBufferTimes bufferTimes;  // Store an array with all simulation times in which the counter was update
    Smp::UInt8 indexBufferTimes;  // Index with the last position written in bufferTimes array

    Smp::Services::ILogger* logger = nullptr; // Logger service
    Smp::Services::IScheduler* scheduler = nullptr; // Scheduler service
    Smp::Services::IEventManager* eventManager = nullptr; // EventManager service
    Smp::Services::ITimeKeeper* timeKeeper = nullptr; // TimeKeeper service
    Smp::IPublication *publication = nullptr;   // Publication

    ExampleEntryPoint* entryPointCounter; // Entry point for Count
    Smp::Services::EventId eventCounterId;
    ExampleEntryPoint* entryPointReset; // Entry point for Reset

};
