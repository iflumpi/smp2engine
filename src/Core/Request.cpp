
#include "Request.h"


namespace Smp2Simulator
{
namespace Core
{

// Constructor
Request::Request(Smp::String8 operationName, Smp::Uuid typeUuid, std::vector<OperationParameter*> operationParameters)
{
    this->operationName = operationName;
    this->typeKind = Common::GetSimpleTypeKind(typeUuid);
    for (int i=0; i<operationParameters.size(); i++)
    {
        auto operationParameter = operationParameters.at(i);
        auto requestParameter = new RequestParameter();
        requestParameter->name = operationParameter->name;
        requestParameter->value = Smp::AnySimple();
        requestParameter->value.type = Common::GetSimpleTypeKind(operationParameter->typeUuid);
        this->requestParameters.push_back(requestParameter);
    }
    this->returnValue = Common::CreateAnySimple("", Smp::ST_None);
}

// Get name of the operation
Smp::String8 Request::GetOperationName() const
{
    return this->operationName;
}

// Get number of parameters of the operation
Smp::Int32 Request::GetParameterCount() const
{
    return this->requestParameters.size();
}

// Get position of a parameter
Smp::Int32 Request::GetParameterIndex(Smp::String8 parameterName) const
{
    for (int i=0; i<this->requestParameters.size(); i++)
    {
        auto requestParameter = this->requestParameters.at(i);
        if (strcmp(requestParameter->name, parameterName))
            return i;
    }

    return -1;
}

// Set the value of a parameter
void Request::SetParameterValue(Smp::Int32 index, Smp::AnySimple value)
{
    auto requestParameter = this->requestParameters.at(index);
    requestParameter->value = value;
}

// Get the value of a parameter
Smp::AnySimple Request::GetParameterValue(Smp::Int32 index) const
{
    auto requestParameter = this->requestParameters.at(index);
    return (requestParameter->value);
}

// Set the value of the operation response
void Request::SetReturnValue(Smp::AnySimple value)
{
    this->returnValue = value;
}

// Get the value of the operation response
Smp::AnySimple Request::GetReturnValue() const
{
    return this->returnValue;
}

}
}
