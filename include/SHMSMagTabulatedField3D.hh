//******************************************************************
/*
Date - 10/14/2013
Author - B.Waidyawansa

SHMSMagTabulatedField3D class

A class to parse the TOSCA field files and load them into GEANT.
Based on the PurgingMagnet example.
*/
//******************************************************************

#ifndef SHMSMagTabulatedField3D_H
#define SHMSMagTabulatedField3D_H 1

#include "globals.hh"
#include "G4MagneticField.hh"
#include "G4ios.hh"
#include "G4RotationMatrix.hh"

#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

class SHMSMagTabulatedField3D
#ifndef STANDALONE
 : public G4MagneticField
#endif
{
  
  // Storage space for the table
  vector< vector< vector< double > > > xField;
  vector< vector< vector< double > > > yField;
  vector< vector< vector< double > > > zField;
  // The dimensions of the table
  int nx,ny,nz; 
  // The physical limits of the defined region
  double minx, maxx, miny, maxy, minz, maxz;
  // The physical extent of the defined region
  double dx, dy, dz;
  double fZoffset;
  bool invertX, invertY, invertZ;

public:
  SHMSMagTabulatedField3D(const char* filename);
  void  GetFieldValue( const  double Point[4],
		       double *Bfield          ) const;
};

#endif
