
#include "GLEESimPhysicsList.hh"

#include "G4EmLivermorePolarizedPhysics.hh"

GLEESimPhysicsList::GLEESimPhysicsList()
    : G4VModularPhysicsList(), fGLEESimPhysicsList(0)
{
    // Register a new physic list to the physics constructor
	fGLEESimPhysicsList = new G4EmLivermorePolarizedPhysics();
    RegisterPhysics(fGLEESimPhysicsList);
}

//***********************************************/

GLEESimPhysicsList::~GLEESimPhysicsList()
{
	delete fGLEESimPhysicsList;
}

//***********************************************/

void GLEESimPhysicsList::ConstructParticle()
{
	fGLEESimPhysicsList->ConstructParticle();
}

//***********************************************/

void GLEESimPhysicsList::ConstructProcess()
{
    AddTransportation();
    fGLEESimPhysicsList->ConstructProcess();
}

//***********************************************/