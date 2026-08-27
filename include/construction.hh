#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "G4SDManager.hh"

#include "G4Box.hh"

#include "G4VPrimitiveScorer.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4PSDoseDeposit.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
        MyDetectorConstruction();
        ~MyDetectorConstruction();
        
        virtual G4VPhysicalVolume *Construct();
        
private:
        virtual void ConstructSDandField();
};

#endif
