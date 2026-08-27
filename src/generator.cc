#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
:G4VUserPrimaryGeneratorAction()
{
        particleSource = new G4GeneralParticleSource;
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
        delete particleSource;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
        particleSource->GeneratePrimaryVertex(anEvent);
}
