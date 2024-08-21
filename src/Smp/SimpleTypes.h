//
// Title:
//      SimpleTypes.h
//
// Project:
//      Simulation Model Portability (SMP) Standard 2.0
//      C++ Mapping
//      Version 1.2 from October 28th, 2005
//
// Origin:
//      Simulation Model Portability (SMP) Configuration Control Board (CCB)
//
// Purpose:
//      This file defines the base types used throughout SMP 2.0.
//      This includes simple types, AnySimple, Uuid, and String8.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_SIMPLETYPES_H
#define SMP_SIMPLETYPES_H

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include <exception>
#include <vector>
#include <inttypes.h>

#include "Smp/Platform.h"

// ----------------------------------------------------------------------------
// ---------------------------- Simple types ----------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
/// This namespace contains all types used within the SMP Component Model.
/// This includes simple types, derived types, interfaces and exceptions.
/// Some specialized interfaces and exceptions are defined in nested namespaces.
namespace Smp
{
/// Character type that is used as well by strings.
typedef char Char8; ///<  8 bit character type.

/// Bool type that is either <code>true</code> or <code>false</code>.
typedef bool Bool; ///< Bool with true and false.

// Integer types
typedef int8_t Int8;     ///<  8 bit   signed integer type.
typedef uint8_t UInt8;   ///<  8 bit unsigned integer type.
typedef int16_t Int16;   ///< 16 bit   signed integer type.
typedef uint16_t UInt16; ///< 16 bit unsigned integer type.
typedef int32_t Int32;   ///< 32 bit   signed integer type.
typedef uint32_t UInt32; ///< 32 bit unsigned integer type.
typedef int64_t Int64;   ///< 64 bit   signed integer type.
typedef uint64_t UInt64; ///< 64 bit unsigned integer type.

// Floating point types
typedef float Float32;  ///< 32 bit floating-point type.
typedef double Float64; ///< 64 bit floating-point type.

// Date and time types
typedef Int64 Duration; ///< Duration in Nanoseconds.
typedef Int64 DateTime; ///< Relative to MJD2000+0.5.

/// 8 bit NULL terminated string type
typedef const Char8* String8; /// String8 of 8 bit characters.
}

// ----------------------------------------------------------------------------
// ---------------------------- AnySimple type --------------------------------
// ----------------------------------------------------------------------------

namespace Smp
{
/// Enumeration of simple type kinds (discriminator for AnySimple)
enum SimpleTypeKind
{
    ST_None, ///< no type, e.g. for void.

    ST_Char8, ///<  8 bit character type.
    ST_Bool,  ///<  1 bit Bool type.

    ST_Int8,   ///<  8 bit   signed integer type.
    ST_UInt8,  ///<  8 bit unsigned integer type.
    ST_Int16,  ///< 16 bit   signed integer type.
    ST_UInt16, ///< 16 bit unsigned integer type.
    ST_Int32,  ///< 32 bit   signed integer type.
    ST_UInt32, ///< 32 bit unsigned integer type.
    ST_Int64,  ///< 64 bit   signed integer type.
    ST_UInt64, ///< 64 bit unsigned integer type.

    ST_Float32, ///< 32 bit single floating-point type.
    ST_Float64, ///< 64 bit double floating-point type.

    ST_Duration, ///< Duration in nanoseconds.
    ST_DateTime, ///< Point in time in nanoseconds.

    ST_String8 ///<  8 bit NULL terminated string type.
};
}

namespace Smp
{
/// Union of simple type values (value for AnySimple)
union SimpleTypeValue {
    Char8 char8Value; ///<  8 bit character type.
    Bool boolValue;   ///<  1 bit Bool type.

    Int8 int8Value;     ///<  8 bit   signed integer type.
    UInt8 uInt8Value;   ///<  8 bit unsigned integer type.
    Int16 int16Value;   ///< 16 bit   signed integer type.
    UInt16 uInt16Value; ///< 16 bit unsigned integer type.
    Int32 int32Value;   ///< 32 bit   signed integer type.
    UInt32 uInt32Value; ///< 32 bit unsigned integer type.
    Int64 int64Value;   ///< 64 bit   signed integer type.
    UInt64 uInt64Value; ///< 64 bit unsigned integer type.

    Float32 float32Value; ///< 32 bit single floating-point type.
    Float64 float64Value; ///< 64 bit double floating-point type.

    Duration durationValue; ///< Duration in nanoseconds.
    DateTime dateTimeValue; ///< Point in time in nanoseconds.

