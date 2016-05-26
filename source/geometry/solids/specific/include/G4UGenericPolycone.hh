//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id:$
//
// 
// --------------------------------------------------------------------
// GEANT 4 class header file
//
//
// G4UGenericPolycone
//
// Class description:
//
//   Wrapper class for G4UGenericPolycone to make use of it from USolids module.

// History:
// 30.10.13 G.Cosmo, CERN/PH
// --------------------------------------------------------------------
#ifndef G4UGENERICPOLYCONE_hh
#define G4UGENERICPOLYCONE_hh

#include "G4USolid.hh"

#if defined(G4GEOM_USE_USOLIDS)

#include "UGenericPolycone.hh"
#include "G4PolyconeSide.hh"

class G4UGenericPolycone : public G4USolid 
{
  public:  // with description

    G4UGenericPolycone(const G4String& name, 
                       G4double phiStart,    // initial phi starting angle
                       G4double phiTotal,    // total phi angle
                       G4int    numRZ,       // number corners in r,z space
                 const G4double r[],         // r coordinate of these corners
                 const G4double z[]       ); // z coordinate of these corners

   ~G4UGenericPolycone();

    inline UGenericPolycone* GetShape() const;

    inline G4double GetStartPhi()  const;
    inline G4double GetEndPhi()    const;
    inline G4bool IsOpen()         const;
    inline G4int  GetNumRZCorner() const;
    inline G4PolyconeSideRZ GetCorner(G4int index) const;
  
  public:  // without description

    G4UGenericPolycone(__void__&);
      // Fake default constructor for usage restricted to direct object
      // persistency for clients requiring preallocation of memory for
      // persistifiable objects.

    G4UGenericPolycone( const G4UGenericPolycone& source );
    G4UGenericPolycone &operator=(const G4UGenericPolycone& source);
      // Copy constructor and assignment operator.
    G4Polyhedron* CreatePolyhedron() const;
};

// --------------------------------------------------------------------
// Inline methods
// --------------------------------------------------------------------

inline UGenericPolycone* G4UGenericPolycone::GetShape() const
{
  return (UGenericPolycone*) fShape;
}

inline G4double G4UGenericPolycone::GetStartPhi() const
{
  return GetShape()->GetStartPhi();
}
inline G4double G4UGenericPolycone::GetEndPhi() const
{
  return GetShape()->GetEndPhi();
}
inline G4bool G4UGenericPolycone::IsOpen() const
{
  return GetShape()->IsOpen();
}
inline G4int G4UGenericPolycone::GetNumRZCorner() const
{
  return GetShape()->GetNumRZCorner();
}
inline G4PolyconeSideRZ G4UGenericPolycone::GetCorner(G4int index) const
{
  UPolyconeSideRZ pside = GetShape()->GetCorner(index);
  G4PolyconeSideRZ psiderz = { pside.r, pside.z };

  return psiderz;
}
  
#endif  // G4GEOM_USE_USOLIDS

#endif
