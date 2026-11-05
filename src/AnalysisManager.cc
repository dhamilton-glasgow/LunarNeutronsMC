#include "AnalysisManager.hh"
#include "PrimaryGeneratorAction.hh"
#include "AnalysisMessenger.hh"

#include "G4UnitsTable.hh"
#include "G4RunManager.hh"
#include "G4Point3D.hh"
#include "G4Transform3D.hh"

#include <iostream>
#include <fstream>
using namespace std;

//---------------------------------------------------------------------------

AnalysisManager::AnalysisManager()
{
  ZeroArray();

  fOutFileName = G4String("out_default.txt");

  fAnaMessenger = new AnalysisMessenger(this);
}

//---------------------------------------------------------------------------

AnalysisManager::~AnalysisManager()
{
  fOutFile.close();
}

//---------------------------------------------------------------------------

void AnalysisManager::InitOutput()
{ 
  fOutFile.open (fOutFileName);
  //  fOutFile.open (fOutFileName, ios_base::out|ios_base::binary);
  //fOutFile.open (fOutFileName, ios::binary | ios::in);
}

//---------------------------------------------------------------------------

void AnalysisManager::ZeroArray()
{
  // Primary
  G4ThreeVector zero(0.,0.,0.);
  fPEne   = 9999;
  fPdir   = (zero);
  fPth    = 9999;
  fPph    = 9999;
  fPTime  = 9999;
  fPPDef  = NULL;
  fPpdg   = 9999;

  // Raw Hits
  fFlux_Nhits  = 0;
  fFluxpdef    = NULL;
  fFluxp3      = (zero);
  fFluxpospre  = (zero);
  fFluxpospost = (zero);
  fFluxid      = 0;
  fFluxtime    = 0;
  fFluxedep    = 0;
  fFluxTid     = 0;
  fFluxANum    = 0;
  fFluxAMass   = 0;

  fEdep_Nhits  = 0;
  fEdeppospre  = (zero);
  fEdeppospost = (zero);
  fEdepid      = 0;
  fEdepedep    = 0;
  fEdept       = 0;

  for ( G4int i = 0; i < fMaxhits; i++ ) {
    fFlux_id[i]      = 9999;  
    fFlux_time[i]    = 9999;
    fFlux_Edep[i]    = 9999;
    fFlux_pdg[i]     = 9999;
    fFlux_mass[i]    = 9999;
    fFlux_mom[i]     = 9999;
    fFlux_px[i]      = 9999;
    fFlux_py[i]      = 9999;
    fFlux_pz[i]      = 9999;
    fFlux_xpre[i]    = 9999;
    fFlux_ypre[i]    = 9999;
    fFlux_zpre[i]    = 9999;
    fFlux_xpost[i]   = 9999;
    fFlux_ypost[i]   = 9999;
    fFlux_zpost[i]   = 9999;
    fFlux_Energy[i]  = 9999;
    fFlux_pid[i]     = 9999;  
    fFlux_tid[i]     = 9999;  
    fFlux_amass[i]   = 9999;  
    fFlux_anum[i]    = 9999; 

    fEdep_id[i]      = 9999;  
    fEdep_Edep[i]    = 9999;
    fEdep_xpre[i]    = 9999;
    fEdep_ypre[i]    = 9999;
    fEdep_zpre[i]    = 9999;
    fEdep_xpost[i]   = 9999;
    fEdep_ypost[i]   = 9999;
    fEdep_zpost[i]   = 9999;
    fEdep_Time[i]    = 9999;
  }
}

//---------------------------------------------------------------------------

