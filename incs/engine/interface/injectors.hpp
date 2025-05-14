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

			struct inputs_s;
			void OnReadInputs( inputs_s &inp, inputs_s &prev );

			void OnTickMovements();
			void OnTickPhysics();
			void OnTickCollides();

			void OnTickSounds();
			void OnTickShapes();
			void OnTickGraphics();

			void OnTickScripts();

			void OnRenderBackground();
			void OnRenderWorld();
			void OnRenderUI();

		void OnEndStep();
	void OnEndLoop();

// ===================== ENTITY TICK INJECTION FUNCTIONS
// for when the EntityManager calls an entity's component tick methods
	class Entity;

	void OnEntityTickMovement( Entity *Ntt ); // TODO : implement and use us
	void OnEntityTickPhysic(   Entity *Ntt );
	void OnEntityTickCollide(  Entity *Ntt );

	void OnEntityTickSound(   Entity *Ntt );
	void OnEntityTickShape(   Entity *Ntt );
	void OnEntityTickGraphic( Entity *Ntt );

	void OnEntityTickScript( Entity *Ntt );

#endif // INJECTORS_HPP