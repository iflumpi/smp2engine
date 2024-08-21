
#include "Gyroscope.h"


namespace Adcs
{

// Constructor
Gyroscope::Gyroscope(::Smp::String8 name, ::Smp::IComposite* parent) : Model(name, parent)
{
    // Initialize values of quaternion
    for (int i=0; i<3; i++)
        this->omega[i] = 0;
}

// Publish fields to the simulation environment
void Gyroscope::Publish(Smp::IPublication* receiver)
{
    // Call to the superclass method
    Model::Publish(receiver);

	// Publish SetOmega operation
	Smp::Publication::IPublishOperation* operationSetOmega = receiver->PublishOperation("SetOmega", "", ::Smp::Publication::Uuid_Void);
	operationSetOmega->PublishParameter("w0", "", ::Smp::Publication::Uuid_Float64);
	operationSetOmega->PublishParameter("w1", "", ::Smp::Publication::Uuid_Float64);
	operationSetOmega->PublishParameter("w2", "", ::Smp::Publication::Uuid_Float64);
}

// Perform custom configuration
void Gyroscope::Configure(Smp::Services::ILogger* logger)
{
    // Call to the superclass method
    Model::Configure(logger);
}

// Get access to services, and register entry points
void Gyroscope::Connect(Smp::ISimulator* simulator)
{
    // Call to the superclass method
    Model::Connect(simulator);
}

// Create a request for the given operation
::Smp::IRequest* Gyroscope::CreateRequest(::Smp::String8 operationName)
{
    return this->publication->CreateRequest(operationName);
}

// Invoke the operation for the given request
void Gyroscope::Invoke(::Smp::IRequest* request)
{
    if(request != nullptr)
    {
        if(strcmp(request->GetOperationName(), "SetOmega") == 0)
        {
            if(request->GetParameterCount() != 3)
                throw ::Smp::IDynamicInvocation::InvalidParameterCount(request->GetOperationName(), 3, request->GetParameterCount());

            if(request->GetParameterValue(0).type != ::Smp::ST_Float64)
                throw ::Smp::IDynamicInvocation::InvalidParameterType("SetOmega", "w0",
                    request->GetParameterValue(0).type, ::Smp::ST_Float64);

            if(request->GetParameterValue(1).type != ::Smp::ST_Float64)
                throw ::Smp::IDynamicInvocation::InvalidParameterType("SetOmega", "w1",
                    request->GetParameterValue(1).type, ::Smp::ST_Float64);

            if(request->GetParameterValue(2).type != ::Smp::ST_Float64)
                throw ::Smp::IDynamicInvocation::InvalidParameterType("SetOmega", "w2",
                    request->GetParameterValue(2).type, ::Smp::ST_Float64);

            // Invoke the method
            this->SetOmega(request->GetParameterValue(0).value.float64Value,
                           request->GetParameterValue(1).value.float64Value,
                           request->GetParameterValue(2).value.float64Value);
        }
    }
}

// Delete given request
void Gyroscope::DeleteRequest(::Smp::IRequest* request)
{
    this->publication->DeleteRequest(request);
}


// Set value of the omega elements (angular velocity)
void Gyroscope::SetOmega(Smp::Float64 w0, Smp::Float64 w1, Smp::Float64 w2)
{
    this->omega[0] = w0;
    this->omega[1] = w1;
    this->omega[2] = w2;
}

// Get value of the omega elements
Smp::Float64* Gyroscope::GetOmega()
{
    return this->omega;
}

}
