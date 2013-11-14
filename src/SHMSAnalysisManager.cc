//******************************************************************
/*
Date - 10/23/2013
Author - B.Waidyawansa

SHMSAnalysisManager class implementation
based on geant4.9.6.p02/examples/advanced/purging_magnet/


*/
//******************************************************************

#include <stdlib.h>
#include <fstream>
#include "SHMSAnalysisManager.hh"
#include "SHMSDetectorHit.hh"

SHMSAnalysisManager* SHMSAnalysisManager::fgInstance = 0;

SHMSAnalysisManager* SHMSAnalysisManager::Instance()
{
// Static acces function via G4RunManager 
  return fgInstance;
}   


SHMSAnalysisManager::SHMSAnalysisManager(SHMSDetectorConstruction*det)
  :fDetector(det){

  // set the root file name using the gdml file name
  fileName  = "/data1/cdaq/buddhini/"+fDetector->GetGeomFile()+"_ntuple.root";
  nDet = 0;
  Clear();
}

SHMSAnalysisManager::~SHMSAnalysisManager() 
{ 
}

void SHMSAnalysisManager::Clear()
{
  if (theTFile)
    {
      Ntuples.clear();
    }
}

void SHMSAnalysisManager::OpenROOTFile()
{
   
  G4cout << "\n----> Open rootfile .. " << G4endl;

  theTFile = new TFile(fileName, "RECREATE");
  detNames = fDetector->GetDetNames();
  nDet = detNames.size();
  Ntuples.resize(nDet);
  for(G4int i=0;i<nDet;i++)
    {
      Ntuples.at(i)  = new TNtuple(detNames.at(i), 
				   "detector hits", 
				   "world_x_cm:world_y_cm:world_z_cm:local_x_cm:local_y_cm:local_z_cm:kinE0_MeV:kinE_MeV:eDep_MeV:scat_angle_deg:flagParticle");	

      //AutoSave after every 50 Mbyte written to disk
      //   Ntuples.at(i) -> SetAutoSave(50000000);
    }
 G4cout << "\n----> Ntuples are opened in " << fileName << G4endl;
}


void SHMSAnalysisManager::SaveROOTFile()
{
  if (theTFile)
    {
      theTFile -> Write(); 
      theTFile -> Close();
    }
  theTFile = 0;
  
}


// This function fills a N-tuple with position and energy of 
// electrons entering the measurement volume.
//

void SHMSAnalysisManager::FillNtuple(SHMSDetectorHit *aHit,G4String ntuple_name)  
{
  TNtuple *ntuple = (TNtuple *)gDirectory->Get(ntuple_name);
  if(!ntuple) {
    G4cout<<" Unable to find ntuple- "<<ntuple<<G4endl;
    return;
  }
  else{
    ntuple->Fill(aHit->GetWorldPos().x()/cm,aHit->GetWorldPos().y()/cm,aHit->GetWorldPos().z()/cm,
		 aHit->GetLocalPos().x()/cm,aHit->GetLocalPos().y()/cm,aHit->GetLocalPos().z()/cm,
		 aHit->GetKineticEnergy0()/MeV,aHit->GetKineticEnergy()/MeV,aHit->GetEnergyDeposit()/MeV,
		 aHit->GetScatAngle(),aHit->GetParticleFlag());
  }
}
