
#include "Smp/Publication/ITypeRegistry.h"
#include "GenericComponent.h"


namespace Smp2Simulator
{
namespace Core
{

/*
 *  Type class
 */

class Type : public virtual ::Smp::Publication::IType, public GenericComponent
{

public:
    Type(Smp::String8 name, Smp::String8 description, Smp::SimpleTypeKind stk, Smp::Uuid uuid) : GenericComponent(name, description)
    {
        this->type = stk;
        this->uuid = uuid;
    }

    Smp::SimpleTypeKind GetSimpleType() const;
    const Smp::Uuid GetUuid() const;
    virtual void Publish(Smp::IPublication* receiver,
                         Smp::String8 name,
                         Smp::String8 description,
                         void* address,
                         Smp::Bool view,
                         Smp::Bool state,
                         Smp::Bool input,
                         Smp::Bool output);


protected:
    Smp::SimpleTypeKind type;
    Smp::Uuid uuid;
};


/*
 *  ArrayType class
 */

class ArrayType : public Type
{

public:
    ArrayType(Smp::String8 name, Smp::String8 description, Smp::SimpleTypeKind std, Smp::Uuid uuid, Smp::Int64 arrayCount)
        : Type(name, description, std, uuid)
    {
        this->arrayCount = arrayCount;
    }

    void Publish(Smp::IPublication* receiver,
                 Smp::String8 name,
                 Smp::String8 description,
                 void* address,
                 Smp::Bool view,
                 Smp::Bool state,
                 Smp::Bool input,
                 Smp::Bool output);

protected:
    Smp::Int64 arrayCount;

};


/*
 *  EnumerationType class
 */

class EnumerationType : virtual public ::Smp::Publication::IEnumerationType, public Type
{

public:
    EnumerationType(Smp::String8 name, Smp::String8 description, Smp::Uuid uuid)
        : Type(name, description, Smp::SimpleTypeKind::ST_Duration, uuid) {}

    void AddLiteral(Smp::String8 name, Smp::String8 description, Smp::Int32 value);

};


/*
 *  StructureType class
 */

class StructureType : virtual public ::Smp::Publication::IStructureType, public Type
{

public:
    StructureType(Smp::String8 name, Smp::String8 description)
        : Type(name, description, Smp::SimpleTypeKind::ST_Duration, Smp::Publication::Uuid_Duration) {}

    void AddField(Smp::String8 name,
                  Smp::String8 description,
                  Smp::Uuid uuid,
                  Smp::Int64 offset,
                  Smp::Bool view = true,
                  Smp::Bool state = true,
                  Smp::Bool input = false,
                  Smp::Bool output = false);
};


/*
 *  ClassType class
 */

class ClassType : virtual public ::Smp::Publication::IClassType, public StructureType
{
public:
    ClassType(Smp::String8 name, Smp::String8 description) : StructureType(name, description) {}
};


/*
 *  TypeRegistry class
 */

class TypeRegistry : public virtual ::Smp::Publication::ITypeRegistry
{
public:
    // ITypeRegistry methods
    Smp::Publication::IType* GetType(Smp::SimpleTypeKind type) const;
    Smp::Publication::IType* GetType(Smp::Uuid typeUuid) const;
    const Smp::Publication::IType* AddFloatType(Smp::String8 name,
                                                Smp::String8 description,
                                                Smp::Uuid typeUuid,
                                                Smp::Float64 minimum,
                                                Smp::Float64 maximum,
                                                Smp::Bool minInclusive,
                                                Smp::Bool maxInclusive,
                                                Smp::String8 unit,
                                                Smp::SimpleTypeKind type = Smp::ST_Float64);
    const Smp::Publication::IType* AddIntegerType(Smp::String8 name, Smp::String8 description, Smp::Uuid typeUuid, Smp::Int64 minimum, Smp::Int64 maximum, Smp::SimpleTypeKind type = Smp::ST_Int32);
    Smp::Publication::IEnumerationType* AddEnumerationType(Smp::String8 name, Smp::String8 description, Smp::Uuid typeUuid, Smp::Int16 memorySize);
    const Smp::Publication::IType* AddArrayType(Smp::String8 name, Smp::String8 description, Smp::Uuid typeUuid, Smp::Uuid itemTypeUuid, Smp::Int64 itemSize, Smp::Int64 arrayCount);
    const Smp::Publication::IType* AddStringType(Smp::String8 name, Smp::String8 description, Smp::Uuid typeUuid, Smp::Int64 length);
    Smp::Publication::IStructureType* AddStructureType(Smp::String8 name, Smp::String8 description, Smp::Uuid typeUuid);
    Smp::Publication::IClassType* AddClassType(Smp::String8 name, Smp::String8 description, Smp::Uuid typeUuid, Smp::Uuid baseClassUuid);

protected:
    // Attributes
    std::vector<Type*> registeredTypes;

};

}
}
