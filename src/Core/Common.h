
#pragma once

#include "Smp/SimpleTypes.h"
#include "Smp/IModel.h"
#include "Smp/Publication/IPublishOperation.h"


namespace Smp2Simulator
{
namespace Core
{


/*
 * Struct Smp2Array
 */

const int MAX_ARRAY_SIZE = 1000;
template <class ArrayItemType> struct Smp2Array
{
    ArrayItemType internalArray[MAX_ARRAY_SIZE];
};


/*
 * Struct OperationParameter
 */

struct OperationParameter
{
    Smp::String8 name;
    Smp::String8 description;
    Smp::Uuid typeUuid;
};


/*
 * Struct RequestParameter
 */

struct RequestParameter
{
    Smp::String8 name;
    Smp::AnySimple value;
};


/*
 * Struct FieldPublished
 */

struct FieldPublished
{
    Smp::IModel* model;
    Smp::String8 name;
    Smp::String8 description;
    void* address;
    Smp::SimpleTypeKind typeKind;
    Smp::Bool view;
    Smp::Bool state;
    Smp::Bool input;
    Smp::Bool output;
};


/*
 * Struct OperationPublished
 */

struct OperationPublished
{
    Smp::IModel* model;
    Smp::Publication::IPublishOperation* publishOperation;
};


/*
 * Struct ArrayFieldPublished
 */

struct ArrayFieldPublished : FieldPublished
{
    Smp::Int64 count;
};


/*
 * Class Common
 */

class Common
{

public:
    static bool EqualUuid(Smp::Uuid uuid, Smp::Uuid uuid2);
    static Smp::SimpleTypeKind GetSimpleTypeKind(Smp::Uuid typeUuid);
    static Smp::Uuid GetUuid(Smp::SimpleTypeKind stk);
    static Smp::AnySimple CreateAnySimple(Smp::String8 value, Smp::SimpleTypeKind typeKind);
    static std::string GetValue(Smp::AnySimple any);

protected:

};

}
}
