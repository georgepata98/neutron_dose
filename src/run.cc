#include "run.hh"

MyRunAction::MyRunAction()
{
        G4RunManager::GetRunManager()->SetPrintProgress(0);
        
        G4AccumulableManager* accMan = G4AccumulableManager::Instance();
        accMan->Register(totalDose);
        accMan->Register(totalDose2);
}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
        G4int runID = run->GetRunID();
        
        G4AccumulableManager* accMan = G4AccumulableManager::Instance();
        accMan->Reset();
        
        G4RunManager::GetRunManager()->SetRandomNumberStore(false);
}

void MyRunAction::EndOfRunAction(const G4Run* run)
{
        G4int runID = run->GetRunID();
        
        G4int nOfEvents = run->GetNumberOfEvent();
        if(nOfEvents == 0) return;
        
        G4AccumulableManager* accMan = G4AccumulableManager::Instance();
        accMan->Merge();
        
        G4double meanDose = totalDose.GetValue() / nOfEvents;
        G4double meanDose2 = totalDose2.GetValue() / nOfEvents;
        G4double var = meanDose2 - meanDose * meanDose;
        G4double err = std::sqrt(var / nOfEvents);
        
        std::ostringstream runFileName;
        runFileName << "output_Run" << runID << ".txt"; // nume fisiere de output cu dozele dupa fiecare Run
        
        std::ofstream runOutputFile(runFileName.str());
        runOutputFile << " ===== REZULTAT (Gy/NPS) RUN" << runID << " =====\n";
        runOutputFile << G4BestUnit(meanDose, "Dose") << "  " << G4BestUnit(err, "Dose") << "\n";
        runOutputFile.close();
}
