
#include "StarTracker.h"


namespace Adcs
{

// Constructor
StarTracker::StarTracker(::Smp::String8 name, ::Smp::IComposite* parent) : Model(name, parent)
{
    // Initialize values of quaternion
    for (int i=0; i<4; i++)
        this->quaternion[i] = 0;
}

// Publish fields to the simulation environment
void StarTracker::Publish(Smp::IPublication* receiver)
{
    // Call to the superclass method
    Model::Publish(receiver);

    // Publish SetQuaternionValue operation
    Smp::Publication::IPublishOperation* operationSetQuaternion = receiver->PublishOperation("SetQuaternion", "", ::Smp::Publication::Uuid_Void);
    operationSetQuaternion->PublishParameter("q0", "", ::Smp::Publication::Uuid_Float64);
    operationSetQuaternion->PublishParameter("q1", "", ::Smp::Publication::Uuid_Float64);
    operationSetQuaternion->PublishParameter("q2", "", ::Smp::Publication::Uuid_Float64);
    operationSetQuaternion->PublishParameter("q3", "", ::Smp::Publication::Uuid_Float64);
}

// Perform custom configuration
void StarTracker::Configure(Smp::Services::ILogger* logger)
{
    // Call to the superclass method
    Model::Configure(logger);
}

// Get access to services, and register entry points
void StarTracker::Connect(Smp::ISimulator* simulator)
{
    // Call to the superclass method
    Model::Connect(simulator);
}

// Create a request for the given operation
::Smp::IRequest* StarTracker::CreateRequest(::Smp::String8 operationName)
{
    return this->publication->CreateRequest(operationName);
}

// Invoke the operation for the given request
void StarTracker::Invoke(::Smp::IRequest* request)
{
    if(request != nullptr)
    {
        if(strcmp(request->GetOperationName(), "SetQuaternion") == 0)
        {
            if(request->GetParameterCount() != 4)
                throw ::Smp::IDynamicInvocation::InvalidParameterCount(request->GetOperationName(), 4, request->GetParameterCount());

            if(request->GetParameterValue(0).type != ::Smp::ST_Float64)
                throw ::Smp::IDynamicInvocation::InvalidParameterType("SetQuaternion", "q0",
                    request->GetParameterValue(0).type, ::Smp::ST_Float64);

            if(request->GetParameterValue(1).type != ::Smp::ST_Float64)
                throw ::Smp::IDynamicInvocation::InvalidParameterType("SetQuaternion", "q1",
                    request->GetParameterValue(1).type, ::Smp::ST_Float64);

            if(request->GetParameterValue(2).type != ::Smp::ST_Float64)
                throw ::Smp::IDynamicInvocation::InvalidParameterType("SetQuaternion", "q2",
                    request->GetParameterValue(2).type, ::Smp::ST_Float64);

            if(request->GetParameterValue(3).type != ::Smp::ST_Float64)
                throw ::Smp::IDynamicInvocation::InvalidParameterType("SetQuaternion", "q3",
                    request->GetParameterValue(3).type, ::Smp::ST_Float64);

            // Invoke the method
            this->SetQuaternion(request->GetParameterValue(0).value.float64Value,
                                request->GetParameterValue(1).value.float64Value,
                                request->GetParameterValue(2).value.float64Value,
                                request->GetParameterValue(3).value.float64Value);
        }
    }
}

// Set value of the quaternion elements (orientation)
void StarTracker::SetQuaternion(Smp::Float64 q0, Smp::Float64 q1, Smp::Float64 q2, Smp::Float64 q3)
{
    this->quaternion[0] = q0;
    this->quaternion[1] = q1;
    this->quaternion[2] = q2;
    this->quaternion[3] = q3;
	std::ostringstream stream;
}

// Get value of the quaternion elements
Smp::Float64* StarTracker::GetQuaternion()
{
    return this->quaternion;
}

// Delete given request
void StarTracker::DeleteRequest(::Smp::IRequest* request)
{
    this->publication->DeleteRequest(request);
}

}
