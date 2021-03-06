//******************************************************************
/*
Date - 10/15/2013
Author - B.Waidyawansa

SHMSCoilsSD  class implementation


11-01-2013 Buddhini Updated to MagnetCoilsSD

*/
//******************************************************************

#include "MagnetCoilsSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

MagnetCoilsSD::MagnetCoilsSD(G4String name)
:G4VSensitiveDetector(name)
{
  G4String HCname;
  collectionName.insert(HCname="coilsCollection");
}

MagnetCoilsSD::~MagnetCoilsSD(){ }

void MagnetCoilsSD::Initialize(G4HCofThisEvent* HCE)
{
//   coilsCollection = new MagnetCoilsHitsCollection
//     (SensitiveDetectorName,collectionName[0]); 
//   static G4int HCID = -1;
//   if(HCID<0)
//     { HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]); }
//   HCE->AddHitsCollection( HCID, coilsCollection ); 
}

G4bool MagnetCoilsSD::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
  G4double edep = aStep->GetTotalEnergyDeposit();

//   if(edep==0.) return false;

//   MagnetCoilsHit* newHit = new MagnetCoilsHit();
//   newHit->SetTrackID  (aStep->GetTrack()->GetTrackID());
//   newHit->SetCoilNb(aStep->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber());
//   newHit->SetEdep     (edep);
//   newHit->SetPos      (aStep->GetPostStepPoint()->GetPosition());
//   coilsCollection->insert( newHit );
  
  //newHit->Print();
  //newHit->Draw();
  
  return true;
}

void MagnetCoilsSD::EndOfEvent(G4HCofThisEvent*)
{
//   if (verboseLevel>0) { 
//     G4int NbHits = coilsCollection->entries();
//     G4cout << "\n-------->Hits Collection: in this event they are " << NbHits 
// 	   << " hits on the coils: " << G4endl;
//     for (G4int i=0;i<NbHits;i++) (*coilsCollection)[i]->Print();
//   } 
}
