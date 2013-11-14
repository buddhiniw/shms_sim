//******************************************************************
/*
Date - 10/11/2013
Author - B.Waidyawansa

SHMSRunAction class implementation using examples/extended/electromagnetic/TestEM4



*/
//******************************************************************

#include "SHMSRunAction.hh"
#include "G4Run.hh"
#include "G4ParticleDefinition.hh"



SHMSRunAction::SHMSRunAction(SHMSDetectorConstruction* det, SHMSAnalysisManager* ana,SHMSEventAction* eve)
  :Detector(det),Output(ana),Event(eve)
{}

SHMSRunAction::~SHMSRunAction()
{}


void SHMSRunAction::BeginOfRunAction(const G4Run* aRun)
{  
  G4cout << "\n### Run Action - Run " << aRun->GetRunID() << " start.." << G4endl;

  // Open ROOT file to store ROOT tree
  Output->OpenROOTFile();
}


void SHMSRunAction::EndOfRunAction(const G4Run*)
{

  //save ntuples
  Output->SaveROOTFile();

  G4cout << "### Run Action complete.." << G4endl;

}
