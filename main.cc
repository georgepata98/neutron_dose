#include <iostream>
#include <string>
#include <ctime>
#include <climits>

#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4ScoringManager.hh"

#include "Randomize.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"

int main(int argc, char** argv)
{
        G4int nOfRuns = 1;  // de modificat aici nr. de run-uri
        G4bool visualization = true;  // true = cu vizualizare geometrie, false = fara vizualizare
        
        G4int visEvents = 15;  // nr. events cand visualization = true
        // G4int eventsPerRun = 2000000000;  // nr. ~max, care depinde de int
        G4int eventsPerRun = 5000000;
        
        /* ATENTIE: loop-ul cu run-uri se executa numai cand visualization = false */
        
        G4UImanager *UImanager = G4UImanager::GetUIpointer();
        G4ScoringManager::GetScoringManager();
        
        G4UIExecutive *ui = nullptr;
        
        if(argc == 1)
        {
                ui = new G4UIExecutive(argc, argv);
        }
        
        G4RunManager *runManager = new G4RunManager();
        runManager->SetUserInitialization(new MyDetectorConstruction());
        runManager->SetUserInitialization(new MyPhysicsList());
        runManager->SetUserInitialization(new MyActionInitialization());
        runManager->Initialize();
        
        G4VisManager *visManager = new G4VisExecutive();
        visManager->Initialize();
        
        if(ui)
        {
                if(visualization)
                {
                        UImanager->ApplyCommand("/control/execute vis.mac");
                        UImanager->ApplyCommand("/control/execute gps.mac");
                        
                        runManager->BeamOn(visEvents);
                        ui->SessionStart();  // activare GUI
                }
                if(!visualization) UImanager->ApplyCommand("/control/execute gps.mac");
                delete ui;
        }
        else
        {
                G4String command = "/control/execute ";
                G4String fileName = argv[1];
                UImanager->ApplyCommand(command + fileName);
        }
        
        
        // Runs loop
        if(!visualization)
        {
                for(G4int i=0; i<nOfRuns; ++i)
                {
                        G4Random::setTheSeed(time(0) + i);
                        runManager->BeamOn(eventsPerRun);
                        
                        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
                }
        }
        
        
        delete visManager;
        delete runManager;
        
        return 0;
}
