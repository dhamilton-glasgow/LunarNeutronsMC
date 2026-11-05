#include "G4GeneralParticleSource.hh"
#include "G4Event.hh"
#include "G4String.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"

#include "PrimaryGeneratorAction.hh"

using namespace CLHEP;

//---------------------------------------------------------------------------

PrimaryGeneratorAction::PrimaryGeneratorAction()

{
  fParticleTable      = G4ParticleTable::GetParticleTable();
  fIonTable           = G4IonTable::GetIonTable(); 
  fPDefinition        = NULL;

  fParticleSource     = new G4GeneralParticleSource();
}

//---------------------------------------------------------------------------

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  //  delete fParticleSource;
}

//---------------------------------------------------------------------------

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

    fParticleSource->GeneratePrimaryVertex(anEvent);

    fVx          = fParticleSource->GetParticlePosition().getX();
    fVy          = fParticleSource->GetParticlePosition().getY();
    fVz          = fParticleSource->GetParticlePosition().getZ();
    fPxp         = fParticleSource->GetParticleMomentumDirection().getX();
    fPyp         = fParticleSource->GetParticleMomentumDirection().getY();
    fPzp         = fParticleSource->GetParticleMomentumDirection().getZ();
    fEp          = fParticleSource->GetParticleEnergy()/GeV;
    fTp          = fParticleSource->GetParticleTime();
    fPDefinition = fParticleSource->GetParticleDefinition();

}

//---------------------------------------------------------------------------
