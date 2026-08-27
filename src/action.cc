#include "action.hh"

MyActionInitialization::MyActionInitialization()
{}

MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::BuildForMaster() const
{
        SetUserAction(new MyRunAction());
}

void MyActionInitialization::Build() const
{
        MyPrimaryGenerator *generator = new MyPrimaryGenerator();
        SetUserAction(generator);
        
        MyRunAction *runAction = new MyRunAction();
        SetUserAction(runAction);
        
        MyEventAction *eventAction = new MyEventAction(runAction);
        SetUserAction(eventAction);
}
