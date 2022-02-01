
#ifndef GLEESIMPRIMARYGENERATORACTION_H
#define GLEESIMPRIMARYGENERATORACTION_H

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"

class G4GeneralParticleSource;

class GLEESimPrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction
{
	public:

		GLEESimPrimaryGeneratorAction();
		virtual ~GLEESimPrimaryGeneratorAction();

		virtual void GeneratePrimaries(G4Event*);

	public:
		G4GeneralParticleSource* fgps;

};
#endif