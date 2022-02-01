
#ifndef GLEESIMPHYSICSLIST_H
#define GLEESIMPHYSICSLIST_H

#include "G4VModularPhysicsList.hh"

class G4VPhysicsConstructor;

class GLEESimPhysicsList: public G4VModularPhysicsList
{
	public:

		GLEESimPhysicsList();
		virtual ~GLEESimPhysicsList();

		virtual void ConstructParticle();
		virtual void ConstructProcess();

	private:
		G4VPhysicsConstructor* fGLEESimPhysicsList;  // Define the physics constructor globally

};
#endif