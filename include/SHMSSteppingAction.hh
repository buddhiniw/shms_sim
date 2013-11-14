//******************************************************************
/*
Date - 10/23/2013
Author - B.Waidyawansa

SHMSSteppingAction class



*/
//******************************************************************

#ifndef SHMSSteppingAction_h
#define SHMSSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "G4LogicalVolume.hh"

#include <vector>

class SHMSRunAction;
class SHMSDetectorConstruction;
class SHMSPrimaryGeneratorAction;
class SHMSAnalysisManager;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class SHMSSteppingAction : public G4UserSteppingAction
{
public:

  SHMSSteppingAction(SHMSRunAction*, SHMSDetectorConstruction*
		     ,SHMSPrimaryGeneratorAction*,SHMSAnalysisManager*);
  ~SHMSSteppingAction();
  
  // static access method
  static SHMSSteppingAction* Instance();

  void UserSteppingAction(const G4Step*);
  G4double GetEnergy() const {return fEnergy; };
  G4double GetEnergyElectrons() const {return fEnergyElec; };
  G4double GetEnergyPositrons() const {return fEnergyPosi; };
  G4double GetEnergyNeutrons() const {return fEnergyNeut; };
  G4double GetEnergyGamma() const {return fEnergyGamma; };

private:
  static SHMSSteppingAction*  fgInstance;  
  SHMSRunAction*              fRun;
  SHMSDetectorConstruction*   fDetector; 
  SHMSPrimaryGeneratorAction* fPrimary;
  SHMSAnalysisManager* 	      fHisto;
  G4double 	              fEnergy;
  G4double 	              fEnergyElec;
  G4double 	              fEnergyPosi;
  G4double 	              fEnergyGamma;
  G4double 	              fEnergyNeut;

  std::vector<G4LogicalVolume*>   fCoils;

      
};
#endif

