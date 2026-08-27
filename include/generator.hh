#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4SystemOfUnits.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "G4Event.hh"

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
public:
        MyPrimaryGenerator();
        ~MyPrimaryGenerator() override;
        
        virtual void GeneratePrimaries(G4Event *anEvent) override;

private:
        G4GeneralParticleSource *particleSource = nullptr;
};

#endif
