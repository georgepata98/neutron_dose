#include "event.hh"

MyEventAction::MyEventAction(MyRunAction* runAction)
:fRunAction(runAction)
{
        G4RunManager::GetRunManager()->SetPrintProgress(0);
        
        auto analysisManager = G4AnalysisManager::Instance();
        analysisManager->SetVerboseLevel(0);
}

MyEventAction::~MyEventAction()
{}

G4THitsMap<G4double>* MyEventAction::GetHitsCollection(G4int hcID, const G4Event *event) const
{
        auto hitsCollection = static_cast<G4THitsMap<G4double>*>(event->GetHCofThisEvent()->GetHC(hcID));
        
        if(!hitsCollection)
        {
                G4ExceptionDescription msg;
                msg << "Cannot access hitsCollection ID " << hcID;
                G4Exception("EventAction::GetHitsCollection()", "MyCode0003", FatalException, msg);
        }
        
        return hitsCollection;
}

G4double MyEventAction::GetSum(G4THitsMap<G4double>* hitsMap) const
{
        G4double sumValue = 0;
        
        for(auto it:*hitsMap->GetMap())
        {
                sumValue += *(it.second);
        }
        
        return sumValue;
}

void MyEventAction::BeginOfEventAction(const G4Event*)
{}

void MyEventAction::EndOfEventAction(const G4Event *event)
{
        if(fAbsoDdepHCID == -1)
        {
                fAbsoDdepHCID = G4SDManager::GetSDMpointer()->GetCollectionID("doseDet/Ddep"); // MultiFunctionalDetector / PrimitiveScorer names
        }
        
        G4double dose = GetSum(GetHitsCollection(fAbsoDdepHCID, event));
        
        if(dose > 0.)
        {
                fRunAction->AddDdep(dose);
                fRunAction->AddDdep2(dose);
                
                sum += dose;
        }
}
