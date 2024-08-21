
#include "ReactionWheel.h"


namespace Adcs
{

// Constructor
ReactionWheel::ReactionWheel(::Smp::String8 name, ::Smp::IComposite* parent) : Model(name, parent)
{
    // Initialize values of torque vector
    for (int i=0; i<3; i++)
        this->torque[i] = 0;
}

// Publish fields to the simulation environment
void ReactionWheel::Publish(Smp::IPublication* receiver)
{
    // Call to the superclass method
    Model::Publish(receiver);

    // Publish torque attribute
    Smp::Uuid uuidArrayTorque = {0, 0, 0, {'t', 'o', 'r', 'q', 'u', 'e', '0', '0'}};
    receiver->GetTypeRegistry()->AddArrayType("ArrayTorque", "", uuidArrayTorque, ::Smp::Publication::Uuid_Float64,
                                               sizeof(::Smp::Float64), 3);
    receiver->PublishField("torque", "Torque vector", &this->torque, uuidArrayTorque);
	
    // Publish SetTorque operation
    Smp::Publication::IPublishOperation* operationsetTorque = receiver->PublishOperation("SetTorque", "", ::Smp::Publication::Uuid_Void);
    operationsetTorque->PublishParameter("t0", "", ::Smp::Publication::Uuid_Float64);
    operationsetTorque->PublishParameter("t1", "", ::Smp::Publication::Uuid_Float64);
    operationsetTorque->PublishParameter("t2", "", ::Smp::Publication::Uuid_Float64);
}

// Perform custom configuration
void ReactionWheel::Configure(Smp::Services::ILogger* logger)
{
    // Call to the superclass method
    Model::Configure(logger);
}

// Get access to services, and register entry points
void ReactionWheel::Connect(Smp::ISimulator* simulator)
{
    // Call to the superclass method
    Model::Connect(simulator);
}

// Create a request for the given operation
::Smp::IRequest* ReactionWheel::CreateRequest(::Smp::String8 operationName)
{
    return this->publication->CreateRequest(operationName);
}

// Invoke the operation for the given request
void ReactionWheel::Invoke(::Smp::IRequest* request)
{
    if(strcmp(request->GetOperationName(), "SetTorque") == 0)
    {
       if(request->GetParameterCount() != 4)
           throw ::Smp::IDynamicInvocation::InvalidParameterCount(request->GetOperationName(), 3, request->GetParameterCount());

       if(request->GetParameterValue(0).type != ::Smp::ST_Float64)
           throw ::Smp::IDynamicInvocation::InvalidParameterType("SetTorque", "t0",
               request->GetParameterValue(0).type, ::Smp::ST_Float64);

       if(request->GetParameterValue(1).type != ::Smp::ST_Float64)
           throw ::Smp::IDynamicInvocation::InvalidParameterType("SetTorque", "t1",
               request->GetParameterValue(0).type, ::Smp::ST_Float64);

       if(request->GetParameterValue(2).type != ::Smp::ST_Float64)
           throw ::Smp::IDynamicInvocation::InvalidParameterType("SetTorque", "t2",
               request->GetParameterValue(2).type, ::Smp::ST_Float64);

       // Invoke the method
       this->SetTorque(request->GetParameterValue(0).value.float64Value,
                       request->GetParameterValue(1).value.float64Value,
                       request->GetParameterValue(2).value.float64Value);
   }
}

// Delete given request
void ReactionWheel::DeleteRequest(::Smp::IRequest* request)
{
    this->publication->DeleteRequest(request);
}

// Set value of torque vector
void ReactionWheel::SetTorque(Smp::Float64 t0, Smp::Float64 t1, Smp::Float64 t2)
{
    this->torque[0] = t0;
    this->torque[1] = t1;
    this->torque[2] = t2;
}


}
