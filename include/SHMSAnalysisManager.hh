//******************************************************************
/*
Date - 10/23/2013
Author - B.Waidyawansa

SHMSAnalysisManager class


*/
//******************************************************************

#ifndef SHMSAnalysisManager_h
#define SHMSAnalysisManager_h 1


#include "TROOT.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TDirectory.h"

#include "g4root.hh"
#include "globals.hh"
#include "G4LogicalVolume.hh"

#include "SHMSDetectorConstruction.hh"
#include "SHMSDetectorHit.hh"


class SHMSAnalysisManager
{

public:
  
  SHMSAnalysisManager(SHMSDetectorConstruction*);
  ~SHMSAnalysisManager();
  
  // static access method
  static SHMSAnalysisManager* Instance();

  inline G4int GetNoSDDetectors() const { return nDet; };

  void Clear();
  void SetFileName   (const G4String& name) { fileName = name;};
  void OpenROOTFile();
  void SaveROOTFile();
  void FillNtuple(SHMSDetectorHit *aHit,G4String ntuple_name);


private:
  static SHMSAnalysisManager*  fgInstance;  
  SHMSDetectorConstruction*   fDetector; 

  TFile *theTFile;
  std::vector<TNtuple*> Ntuples;
  G4int nDet;

  G4double kinE0,kinE;
  G4String         fileName;
  G4bool           factoryOn;       
  std::vector<G4String>   detNames;
 
};

#endif