void AnalysisManager::FillFluxArray( G4int hitn ) 
{
    fFlux_Nhits++;
    fFlux_id[hitn]     = (G4int)fFluxid;
    fFlux_tid[hitn]    = (G4int)fFluxTid;
    fFlux_pid[hitn]    = (G4int)fFluxPid;
    fFlux_anum[hitn]   = (G4int)fFluxANum;
    fFlux_amass[hitn]  = (G4int)fFluxAMass;
    fFlux_pdg[hitn]    = (G4int)fFluxpdef->GetPDGEncoding();
    fFlux_mass[hitn]   = (G4double)fFluxpdef->GetPDGMass();
    fFlux_time[hitn]   = (G4double)fFluxtime;                                   
    fFlux_mom[hitn]    = (G4double)fFluxp3.mag();                             
    fFlux_px[hitn]     = (G4double)fFluxp3.getX();                             
    fFlux_py[hitn]     = (G4double)fFluxp3.getY();                             
    fFlux_pz[hitn]     = (G4double)fFluxp3.getZ();                             
    fFlux_xpre[hitn]   = (G4double)fFluxpospre.getX();                             
    fFlux_ypre[hitn]   = (G4double)fFluxpospre.getY();                             
    fFlux_zpre[hitn]   = (G4double)fFluxpospre.getZ();                             
    fFlux_xpost[hitn]  = (G4double)fFluxpospost.getX();                             
    fFlux_ypost[hitn]  = (G4double)fFluxpospost.getY();                             
    fFlux_zpost[hitn]  = (G4double)fFluxpospost.getZ();                             
    fFlux_Edep[hitn]   = (G4double)fFluxedep;
    fFlux_Energy[hitn] = sqrt( fFlux_mom[hitn]*fFlux_mom[hitn] 
			       + fFlux_mass[hitn]*fFlux_mass[hitn] );

    fFlux_Energy[hitn] = fFlux_mom[hitn] - fFlux_mass[hitn];

    fFlux_xpre[hitn]   = (fFlux_xpre[hitn] + fFlux_xpost[hitn])/2.;
    fFlux_ypre[hitn]   = (fFlux_ypre[hitn] + fFlux_ypost[hitn])/2.;
    fFlux_zpre[hitn]   = (fFlux_zpre[hitn] + fFlux_zpost[hitn])/2.;

}

//---------------------------------------------------------------------------

void AnalysisManager::FillEdepArray( G4int hitn ) 
{
    fEdep_Nhits++;
    fEdep_id[hitn]     = (G4int)fEdepid;
    fEdep_xpre[hitn]   = (G4double)fEdeppospre.getX();                             
    fEdep_ypre[hitn]   = (G4double)fEdeppospre.getY();                             
    fEdep_zpre[hitn]   = (G4double)fEdeppospre.getZ();                             
    fEdep_xpost[hitn]  = (G4double)fEdeppospost.getX();                             
    fEdep_ypost[hitn]  = (G4double)fEdeppospost.getY();                             
    fEdep_zpost[hitn]  = (G4double)fEdeppospost.getZ();                             
    fEdep_Edep[hitn]   = (G4double)fEdepedep;
    fEdep_Time[hitn]   = (G4double)fEdept;

    fEdep_xpre[hitn]   = (fEdep_xpre[hitn] + fEdep_xpost[hitn])/2.;
    fEdep_ypre[hitn]   = (fEdep_ypre[hitn] + fEdep_ypost[hitn])/2.;
    fEdep_zpre[hitn]   = (fEdep_zpre[hitn] + fEdep_zpost[hitn])/2.;

}

//---------------------------------------------------------------------------

void AnalysisManager::FillTree(G4int evid)
{
  // Primary Variables
  fPTime  = (G4double)fPTime;
  fPth    = (G4double)fPdir.getTheta();                         
  fPph    = (G4double)fPdir.getPhi();                                                      
  fPEne   = (G4double)fPEne;                         
  fPpdg   = (G4int)  fPPDef->GetPDGEncoding();
  
  fOutFile << "Event = " << evid << endl;
  fOutFile << fPTime << "," << fPth << "," << fPph << "," << fPEne << "," << fPpdg << endl; 

  fOutFile << "Detector Hits = " << fEdep_Nhits << endl; 
  for(int i=0; i< fEdep_Nhits; i++ ) 
    fOutFile << fEdep_id[i] << "," <<  fEdep_Edep[i] << "," <<  fEdep_Time[i] << endl; 

  fOutFile << "Flux Hits = " << fFlux_Nhits << endl; 
  for(int i=0; i< fFlux_Nhits; i++ ) 
    fOutFile << fFlux_id[i] << "," <<  fFlux_Edep[i] << ","  << fFlux_xpre[i] << "," <<  fFlux_ypre[i] << "," <<  fFlux_zpre[i] 
	     << "," <<  fFlux_pdg[i] << endl;


}

//---------------------------------------------------------------------------
