// -----------------------------------------------------------------------------
//
// (C) 2008 ESA (www.esa.int)
//
// -----------------------------------------------------------------------------
//
// Sub-System    : Smp
//
// File Name     : SmpNamespace.h
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

/// @file SmpNamespace.h
///    Smp standard namespace

#ifndef _SMP_SMP_NAMESPACE_H_
#define _SMP_SMP_NAMESPACE_H_

// -----------------------------------------------------------------------------
// --------------------------------- Includes ----------------------------------
// -----------------------------------------------------------------------------

#include "Smp/IModel.h"     // ModelStateKind
#include "Smp/ISimulator.h" // SimulatorStateKind
#include "Smp/Publication/IEnumerationType.h"
#include "Smp/Publication/IStructureType.h"
#include "Smp/Publication/ITypeRegistry.h"
#include "Smp/SimpleTypes.h" // SimpleTypeKind, Uuid

namespace Smp
{
// -----------------------------------------------------------------------------
// --------------------------------- UUIDs -------------------------------------
// -----------------------------------------------------------------------------

/// Unique Identifier of type SimpleTypeKind.
/// 926e9173-75ed-460c-bb56-75fd7f47c681
extern const ::Smp::Uuid Uuid_SimpleTypeKind;

/// Unique Identifier of type ModelStateKind.
/// eb58e23b-4eff-11dc-b6b7-a3c223ce03de
extern const ::Smp::Uuid Uuid_ModelStateKind;

/// Unique Identifier of type SimulatorStateKind.
/// eb5b2cc5-4eff-11dc-b6b7-a3c223ce03de
extern const ::Smp::Uuid Uuid_SimulatorStateKind;

/// Unique Identifier of type Uuid.
/// eb5671e9-4eff-11dc-b6b7-a3c223ce03de
extern const ::Smp::Uuid Uuid_Uuid;

/// Unique Identifier of type UuidBytes
/// eb5671e7-4eff-11dc-b6b7-a3c223ce03de
extern const ::Smp::Uuid Uuid_UuidBytes;

// -----------------------------------------------------------------------------
// ---------------- Static Registration Functions Declarations  ----------------
// -----------------------------------------------------------------------------

/// Register Type: SimpleTypeKind
void _Register_SimpleTypeKind(::Smp::Publication::ITypeRegistry* registry);

/// Register Type: ModelStateKind
void _Register_ModelStateKind(::Smp::Publication::ITypeRegistry* registry);

/// Register Type: SimulatorStateKind
void _Register_SimulatorStateKind(::Smp::Publication::ITypeRegistry* registry);

/// Register Function for UuidBytes
void _Register_UuidBytes(Smp::Publication::ITypeRegistry* registry);

/// Register Function for Uuid structure
void _Register_Uuid(Smp::Publication::ITypeRegistry* registry);
}

#endif // _SMP_SMP_NAMESPACE_H_

//----------
// History
//----------
// $Log: SmpNamespace.h,v $
// Revision 1.5  2010-02-18 18:44:03  jco
// SmpExt patch from GMPORT applied.
//
// Revision 1.1.1.1  2009/11/03 14:55:39  jco
// Initial import
//
// Revision 1.3  2008/11/25 13:27:46  nin
// SPR-855: UUIDs aligned with those in Smp.cat
//
// Revision 1.2  2008/11/04 16:24:32  nin
// _Register_Uuid() properly publishes the last 8 bytes array.
//
// Revision 1.1  2008/11/04 14:46:33  nin
// Released.
//
