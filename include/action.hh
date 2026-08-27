#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"

#include "generator.hh"
#include "run.hh"
#include "event.hh"

class MyActionInitialization : public G4VUserActionInitialization
{
public:
        MyActionInitialization();
        ~MyActionInitialization() override;
        
        virtual void BuildForMaster() const override;
        virtual void Build() const override;
};

#endif
