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


#define NTUPLES 1
#define HISTO  1
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
  if(theTFile) delete theTFile;
}

void SHMSAnalysisManager::Clear()
{
  if (theTFile) {
    Ntuples.clear();  
    histo3d.clear();
    histo2d.clear(); 
    histo1d.clear(); 
  }

}

void SHMSAnalysisManager::OpenROOTFile()
{
   
  G4cout << "\n----> Open rootfile .. " << G4endl;
  theTFile = new TFile(fileName, "RECREATE");

  CreateNtuplesHistos();

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

//Create Ntuples
void SHMSAnalysisManager::CreateNtuplesHistos()
{
  detNames = fDetector->GetDetNames();
  nDet = detNames.size();

  Ntuples.resize(nDet);
  histo1d.resize(nDet);
  histo2d.resize(nDet);
  histo3d.resize(nDet);


  for(G4int i=0;i<nDet;i++)
    {
      // create Ntuples

      if(NTUPLES)
	Ntuples.at(i)  = new TNtuple(detNames.at(i), 
				     "detector hits", 
				     "local_x_cm:local_y_cm:local_z_cm:vertexE_MeV:eDep_MeV:scat_angle_deg:flagParticle");	

      // Create histogram(s)
      histo1d.at(i) = new TH1D(Form("Tot_Edep_%s",(detNames.at(i)).data()), "Total Energy Deposition in the Volume; Total Energy Deposition (MeV); Electrons in the Beam ", 800, 0.0, 800.0*MeV);
      histo2d.at(i) = new TH2D(Form("XYpos_%s",(detNames.at(i)).data()), "Hits on the XY plane; X (cm); Y (cm)", 0, 0.0, 0.0, 0, 0.0, 0.0);         
      histo3d.at(i) = new TH3D(Form("Edep_%s",(detNames.at(i)).data()), "Energy Deposition Spectrum in Volume; X (cm); Y(cm); Z(cm)", 0, 0.0, 0.0, 0, 0.0, 0.0, 0, 0.0, 0.0);
    }

  G4cout << "\n----> Histograms and Ntuples are opened in "<<fileName<< G4endl;

}


// This function fills a N-tuple with position and energy of 
// electrons entering the measurement volume.
//
void SHMSAnalysisManager::FillNtuples(SHMSDetectorHit *aHit,G4String ntuple_name)  
{
  if(NTUPLES){
    TNtuple *ntuple = (TNtuple*)gDirectory->Get(ntuple_name);
    
    if(!ntuple) {
      G4cout<<" Unable to find ntuple- "<<ntuple_name<<G4endl;
      return;
    }
    else{
      ntuple->Fill(aHit->GetLocalPos().x()/cm,
		   aHit->GetLocalPos().y()/cm,
		   aHit->GetLocalPos().z()/cm,
		   aHit->GetVertexEnergy()/MeV,
		   aHit->GetEnergyDeposit()/MeV,
		   aHit->GetScatAngle(),
		   aHit->GetParticleFlag());
      
    }
  }

}


void SHMSAnalysisManager::FillHistograms(SHMSDetectorHit *aHit,G4String hist_name)
{
  
  TH2* histo2 = (TH2D*)gDirectory->Get(Form("XYpos_%s",hist_name.data()));
  TH3* histo3 = (TH3D*)gDirectory->Get(Form("Edep_%s",hist_name.data()));

  if(!histo3){
    G4cout<<" Unable to find the 3D energy deposit histogram for "<<hist_name<<G4endl;
    return;
  }
  else{
    histo3 ->Fill(aHit->GetLocalPos().x()/cm,
		  aHit->GetLocalPos().y()/cm,
		  aHit->GetLocalPos().z()/cm,
		  aHit->GetEnergyDeposit()/MeV); 
  }

  if(!histo2){
    G4cout<<" Unable to find the xy plane hit histogram for "<<hist_name<<G4endl;
    return;
  }
  else{
    histo2 ->Fill(aHit->GetLocalPos().y()/cm, aHit->GetLocalPos().x()/cm); 
  }


}
