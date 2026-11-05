#ifndef DetectorConstruction_H
#define DetectorConstruction_H 1

#include "G4VUserDetectorConstruction.hh"
#include "G4NistManager.hh"

//---------------------------------------------------------------------------

class G4VPhysicalVolume;
class FluxSD;
class EnergyDepositSD;

//---------------------------------------------------------------------------

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
  DetectorConstruction();
  ~DetectorConstruction();

  G4VPhysicalVolume* Construct();

  void UpdateGeometry();

  inline G4VPhysicalVolume* GetExpHall()    { return fExpHall;     };
  inline G4VPhysicalVolume* GetDetVol(G4int i)     { return fDetVol[i]; };
  inline G4VPhysicalVolume* GetSurfVol()    { return fSurfVol;  };
  inline FluxSD*            GetFluxSD()     { return fFluxSD;    };

  private:

  G4NistManager*     fNistManager;

  G4VPhysicalVolume* fExpHall;
  G4VPhysicalVolume* fDetVol[120];
  G4VPhysicalVolume* fSurfVol;

  FluxSD*            fFluxSD;
  EnergyDepositSD*   fEdepSD;

};
#endif

//---------------------------------------------------------------------------

