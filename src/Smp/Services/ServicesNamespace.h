// -----------------------------------------------------------------------------
//
// (C) 2008 ESA (www.esa.int)
//
// -----------------------------------------------------------------------------
//
// Sub-System    : Smp
//
// File Name     : ServicesNamespace.h
//
// Author        : SMP Standard
//
// Creation Date : 2008-11-04
//
// Update        : see bottom of file
//
// Generated from: SIMSAT 4.0 MIE
//                 Catalogue: Smp - V1.2
//
// -----------------------------------------------------------------------------

/// @file ServicesNamespace.h
///    Namespace for standard services

#ifndef _SMP_SERVICES_SERVICES_NAMESPACE_H_
#define _SMP_SERVICES_SERVICES_NAMESPACE_H_

// -----------------------------------------------------------------------------
// --------------------------------- Includes ----------------------------------
// -----------------------------------------------------------------------------

#include "Smp/IService.h" // EventId
#include "Smp/Publication/IEnumerationType.h"
#include "Smp/Publication/ITypeRegistry.h"
#include "Smp/Services/ILogger.h"    // LogMessageKind
#include "Smp/Services/IScheduler.h" // TimeKind
#include "Smp/SimpleTypes.h"

namespace Smp
{
namespace Services
{
// -----------------------------------------------------------------------------
// --------------------------------- UUIDs -------------------------------------
// -----------------------------------------------------------------------------

/// Unique Identifier of type TimeKind.
/// eb4a8a66-4eff-11dc-b6b7-a3c223ce03de
static const ::Smp::Uuid Uuid_TimeKind = {3947530854, 20223, 4572, {182, 183, 163, 194, 35, 206, 3, 222}};

/// Unique Identifier of type LogMessageKind.
/// eb481933-4eff-11dc-b6b7-a3c223ce03de
static const ::Smp::Uuid Uuid_LogMessageKind = {3947370803, 20223, 4572, {182, 183, 163, 194, 35, 206, 3, 222}};

/// Unique Identifier of type EventId.
/// eb4a8a64-4eff-11dc-b6b7-a3c223ce03de
static const ::Smp::Uuid Uuid_EventId = {3947530852, 20223, 4572, {182, 183, 163, 194, 35, 206, 3, 222}};

void _Register_TimeKind(::Smp::Publication::ITypeRegistry*);
void _Register_LogMessageKind(::Smp::Publication::ITypeRegistry*);
void _Register_EventId(::Smp::Publication::ITypeRegistry*);
}
}

#endif // _SMP_SERVICES_SERVICES_NAMESPACE_H_

//----------
// History
//----------
// $Log: ServicesNamespace.h,v $
// Revision 1.3  2010-02-18 18:44:03  jco
// SmpExt patch from GMPORT applied.
//
// Revision 1.1.1.1  2009/11/03 14:55:39  jco
// Initial import
//
// Revision 1.2  2008/11/25 13:27:46  nin
// SPR-855: UUIDs aligned with those in Smp.cat
//
// Revision 1.1  2008/11/04 14:46:33  nin
// Released.
//
