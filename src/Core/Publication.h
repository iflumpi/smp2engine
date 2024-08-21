
#include "Smp/IPublication.h"
#include "Smp/Publication/IPublishOperation.h"
#include "Smp/IModel.h"
#include "Common.h"


namespace Smp2Simulator
{
namespace Core
{

class Publication : public Smp::IPublication
{

public:
    // Constructor
    Publication(Smp::Publication::ITypeRegistry* registry)
    {
        this->registry = registry;
    }

    // IPublication methods
    Smp::Publication::ITypeRegistry* GetTypeRegistry() const;
    void PublishField(
        Smp::String8 name, Smp::String8 description, Smp::Char8* address, Smp::Bool view = true, Smp::Bool state = true, Smp::Bool input = false, Smp::Bool output = false);
    void PublishField(
        Smp::String8 name, Smp::String8 description, Smp::Bool* address, Smp::Bool view = true, Smp::Bool state = true, Smp::Bool input = false, Smp::Bool output = false);
    void PublishField(
        Smp::String8 name, Smp::String8 description, Smp::Int8* address, Smp::Bool view = true, Smp::Bool state = true, Smp::Bool input = false, Smp::Bool output = false);
    void PublishField(
        Smp::String8 name, Smp::String8 description, Smp::Int16* address, Smp::Bool view = true, Smp::Bool state = true, Smp::Bool input = false, Smp::Bool output = false);
    void PublishField(
        Smp::String8 name, Smp::String8 description, Smp::Int32* address, Smp::Bool view = true, Smp::Bool state = true, Smp::Bool input = false, Smp::Bool output = false);
    void PublishField(
        Smp::String8 name, Smp::String8 description, Smp::Int64* address, Smp::Bool view = true, Smp::Bool state = true, Smp::Bool input = false, Smp::Bool output = false);
    void PublishField(
        Smp::String8 name, Smp::String8 description, Smp::UInt8* address, Smp::Bool view = true, Smp::Bool state = true, Smp::Bool input = false, Smp::Bool output = false);
    void PublishField(
        Smp::String8 name, Smp::String8 description, Smp::UInt16* address, Smp::Bool view = true, Smp::Bool state = true, Smp::Bool input = false, Smp::Bool output = false);
    void PublishField(
        Smp::String8 name, Smp::String8 description, Smp::UInt32* address, Smp::Bool view = true, Smp::Bool state = true, Smp::Bool input = false, Smp::Bool output = false);
    void PublishField(
        Smp::String8 name, Smp::String8 description, Smp::UInt64* address, Smp::Bool view = true, Smp::Bool state = true, Smp::Bool input = false, Smp::Bool output = false);
    void PublishField(
        Smp::String8 name, Smp::String8 description, Smp::Float32* address, Smp::Bool view = true, Smp::Bool state = true, Smp::Bool input = false, Smp::Bool output = false);
    void PublishField(
        Smp::String8 name, Smp::String8 description, Smp::Float64* address, Smp::Bool view = true, Smp::Bool state = true, Smp::Bool input = false, Smp::Bool output = false);
    void PublishField(Smp::String8 name,
                      Smp::String8 description,
                      void* address,
                      Smp::Uuid typeUuid,
                      Smp::Bool view = true,
                      Smp::Bool state = true,
                      Smp::Bool input = false,
                      Smp::Bool output = false);
    void PublishArray(Smp::String8 name,
                      Smp::String8 description,
                      Smp::Int64 count,
                      void* address,
                      Smp::SimpleTypeKind type,
                      Smp::Bool view = true,
                      Smp::Bool state = true,
                      Smp::Bool input = false,
                      Smp::Bool output = false);
    IPublication* PublishArray(Smp::String8 name, Smp::String8 description);
    IPublication* PublishStructure(Smp::String8 name, Smp::String8 description);
    Smp::Publication::IPublishOperation* PublishOperation(Smp::String8 name, Smp::String8 description, Smp::Uuid returnTypeUuid);
    void PublishProperty(Smp::String8 name, Smp::String8 description, Smp::Uuid typeUuid, Smp::AccessKind accessKind);
    Smp::AnySimple GetFieldValue(Smp::String8 fullName);
    void SetFieldValue(Smp::String8 fullName, Smp::AnySimple value);
    void GetArrayValue(Smp::String8 fullName, Smp::AnySimpleArray values, Smp::Int32 length);
    void SetArrayValue(Smp::String8 fullName, Smp::AnySimpleArray values, Smp::Int32 length);
    Smp::IRequest* CreateRequest(Smp::String8 operationName);
    void DeleteRequest(Smp::IRequest* request);

    // Methods
    std::vector<FieldPublished*> GetFieldsPublished();
    void SetTypeRegistry(Smp::Publication::ITypeRegistry* registry);
    std::vector<OperationPublished*> GetOperationsPublished();
    FieldPublished* GetField(Smp::String8 fullName);
    bool IsArrayField(FieldPublished* field);
    OperationPublished* GetOperation(Smp::String8 fullName);
    Smp::String8 GetFullNameField(FieldPublished* field);
    Smp::String8 GetFullNameOperation(OperationPublished* field);
    Smp::AnySimple GetArrayItemValue(Smp::String8 fullName, int index);
    void SetArrayItemValue(Smp::String8 fullName, int index, Smp::AnySimple value);
    void SetCurrentPublisherModel(Smp::IModel* model);


protected:
    // Attributes
    Smp::Publication::ITypeRegistry* registry;
    std::vector<FieldPublished*> fieldsPublished;
    std::vector<OperationPublished*> operationsPublished;
    Smp::IModel* currentPublisherModel = nullptr;

    // Methods
    void AddFieldPublished(Smp::IModel* model, Smp::String8 name, Smp::String8 description, void* address, Smp::SimpleTypeKind typeKind,
                           Smp::Bool view, Smp::Bool state, Smp::Bool input, Smp::Bool output);
    void AddArrayFieldPublished(Smp::IModel* model, Smp::String8 name, Smp::String8 description, Smp::Int64 count,
                                void* address, Smp::SimpleTypeKind typeKind,
                                Smp::Bool view, Smp::Bool state, Smp::Bool input, Smp::Bool output);
    Smp::SimpleTypeValue GetSimpleTypeValue(FieldPublished* field);
    Smp::AnySimple GetArrayItemValueFromField(ArrayFieldPublished* arrayField, int index);
    void SetArrayItemValueFromField(ArrayFieldPublished* arrayField, int index, Smp::AnySimple anyValue);

};

}
}
