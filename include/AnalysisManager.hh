#ifndef AnalysisManager_h
#define AnalysisManager_h 1

#include "globals.hh"
#include "PrimaryGeneratorAction.hh"
#include "AnalysisMessenger.hh"

#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"

#include <iostream>
#include <fstream>
using namespace std;

//---------------------------------------------------------------------------

class AnalysisManager {

public:

  AnalysisManager();
  ~AnalysisManager();

  void InitOutput();

  void ZeroArray();
  void FillFluxArray( G4int );
  void FillEdepArray( G4int );
  void FillTree( G4int );

  void SetOutFileName  ( G4String fname )           { fOutFileName  = fname; }

  void SetPrimaryEnergy   (G4double       ene  )       { fPEne  = ene;  }
  void SetPrimaryTime     (G4double       time )       { fPTime = time; }
  void SetPrimaryPDef     (G4ParticleDefinition* pdef) { fPPDef = pdef; }
  void SetPrimaryDirection(G4ThreeVector  dir  )       { fPdir  = dir;  }

  void SetFluxPDef      ( G4ParticleDefinition* sp ) { fFluxpdef = sp;    }
  void SetFluxPosPre    ( G4ThreeVector  spos )      { fFluxpospre  = spos;  }
  void SetFluxPosPost   ( G4ThreeVector  spos )      { fFluxpospost  = spos;  }
  void SetFluxP3        ( G4ThreeVector  smom )      { fFluxp3   = smom;  }
  void SetFluxTime      ( G4double       stime )     { fFluxtime = stime; }
  void SetFluxID        ( G4int          sid )       { fFluxid   = sid;   }
  void SetFluxEnergy    ( G4double       sedep)      { fFluxedep = sedep; }
  void SetFluxANum      ( G4int          ann )       { fFluxANum  = ann;   }
  void SetFluxAMass     ( G4int          amm )       { fFluxAMass = amm;   }
  void SetFluxPID       ( G4int          pid )       { fFluxPid   = pid;   }
  void SetFluxTID       ( G4int          tid )       { fFluxTid   = tid;   }

  void SetEdepPosPre    ( G4ThreeVector  epos )      { fEdeppospre  = epos;  }
  void SetEdepPosPost   ( G4ThreeVector  epos )      { fEdeppospost  = epos;  }
  void SetEdepID        ( G4int          eid )       { fEdepid   = eid;   }
  void SetEdepEdep      ( G4double       eedep)      { fEdepedep = eedep; }
  void SetEdepTime      ( G4double       time)       { fEdept = time; }

private:
  
  AnalysisMessenger*    fAnaMessenger;
  G4String              fOutFileName;

  ofstream              fOutFile;


  // Primary
  G4double               fPEne;
  G4double               fPth;
  G4double               fPph;
  G4double               fPTime;
  G4ParticleDefinition* fPPDef;
  G4int                 fPpdg;
  G4ThreeVector         fPdir;

  // Flux raw
  G4ParticleDefinition* fFluxpdef;
  G4ThreeVector         fFluxp3;
  G4ThreeVector         fFluxpospre;
  G4ThreeVector         fFluxpospost;
  G4double              fFluxtime;
  G4int                 fFluxid;
  G4int                 fFluxPid;
  G4int                 fFluxTid;
  G4int                 fFluxANum;
  G4int                 fFluxAMass;
  G4double              fFluxedep;

  static const G4int    fMaxhits = 50000;

  G4int                 fFlux_Nhits;
  G4int                 fFlux_id[fMaxhits];
  G4double               fFlux_time[fMaxhits];
  G4double               fFlux_Edep[fMaxhits];
  G4int                 fFlux_pdg[fMaxhits];
  G4int                 fFlux_tid[fMaxhits];//Track ID 
  G4int                 fFlux_pid[fMaxhits];// Process ID 
  G4int                 fFlux_anum[fMaxhits];//Atomic Number
  G4int                 fFlux_amass[fMaxhits];//Atomic Mass
  G4double               fFlux_mass[fMaxhits];
  G4double               fFlux_mom[fMaxhits];
  G4double               fFlux_px[fMaxhits];
  G4double               fFlux_py[fMaxhits];
  G4double               fFlux_pz[fMaxhits];
  G4double               fFlux_xpre[fMaxhits];
  G4double               fFlux_ypre[fMaxhits];
  G4double               fFlux_zpre[fMaxhits];
  G4double               fFlux_xpost[fMaxhits];
  G4double               fFlux_ypost[fMaxhits];
  G4double               fFlux_zpost[fMaxhits];
  G4double               fFlux_Energy[fMaxhits];

  // Edep raw
  G4ThreeVector         fEdeppospre;
  G4ThreeVector         fEdeppospost;
  G4int                 fEdepid;
  G4double              fEdepedep;
  G4double              fEdept;

  G4int                 fEdep_Nhits;
  G4int                 fEdep_id[fMaxhits];
  G4double               fEdep_Edep[fMaxhits];
  G4double               fEdep_xpre[fMaxhits];
  G4double               fEdep_ypre[fMaxhits];
  G4double               fEdep_zpre[fMaxhits];
  G4double               fEdep_xpost[fMaxhits];
  G4double               fEdep_ypost[fMaxhits];
  G4double               fEdep_zpost[fMaxhits];
  G4double               fEdep_Time[fMaxhits];

};

#endif

//---------------------------------------------------------------------------
