#ifndef PHYSICS_HH
#define PHYSICS_HH

#include "Shielding.hh"

class MyPhysicsList : public Shielding
{
public:
        MyPhysicsList();
        ~MyPhysicsList() override;
};

#endif
