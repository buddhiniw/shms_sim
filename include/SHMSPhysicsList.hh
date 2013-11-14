//******************************************************************
/*
Date - 10/14/2013
Author - B.Waidyawansa

SHMSPhysicsList class to generate the physics events relevent to
this simulation



*/
//******************************************************************

#ifndef SHMSPhysicsList_h
#define SHMSPhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"


class G4GammaConversion;     
class G4ComptonScattering;   
class G4PhotoElectricEffect;       

class G4eIonisation;          
class G4eBremsstrahlung;     


class SHMSPhysicsList: public G4VUserPhysicsList
{
public:
  SHMSPhysicsList();
  ~SHMSPhysicsList();
  
protected:
  // Construct particle and physics
  void ConstructParticle();
  void ConstructProcess();
  
  void SetCuts();
  
public: 
  // Set Cuts
  void SetGammaCut(G4double);
  void SetElectronCut(G4double);
  void SetPositronCut(G4double);
  void SetProtonCut(G4double);
  
  void SetGammaLowLimit(G4double);
  void SetElectronLowLimit(G4double);
  void SetPositronLowLimit(G4double);
  void SetProtonLowLimit(G4double);
  void SetGEPLowLimit(G4double);

  void SetGELowLimit(G4double);
  
private:
  
  G4double cutForGamma;
  G4double cutForElectron;
  G4double cutForPositron;
  G4double cutForProton;
  
protected:
  // these methods Construct particles 
  void ConstructBosons();
  void ConstructLeptons();
  void ConstructBarions();
  
protected:
  // these methods Construct physics processes and register them
  void ConstructGeneral();
  void ConstructEM();
  
private:
  
};
#endif



