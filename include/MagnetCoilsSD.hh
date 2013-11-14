//******************************************************************
/*
Date - 10/15/2013
Author - B.Waidyawansa

MagnetCoilsSD - class for the sensitive volume of the coils

11-01-2013 Buddhini Updated to MagnetCoilsSD


*/
//******************************************************************

#ifndef MagnetCoilsSD_h
#define MagnetCoilsSD_h 1

#include "G4VSensitiveDetector.hh"
#include "MagnetCoilsHit.hh"

class G4Step;
class G4HCofThisEvent;

class MagnetCoilsSD : public G4VSensitiveDetector
{
public:
  MagnetCoilsSD(G4String);
  ~MagnetCoilsSD();
  
  void Initialize(G4HCofThisEvent*);
  G4bool ProcessHits(G4Step*, G4TouchableHistory*);
  void EndOfEvent(G4HCofThisEvent*);
  
private:
  MagnetCoilsHitsCollection* coilsCollection;
  
};


#endif



