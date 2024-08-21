
#include "TypeRegistry.h"
#include "Common.h"
#include "Publication.h"


namespace Smp2Simulator
{
namespace Core
{


/*
 *  Type class
 */

// Get simple type that this type describes
Smp::SimpleTypeKind Type::GetSimpleType() const
{
    return Smp::SimpleTypeKind::ST_Int8;
}

// Get Universally Unique Identifier of type
const Smp::Uuid Type::GetUuid() const
{
    return this->uuid;
}

// Publish an instance of the type against a receiver
void Type::Publish(Smp::IPublication* receiver,
                   Smp::String8 name,
                   Smp::String8 description,
                   void* address,
                   Smp::Bool view,
                   Smp::Bool state,
                   Smp::Bool input,
                   Smp::Bool output)
{
    receiver->PublishField(name, description, address, this->GetUuid(), view, state, input, output);
}

/*
 *  ArrayType class
 */

// Publish an instance of the type against a receiver
void ArrayType::Publish(Smp::IPublication* receiver,
                        Smp::String8 name,
                        Smp::String8 description,
                        void* address,
                        Smp::Bool view,
                        Smp::Bool state,
                        Smp::Bool input,
                        Smp::Bool output)
{
    receiver->PublishArray(name, description, this->arrayCount, address, this->type, view, state, input, output);
}


/*
 *  EnumerateType class
 */

// Add a literal to the enumerate type
void EnumerationType::AddLiteral(Smp::String8 name, Smp::String8 description, Smp::Int32 value)
{
}


/*
 *  StructureType class
 */

void StructureType::AddField(Smp::String8 name,
                             Smp::String8 description,
                             Smp::Uuid uuid,
                             Smp::Int64 offset,
                             Smp::Bool view,
                             Smp::Bool state,
                             Smp::Bool input,
                             Smp::Bool output)
{
}


/*
 *  TypeRegistry class
 */

// Returns a type by its simple type kind
Smp::Publication::IType* TypeRegistry::GetType(Smp::SimpleTypeKind type) const
{
    auto trType = new Type("", "", type, Common::GetUuid(type));
    return trType;
}

// Returns a type by universally unique identifier
Smp::Publication::IType* TypeRegistry::GetType(Smp::Uuid typeUuid) const
{
    for (int i=0; i<this->registeredTypes.size(); i++)
    {
        auto trType = this->registeredTypes.at(i);
        if (Common::EqualUuid(trType->GetUuid(), typeUuid))
            return trType;
    }
    return nullptr;
}

// Add a float type to the registry
const Smp::Publication::IType* TypeRegistry::AddFloatType(Smp::String8 name,
                                                          Smp::String8 description,
                                                          Smp::Uuid typeUuid,
                                                          Smp::Float64 minimum,
                                                          Smp::Float64 maximum,
                                                          Smp::Bool minInclusive,
                                                          Smp::Bool maxInclusive,
                                                          Smp::String8 unit,
                                                          Smp::SimpleTypeKind type)
{
    // NOT IMPLEMENTED
    auto stp = new Type("", "", Smp::SimpleTypeKind::ST_Float32, Smp::Publication::Uuid_Float32);
    return stp;
}

// Add an integer type to the registry
const Smp::Publication::IType* TypeRegistry::AddIntegerType(Smp::String8 name, Smp::String8 description, Smp::Uuid typeUuid, Smp::Int64 minimum, Smp::Int64 maximum, Smp::SimpleTypeKind type)
{
    // NOT IMPLEMENTED
    auto stp = new Type("", "", Smp::ST_Int64, Smp::Publication::Uuid_UInt64);
    return stp;
}

// Add an enumeration type to the registry
Smp::Publication::IEnumerationType* TypeRegistry::AddEnumerationType(Smp::String8 name, Smp::String8 description, Smp::Uuid typeUuid, Smp::Int16 memorySize)
{
    // NOT IMPLEMENTED
    auto enumType = new EnumerationType("", "", typeUuid);
    return enumType;
}

// Add an array type to the registry
const Smp::Publication::IType* TypeRegistry::AddArrayType(Smp::String8 name, Smp::String8 description, Smp::Uuid typeUuid, Smp::Uuid itemTypeUuid, Smp::Int64 itemSize, Smp::Int64 arrayCount)
{
    auto stkItem = Common::GetSimpleTypeKind(itemTypeUuid);
    auto trType = new ArrayType(name, description, stkItem, typeUuid, arrayCount);
    this->registeredTypes.push_back(trType);
    return trType;
}

// Add a string type to the registry
const Smp::Publication::IType* TypeRegistry::AddStringType(Smp::String8 name, Smp::String8 description, Smp::Uuid typeUuid, Smp::Int64 length)
{
    // NOT IMPLEMENTED
    auto stp = new Type("", "", Smp::ST_String8, Smp::Publication::Uuid_String8);
    return stp;
}

// Add a structure type to the registry
Smp::Publication::IStructureType* TypeRegistry::AddStructureType(Smp::String8 name, Smp::String8 description, Smp::Uuid typeUuid)
{
    // NOT IMPLEMENTED
    return new StructureType("", "");
}

// Add a class type to the registry
Smp::Publication::IClassType* TypeRegistry::AddClassType(Smp::String8 name, Smp::String8 description, Smp::Uuid typeUuid, Smp::Uuid baseClassUuid)
{
    // NOT IMPLEMENTED
    return new ClassType("", "");
}

}
}
