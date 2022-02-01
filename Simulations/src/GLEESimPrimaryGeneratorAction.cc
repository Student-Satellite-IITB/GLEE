
#include "GLEESimPrimaryGeneratorAction.hh"  
	
GLEESimPrimaryGeneratorAction::GLEESimPrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction()
{
    fgps = new G4GeneralParticleSource();
}

//***********************************************/

GLEESimPrimaryGeneratorAction::~GLEESimPrimaryGeneratorAction()
{
	delete fgps;

}
//***********************************************/

void GLEESimPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	fgps->GeneratePrimaryVertex(anEvent);
	
}