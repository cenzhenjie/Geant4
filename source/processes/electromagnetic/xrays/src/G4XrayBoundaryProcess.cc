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
////////////////////////////////////////////////////////////////////////
// X-ray Boundary Process Class Implementation
////////////////////////////////////////////////////////////////////////
//
// File:        G4XrayBoundaryProcess.cc
// Description: Discrete Process -- reflection/refraction at
//                                  interfaces
// Version:     1.0
// Created:     2016-05-26
// Modified:
//
// Author:      Zhenjie Cen
// mail:        zhenjie.cen@creatis.insa-lyon.fr
//
////////////////////////////////////////////////////////////////////////

#include "G4XrayBoundaryProcess.hh"


/////////////////////////
// Class Implementation
/////////////////////////

//////////////
// Operators
//////////////


/////////////////
// Constructors
/////////////////
G4XrayBoundaryProcess::G4XrayBoundaryProcess(const G4String &processName, G4ProcessType type) : G4VDiscreteProcess(processName, type) {}


////////////////
// Destructors
////////////////
G4XrayBoundaryProcess::~G4XrayBoundaryProcess() {}

////////////
// Methods
////////////

// PostStepDoIt
// ------------
//
G4VParticleChange* G4XrayBoundaryProcess::PostStepDoIt(const G4Track& aTrack, const G4Step& aStep)
{
    // Get hyperStep from  G4ParallelWorldProcess
    //  NOTE: PostSetpDoIt of this process should be
    //        invoked after G4ParallelWorldProcess!

    const G4Step* pStep = &aStep;

    const G4Step* hStep = G4ParallelWorldProcess::GetHyperStep();

    if (hStep) pStep = hStep;

    G4bool isOnBoundary =
            (pStep->GetPostStepPoint()->GetStepStatus() == fGeomBoundary);

    if (isOnBoundary) {
       Material1 = pStep->GetPreStepPoint()->GetMaterial();
       Material2 = pStep->GetPostStepPoint()->GetMaterial();
    } else {
       // if ( verboseLevel > 0) BoundaryProcessVerbose();
       return G4VDiscreteProcess::PostStepDoIt(aTrack, aStep);
    }

    G4VPhysicalVolume* thePrePV  =
                           pStep->GetPreStepPoint() ->GetPhysicalVolume();
    G4VPhysicalVolume* thePostPV =
                           pStep->GetPostStepPoint()->GetPhysicalVolume();

    if ( verboseLevel > 0 ) {
       G4cout << " X-ray at Boundary! " << G4endl;
       if (thePrePV)  G4cout << " thePrePV:  " << thePrePV->GetName()  << G4endl;
       if (thePostPV) G4cout << " thePostPV: " << thePostPV->GetName() << G4endl;
    }

    return G4VDiscreteProcess::PostStepDoIt(aTrack, aStep);
}

// GetMeanFreePath
// ---------------
//
G4double G4XrayBoundaryProcess::GetMeanFreePath(const G4Track &, G4double previousStepSize, G4ForceCondition *condition) {
  *condition = Forced;

  return DBL_MAX;
}
