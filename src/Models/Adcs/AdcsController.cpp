
#include "AdcsController.h"


namespace Adcs
{

// Constructor
AdcsController::AdcsController(Gyroscope* gyroscope, StarTracker* starTracker, ReactionWheel* reactionWheel,
                       ::Smp::String8 name, ::Smp::IComposite* parent) : Model(name, parent)
{
    // Initialization of sensors
    this->gyroscope = gyroscope;
    this->starTracker = starTracker;

    // Initialization of actuators
    this->reactionWheel = reactionWheel;

    // Initialization of PD controller
    this->pdController = new Pid::QuaternionFeedbackPd(this->INITIAL_KW_PID_VALUE, this->INITIAL_KQ_PID_VALUE, this->INITIAL_DELTA_PID_VALUE);

    // Initialization of target reference for orientation
    for (int i=0; i<4; i++)
        this->targetOrientation.push_back(0);

    // Definition of entry point and related eventId to perform a step
    this->entryPointStep = new EntryPoint<AdcsController>("AdcsControlTask", "", this, &AdcsController::ExecuteControlStep);
    this->controlEventId = -1;
}

// Destructor
AdcsController::~AdcsController()
{
    delete this->gyroscope;
    delete this->starTracker;
    delete this->reactionWheel;
    delete this->pdController;
}

// Publish fields to the simulation environment
void AdcsController::Publish(Smp::IPublication* receiver)
{
    // Call to the superclass method
    Model::Publish(receiver);

    // Publish SetPidParameters method
    Smp::Publication::IPublishOperation* operationSetPdParameters = receiver->PublishOperation("SetPdParameters", "", ::Smp::Publication::Uuid_Void);
    operationSetPdParameters->PublishParameter("kw", "", ::Smp::Publication::Uuid_Float64);
    operationSetPdParameters->PublishParameter("kq", "", ::Smp::Publication::Uuid_Float64);

    // Publish SetTargetOrientation method
    Smp::Publication::IPublishOperation* operationSetTargetOrientation = receiver->PublishOperation("SetTargetOrientation", "", ::Smp::Publication::Uuid_Void);
    operationSetTargetOrientation->PublishParameter("t0", "", ::Smp::Publication::Uuid_Float64);
    operationSetTargetOrientation->PublishParameter("t1", "", ::Smp::Publication::Uuid_Float64);
    operationSetTargetOrientation->PublishParameter("t2", "", ::Smp::Publication::Uuid_Float64);
    operationSetTargetOrientation->PublishParameter("t3", "", ::Smp::Publication::Uuid_Float64);

    // Publish ExecuteControlStep method
    receiver->PublishOperation("ExecuteControlStep", "", ::Smp::Publication::Uuid_Void);
}

void AdcsController::Configure(Smp::Services::ILogger* logger)
{
    // Call to the superclass method
    Model::Configure(logger);
}

// Perform custom configuration
void AdcsController::Connect(Smp::ISimulator* simulator)
{
    // Call to the superclass method
    Model::Connect(simulator);
}

// Create a request for the given operation
::Smp::IRequest* AdcsController::CreateRequest(::Smp::String8 operationName)
{
    return this->publication->CreateRequest(operationName);
}

// Invoke the operation for the given request
void AdcsController::Invoke(::Smp::IRequest* request)
{
    if(request != nullptr)
    {
        if(strcmp(request->GetOperationName(), "SetPdParameters") == 0)
        {
            if(request->GetParameterCount() != 2)
                throw ::Smp::IDynamicInvocation::InvalidParameterCount(request->GetOperationName(), 2, request->GetParameterCount());

            if(request->GetParameterValue(0).type != ::Smp::ST_Float64)
                throw ::Smp::IDynamicInvocation::InvalidParameterType("SetPidParameters", "kw",
                    request->GetParameterValue(0).type, ::Smp::ST_Float64);

            if(request->GetParameterValue(1).type != ::Smp::ST_Float64)
                throw ::Smp::IDynamicInvocation::InvalidParameterType("SetPidParameters", "kq",
                    request->GetParameterValue(1).type, ::Smp::ST_Float64);

            // Invoke the method
            this->SetPdParameters(request->GetParameterValue(0).value.float64Value, request->GetParameterValue(1).value.float64Value);
        }

        if(strcmp(request->GetOperationName(), "SetTargetOrientation") == 0)
        {
            if(request->GetParameterCount() != 4)
                throw ::Smp::IDynamicInvocation::InvalidParameterCount(request->GetOperationName(), 4, request->GetParameterCount());

            if(request->GetParameterValue(0).type != ::Smp::ST_Float64)
                throw ::Smp::IDynamicInvocation::InvalidParameterType("SetTargetOrientation", "t0",
                    request->GetParameterValue(0).type, ::Smp::ST_Float64);

            if(request->GetParameterValue(1).type != ::Smp::ST_Float64)
                throw ::Smp::IDynamicInvocation::InvalidParameterType("SetTargetOrientation", "t1",
                    request->GetParameterValue(1).type, ::Smp::ST_Float64);

            if(request->GetParameterValue(2).type != ::Smp::ST_Float64)
                throw ::Smp::IDynamicInvocation::InvalidParameterType("SetTargetOrientation", "t2",
                    request->GetParameterValue(2).type, ::Smp::ST_Float64);

            if(request->GetParameterValue(3).type != ::Smp::ST_Float64)
                throw ::Smp::IDynamicInvocation::InvalidParameterType("SetTargetOrientation", "t3",
                    request->GetParameterValue(3).type, ::Smp::ST_Float64);

            // Invoke the method
            this->SetTargetOrientation(request->GetParameterValue(0).value.float64Value,
                                       request->GetParameterValue(1).value.float64Value,
                                       request->GetParameterValue(2).value.float64Value,
                                       request->GetParameterValue(3).value.float64Value);
       }

       if(strcmp(request->GetOperationName(), "ExecuteControlStep") == 0)
       {
            if(request->GetParameterCount() != 0)
                throw ::Smp::IDynamicInvocation::InvalidParameterCount(request->GetOperationName(), 0, request->GetParameterCount());

            // Invoke the method
            this->ExecuteControlStep();
       }
    }
}

// Delete given request
void AdcsController::DeleteRequest(::Smp::IRequest* request)
{
    this->publication->DeleteRequest(request);
}

// Get gyroscope used by the module
Gyroscope* AdcsController::GetGyroscope()
{
    return this->gyroscope;
}

// Get star tracker used by the module
StarTracker* AdcsController::GetStarTracker()
{
    return this->starTracker;
}

// Get reaction wheel used by the module
ReactionWheel* AdcsController::GetReactionWheel()
{
    return this->reactionWheel;
}

// Get satellite status from sensors
void AdcsController::AcquireSensorsData(std::vector<Smp::Float64>& quaternion, std::vector<Smp::Float64>& omega)
{
    // Angular velocity (omega)
    Smp::Float64* gOmega = this->gyroscope->GetOmega();
    omega.push_back(gOmega[0]);
    omega.push_back(gOmega[1]);
    omega.push_back(gOmega[2]);

    // Orientation (quaternion)
    Smp::Float64* stQuaternion = this->starTracker->GetQuaternion();
    quaternion.push_back(stQuaternion[0]);
    quaternion.push_back(stQuaternion[1]);
    quaternion.push_back(stQuaternion[2]);
    quaternion.push_back(stQuaternion[3]);
}

// Send torque to apply to the reaction wheel
void AdcsController::SendTorqueRw(std::vector<Smp::Float64> torque)
{
    this->reactionWheel->SetTorque(torque.at(0), torque.at(1), torque.at(2));
}

// Get the torque vector to send to reaction wheel according a PD control algorithm
std::vector<Smp::Float64> AdcsController::executePd(std::vector<Smp::Float64> quaternion, std::vector<Smp::Float64> omega)
{
    // Execute PD controllers
    auto torque = this->pdController->execute(quaternion, omega, this->targetOrientation);

    // Return torque
    return torque;
}

// Execute a control step
void AdcsController::ExecuteControlStep()
{
    // Adquire data from sensors
	this->logger->Log(this, "Acquiring satellite status from sensors", Smp::Services::LMK_Information);
    std::vector<Smp::Float64> quaternion, omega;
    this->AcquireSensorsData(quaternion, omega);
	
	// Execute PD controller
    this->logger->Log(this, "Executing PD controller", Smp::Services::LMK_Information);
    auto torque = this->executePd(quaternion, omega);
	
	// Log current value of orientation
	std::ostringstream stream;
	stream << " + Quaternion: " << quaternion.at(0) << "," << quaternion.at(1) << "," << quaternion.at(2) << "," << quaternion.at(3);
	this->logger->Log(this, stream.str().c_str(), Smp::Services::LMK_Information);
	
	// Log value of desired orientation
	stream.str("");
	stream.clear();
	stream << " + Quaternion_ref: " << this->targetOrientation.at(0) << "," << this->targetOrientation.at(1) << "," << this->targetOrientation.at(2) << "," << this->targetOrientation.at(3);
	this->logger->Log(this, stream.str().c_str(), Smp::Services::LMK_Information);
	
	// Log current value of angular velocity
	stream.str("");
	stream.clear();
	stream << " + Omega: " << omega.at(0) << "," << omega.at(1) << "," << omega.at(2);
	this->logger->Log(this, stream.str().c_str(), Smp::Services::LMK_Information);
	
	// Log torque value obtained from PD controller
	stream.str("");
	stream.clear();
	stream << " + Torque: " << torque.at(0) << "," << torque.at(1) << "," << torque.at(2);
	this->logger->Log(this, stream.str().c_str(), Smp::Services::LMK_Information);

	// Set torque obtained to the reaction wheel
    this->logger->Log(this, "Sending torque value to reaction wheel", Smp::Services::LMK_Information);
    this->SendTorqueRw(torque);
}

// Set PID parameters
void AdcsController::SetPdParameters(Smp::Float64 kp, Smp::Float64 kd)
{    
    this->pdController->setKq(kp);
	this->pdController->setKw(kd);
}

// Set value of target orientation
void AdcsController::SetTargetOrientation(Smp::Float64 t0, Smp::Float64 t1, Smp::Float64 t2, Smp::Float64 t3)
{
    this->targetOrientation[0] = t0;
    this->targetOrientation[1] = t1;
    this->targetOrientation[2] = t2;
    this->targetOrientation[3] = t3;
}

// Enable event to perform control step
void AdcsController::EnableCyclicalControlEvent(Smp::Float64 period)
{
    this->controlEventId = this->scheduler->AddSimulationTimeEvent(this->entryPointStep, 0, period, -1);
}

// Disable event to perform control step
void AdcsController::DisableCyclicalControlEvent()
{
    this->scheduler->RemoveEvent(this->controlEventId);
}


}
