
#include "GLEESimDetectorConstruction.hh"

// Necessary geometry classes
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

// Includes for material and unit definitions
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"

// Geometry shape header files
#include "G4Box.hh"

GLEESimDetectorConstruction::GLEESimDetectorConstruction()
    : G4VUserDetectorConstruction()
{ 
}

//***********************************************/

GLEESimDetectorConstruction::~GLEESimDetectorConstruction()
{
}

//***********************************************/

G4VPhysicalVolume* GLEESimDetectorConstruction::Construct()
{
    //Get material list pointer
	G4NistManager* nistManager = G4NistManager::Instance();
    // Build  materials directly from the NIST manager
    G4Material* galactic = nistManager->FindOrBuildMaterial("G4_Galactic");
    //Define World
	G4double Ws = 1.0*m; // world side
    //Create world volume (Sphere of radius 1 m having intergalactic material density)
    // Define the solid shape
	G4Box* worldS = new G4Box("worldS",Ws,Ws,Ws);
    // Define its logical volume
    G4LogicalVolume* worldLV = new G4LogicalVolume(worldS, galactic, "World");
    // Place
    G4VPhysicalVolume* worldPV = new G4PVPlacement(0, G4ThreeVector(), worldLV, "World", 0, false, 0, true);

    G4Material* epoxy = new G4Material("Epoxy", 1.2*g/cm3,2);
    epoxy->AddElement(nistManager->FindOrBuildElement("H"),2);
    epoxy->AddElement(nistManager->FindOrBuildElement("C"),2);

    G4Material* SiO2 = new G4Material("quartz", 2.2*g/cm3,2);
    SiO2->AddElement(nistManager->FindOrBuildElement("Si"),1);
    SiO2->AddElement(nistManager->FindOrBuildElement("O"),2);

    G4Material* FR4 = new G4Material("FR4", 1.86*g/cm3,2);
    FR4->AddMaterial(SiO2,0.528);
    FR4->AddMaterial(epoxy, 0.472);

    G4Box* pcb = new G4Box("PCB",5*cm,5*cm,1.57*mm);
    G4LogicalVolume* pcbLV = new G4LogicalVolume(pcb, FR4, "PCB");
    G4VPhysicalVolume* pcbPV = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.5*m), pcbLV, "PCB", worldLV, false, 0, true);
    return worldPV; 
}