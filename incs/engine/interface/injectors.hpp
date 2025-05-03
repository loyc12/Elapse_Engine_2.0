#ifndef INJECTORS_HPP
# define INJECTORS_HPP

#include "../../base.hpp"

/*
these functions are called by the engine at an appropriate time during their respective function calls
they are used to inject game specific code into the engine without modifying the engine itself
*/

// ==================== ENGINE STATE INJECTION FUNCTIONS
// for when the engine changes state
	void OnEngineInit();
		void OnEngineStart();
			void OnEngineResume();

			void OnEnginePause();
		void OnEngineStop();
	void OnEngineClose();

// ==================== ENGINE STEP INJECTION FUNCTIONS
// for when the engine calls one of the step method
	void OnStartLoop();
		void OnStartStep();

			void OnReadInputs(); // NOTE : is this archaic ?

			void OnTickScripts();
			void OnTickPhysics();
			void OnTickCollides();
			void OnTickMovements();
			void OnTickVisuals();

			void OnRenderBackground();
			void OnRenderWorld();
			void OnRenderUI();

		void OnEndStep();
	void OnEndLoop();

// ===================== ENTITY TICK INJECTION FUNCTIONS
// for when the CompManager calls an entity's component tick methods
	class Entity;

	void OnEntityTickScript(   Entity *Ntt );
	void OnEntityTickPhysic(   Entity *Ntt );
	void OnEntityTickCollide(  Entity *Ntt );
	void OnEntityTickMovement( Entity *Ntt );
	void OnEntityTickVisual(   Entity *Ntt );

#endif // INJECTORS_HPP