//******************************************************************
/*
Date - 10/15/2013
Author - B.Waidyawansa

SHMSDetectorSD  class implementation



*/
//******************************************************************

#include "SHMSDetectorSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"

SHMSDetectorSD::SHMSDetectorSD(G4String name, G4String type)
:G4VSensitiveDetector(name)
{
  G4String HCname;
  collectionName.insert(HCname="hitsColl");
  identifier = type;
}

SHMSDetectorSD::~SHMSDetectorSD()
{ }

void SHMSDetectorSD::Initialize(G4HCofThisEvent* HCE)
{
  hitsCollection = new SHMSDetectorHitsCollection(SensitiveDetectorName,collectionName[0]); 
  HCID = -1;
  if(HCID<0)
    { HCID = G4SDManager::GetSDMpointer()->GetCollectionID(hitsCollection); }
  HCE->AddHitsCollection( HCID, hitsCollection); 
}

G4bool SHMSDetectorSD::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{


  // Identify and flag the particle
  //

  G4double flagParticle=0.;

  if (aStep->GetTrack()->GetDynamicParticle()->GetDefinition() ->GetParticleName() == "e-")       flagParticle = 1;    
  if (aStep->GetTrack()->GetDynamicParticle()->GetDefinition() ->GetParticleName() == "e+")       flagParticle = 2;
  if (aStep->GetTrack()->GetDynamicParticle()->GetDefinition() ->GetParticleName() == "gamma")    flagParticle = 3;
  if (aStep->GetTrack()->GetDynamicParticle()->GetDefinition() ->GetParticleName() == "neutron")  flagParticle = 4;

   /*
    
  PreStepPoint and PostStepPoint.
  
  
  NOTE: In Geant4, "particles are NOT transported in the tracking category".
  
  It means that tracking is not been done from one point to the other.
  Instead, G4 uses concept of 'step', which is related with physics process.
  It calculates most probable process and do it.  As a result, it results in
  two points; PreStepPoint and PostStepPoint.
    
  PreStepPoint contains track information before a process has been occurred,
  while PostStepPoint has information after the process has been processed.
  
  PreStepPoint
  
  --> G4 calculates probabilities of the physics processes
  --> Take smallest process step length among the processes
  --> Calculate other processes during the step
  
  --> 
  PostStepPoint
  
  
  So to get the information related with the current 'position', such as 
  current volume, we have to use PreStepPoint.  
  
  But if we need information releted with the 'processes', we have to use
  PostStepPoint.
  
  
  Positional Information: PreStepPoint  : current volume, ...
  Procedural Information: PostStepPoint : process name, eLoss, step length, ...
  */
  const G4Track* fTrack = aStep->GetTrack();
  G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
  G4VPhysicalVolume* volume = preStepPoint->GetTouchableHandle()->GetVolume();
  G4ThreeVector worldPosition = preStepPoint->GetPosition();
  G4ThreeVector localPosition = preStepPoint->GetTouchableHandle()->GetHistory()->GetTopTransform().TransformPoint(worldPosition);

  G4ThreeVector vertexMomentum = fTrack->GetVertexMomentumDirection();
  // scattering angle
  G4double scat_ang = sqrt(vertexMomentum.x()*vertexMomentum.x() + 
			   vertexMomentum.y()*vertexMomentum.y());


  // Creator process
  const G4VProcess* creatorProcess = fTrack->GetCreatorProcess();
  G4String process;
  if (creatorProcess!=0) process = creatorProcess->GetProcessName();

  // Kinetic energy of the original electron which interacted inside the target
  G4double kineE0 = fTrack->GetVertexKineticEnergy();

  // Kinetic energy of the electron when it hit the sensitive detector
  G4double kineE = fTrack->GetKineticEnergy();

  // Total energy deposited
  G4double eDep = aStep->GetTotalEnergyDeposit();

  // Create and define Hit attributes 
  //
  SHMSDetectorHit* newHit = new SHMSDetectorHit();
 
  newHit->SetWorldPos(worldPosition);
  newHit->SetLocalPos(localPosition);
  newHit->SetScatAngle(scat_ang);

  newHit->SetKineticEnergy(kineE);
  newHit->SetKineticEnergy0(kineE0);
  newHit->SetEnergyDeposit(eDep);
    
  newHit->SetCreatorProcess(process);
  newHit->SetParticleFlag(flagParticle);
     
  hitsCollection->insert( newHit );
  
  //newHit->Print();
  //newHit->Draw();
  
  return true;
}

void SHMSDetectorSD::EndOfEvent(G4HCofThisEvent*)
{}
