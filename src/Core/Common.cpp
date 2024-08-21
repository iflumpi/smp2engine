
#include "Request.h"
#include "Smp/IPublication.h"


namespace Smp2Simulator
{
namespace Core
{

// Check if two uuid are equals
bool Common::EqualUuid(Smp::Uuid uuid, Smp::Uuid uuid2)
{
    return uuid.Data1 == uuid2.Data1 && uuid.Data2 == uuid2.Data2 && uuid.Data3 == uuid2.Data3 &&
           uuid.Data4[0] == uuid2.Data4[0] && uuid.Data4[1] == uuid2.Data4[1] && uuid.Data4[2] == uuid2.Data4[2] &&
           uuid.Data4[3] == uuid2.Data4[3] && uuid.Data4[4] == uuid2.Data4[4] && uuid.Data4[5] == uuid2.Data4[5] &&
           uuid.Data4[6] == uuid2.Data4[6] && uuid.Data4[7] == uuid2.Data4[7];
}

// Get the simple type kind related to a uuid
Smp::SimpleTypeKind Common::GetSimpleTypeKind(Smp::Uuid typeUuid)
{
    if (EqualUuid(typeUuid, Smp::Publication::Uuid_Bool))
        return Smp::SimpleTypeKind::ST_Bool;
    else if (EqualUuid(typeUuid, Smp::Publication::Uuid_Char8))
        return Smp::SimpleTypeKind::ST_Char8;
    else if (EqualUuid(typeUuid, Smp::Publication::Uuid_DateTime))
        return Smp::SimpleTypeKind::ST_DateTime;
    else if (EqualUuid(typeUuid, Smp::Publication::Uuid_Duration))
        return Smp::SimpleTypeKind::ST_Duration;
    else if (EqualUuid(typeUuid, Smp::Publication::Uuid_Float32))
        return Smp::SimpleTypeKind::ST_Float32;
    else if (EqualUuid(typeUuid, Smp::Publication::Uuid_Float64))
        return Smp::SimpleTypeKind::ST_Float64;
    else if (EqualUuid(typeUuid, Smp::Publication::Uuid_Int8))
        return Smp::SimpleTypeKind::ST_Int8;
    else if (EqualUuid(typeUuid, Smp::Publication::Uuid_Int16))
        return Smp::SimpleTypeKind::ST_Int16;
    else if (EqualUuid(typeUuid, Smp::Publication::Uuid_Int32))
        return Smp::SimpleTypeKind::ST_Int32;
    else if (EqualUuid(typeUuid, Smp::Publication::Uuid_Int64))
        return Smp::SimpleTypeKind::ST_Int64;
    else if (EqualUuid(typeUuid, Smp::Publication::Uuid_UInt8))
        return Smp::SimpleTypeKind::ST_UInt8;
    else if (EqualUuid(typeUuid, Smp::Publication::Uuid_UInt16))
        return Smp::SimpleTypeKind::ST_UInt16;
    else if (EqualUuid(typeUuid, Smp::Publication::Uuid_UInt32))
        return Smp::SimpleTypeKind::ST_UInt32;
    else if (EqualUuid(typeUuid, Smp::Publication::Uuid_UInt64))
        return Smp::SimpleTypeKind::ST_UInt64;
    else
        return Smp::SimpleTypeKind::ST_None;
}

// Get the uuid related to a simple type kind
Smp::Uuid Common::GetUuid(Smp::SimpleTypeKind stk)
{
    switch (stk)
    {
        case Smp::SimpleTypeKind::ST_Bool:
            return Smp::Publication::Uuid_Bool;
        case Smp::SimpleTypeKind::ST_Char8:
            return Smp::Publication::Uuid_Char8;
        case Smp::SimpleTypeKind::ST_DateTime:
            return Smp::Publication::Uuid_DateTime;
        case Smp::SimpleTypeKind::ST_Duration:
            return Smp::Publication::Uuid_Duration;
        case Smp::SimpleTypeKind::ST_Float32:
            return Smp::Publication::Uuid_Float32;
        case Smp::SimpleTypeKind::ST_Float64:
            return Smp::Publication::Uuid_Float64;
        case Smp::SimpleTypeKind::ST_Int8:
            return Smp::Publication::Uuid_Int8;
        case Smp::SimpleTypeKind::ST_Int16:
            return Smp::Publication::Uuid_Int16;
        case Smp::SimpleTypeKind::ST_Int32:
            return Smp::Publication::Uuid_Int32;
        case Smp::SimpleTypeKind::ST_Int64:
            return Smp::Publication::Uuid_Int64;
        case Smp::SimpleTypeKind::ST_UInt8:
            return Smp::Publication::Uuid_UInt8;
        case Smp::SimpleTypeKind::ST_UInt16:
            return Smp::Publication::Uuid_UInt16;
        case Smp::SimpleTypeKind::ST_UInt32:
            return Smp::Publication::Uuid_UInt32;
        case Smp::SimpleTypeKind::ST_UInt64:
            return Smp::Publication::Uuid_UInt64;
        default:
            return {0, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0}};
    }
}

// Create an instance of AnySimple from a value and a simple type kind
Smp::AnySimple Common::CreateAnySimple(Smp::String8 value, Smp::SimpleTypeKind typeKind)
{
    auto any = Smp::AnySimple();
    any.type = typeKind;

    auto stv = Smp::SimpleTypeValue();
    switch (typeKind)
    {
        case Smp::SimpleTypeKind::ST_Bool:
            stv.boolValue = (Smp::Bool)std::atoi(value);
            break;

        case Smp::SimpleTypeKind::ST_Char8:
            stv.char8Value = (Smp::Char8)std::atoi(value);
            break;

        case Smp::SimpleTypeKind::ST_DateTime:
            stv.dateTimeValue = (Smp::DateTime)std::atol(value);
            break;

        case Smp::SimpleTypeKind::ST_Duration:
            stv.durationValue = (Smp::Duration)std::atol(value);
            break;

        case Smp::SimpleTypeKind::ST_Float32:
            stv.float32Value = (Smp::Float32)std::atof(value);
            break;

        case Smp::SimpleTypeKind::ST_Float64:
            stv.float64Value = (Smp::Float64)std::atof(value);
            break;

        case Smp::SimpleTypeKind::ST_Int8:
            stv.int8Value = (Smp::Int8)std::atoi(value);
            break;

        case Smp::SimpleTypeKind::ST_Int16:
            stv.int16Value = (Smp::Int16)std::atoi(value);
            break;

        case Smp::SimpleTypeKind::ST_Int32:
            stv.int32Value = (Smp::Int32)std::atoi(value);
            break;

        case Smp::SimpleTypeKind::ST_Int64:
            stv.int64Value = (Smp::Int64)std::atol(value);
            break;

        case Smp::SimpleTypeKind::ST_String8:
            stv.string8Value = value;
            break;

        case Smp::SimpleTypeKind::ST_UInt8:
            stv.uInt8Value = (Smp::UInt8)std::atoi(value);
            break;

        case Smp::SimpleTypeKind::ST_UInt16:
            stv.uInt16Value = (Smp::UInt16)std::atoi(value);
            break;

        case Smp::SimpleTypeKind::ST_UInt32:
            stv.uInt32Value = (Smp::UInt32)std::atoi(value);
            break;

        case Smp::SimpleTypeKind::ST_UInt64:
            stv.uInt64Value = (Smp::UInt64)std::atol(value);
            break;

        case Smp::SimpleTypeKind::ST_None:
            stv.string8Value = "";
            break;

    }

    any.value = stv;
    return any;
}

// Get the value of an instance of AnySimple
std::string Common::GetValue(Smp::AnySimple any)
{
    switch (any.type)
    {
        case Smp::SimpleTypeKind::ST_Bool:
            return std::to_string(any.value.boolValue);

        case Smp::SimpleTypeKind::ST_Char8:
            return std::to_string(any.value.char8Value);

        case Smp::SimpleTypeKind::ST_DateTime:
            return std::to_string(any.value.dateTimeValue);

        case Smp::SimpleTypeKind::ST_Duration:
            return std::to_string(any.value.durationValue);

        case Smp::SimpleTypeKind::ST_Float32:
            return std::to_string(any.value.float32Value);

        case Smp::SimpleTypeKind::ST_Float64:
            return std::to_string(any.value.float64Value);

        case Smp::SimpleTypeKind::ST_Int8:
            return std::to_string(any.value.int8Value);

        case Smp::SimpleTypeKind::ST_Int16:
            return std::to_string(any.value.int16Value);

        case Smp::SimpleTypeKind::ST_Int32:
            return std::to_string(any.value.int32Value);

        case Smp::SimpleTypeKind::ST_Int64:
            return std::to_string(any.value.int64Value);

        case Smp::SimpleTypeKind::ST_String8:
            return any.value.string8Value;

        case Smp::SimpleTypeKind::ST_UInt8:
            return std::to_string(any.value.uInt8Value);

        case Smp::SimpleTypeKind::ST_UInt16:
            return std::to_string(any.value.uInt16Value);

        case Smp::SimpleTypeKind::ST_UInt32:
            return std::to_string(any.value.uInt32Value);

        case Smp::SimpleTypeKind::ST_UInt64:
            return std::to_string(any.value.uInt64Value);

        default:
            return any.value.string8Value;
    }
}


}
}
