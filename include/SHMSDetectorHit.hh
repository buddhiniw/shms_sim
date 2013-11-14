//******************************************************************
/*
Date - 11/6/2013
Author - B.Waidyawansa





*/
//******************************************************************

#ifndef SHMSDetectorHit_h
#define SHMSDetectorHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"
#include "G4Allocator.hh"

class SHMSDetectorHit : public G4VHit
{
  
public:
  SHMSDetectorHit();
  ~SHMSDetectorHit();


  void Draw();
  void Print();
  
  // Get/Set functions
  //
  inline void SetWorldPos(G4ThreeVector xyz) 
  { worldPos = xyz; }
  inline G4ThreeVector GetWorldPos() const 
  { return worldPos; }
  
  inline void SetLocalPos(G4ThreeVector xyz) 
  { localPos = xyz; }
  inline G4ThreeVector GetLocalPos() const 
  { return localPos; }

  inline void SetKineticEnergy(G4double e)
  { kineE = e; }
  inline G4double GetKineticEnergy()
  { return kineE; }

  inline void SetKineticEnergy0(G4double e)
  { kineE0 = e; }
  inline G4double GetKineticEnergy0()
  { return kineE0; }

  inline void SetEnergyDeposit(G4double e)
  { eDep = e; }
  inline G4double GetEnergyDeposit()
  { return eDep; }

  
  inline void  SetCreatorProcess(G4String creator)
  { creatorProcess = creator; }
  inline G4String GetCreatorProcess() const 
  { return creatorProcess; }

  inline void  SetParticleFlag(G4double f)  
  { particleFlag = f; }
  inline G4double GetParticleFlag() const 
  { return particleFlag; }
 
  inline void SetScatAngle(G4double ang)
  { scat_ang = ang; }
  inline G4double GetScatAngle()
  { return scat_ang; }

private:

  G4ThreeVector worldPos;
  G4ThreeVector localPos;

  G4double kineE;
  G4double kineE0;
  G4double eDep;
  G4double particleFlag;
  G4String creatorProcess;
  
  G4double scat_ang;

};

typedef G4THitsCollection<SHMSDetectorHit> SHMSDetectorHitsCollection;
extern G4Allocator<SHMSDetectorHit> SHMSDetectorHitAllocator;

#endif



