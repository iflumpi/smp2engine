
#include "PublishOperation.h"


namespace Smp2Simulator
{
namespace Core
{

// Publish a parameter of an operation
void PublishOperation::PublishParameter(Smp::String8 name, Smp::String8 description, Smp::Uuid typeUuid)
{
    auto parameter = new OperationParameter();
    parameter->name = name;
    parameter->description = description;
    parameter->typeUuid = typeUuid;

    this->parameters.push_back(parameter);
}

// Get the name of the operation
Smp::String8 PublishOperation::GetName()
{
    return this->operationDescriptor->name;
}

// Get the description of the operation
Smp::String8 PublishOperation::GetDescription()
{
    return this->operationDescriptor->description;
}

// Get the uuid type of the operation
Smp::Uuid PublishOperation::GetTypeUuid()
{
    return this->operationDescriptor->typeUuid;
}

// Get the parameters of the operation
std::vector<OperationParameter*> PublishOperation::GetParameters()
{
    return this->parameters;
}

}
}
