
#include "Smp/IRequest.h"
#include "Common.h"


namespace Smp2Simulator
{
namespace Core
{


class Request : public Smp::IRequest
{

public:
    // Constructor
    Request(Smp::String8 operationName, Smp::Uuid typeUuid, std::vector<OperationParameter*> operationParameters);

    // IRequest methods
    virtual Smp::String8 GetOperationName() const;
    virtual Smp::Int32 GetParameterCount() const;
    virtual Smp::Int32 GetParameterIndex(Smp::String8 parameterName) const ;
    virtual void SetParameterValue(Smp::Int32 index, Smp::AnySimple value);
    virtual Smp::AnySimple GetParameterValue(Smp::Int32 index) const;
    virtual void SetReturnValue(Smp::AnySimple value);
    virtual Smp::AnySimple GetReturnValue() const;

protected:
    // Attributes
    Smp::String8 operationName;
    Smp::SimpleTypeKind typeKind;
    Smp::AnySimple returnValue;
    std::vector<RequestParameter *> requestParameters;

};

}
}
