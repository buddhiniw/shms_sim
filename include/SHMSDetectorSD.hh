//******************************************************************
/*
Date - 11/6/2013
Author - B.Waidyawansa





*/
//******************************************************************

#ifndef SHMSDetectorSD_h
#define SHMSDetectorSD_h 1

#include "G4VSensitiveDetector.hh"
#include "SHMSDetectorHit.hh"

class SHMSDetectorSD: public G4VSensitiveDetector 
{
  
public:
  SHMSDetectorSD(G4String name,  G4String type);
  ~SHMSDetectorSD();
  
  virtual void Initialize(G4HCofThisEvent*HCE);
  virtual G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*x);
  virtual void EndOfEvent(G4HCofThisEvent*HCE);
  inline G4String GetIdentifier() const {return identifier;};
  
private:
  SHMSDetectorHitsCollection *hitsCollection;
  G4int HCID;
  G4String identifier;
};

#endif



