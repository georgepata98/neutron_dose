#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume* MyDetectorConstruction::Construct()
{
        G4NistManager *nist = G4NistManager::Instance();
        
        G4Material *air = nist->FindOrBuildMaterial("G4_AIR");
        G4Material *water = nist->FindOrBuildMaterial("G4_WATER");
        
        G4Box *solidWorld = new G4Box("solidWorld", 25*cm, 25*cm, 25*cm);
        G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, air, "logicWorld");
        G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicWorld, "physWorld", 0, false, 0);
        
        G4Box *sTarget = new G4Box("sTarget", 10*cm, 10*cm, 5*cm);  // 20x20x10 cm placa
        G4LogicalVolume *lTarget = new G4LogicalVolume(sTarget, water, "lTarget");
        G4VPhysicalVolume *pTarget = new G4PVPlacement(0, G4ThreeVector(0, 0, 10*cm), lTarget, "pTarget", logicWorld, false, 0);
        
        return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
        G4SDManager::GetSDMpointer()->SetVerboseLevel(1);
        G4VPrimitiveScorer *primitive;
        G4MultiFunctionalDetector *doseDet;
        
        doseDet = new G4MultiFunctionalDetector("doseDet");
        G4SDManager::GetSDMpointer()->AddNewDetector(doseDet);
        
        primitive = new G4PSDoseDeposit("Ddep");

        doseDet->RegisterPrimitive(primitive);
        
        SetSensitiveDetector("lTarget", doseDet);
}
