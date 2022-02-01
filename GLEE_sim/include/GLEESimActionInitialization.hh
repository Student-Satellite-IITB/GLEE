
#ifndef GLEESIMACTIONINITIALIZATION_H
#define GLEESIMACTIONINITIALIZATION_H

#include "G4VUserActionInitialization.hh"

class GLEESimPrimaryGeneratorAction;

class GLEESimActionInitialization: public G4VUserActionInitialization
{
	public:

		GLEESimActionInitialization();
		virtual ~GLEESimActionInitialization();

		virtual void Build() const;

};
#endif