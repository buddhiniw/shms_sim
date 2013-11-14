//******************************************************************
/*
Date - 10/15/2013
Author - B.Waidyawansa

SHMSCoilsHit - class to handle the interactions of the particles with the coils.



*/
//******************************************************************

#ifndef SHMSCoilsHit_h
#define SHMSCoilsHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class SHMSCoilsHit : public G4VHit
{
public:
  
  SHMSCoilsHit();
  ~SHMSCoilsHit();
  SHMSCoilsHit(const SHMSCoilsHit&);
  const SHMSCoilsHit& operator=(const SHMSCoilsHit&);
  G4int operator==(const SHMSCoilsHit&) const;
  
  inline void* operator new(size_t);
  inline void  operator delete(void*);
  
  void Draw();
  void Print();
  
public:
  
  void SetTrackID  (G4int track)      { trackID = track; };
  void SetCoilsNb(G4int chamb)      { chamberNb = chamb; };  
  void SetEdep     (G4double de)      { edep = de; };
  void SetPos      (G4ThreeVector xyz){ pos = xyz; };
  
  G4int GetTrackID()    { return trackID; };
  G4int GetCoilsNb()  { return coilsNb; };
  G4double GetEdep()    { return edep; };      
  G4ThreeVector GetPos(){ return pos; };
  
private:
  
  G4int         trackID;
  G4int         coilsNb;
  G4double      edep;
  G4ThreeVector pos;
};

#endif



