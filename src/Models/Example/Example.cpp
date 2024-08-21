
#include "Example.h"
#include "Smp/ISimulator.h"
#include "Smp/IPublication.h"
#include "Smp/Publication/IPublishOperation.h"
#include <iostream>
#include <sstream>


// Log a message to the logger on Counter
void Example::Count(void)
{
    // Increase count
    this->counter += 1;

    // Update simulation time
    this->lastSimulationTime = this->timeKeeper->GetSimulationTime();

    // Store simulation time in the buffer
    this->bufferTimes.internalArray[this->indexBufferTimes] = this->lastSimulationTime;
    this->indexBufferTimes = (this->indexBufferTimes + 1) % 80;

    // Send an information message to the logger
    std::ostringstream stream;
    stream << "Counter value: " << this->counter;
    logger->Log(this, stream.str().c_str(), Smp::Services::LMK_Information);
}

// Log a message to the logger on Reset
void Example::Reset(void)
{
    // Reset counter value to 0
    counter = 0;

    // Send an information message to the logger
    logger->Log(this, "Reset counter", Smp::Services::LMK_Information);
}

// Set the value of the counter
void Example::SetCounter(Smp::Int64 value)
{
    this->counter = value;
}

// Change the period time to update the counter
void Example::SetPeriodTime(Smp::Duration value)
{
    this->scheduler->RemoveEvent(this->eventCounterId);
    this->eventCounterId = scheduler->AddSimulationTimeEvent(this->entryPointCounter, 0, value, -1);
}

// Publish fields to the simulation environment
void Example::Publish(Smp::IPublication* receiver)
{
    if (state == Smp::MSK_Created)
    {
        // Get publication instance
        this->publication = receiver;

        // Update state
        state = Smp::MSK_Publishing;

        // Publish simple fields
        receiver->PublishField("counter", "Counter state", &counter, true, true, true, true);
        receiver->PublishField("lastSimulationTime", "Last Simulation Time", &lastSimulationTime, true, true, false, false);

        // Publish array fields
        Smp::Uuid uuidArray80Duration = {0, 0, 0, {'a', '8', '0', 'D', 'u', 'r', 'a', 't'}};
        receiver->GetTypeRegistry()->AddArrayType("Array80Duration", "", uuidArray80Duration, ::Smp::Publication::Uuid_Duration,
                                                  sizeof(::Smp::Duration), 80);
        receiver->PublishField("bufferTimes", "Array with last simulation times stored", &bufferTimes, uuidArray80Duration, true, true, true, true);

        // Publish SetCounter method
        Smp::Publication::IPublishOperation* operationSetCounter = receiver->PublishOperation("SetCounter", "Set the value of the counter",
                                                                                              ::Smp::Publication::Uuid_Void);
        operationSetCounter->PublishParameter("value", "", ::Smp::Publication::Uuid_Int64);

        // Publish SetPeriodTime method
        Smp::Publication::IPublishOperation* operationSetPeriodTime = receiver->PublishOperation("SetPeriodTime", "Set the value of the period time to update the counter",
                                                                                                  ::Smp::Publication::Uuid_Void);
        operationSetPeriodTime->PublishParameter("value", "", ::Smp::Publication::Uuid_Int64);
    }
    else
    {
        throw Smp::IModel::InvalidModelState(state, Smp::MSK_Created);
    }
}

// Perform custom configuration
void Example::Configure(Smp::Services::ILogger*)
{
    if (state == Smp::MSK_Publishing)
        state = Smp::MSK_Configured;
    else
        throw Smp::IModel::InvalidModelState(state, Smp::MSK_Publishing);
}

// Get access to services, and register entry points
void Example::Connect(Smp::ISimulator* simulator)
{
    if (state == Smp::MSK_Configured)
    {
        // Update state
        this->state = Smp::MSK_Connected;

        // Store instances of logger, scheduler, event manager and time keeper
        this->logger = simulator->GetLogger();
        this->scheduler = simulator->GetScheduler();
        this->eventManager = simulator->GetEventManager();
        this->timeKeeper = simulator->GetTimeKeeper();

        // Add a event to execute the count method each 1 second
        this->eventCounterId = this->scheduler->AddSimulationTimeEvent(this->entryPointCounter, 0, 1e9, -1);

        // Add a subscription to execute the reset method when simulator state change to Standby
        this->eventManager->Subscribe(Smp::Services::SMP_EnterStandbyId, this->entryPointReset);
    }
    else
    {
        throw Smp::IModel::InvalidModelState(state, Smp::MSK_Configured);
    }
}

// Create a request for the given operation
::Smp::IRequest* Example::CreateRequest(::Smp::String8 operationName)
{
    return this->publication->CreateRequest(operationName);
}

// Invoke the operation for the given request
void Example::Invoke(::Smp::IRequest* request)
{
    if(request != nullptr)
    {
        // SetCounter operation
        if(strcmp(request->GetOperationName(), "SetCounter") == 0)
        {
            if(request->GetParameterCount() != 1)
            {
                throw ::Smp::IDynamicInvocation::InvalidParameterCount(request->GetOperationName(), 1, request->GetParameterCount());
            }
            if(request->GetParameterValue(0).type != ::Smp::ST_Int64)
            {
                throw ::Smp::IDynamicInvocation::InvalidParameterType("SetCounter", "value",
                                                                      request->GetParameterValue(0).type, ::Smp::ST_Int64);
            }

            // Invoke the method
            this->SetCounter(request->GetParameterValue(0).value.int64Value);
        }

        // SetPeriodTime operation
        if(strcmp(request->GetOperationName(), "SetPeriodTime") == 0)
        {
            if(request->GetParameterCount() != 1)
            {
                throw ::Smp::IDynamicInvocation::InvalidParameterCount(request->GetOperationName(), 1, request->GetParameterCount());
            }
            if(request->GetParameterValue(0).type != ::Smp::ST_Int64)
            {
                throw ::Smp::IDynamicInvocation::InvalidParameterType("SetPeriodTime", "value",
                                                                      request->GetParameterValue(0).type, ::Smp::ST_Int64);
            }

            // Invoke the method
            this->SetPeriodTime(request->GetParameterValue(0).value.int64Value);
        }
    }
}

// Delete given request
void Example::DeleteRequest(::Smp::IRequest* request)
{
    this->publication->DeleteRequest(request);
}