    String8 string8Value; ///<  8 bit NULL terminated string type.
};
}

namespace Smp
{
/// Variant of simple type values.
/// The AnySimple type is a <em>Discriminated Union</em>, with type and value.
struct AnySimple
{
    SimpleTypeKind type{ST_None}; ///< Contained simple type
    SimpleTypeValue value{};      ///< Union of values and references
    bool owner{false};            ///< Ownership of the value, only for type
                                  ///  that can be allocated on the heap

    /// @brief Constructor
    AnySimple()
    {
        value.string8Value = nullptr;
    }

    /// @brief Destructor
    /// @remark If the value is of a type that can be allocated on the heap
    ///         and the ownership of the value is set to true, then the value
    ///         if disposed.
    ~AnySimple()
    {
        if(true == owner && ST_String8 == type)
        {
            delete[] value.string8Value;
        }
    };

    /// @brief Copy Constructor
    /// @remark The new copy is always owner of the value (for types that can
    ///         be allocated on the heap), even if the copied object was not an
    ///         owner. This avoids possible side-effects.
    AnySimple(const AnySimple& r) : type(r.type)
    {
        if(ST_String8 == type)
        {
            owner = true;
            if(r.value.string8Value != nullptr)
            {
                auto* buff = new Smp::Char8[std::strlen(r.value.string8Value) + 1];
                std::strcpy(buff, r.value.string8Value);
                value.string8Value = buff;
            }
            else
            {
                value.string8Value = nullptr;
            }
        }
        else
        {
            value = r.value;
        }
    }

    /// @brief Assignement operator
    /// @remark The assigned copy is always owner of the value (for types that can
    ///         be allocated on the heap), even if the copied object was not an
    ///         owner. This avoids possible side-effects.
    AnySimple& operator=(const AnySimple& r)
    {
        if(true == owner && ST_String8 == type)
        {
            delete[] value.string8Value;
            value.string8Value = nullptr;
        }

        type = r.type;
        if(ST_String8 == r.type)
        {
            owner = true;
            if(r.value.string8Value != nullptr)
            {
                auto* buff = new Smp::Char8[std::strlen(r.value.string8Value) + 1];
                std::strcpy(buff, r.value.string8Value);
                value.string8Value = buff;
            }
            else
            {
                value.string8Value = nullptr;
            }
        }
        else
        {
            value = r.value;
        }
        return *this;
    }
};
}

// ----------------------------------------------------------------------------
// ---------------------------- AnySimpleArray type ---------------------------
// ----------------------------------------------------------------------------

namespace Smp
{
/// Array of AnySimple values.
typedef AnySimple* AnySimpleArray;
}

// ----------------------------------------------------------------------------
// ---------------------------- Uuid type -------------------------------------
// ----------------------------------------------------------------------------

namespace Smp
{
/// Universally Unique Identifier
/// @remarks The 8-4-4-4-12 format as specified by the Open Group is used.
struct Uuid
{
    UInt32 Data1;   ///< 8 hex nibbles
    UInt16 Data2;   ///< 4 hex nibbles
    UInt16 Data3;   ///< 4 hex nibbles
    UInt8 Data4[8]; ///< 4+12 hex nibbles
};
}

#endif // SMP_SIMPLETYPES_H

/***********
 * History *
 ***********/

//$Log: SimpleTypes.h,v $
// Revision 1.9  2008/02/19 18:38:20  nin
// SPR-721: Memory leak analysis of the SMP2 Adapter
//
// Revision 1.8  2007/04/26 13:15:39  nin
// Proper Doxygen comments added in AnySimple to the new code for supporting
// String8 in AnySimple (SPR-292)
//
// Revision 1.7  2007/02/07 22:56:23  nin
// AnySimple does not own strings by default, but ownership is taken if
// Constructor from AnySimple or operator= is used.
//
// Revision 1.6  2007/01/28 16:42:26  nin
// Added memory management for String8 in AnySimple.
//
// Revision 1.5  2006/12/22 15:03:02  nin
// AnySimple structure set type value.string8Value to NULL in constructor.
//
// Revision 1.4  2006/12/22 14:30:50  nin
// AnySimple structure set type to ST_None in constructor.
//
// Revision 1.3  2006/12/21 16:02:30  nin
// String8 added among simple types.
//
// Revision 1.2  2006/09/27 11:43:48  nin
// SMP2 v1.2
//
