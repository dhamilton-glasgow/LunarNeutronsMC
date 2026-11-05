#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh" 
#include "G4ThreeVector.hh"
#include "globals.hh"

//---------------------------------------------------------------------------

class G4GeneralParticleSource;
class G4Event;

//---------------------------------------------------------------------------

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorAction();    
  ~PrimaryGeneratorAction();

  void GeneratePrimaries (G4Event*);

  G4ThreeVector GetVertex()           { return G4ThreeVector(fVx,  fVy,  fVz);  }
  G4ThreeVector GetDirection()        { return G4ThreeVector(fPxp, fPyp, fPzp); }
  G4double      GetEnergy()           { return fEp; }
  G4double      GetTime()             { return fTp; }
  G4ParticleDefinition* GetPrimPDef() { return fPDefinition; }

private:

  G4GeneralParticleSource*   fParticleSource;
  G4ParticleTable*           fParticleTable;
  G4IonTable*                fIonTable; 

  G4ParticleDefinition*      fPDefinition;
  
  G4int                      fNGenBranches;   
  G4int                      fNevent;
  G4int                      fPDG;
  G4double                   fVx;
  G4double                   fVy;
  G4double                   fVz;
  G4double                   fPxp;
  G4double                   fPyp;
  G4double                   fPzp;
  G4double                   fEp;
  G4double                   fTp;

};
#endif

//---------------------------------------------------------------------------


