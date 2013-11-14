//******************************************************************
/*
Date - 10/11/2013
Author - B.Waidyawansa

SHMSDetectorConstruction class

SHMS detector construction class loading the geometry from GDML files.

*/
//******************************************************************

#ifndef SHMSDetectorConstruction_H
#define SHMSDetectorConstruction_H 1

#include "G4VUserDetectorConstruction.hh"
#include "G4GDMLParser.hh"
#include "globals.hh"


#include "SHMSMagTabulatedField3D.hh"
#include "MagnetCoilsSD.hh"

class G4SDManager;
class G4LogicalVolume;
class G4VSensitiveDetector;
class G4Material;

class SHMSDetectorConstruction : public G4VUserDetectorConstruction
{

public:

  SHMSDetectorConstruction(G4String fGDMLFile);
  ~SHMSDetectorConstruction();

  // static access method
  static SHMSDetectorConstruction* Instance();


  G4VPhysicalVolume* Construct();
  inline G4String GetGeomFile() const { return fGeomFile; };
  const std::vector<G4String> GetDetNames() const { return detNames; };

  // Magnetic field
  G4MagneticField* SHMSMagField;


private:
  static SHMSDetectorConstruction*  fgInstance;  

  // Make List of materials
  //
  void DefineMaterials();
  
  // Materials used
  //
  G4Material* fVacuum;
  G4Material* fSSteel;
  
  // GDML Reading and Writing Settings
  //
  G4String fGeomFile;

  // GDMLparser
  //
  G4GDMLParser fGDMLParser;

  // Physical volumes
  //
  G4VPhysicalVolume* fWorldPhysVol;

  // Sensitive Detector Manager
  //
  G4SDManager*  SDman;    
  // Array for ensitive detectors
  //
  std::vector<G4String> detNames;


};

#endif
