//******************************************************************
/*
Date - 10/15/2013
Author - B.Waidyawansa

SHMSDetectorHit  class implementation



*/
//******************************************************************

#include "SHMSDetectorHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4Allocator<SHMSDetectorHit> SHMSDetectorHitAllocator;

SHMSDetectorHit::SHMSDetectorHit()
  : G4VHit()
{
  worldPos = G4ThreeVector(0,0,0);
  localPos = G4ThreeVector(0,0,0);

  kineE=0;
  kineE0=0;
  eDep=0;
  particleFlag=0;

  creatorProcess = "";
}

SHMSDetectorHit::~SHMSDetectorHit() {}


void SHMSDetectorHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
  {
    G4Circle circle(worldPos);
    circle.SetScreenSize(2.);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,0.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}

void SHMSDetectorHit::Print()
{
  G4cout << "  particleFlag: " << particleFlag 
	 << "  created by " <<creatorProcess << " hit detector at \n(xy,z) cm "
	 << localPos.x()/cm << ", " << localPos.y()/cm << ", " << localPos.z()/cm 
	 << " with energy E = "<<kineE/GeV << "GeV and deposited a total energy of "
	 << eDep/MeV << " MeV " 
	 << G4endl;
}
