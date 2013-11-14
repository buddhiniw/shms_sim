//******************************************************************
/*
Date - 10/15/2013
Author - B.Waidyawansa

SHMSCoilsHit  class implementation



*/
//******************************************************************

#include "MagnetCoilsHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4Allocator<MagnetCoilsHit> MagnetCoilsHitAllocator;

MagnetCoilsHit::MagnetCoilsHit() {}

MagnetCoilsHit::~MagnetCoilsHit() {}

MagnetCoilsHit::MagnetCoilsHit(const MagnetCoilsHit& right)
  : G4VHit()
{
  trackID   = right.trackID;
  coilsNb   = right.coilsNb;
  edep      = right.edep;
  pos       = right.pos;
}

const MagnetCoilsHit& MagnetCoilsHit::operator=(const MagnetCoilsHit& right)
{
  trackID   = right.trackID;
  coilsNb   = right.coilsNb;
  edep      = right.edep;
  pos       = right.pos;
  return *this;
}

G4int MagnetCoilsHit::operator==(const MagnetCoilsHit& right) const
{
  return (this==&right) ? 1 : 0;
}

void MagnetCoilsHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
  {
    G4Circle circle(pos);
    circle.SetScreenSize(2.);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,0.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}

void MagnetCoilsHit::Print()
{
  G4cout << "  trackID: " << trackID << "  coilNb: " << coilsNb
         << "  energy deposit: " << G4BestUnit(edep,"Energy")
         << "  position: " << G4BestUnit(pos,"Length") << G4endl;
}
