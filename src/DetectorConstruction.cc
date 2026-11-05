#include "DetectorConstruction.hh"
#include "FluxSD.hh"
#include "EnergyDepositSD.hh"

#include "G4Material.hh"
#include "G4BooleanSolid.hh"
#include "G4CSGSolid.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4RotationMatrix.hh"
#include "G4UserLimits.hh"

#include "G4TransportationManager.hh"
#include "G4SDManager.hh"

#include "G4GeometryManager.hh"
#include "G4SolidStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "G4VisAttributes.hh"
#include "G4String.hh"
#include "globals.hh"

using namespace CLHEP;

//---------------------------------------------------------------------------

DetectorConstruction::DetectorConstruction()
{
  fNistManager  = G4NistManager::Instance();
}

//---------------------------------------------------------------------------

DetectorConstruction::~DetectorConstruction() 
{
}

//---------------------------------------------------------------------------

G4VPhysicalVolume* DetectorConstruction::Construct()
{ 
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();


  //---------------------------------------------------------------------------
  // vacuum
  //---------------------------------------------------------------------------

  G4int    nElem, nAtoms, nComponents;
  G4double fractionMass, z, a;
  G4double density     = 1.e-25 *g/cm3;
  G4double pressure    = 3.e-18*pascal;
  G4double temperature = 2.73*kelvin;

  G4Material* vacuum   = new G4Material("Galactic", 1., 1.01*g/mole,
					density,kStateGas,temperature,pressure);

  //---------------------------------------------------------------------------
  // Soil
  //---------------------------------------------------------------------------

  G4Element* H  = new G4Element("Hydrogen",  "H",  1.,  1.00794*g/mole );
  G4Element* C  = new G4Element("Carbon",    "C",  6.,  12.01*g/mole );
  G4Element* O  = new G4Element("Oxygen",    "O" , 8.,  16.00*g/mole );
  G4Element* Na = new G4Element("Sodium",    "Na", 11., 22.99*g/mole );
  G4Element* Mg = new G4Element("Magnesium", "Mg", 12., 24.305*g/mole );
  G4Element* Al = new G4Element("Aluminium", "Al", 13., 26.98*g/mole );
  G4Element* Si = new G4Element("Silicon",   "Si", 14., 28.08*g/mole );
  G4Element* K  = new G4Element("Potassium", "K",  19., 39.0983*g/mole );
  G4Element* Ca = new G4Element("Calcium",   "Ca", 20., 40.08*g/mole );
  G4Element* Ti = new G4Element("Titanium",  "Ti", 22., 47.87*g/mole );
  G4Element* Cr = new G4Element("Chromium",  "Cr", 24., 51.996*g/mole );
  G4Element* Fe = new G4Element("Iron",      "Fe", 26., 55.85*g/mole );
  G4Element* Sm = new G4Element("Samarium",  "Sm", 62., 150.36*g/mole );
  G4Element* Eu = new G4Element("Europium",  "Eu", 63., 151.96*g/mole );
  G4Element* Gd = new G4Element("Gadolinium","Gd", 64., 157.25*g/mole );
  G4Element* Th = new G4Element("Thorium",   "Cr", 90., 232.038*g/mole );
  G4Element* Mn = new G4Element("Maganese",  "Mn", 25., 54.938*g/mole );

  G4Material* water = new G4Material("water", 1.*kg/m3, 2);
  water->AddElement(H, 2);
  water->AddElement(O, 1);

  G4Material* soil  = new G4Material("soil", 1.8*g/cm3, 8);
  soil->AddElement(C,  0.005065);
  soil->AddElement(O,  0.4560);
  soil->AddElement(Na, 0.004452);
  soil->AddElement(Al, 0.1763);
  soil->AddElement(Si, 0.2066);
  soil->AddElement(Ca, 0.1359);
  soil->AddElement(Ti, 0.0007791);
  soil->AddElement(Fe, 0.01485);

  G4Material* wetSoil = new G4Material("WetSoil",density=1.8*g/cm3,nComponents=2);  
  wetSoil->AddMaterial(soil, fractionMass=90*perCent);
  wetSoil->AddMaterial(water, fractionMass=10*perCent);

  G4Material* soil1  = new G4Material("soil1", 1.76*g/cm3, 11);
  soil1->AddElement(O,  0.41739 * 1/1.07196);
  soil1->AddElement(Na, 0.00292 * 1/1.07196);
  soil1->AddElement(Mg, 0.06162 * 1/1.07196);
  soil1->AddElement(Al, 0.06061 * 1/1.07196);
  soil1->AddElement(Si, 0.19026 * 1/1.07196);
  soil1->AddElement(K,  0.072624 * 1/1.07196);
  soil1->AddElement(Ca, 0.07541 * 1/1.07196);
  soil1->AddElement(Ti, 0.05144 * 1/1.07196);
  soil1->AddElement(Cr, 0.00297 * 1/1.07196);
  soil1->AddElement(Mn, 0.00176 * 1/1.07196);
  soil1->AddElement(Fe, 0.13496 * 1/1.07196);
//   soil1->AddElement(Sm, 0.00083342);
//   soil1->AddElement(Eu, 0.00018164);
//   soil1->AddElement(Gd, 0.0010997);
//   soil1->AddElement(Th, 0.00009449);

  G4Material* soil2  = new G4Material("soil2", 2.11*g/cm3, 11);
  soil2->AddElement(O,  0.41557 * 1/1.07815);
  soil2->AddElement(Na, 0.003137 * 1/1.07815);
  soil2->AddElement(Mg, 0.060267 * 1/1.07815);
  soil2->AddElement(Al, 0.059777 * 1/1.07815);
  soil2->AddElement(Si, 0.189557 * 1/1.07815);
  soil2->AddElement(K,  0.0789657 * 1/1.07815);
  soil2->AddElement(Ca, 0.076687 * 1/1.07815);
  soil2->AddElement(Ti, 0.049057 * 1/1.07815);
  soil2->AddElement(Cr, 0.003097 * 1/1.07815);
  soil2->AddElement(Mn, 0.001787 * 1/1.07815);
  soil2->AddElement(Fe, 0.140307 * 1/1.07815);
//   soil2->AddElement(Sm, 0.00077459);
//   soil2->AddElement(Eu, 0.00017821);
//   soil2->AddElement(Gd, 0.0010577);
//   soil2->AddElement(Th, 0.00009022);

  G4Material* soil3  = new G4Material("soil3", 1.78*g/cm3, 11);
  soil3->AddElement(O,  0.4229 *1/1.09107 );
  soil3->AddElement(Na, 0.00307 *1/1.09107 );
  soil3->AddElement(Mg, 0.06156 *1/1.09107 );
  soil3->AddElement(Al, 0.07384 *1/1.09107 );
  soil3->AddElement(Si, 0.19668 *1/1.09107 );
  soil3->AddElement(K,  0.092011 *1/1.09107 );
  soil3->AddElement(Ca, 0.08020 *1/1.09107 );
  soil3->AddElement(Ti, 0.03380 *1/1.09107 );
  soil3->AddElement(Cr, 0.00264 *1/1.09107 );
  soil3->AddElement(Mn, 0.00152 *1/1.09107 );
  soil3->AddElement(Fe, 0.12277 *1/1.09107 );
//   soil3->AddElement(Sm, 0.00073429);
//   soil3->AddElement(Eu, 0.00015453);
//   soil3->AddElement(Gd, 0.00098178);
//   soil3->AddElement(Th, 0.00013819);

  G4Material* soil4  = new G4Material("soil4", 1.79*g/cm3, 11);
  soil4->AddElement(O,  0.42636 * 1/1.16201 );
  soil4->AddElement(Na, 0.00346* 1/1.16201);
  soil4->AddElement(Mg, 0.06091* 1/1.16201);
  soil4->AddElement(Al, 0.07598* 1/1.16201);
  soil4->AddElement(Si, 0.20218* 1/1.16201);
  soil4->AddElement(K,  0.16318* 1/1.16201);
  soil4->AddElement(Ca, 0.07707* 1/1.16201);
  soil4->AddElement(Ti, 0.03198* 1/1.16201);
  soil4->AddElement(Cr, 0.00255* 1/1.16201);
  soil4->AddElement(Mn, 0.00146* 1/1.16201);
  soil4->AddElement(Fe, 0.11688* 1/1.16201);
//   soil4->AddElement(Sm, 0.0010506);
//   soil4->AddElement(Eu, 0.00016997);
//   soil4->AddElement(Gd, 0.0013547);
//   soil4->AddElement(Th, 0.00030065);

  //---------------------------------------------------------------------------
  // Create Experimental Hall
  //---------------------------------------------------------------------------

  G4Box* expHall_box           = new G4Box("expHall_box",
					   8000.0 *m, 8000.0 *m, 20.0 *m );
  
  G4LogicalVolume* expHall_log = new G4LogicalVolume(expHall_box,
						     vacuum,
						     "expHall_log", 0, 0, 0);
  
  fExpHall                     = new G4PVPlacement(0, G4ThreeVector(),
						   expHall_log, "expHall", 0, false, 99);

  //---------------------------------------------------------------------------
  // Create Surface Volume
  //---------------------------------------------------------------------------

  G4Box* surf_box           = new G4Box("surf_box",
					8000. *m, 8000.*m, 10 *m );
  
  G4LogicalVolume* surf_log = new G4LogicalVolume(surf_box,
						  vacuum,
						  "surf_log", 0, 0, 0);
  
  fSurfVol                   = new G4PVPlacement(0, G4ThreeVector(0.,0.,-10.*m),
                                                 surf_log, "surf", expHall_log, false, 98);

  //---------------------------------------------------------------------------
  // Create Detector Volumes
  //---------------------------------------------------------------------------
  
  G4Box* det1_box           = new G4Box("det1_box",
                                       8000. *m, 8000. *m, 5.0 *cm );
  
  G4LogicalVolume* det1_log = new G4LogicalVolume(det1_box,
                                                 soil1,
                                                 "det1_log", 0, 0, 0);

  fDetVol[0] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-5)*cm),
				   det1_log, "det1", surf_log, false, 0);

  fDetVol[1] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-10-5)*cm),
				   det1_log, "det2", surf_log, false, 1);

  //---------------------------------------------------------------------------

  G4Box* det2_box           = new G4Box("det2_box",
                                       8000. *m, 8000. *m, 5.0 *cm );
  
  G4LogicalVolume* det2_log = new G4LogicalVolume(det2_box,
                                                 soil2,
                                                 "det2_log", 0, 0, 0);

  fDetVol[2] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-20-5)*cm),
				   det2_log, "det3", surf_log, false, 2);

  fDetVol[3] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-20-10-5)*cm),
				   det2_log, "det4", surf_log, false, 3);

  fDetVol[4] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-20-20-5)*cm),
				   det2_log, "det5", surf_log, false, 4);

  fDetVol[5] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-20-30-5)*cm),
				   det2_log, "det6", surf_log, false, 5);

  fDetVol[6] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-20-40-5)*cm),
				   det2_log, "det7", surf_log, false, 6);

  //---------------------------------------------------------------------------

  G4Box* det3_box           = new G4Box("det3_box",
                                       8000. *m, 8000. *m, 5.0 *cm );
  
  G4LogicalVolume* det3_log = new G4LogicalVolume(det3_box,
                                                 soil3,
                                                 "det3_log", 0, 0, 0);

  fDetVol[7] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-70-5)*cm),
				   det3_log, "det8", surf_log, false, 7);

  fDetVol[8] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-80-5)*cm),
				   det3_log, "det9", surf_log, false, 8);

  fDetVol[9] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-90-5)*cm),
				   det3_log, "det10", surf_log, false, 9);

  fDetVol[10] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-100-5)*cm),
				   det3_log, "det11", surf_log, false, 10);

  fDetVol[11] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-110-5)*cm),
				   det3_log, "det12", surf_log, false, 11);

  fDetVol[12] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-120-5)*cm),
				   det3_log, "det13", surf_log, false, 12);

  fDetVol[13] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-130-5)*cm),
				   det3_log, "det14", surf_log, false, 13);

  fDetVol[14] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-140-5)*cm),
				   det3_log, "det15", surf_log, false, 14);

  fDetVol[15] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-150-5)*cm),
				   det3_log, "det16", surf_log, false, 15);

  fDetVol[16] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-160-5)*cm),
				   det3_log, "det17", surf_log, false, 16);

  fDetVol[17] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-170-5)*cm),
				  det3_log, "det18", surf_log, false, 17);

  fDetVol[18] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-180-5)*cm),
				  det3_log, "det19", surf_log, false, 18);

  fDetVol[19] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-190-5)*cm),
				  det3_log, "det20", surf_log, false, 19);

  fDetVol[20] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-200-5)*cm),
				  det3_log, "det21", surf_log, false, 20);

  fDetVol[21] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-210-5)*cm),
				  det3_log, "det22", surf_log, false, 21);

  //---------------------------------------------------------------------------

  G4Box* det4_box           = new G4Box("det4_box",
                                       8000. *m, 8000. *m, 5.0 *cm );
  
  G4LogicalVolume* det4_log = new G4LogicalVolume(det4_box,
                                                 soil4,
                                                 "det4_log", 0, 0, 0);

  fDetVol[22] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-220-5)*cm),
				   det4_log, "det23", surf_log, false, 22);

  fDetVol[23] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-230-5)*cm),
				   det4_log, "det24", surf_log, false, 23);

  fDetVol[24] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-240-5)*cm),
				   det4_log, "det25", surf_log, false, 24);

  fDetVol[25] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-250-5)*cm),
				   det4_log, "det26", surf_log, false, 25);

  fDetVol[26] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-260-5)*cm),
				   det4_log, "det27", surf_log, false, 26);

  fDetVol[27] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-270-5)*cm),
				   det4_log, "det28", surf_log, false, 27);

  fDetVol[28] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-280-5)*cm),
				   det4_log, "det29", surf_log, false, 28);

  fDetVol[29] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-290-5)*cm),
				   det4_log, "det30", surf_log, false, 29);

  fDetVol[30] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-300-5)*cm),
				   det4_log, "det31", surf_log, false, 30);

  fDetVol[31] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-310-5)*cm),
				   det4_log, "det32", surf_log, false, 31);

  fDetVol[32] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-320-5)*cm),
				   det4_log, "det33", surf_log, false, 32);

  fDetVol[33] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-330-5)*cm),
				   det4_log, "det34", surf_log, false, 33);

  fDetVol[34] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-340-5)*cm),
				   det4_log, "det35", surf_log, false, 34);

  fDetVol[35] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-350-5)*cm),
				   det4_log, "det36", surf_log, false, 35);

  fDetVol[36] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-360-5)*cm),
				   det4_log, "det37", surf_log, false, 36);

  fDetVol[37] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-370-5)*cm),
				   det4_log, "det38", surf_log, false, 37);

  fDetVol[38] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-380-5)*cm),
				   det4_log, "det39", surf_log, false, 38);

  fDetVol[39] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-390-5)*cm),
				   det4_log, "det40", surf_log, false, 39);

  fDetVol[40] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-400-5)*cm),
				   det4_log, "det41", surf_log, false, 40);

  fDetVol[41] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-410-5)*cm),
				   det4_log, "det42", surf_log, false, 41);

  fDetVol[42] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-420-5)*cm),
				   det4_log, "det43", surf_log, false, 42);

  fDetVol[43] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-430-5)*cm),
				   det4_log, "det44", surf_log, false, 43);

  fDetVol[44] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-440-5)*cm),
				   det4_log, "det45", surf_log, false, 44);

  fDetVol[45] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-450-5)*cm),
				   det4_log, "det46", surf_log, false, 45);

  fDetVol[46] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-460-5)*cm),
				   det4_log, "det47", surf_log, false, 46);

  fDetVol[47] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-470-5)*cm),
				   det4_log, "det48", surf_log, false, 47);

  fDetVol[48] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-480-5)*cm),
				   det4_log, "det49", surf_log, false, 48);

  fDetVol[49] = new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-490-5)*cm),
				   det4_log, "det50", surf_log, false, 49);

  //---------------------------------------------------------------------------

  G4Box* det5_box           = new G4Box("det5_box",
                                       8000. *m, 8000. *m, 500.0 *cm );
  
  G4LogicalVolume* det5_log = new G4LogicalVolume(det5_box,
                                                 soil4,
                                                 "det5_log", 0, 0, 0);

  new G4PVPlacement(0, G4ThreeVector(0.,0.,(1000-500-500)*cm),
				   det5_log, "det55", surf_log, false, 55);

  //---------------------------------------------------------------------------
  // Set Step Limits, Sensitive Detector and Visualisation
  //---------------------------------------------------------------------------

  G4double maxStep = 0.5 *mm;;
  G4UserLimits* stepLimit = new G4UserLimits(maxStep);

  G4SDManager* SDman = G4SDManager::GetSDMpointer();

  fFluxSD = new FluxSD("FluxSD", 1);
  SDman->AddNewDetector( fFluxSD );
  det1_log->SetSensitiveDetector( fFluxSD );
  det2_log->SetSensitiveDetector( fFluxSD );
  det3_log->SetSensitiveDetector( fFluxSD );
  det4_log->SetSensitiveDetector( fFluxSD );

//  fEdepSD = new EnergyDepositSD("EdepSD", 1);
//  SDman->AddNewDetector( fEdepSD );
//  det_log->SetSensitiveDetector( fEdepSD );
    
  G4VisAttributes* blue    = new G4VisAttributes( G4Colour(0.0,0.0,1.0)   );
  G4VisAttributes* red     = new G4VisAttributes( G4Colour(1.0,0.0,0.0)   );

  det1_log->SetVisAttributes(red);
  det2_log->SetVisAttributes(blue);
  det3_log->SetVisAttributes(red);
  det4_log->SetVisAttributes(blue);

  return fExpHall;
}

//---------------------------------------------------------------------------

void DetectorConstruction::UpdateGeometry()
{
  G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
}

//---------------------------------------------------------------------------
