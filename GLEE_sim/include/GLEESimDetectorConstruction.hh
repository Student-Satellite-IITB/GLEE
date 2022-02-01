
#ifndef GLEESIMDETECTORCONSTRUCTION_H
#define GLEESIMDETECTORCONSTRUCTION_H

#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;

class GLEESimDetectorConstruction: public G4VUserDetectorConstruction  
{
	public:

		GLEESimDetectorConstruction();
		virtual ~GLEESimDetectorConstruction();

		virtual G4VPhysicalVolume* Construct();

};
#endif