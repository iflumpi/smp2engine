
#include "Publication.h"

#include "PublishOperation.h"
#include "Request.h"


namespace Smp2Simulator
{
namespace Core
{

// Give access to the global type registry
Smp::Publication::ITypeRegistry* Publication::GetTypeRegistry() const
{
    return this->registry;
}

// Publish Char8 field
void Publication::PublishField(
    Smp::String8 name, Smp::String8 description, Smp::Char8* address, Smp::Bool view, Smp::Bool state, Smp::Bool input, Smp::Bool output)
{
    this->AddFieldPublished(this->currentPublisherModel, name, description, address, Smp::SimpleTypeKind::ST_Char8, view, state, input, output);
}

// Publish a Bool field
void Publication::PublishField(
   Smp::String8 name, Smp::String8 description, Smp::Bool* address, Smp::Bool view, Smp::Bool state, Smp::Bool input, Smp::Bool output)
{
    this->AddFieldPublished(this->currentPublisherModel, name, description, address, Smp::SimpleTypeKind::ST_Bool, view, state, input, output);
}

// Publish Int8 field
void Publication::PublishField(
   Smp::String8 name, Smp::String8 description, Smp::Int8* address, Smp::Bool view, Smp::Bool state, Smp::Bool input, Smp::Bool output)
{
    this->AddFieldPublished(this->currentPublisherModel, name, description, address, Smp::SimpleTypeKind::ST_Int8, view, state, input, output);
}

// Publish Int16 field
void Publication::PublishField(
   Smp::String8 name, Smp::String8 description, Smp::Int16* address, Smp::Bool view, Smp::Bool state, Smp::Bool input, Smp::Bool output)
{
    this->AddFieldPublished(this->currentPublisherModel, name, description, address, Smp::SimpleTypeKind::ST_Int16, view, state, input, output);
}

// Publish Int32 field
void Publication::PublishField(
   Smp::String8 name, Smp::String8 description, Smp::Int32* address, Smp::Bool view, Smp::Bool state, Smp::Bool input, Smp::Bool output)
{
    this->AddFieldPublished(this->currentPublisherModel, name, description, address, Smp::SimpleTypeKind::ST_Int32, view, state, input, output);
}

// Publish Int64 field
void Publication::PublishField(
   Smp::String8 name, Smp::String8 description, Smp::Int64* address, Smp::Bool view, Smp::Bool state, Smp::Bool input, Smp::Bool output)
{
    this->AddFieldPublished(this->currentPublisherModel, name, description, address, Smp::SimpleTypeKind::ST_Int64, view, state, input, output);
}

// Publish UInt8 field
void Publication::PublishField(
   Smp::String8 name, Smp::String8 description, Smp::UInt8* address, Smp::Bool view, Smp::Bool state, Smp::Bool input, Smp::Bool output)
{
    this->AddFieldPublished(this->currentPublisherModel, name, description, address, Smp::SimpleTypeKind::ST_UInt8, view, state, input, output);
}

// Publish UInt16 field
void Publication::PublishField(
   Smp::String8 name, Smp::String8 description, Smp::UInt16* address, Smp::Bool view, Smp::Bool state, Smp::Bool input, Smp::Bool output)
{
    this->AddFieldPublished(this->currentPublisherModel, name, description, address, Smp::SimpleTypeKind::ST_UInt16, view, state, input, output);
}

// Publish UInt32 field
void Publication::PublishField(
   Smp::String8 name, Smp::String8 description, Smp::UInt32* address, Smp::Bool view, Smp::Bool state, Smp::Bool input, Smp::Bool output)
{
    this->AddFieldPublished(this->currentPublisherModel, name, description, address, Smp::SimpleTypeKind::ST_UInt32, view, state, input, output);
}

// Publish UInt64 field
void Publication::PublishField(
   Smp::String8 name, Smp::String8 description, Smp::UInt64* address, Smp::Bool view, Smp::Bool state, Smp::Bool input, Smp::Bool output)
{
    this->AddFieldPublished(this->currentPublisherModel, name, description, address, Smp::SimpleTypeKind::ST_UInt64, view, state, input, output);
}

// Publish Float32 field
void Publication::PublishField(
   Smp::String8 name, Smp::String8 description, Smp::Float32* address, Smp::Bool view, Smp::Bool state, Smp::Bool input, Smp::Bool output)
{
    this->AddFieldPublished(this->currentPublisherModel, name, description, address, Smp::SimpleTypeKind::ST_Float32, view, state, input, output);
}

// Publish Float64 field
void Publication::PublishField(
   Smp::String8 name, Smp::String8 description, Smp::Float64* address, Smp::Bool view, Smp::Bool state, Smp::Bool input, Smp::Bool output)
{
    this->AddFieldPublished(this->currentPublisherModel, name, description, address, Smp::SimpleTypeKind::ST_Float64, view, state, input, output);
}

// Publish field of any type
void Publication::PublishField(Smp::String8 name,
                               Smp::String8 description,
                               void* address,
                               Smp::Uuid typeUuid,
                               Smp::Bool view,
                               Smp::Bool state,
                               Smp::Bool input,
                               Smp::Bool output)
{
    auto trType = this->registry->GetType(typeUuid);
    if (trType != nullptr)
        trType->Publish(this, name, description, address, view, state, input, output);
}

// Publish array of simple type
void Publication::PublishArray(Smp::String8 name,
                               Smp::String8 description,
                               Smp::Int64 count,
                               void* address,
                               Smp::SimpleTypeKind type,
                               Smp::Bool view,
                               Smp::Bool state,
                               Smp::Bool input,
                               Smp::Bool output)
{
    this->AddArrayFieldPublished(this->currentPublisherModel, name, description, count, address, type, view, state, input, output);
}

// Publish array of any type
Smp::IPublication* Publication::PublishArray(Smp::String8 name, Smp::String8 description)
{
    // NOT IMPLEMENTED
    return nullptr;
}

// Publish structure
Smp::IPublication* Publication::PublishStructure(Smp::String8 name, Smp::String8 description)
{
    // NOT IMPLEMENTED
    return nullptr;
}

// Publish an operation with complex return type
Smp::Publication::IPublishOperation* Publication::PublishOperation(Smp::String8 name, Smp::String8 description, Smp::Uuid returnTypeUuid)
{
    auto operation = new OperationPublished();
    operation->model = this->currentPublisherModel;
    operation->publishOperation = new Smp2Simulator::Core::PublishOperation(name, description, returnTypeUuid);
    this->operationsPublished.push_back(operation);
    return operation->publishOperation;
}

// Publish a property
void Publication::PublishProperty(Smp::String8 name, Smp::String8 description, Smp::Uuid typeUuid, Smp::AccessKind accessKind)
{
    // NOT IMPLEMENTED
}

// Get a simple type value from according to the type of a field
Smp::SimpleTypeValue Publication::GetSimpleTypeValue(FieldPublished* field)
{
    Smp::SimpleTypeValue stv = Smp::SimpleTypeValue();

    switch (field->typeKind)
    {
        case Smp::SimpleTypeKind::ST_Bool:
            stv.boolValue = *(Smp::Bool*)field->address;
            break;

        case Smp::SimpleTypeKind::ST_Char8:
            stv.char8Value = *(Smp::Char8*)field->address;
            break;

        case Smp::SimpleTypeKind::ST_DateTime:
            stv.dateTimeValue = *(Smp::DateTime*)field->address;
            break;

        case Smp::SimpleTypeKind::ST_Duration:
            stv.durationValue = *(Smp::Duration*)field->address;
            break;

        case Smp::SimpleTypeKind::ST_Float32:
            stv.float32Value = *(Smp::Float32*)field->address;
            break;

        case Smp::SimpleTypeKind::ST_Float64:
            stv.float64Value = *(Smp::Float64*)field->address;
            break;

        case Smp::SimpleTypeKind::ST_Int8:
            stv.int8Value = *(Smp::Int8*)field->address;
            break;

        case Smp::SimpleTypeKind::ST_Int16:
            stv.int16Value = *(Smp::Int16*)field->address;
            break;

        case Smp::SimpleTypeKind::ST_Int32:
            stv.int32Value = *(Smp::Int32*)field->address;
            break;

        case Smp::SimpleTypeKind::ST_Int64:
            stv.int64Value = *(Smp::Int64*)field->address;
            break;

        case Smp::SimpleTypeKind::ST_String8:
            stv.string8Value = *(Smp::String8*)field->address;
            break;

        case Smp::SimpleTypeKind::ST_UInt8:
            stv.uInt8Value = *(Smp::UInt8*)field->address;
            break;

        case Smp::SimpleTypeKind::ST_UInt16:
            stv.uInt16Value = *(Smp::UInt16*)field->address;
            break;

        case Smp::SimpleTypeKind::ST_UInt32:
            stv.uInt32Value = *(Smp::UInt32*)field->address;
            break;

        case Smp::SimpleTypeKind::ST_UInt64:
            stv.uInt64Value = *(Smp::UInt64*)field->address;
            break;

    }

    return stv;
}

// Get the value of a field which is typed by a system type.
Smp::AnySimple Publication::GetFieldValue(Smp::String8 fullName)
{
    Smp::AnySimple any = Smp::AnySimple();
    auto field = this->GetField(fullName);
    if (field != nullptr)
    {
        Smp::SimpleTypeValue stv = this->GetSimpleTypeValue(field);
		any.type = field->typeKind;
        any.value = stv;
    }
    return any;
}

// Set the value of a field which is typed by a system type
void Publication::SetFieldValue(Smp::String8 fullName, Smp::AnySimple value)
{
    auto field = this->GetField(fullName);
    if (field != nullptr)
    {
        switch (field->typeKind)
        {
            case Smp::SimpleTypeKind::ST_Bool:
                *(Smp::Bool*)field->address = value.value.boolValue;
                break;

            case Smp::SimpleTypeKind::ST_Char8:
                *(Smp::Char8*)field->address = value.value.char8Value;
                break;

            case Smp::SimpleTypeKind::ST_DateTime:
                *(Smp::DateTime*)field->address = value.value.dateTimeValue;
                break;

            case Smp::SimpleTypeKind::ST_Duration:
                *(Smp::Duration*)field->address = value.value.durationValue;
                break;

            case Smp::SimpleTypeKind::ST_Float32:
                *(Smp::Float32*)field->address = value.value.float32Value;
                break;

            case Smp::SimpleTypeKind::ST_Float64:
                *(Smp::Float64*)field->address = value.value.float64Value;
                break;

            case Smp::SimpleTypeKind::ST_Int8:
                *(Smp::Int8*)field->address = value.value.int8Value;
                break;

            case Smp::SimpleTypeKind::ST_Int16:
                *(Smp::Int16*)field->address = value.value.int16Value;
                break;

            case Smp::SimpleTypeKind::ST_Int32:
                *(Smp::Int32*)field->address = value.value.int32Value;
                break;

            case Smp::SimpleTypeKind::ST_Int64:
                *(Smp::Int64*)field->address = value.value.int64Value;
                break;

            case Smp::SimpleTypeKind::ST_String8:
                *(Smp::String8*)field->address = value.value.string8Value;
                break;

            case Smp::SimpleTypeKind::ST_UInt8:
                *(Smp::UInt8*)field->address = value.value.uInt8Value;
                break;

            case Smp::SimpleTypeKind::ST_UInt16:
                *(Smp::UInt16*)field->address = value.value.uInt16Value;
                break;

            case Smp::SimpleTypeKind::ST_UInt32:
                *(Smp::UInt32*)field->address = value.value.uInt32Value;
                break;

            case Smp::SimpleTypeKind::ST_UInt64:
                *(Smp::UInt64*)field->address = value.value.uInt64Value;
                break;

        }
    }
}

// Get the value of an array field which is typed by a system type
void Publication::GetArrayValue(Smp::String8 fullName, Smp::AnySimpleArray values, Smp::Int32 length)
{
    auto field = this->GetField(fullName);
    auto arrayField = (ArrayFieldPublished *)(field);
    if (arrayField != nullptr)
    {
        for (int i=0; i<length; i++)
        {
            auto value = this->GetArrayItemValueFromField(arrayField, i);
            values[i] = value;
        }
    }
}

// Set the value of an array field which is typed by a system type
void Publication::SetArrayValue(Smp::String8 fullName, Smp::AnySimpleArray values, Smp::Int32 length)
{
    // NOT IMPLEMENTED
}

// Create request Object
Smp::IRequest* Publication::CreateRequest(Smp::String8 operationName)
{
    for (int i=0; i<this->operationsPublished.size(); i++)
    {
        auto operation = this->operationsPublished.at(i);
        auto publishOperation = (Smp2Simulator::Core::PublishOperation*)operation->publishOperation;
        if (strcmp(operationName, publishOperation->GetName()) == 0)
        {
            auto request = new Request(publishOperation->GetName(), publishOperation->GetTypeUuid(), publishOperation->GetParameters());
            return request;
        }
    }

    return nullptr;
}

// Delete request object
void Publication::DeleteRequest(Smp::IRequest* request)
{
    delete request;
}

// Get full name of a field
Smp::String8 Publication::GetFullNameField(FieldPublished* field)
{
    std::string fullName = "";
    fullName.append(field->model->GetName());
    fullName.append(".");
    fullName.append(field->name);
    return fullName.c_str();
}

// Get full name of a operation
Smp::String8 Publication::GetFullNameOperation(OperationPublished* operation)
{
    std::string fullName = "";
    auto publishOperation = (Smp2Simulator::Core::PublishOperation*)operation->publishOperation;
    fullName.append(operation->model->GetName());
    fullName.append(".");
    fullName.append(publishOperation->GetName());
    return fullName.c_str();
}

// Get field by its full name
FieldPublished* Publication::GetField(Smp::String8 fullName)
{
    for (int i=0; i<this->fieldsPublished.size(); i++)
    {
        auto field = this->fieldsPublished[i];
        auto fieldFullName = this->GetFullNameField(field);
        if (strcmp(fieldFullName, fullName) == 0)
        {
            return field;
        }
    }

    return nullptr;
}

// Check whether the type of a field is array
bool Publication::IsArrayField(FieldPublished* field)
{
    auto arrayField = (ArrayFieldPublished *)(field);
    return arrayField != nullptr;
}

// Get operation by its full name
OperationPublished* Publication::GetOperation(Smp::String8 fullName)
{
    for (int i=0; i<this->operationsPublished.size(); i++)
    {
        auto operation = this->operationsPublished[i];
        auto operationFullName = this->GetFullNameOperation(operation);
        if (strcmp(operationFullName, fullName) == 0)
        {
            return operation;
        }
    }

    return nullptr;
}

// Get all the published fields
std::vector<FieldPublished*> Publication::GetFieldsPublished()
{
    return this->fieldsPublished;
}

// Get all the published operations
std::vector<OperationPublished*> Publication::GetOperationsPublished()
{
    return this->operationsPublished;
}

// Add a field to the published fields list
void Publication::AddFieldPublished(Smp::IModel* model, Smp::String8 name, Smp::String8 description, void* address, Smp::SimpleTypeKind typeKind,
                                    Smp::Bool view, Smp::Bool state, Smp::Bool input, Smp::Bool output)
{
    auto field = new FieldPublished();

    field->model = model;
    field->name = name;
    field->description = description;
    field->address = address;
    field->typeKind = typeKind;
    field->view = view;
    field->state = state;
    field->input = input;
    field->output = output;

    this->fieldsPublished.push_back(field);
}

// Add a array field to the published array fields list
void Publication::AddArrayFieldPublished(Smp::IModel* model, Smp::String8 name, Smp::String8 description, Smp::Int64 count,
                                         void* address, Smp::SimpleTypeKind typeKind,
                                         Smp::Bool view, Smp::Bool state, Smp::Bool input, Smp::Bool output)
{
    auto field = new ArrayFieldPublished();

    field->model = model;
    field->name = name;
    field->description = description;
    field->count = count;
    field->address = address;
    field->typeKind = typeKind;
    field->view = view;
    field->state = state;
    field->input = input;
    field->output = output;

    this->fieldsPublished.push_back(field);

}

// Get the value of a array item from its name
Smp::AnySimple Publication::GetArrayItemValue(Smp::String8 fullName, int index)
{
    auto field = this->GetField(fullName);
    auto arrayField = (ArrayFieldPublished *)(field);
    if (arrayField != nullptr)
    {
        return this->GetArrayItemValueFromField(arrayField, index);
    }
    else
    {
        Smp::AnySimple any;
        return any;
    }
}

// Set the value of a array item from its name
void Publication::SetArrayItemValue(Smp::String8 fullName, int index, Smp::AnySimple value)
{
    auto field = this->GetField(fullName);
    auto arrayField = (ArrayFieldPublished *)(field);
    if (arrayField != nullptr)
    {
        this->SetArrayItemValueFromField(arrayField, index, value);
    }
}

// Get the value of a array item from a published field
Smp::AnySimple Publication::GetArrayItemValueFromField(ArrayFieldPublished* arrayField, int index)
{
    switch (arrayField->typeKind)
    {
        case Smp::SimpleTypeKind::ST_Bool:
            return Common::CreateAnySimple(
                std::to_string(((Smp2Array<Smp::Bool>*)arrayField->address)->internalArray[index]).c_str(),
                Smp::ST_Bool);

        case Smp::SimpleTypeKind::ST_Char8:
            return Common::CreateAnySimple(
                std::to_string(((Smp2Array<Smp::Char8>*)arrayField->address)->internalArray[index]).c_str(),
                Smp::ST_Char8);

        case Smp::SimpleTypeKind::ST_DateTime:
            return Common::CreateAnySimple(
                std::to_string(((Smp2Array<Smp::DateTime>*)arrayField->address)->internalArray[index]).c_str(),
                Smp::ST_DateTime);

        case Smp::SimpleTypeKind::ST_Duration:
            return Common::CreateAnySimple(
                std::to_string(((Smp2Array<Smp::Duration>*)arrayField->address)->internalArray[index]).c_str(),
                Smp::ST_Duration);

        case Smp::SimpleTypeKind::ST_Float32:
            return Common::CreateAnySimple(
                std::to_string(((Smp2Array<Smp::Float32>*)arrayField->address)->internalArray[index]).c_str(),
                Smp::ST_Float32);

        case Smp::SimpleTypeKind::ST_Float64:
            return Common::CreateAnySimple(
                std::to_string(((Smp2Array<Smp::Float64>*)arrayField->address)->internalArray[index]).c_str(),
                Smp::ST_Float64);

        case Smp::SimpleTypeKind::ST_Int8:
            return Common::CreateAnySimple(
                std::to_string(((Smp2Array<Smp::Int8>*)arrayField->address)->internalArray[index]).c_str(),
                Smp::ST_Int8);

        case Smp::SimpleTypeKind::ST_Int16:
            return Common::CreateAnySimple(
                std::to_string(((Smp2Array<Smp::Int16>*)arrayField->address)->internalArray[index]).c_str(),
                Smp::ST_Int16);

        case Smp::SimpleTypeKind::ST_Int32:
            return Common::CreateAnySimple(
                std::to_string(((Smp2Array<Smp::Int32>*)arrayField->address)->internalArray[index]).c_str(),
                Smp::ST_Int32);

        case Smp::SimpleTypeKind::ST_Int64:
            return Common::CreateAnySimple(
                std::to_string(((Smp2Array<Smp::Int64>*)arrayField->address)->internalArray[index]).c_str(),
                Smp::ST_Int64);

        case Smp::SimpleTypeKind::ST_UInt8:
            return Common::CreateAnySimple(
                std::to_string(((Smp2Array<Smp::UInt8>*)arrayField->address)->internalArray[index]).c_str(),
                Smp::ST_UInt8);

        case Smp::SimpleTypeKind::ST_UInt16:
            return Common::CreateAnySimple(
                std::to_string(((Smp2Array<Smp::UInt16>*)arrayField->address)->internalArray[index]).c_str(),
                Smp::ST_UInt16);

        case Smp::SimpleTypeKind::ST_UInt32:
            return Common::CreateAnySimple(
                std::to_string(((Smp2Array<Smp::UInt32>*)arrayField->address)->internalArray[index]).c_str(),
                Smp::ST_UInt32);

        case Smp::SimpleTypeKind::ST_UInt64:
            return Common::CreateAnySimple(
                std::to_string(((Smp2Array<Smp::UInt64>*)arrayField->address)->internalArray[index]).c_str(),
                Smp::ST_UInt64);

        default:
            return Smp::AnySimple();
    }
}

// Set the value of a array item from a published field
void Publication::SetArrayItemValueFromField(ArrayFieldPublished* arrayField, int index, Smp::AnySimple anyValue)
{
    switch (arrayField->typeKind)
    {
        case Smp::SimpleTypeKind::ST_Bool:
            ((Smp2Array<Smp::Bool>*)arrayField->address)->internalArray[index] = anyValue.value.boolValue;
            break;

        case Smp::SimpleTypeKind::ST_Char8:
            ((Smp2Array<Smp::Char8>*)arrayField->address)->internalArray[index] = anyValue.value.char8Value;
            break;

        case Smp::SimpleTypeKind::ST_DateTime:
            ((Smp2Array<Smp::DateTime>*)arrayField->address)->internalArray[index] = anyValue.value.dateTimeValue;
            break;

        case Smp::SimpleTypeKind::ST_Duration:
            ((Smp2Array<Smp::Duration>*)arrayField->address)->internalArray[index] = anyValue.value.durationValue;
            break;

        case Smp::SimpleTypeKind::ST_Float32:
            ((Smp2Array<Smp::Float32>*)arrayField->address)->internalArray[index] = anyValue.value.float32Value;
            break;

        case Smp::SimpleTypeKind::ST_Float64:
            ((Smp2Array<Smp::Float64>*)arrayField->address)->internalArray[index] = anyValue.value.float64Value;
            break;

        case Smp::SimpleTypeKind::ST_Int8:
            ((Smp2Array<Smp::Int8>*)arrayField->address)->internalArray[index] = anyValue.value.int8Value;
            break;

        case Smp::SimpleTypeKind::ST_Int16:
            ((Smp2Array<Smp::Int16>*)arrayField->address)->internalArray[index] = anyValue.value.int16Value;
            break;

        case Smp::SimpleTypeKind::ST_Int32:
            ((Smp2Array<Smp::Int32>*)arrayField->address)->internalArray[index] = anyValue.value.int32Value;
            break;

        case Smp::SimpleTypeKind::ST_Int64:
            ((Smp2Array<Smp::Int64>*)arrayField->address)->internalArray[index] = anyValue.value.int64Value;
            break;

        case Smp::SimpleTypeKind::ST_UInt8:
            ((Smp2Array<Smp::UInt8>*)arrayField->address)->internalArray[index] = anyValue.value.uInt8Value;
            break;

        case Smp::SimpleTypeKind::ST_UInt16:
            ((Smp2Array<Smp::UInt16>*)arrayField->address)->internalArray[index] = anyValue.value.uInt16Value;
            break;

        case Smp::SimpleTypeKind::ST_UInt32:
            ((Smp2Array<Smp::UInt32>*)arrayField->address)->internalArray[index] = anyValue.value.uInt32Value;
            break;

        case Smp::SimpleTypeKind::ST_UInt64:
            ((Smp2Array<Smp::UInt64>*)arrayField->address)->internalArray[index] = anyValue.value.uInt64Value;
            break;

        default:
            break;
    }
}

// Set current publisher model
void Publication::SetCurrentPublisherModel(Smp::IModel* model)
{
    this->currentPublisherModel = model;
}

}
}
