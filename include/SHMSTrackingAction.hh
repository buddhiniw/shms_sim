//******************************************************************
/*
Date - 10/11/2013
Author - B.Waidyawansa

SHMSRunAction class

It accumulates statistic and computes dispersion of the energy deposit 
of charged particles with use of analysis tools:
H1D histograms are created in BeginOfRunAction() for the following 
physics quantities:
- Edep in coils
The same values are also saved in the ntuple.
The histograms and ntuple are saved in the output file in root format

In EndOfRunAction(), the accumulated statistic and computed 
dispersion is printed.

*/
//******************************************************************

#ifndef SHMSTrackingAction_h
#define SHMSTrackingAction_h 1


#include "G4UserTrackingAction.hh"
#include <map>

class G4Region;
class G4ParticleDefinition;
class SHMSDetectorConstruction;

class SHMSTrackingAction : public G4UserTrackingAction
{
public:
  SHMSTrackingAction();
  ~SHMSTrackingAction();

//   virtual void PreUserTrackingAction(const G4Track*);
  
//   void SetDetector(SHMSDetectorConstruction* detector)
//   {
//     fDetector = detector;
//   }
  
//   std::map<const G4ParticleDefinition*, int>& GetNParticlesCreatedInWorld()
//   {
//     return fNParticleInWorld;
//   }
  
private:
//   SHMSDetectorConstruction* fDetector;
//   std::map<const G4ParticleDefinition*, int> fNParticleInWorld;
};

#endif
