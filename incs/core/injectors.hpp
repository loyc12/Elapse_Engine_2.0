#ifndef INJECTORS_HPP
# define INJECTORS_HPP

#include "../base.hpp"

/*
These functions are called by the engine at specific points in the game loop
They are used to inject game specific code into the engine without haviong to modify it yourself
This mean you can define them in your game code to add your custom game logic
They can be left undefined if you don't need them, in which case the engine will simply skip them
*/

// ==================== ENGINE STATE INJECTION FUNCTIONS
// for when the engine changes state
	void OnEngineStart()  __attribute__(( weak ));
	void OnEngineResume() __attribute__(( weak ));

	void OnEnginePause()  __attribute__(( weak ));
	void OnEngineStop()   __attribute__(( weak ));

// ==================== ENGINE STEP INJECTION FUNCTIONS
// for when the engine calls one of the step method
	void OnStartLoop()    __attribute__(( weak ));
	void OnStartStep()    __attribute__(( weak ));

	void OnReadInputs()   __attribute__(( weak ));

	void OnEndStep()      __attribute__(( weak ));
	void OnEndLoop()      __attribute__(( weak ));

// ==================== RENDER INJECTION FUNCTIONS
	void OnRenderStart()  __attribute__(( weak ));
	void OnRenderWorld()  __attribute__(( weak ));
	void OnRenderEnd()    __attribute__(( weak ));


#endif // INJECTORS_HPP