
#include "Smp/Publication/IPublishOperation.h"
#include "Common.h"


namespace Smp2Simulator
{
namespace Core
{

class PublishOperation : public Smp::Publication::IPublishOperation
{

public:
    // Constructor
    PublishOperation(Smp::String8 name, Smp::String8 description, Smp::Uuid returnTypeUuid)
    {
        this->operationDescriptor = new OperationParameter();
        operationDescriptor->name = name;
        operationDescriptor->description = description;
        operationDescriptor->typeUuid = returnTypeUuid;
    };

    // IPublishOperation methods
    void PublishParameter(Smp::String8 name, Smp::String8 description, Smp::Uuid typeUuid);

    // Methods
    Smp::String8 GetName();
    Smp::String8 GetDescription();
    Smp::Uuid GetTypeUuid();
    std::vector<OperationParameter*> GetParameters();

protected:
    // Attributes
    OperationParameter* operationDescriptor;
    std::vector<OperationParameter*> parameters;

};

}
}
