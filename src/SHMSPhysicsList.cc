//******************************************************************
/*
Date - 10/14/2013
Author - B.Waidyawansa

SHMSPhysicsList class implementation



*/
//******************************************************************



#include "SHMSPhysicsList.hh"

#include "G4SystemOfUnits.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleWithCuts.hh"
#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
#include "G4Material.hh"
#include "G4UnitsTable.hh"
#include "G4ios.hh"              


SHMSPhysicsList::SHMSPhysicsList():  G4VUserPhysicsList()
{
  SetCuts();
  defaultCutValue = 1*micrometer;
//   cutForGamma     = defaultCutValue;
//   cutForElectron  = defaultCutValue;
//   cutForPositron  = defaultCutValue;
//   cutForProton    = defaultCutValue;
  
  SetVerboseLevel(1);
}


SHMSPhysicsList::~SHMSPhysicsList()
{}


void SHMSPhysicsList::ConstructParticle()
{
  // In this method, static member functions should be called
  // for all particles which you want to use.
  // This ensures that objects of these particle types will be
  // created in the program. 

  ConstructBosons();
  ConstructLeptons();
  ConstructBarions();
}


void SHMSPhysicsList::ConstructBosons()
{ 

  // gamma
  G4Gamma::GammaDefinition();

  // optical photon
  G4OpticalPhoton::OpticalPhotonDefinition();
}

void SHMSPhysicsList::ConstructLeptons()
{
  // leptons
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
}


void SHMSPhysicsList::ConstructBarions()
{
  //  barions
  G4Proton::ProtonDefinition();
  G4AntiProton::AntiProtonDefinition();
}


void SHMSPhysicsList::ConstructProcess()
{
  AddTransportation();
  ConstructEM();
  ConstructGeneral();
}


#include "G4eMultipleScattering.hh"            
#include "G4hMultipleScattering.hh"            
// Bosons
#include "G4PhotoElectricEffect.hh"                  
#include "G4ComptonScattering.hh"              
#include "G4GammaConversion.hh"                
// Leptons
#include "G4eIonisation.hh"                   
#include "G4eBremsstrahlung.hh"                
#include "G4eplusAnnihilation.hh"             


void SHMSPhysicsList::ConstructEM()
{
  theParticleIterator->reset();
  while( (*theParticleIterator)() )
    {
      G4ParticleDefinition* particle = theParticleIterator->value();
      G4ProcessManager* pmanager = particle->GetProcessManager();
      G4String particleName = particle->GetParticleName();
      
      
      if (particleName == "gamma") {
	//gamma
	pmanager->AddDiscreteProcess(new G4GammaConversion);
	pmanager->AddDiscreteProcess(new G4ComptonScattering);
	pmanager->AddDiscreteProcess(new G4PhotoElectricEffect);
	
      } else if (particleName == "e-") {
	//electron
	pmanager->AddProcess(new G4eBremsstrahlung,    -1,-1,3);      
	pmanager->AddProcess(new G4eIonisation,        -1, 2,2);
	pmanager->AddProcess(new G4eMultipleScattering, -1, 1,1);      
	
      } else if (particleName == "e+") {
	//positron      
	pmanager->AddProcess(new G4eBremsstrahlung,    -1,-1,3);      
	pmanager->AddProcess(new G4eIonisation,        -1, 2,2);
	pmanager->AddProcess(new G4eMultipleScattering, -1, 1,1);      
	pmanager->AddProcess(new G4eplusAnnihilation,   0,-1,4);      
      }
    }
}


void SHMSPhysicsList::ConstructGeneral()
{ }


void SHMSPhysicsList::SetCuts()
{
  if (verboseLevel >0){
    G4cout << "SHMSPhysicsList::SetCuts:";
    G4cout << "\nCutLength : " << G4BestUnit(defaultCutValue,"Length") << G4endl;
  }  
  
  SetCutsWithDefault(); 
  
//   // set cut values for gamma at first and for e- second and next for e+,
//   // because some processes for e+/e- need cut values for gamma 
//   SetCutValue(cutForGamma, "gamma");
//   SetCutValue(cutForElectron, "e-");
//   SetCutValue(cutForPositron, "e+");
  
  
  if (verboseLevel>0) DumpCutValuesTable();
}


