
#include "GLEESimActionInitialization.hh"  
#include "GLEESimPrimaryGeneratorAction.hh"

GLEESimActionInitialization::GLEESimActionInitialization()
    : G4VUserActionInitialization()
{
}

//***********************************************/

GLEESimActionInitialization::~GLEESimActionInitialization()
{
	
}

//***********************************************/

void GLEESimActionInitialization::Build() const
{
    SetUserAction(new GLEESimPrimaryGeneratorAction());
}