// -----------------------------------------------------------------------------
//
// (C) 2004-2011 European Space Agency
// European Space Operations Centre
// Darmstadt, Germany
//
// -----------------------------------------------------------------------------
//
// Sub-System    : Smp
//
// File Name     : Smp.h
//
// Author        : Alberto Ingenito
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
///    Smp initialise declaration

#ifndef _SMP_SMP_H_
#define _SMP_SMP_H_

// Forward declarations
namespace Smp
{
class IDynamicSimulator;

namespace Publication
{
class ITypeRegistry;
}
}

// Entry points
extern "C" {
/// @brief SMP2 Initialisation method
bool InitialiseSmp(Smp::IDynamicSimulator* simulator, Smp::Publication::ITypeRegistry*);

/// @brief SMP2 Finalisation method
bool FinaliseSmp(void);
}

#endif // _SMP_SMP_H_

//----------
// History
//----------
// $Log: Smp.h,v $
// Revision 1.2  2011-03-18 19:26:01  jowh
// Added ESA copyright statements to changed files
//
// Revision 1.1  2010-02-18 18:44:03  jco
// SmpExt patch from GMPORT applied.
//
// Revision 1.1.1.1  2009/11/03 14:55:39  jco
// Initial import
//
//