void SHMSPhysicsList::SetGammaLowLimit(G4double lowcut)
{
  if (verboseLevel >0){
    G4cout << "SHMSPhysicsList::SetCuts:";
    G4cout << "Gamma cut in energy: " << lowcut*MeV << " (MeV)" << G4endl;
  }  

  // G4Gamma::SetEnergyRange(lowcut,1e5); 
  SetGELowLimit(lowcut);
}


void SHMSPhysicsList::SetElectronLowLimit(G4double lowcut)
{
  if (verboseLevel >0){
    
    G4cout << "SHMSPhysicsList::SetCuts:";
    G4cout << "Electron cut in energy: " << lowcut*MeV << " (MeV)" << G4endl;
  }  

  // G4Electron::SetEnergyRange(lowcut,1e5);
  SetGELowLimit(lowcut);
}


void SHMSPhysicsList::SetPositronLowLimit(G4double lowcut)
{
  if (verboseLevel >0){
    
    G4cout << "SHMSPhysicsList::SetCuts:";
    G4cout << "Positron cut in energy: " << lowcut*MeV << " (MeV)" << G4endl;
  }  

  G4cerr << "SHMSPhysicsList::SetPositronLowLimit: Not currently able to set Positron LowLimit." << G4endl;
  G4Exception("SHMSPhysicsList::SetPositronLowLimit()","PurMag001",
	      FatalException,"Positron Low Limit: not implemented in SHMSPhysicsList"); 
  //
  // G4Positron::SetEnergyRange(lowcut,1e5);
}


void SHMSPhysicsList::SetProtonLowLimit(G4double lowcut)
{
  if (verboseLevel >0){
    
    G4cout << "SHMSPhysicsList::SetCuts:";
    G4cout << "Proton cut in energy: " << lowcut*MeV << " (MeV)" << G4endl;  
  }  

  G4cerr << "SHMSPhysicsList::SetProtonLowLimit: Not currently able to set Proton LowLimit." << G4endl;
  G4Exception("SHMSPhysicsList::SetProtonLowLimit()","PurMag002",
	      FatalException,"Proton Low Limit: not implemented in SHMSPhysicsList"); 
  //
  // G4Proton::SetEnergyRange(lowcut,1e5);
  // G4AntiProton::SetEnergyRange(lowcut,1e5);
}


void SHMSPhysicsList::SetGEPLowLimit(G4double lowcut)
{
  if (verboseLevel >0){
    G4cout << "SHMSPhysicsList::SetGEPLowLimit:";
    G4cout << "Gamma and Electron cut in energy: " << lowcut*MeV << " (MeV)" << G4endl;
  }  

  // G4Gamma::SetEnergyRange(lowcut,1e5);
  // G4Electron::SetEnergyRange(lowcut,1e5);
  // G4Positron::SetEnergyRange(lowcut,1e5);
  this->SetGELowLimit(lowcut); 

  G4cerr << " SetGEPLowLimit : Uncertain whether setting Positron low limit " << G4endl;
}

void SHMSPhysicsList::SetGELowLimit(G4double lowcut)
{
  if (verboseLevel >0){
    G4cout << "SHMSPhysicsList::SetGELowLimit:";
    G4cout << "Gamma and Electron cut in energy: " << lowcut*MeV << " (MeV)" << G4endl;
  }  
 
  G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(lowcut,1e5);
}
void SHMSPhysicsList::SetGammaCut(G4double val)
{
  ResetCuts();
  cutForGamma = val;
}


void SHMSPhysicsList::SetElectronCut(G4double val)
{
  //  ResetCuts();
  cutForElectron = val;
}


void SHMSPhysicsList::SetPositronCut(G4double val)
{
  //  ResetCuts();
  cutForPositron = val;
}


void SHMSPhysicsList::SetProtonCut(G4double val)
{
  //ResetCuts();
  cutForProton = val;
}

// void SHMSPhysicsList::SetCuts()
// {
//   //   the G4VUserPhysicsList::SetCutsWithDefault() method sets 
//   //   the default cut value for all particle types 
//   SetCutsWithDefault();   
// }





