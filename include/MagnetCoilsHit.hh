//******************************************************************
/*
Date - 10/15/2013
Author - B.Waidyawansa

SHMSCoilsHit - class for the sensitive volume of the coils



*/
//******************************************************************

#ifndef MagnetCoilsHit_h
#define MagnetCoilsHIt_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class MagnetCoilsHit : public G4VHit
{
  public:

      MagnetCoilsHit();
     ~MagnetCoilsHit();
      MagnetCoilsHit(const MagnetCoilsHit&);
      const MagnetCoilsHit& operator=(const MagnetCoilsHit&);
      G4int operator==(const MagnetCoilsHit&) const;

      inline void* operator new(size_t);
      inline void  operator delete(void*);

      void Draw();
      void Print();

  public:
  
      void SetTrackID  (G4int track)      { trackID = track; };
      void SetCoilNb(G4int chamb)      { coilsNb = chamb; };  
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

typedef G4THitsCollection<MagnetCoilsHit> MagnetCoilsHitsCollection;

extern G4Allocator<MagnetCoilsHit> MagnetCoilsHitAllocator;

inline void* MagnetCoilsHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) MagnetCoilsHitAllocator.MallocSingle();
  return aHit;
}

inline void MagnetCoilsHit::operator delete(void *aHit)
{
  MagnetCoilsHitAllocator.FreeSingle((MagnetCoilsHit*) aHit);
}


#endif



