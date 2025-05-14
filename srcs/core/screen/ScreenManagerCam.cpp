#include <raylib.h>
#include "../../../incs/engine.hpp"

// ================================ CAMERA METHODS

fixed_t ScreenManager::getZmdWidth()  const { return _windowSize.x / _camera.zoom; } // returns the width of the camera view in world units
fixed_t ScreenManager::getZmdHeight() const { return _windowSize.y / _camera.zoom; } // returns the height of the camera view in world units

vec2_t ScreenManager::getSize()     const { return _windowSize; }
vec2_t ScreenManager::getCenter()   const { return _camera.target; }
vec2_t ScreenManager::getOrigin()   const { return GetScreenToWorld2D({ 0, 0 }, _camera ); } // returns the origin of the camera view in world units

vec2_t ScreenManager::getTopLeft()  const { return GetScreenToWorld2D({ 0,             0 },              _camera ); }
vec2_t ScreenManager::getTopRight() const { return GetScreenToWorld2D({ getZmdWidth(), 0 },              _camera ); }
vec2_t ScreenManager::getBotLeft()  const { return GetScreenToWorld2D({ 0,             getZmdHeight() }, _camera ); }
vec2_t ScreenManager::getBotRight() const { return GetScreenToWorld2D({ getZmdWidth(), getZmdHeight() }, _camera ); }

vec2_t ScreenManager::getTop()   const { return GetScreenToWorld2D({ _camera.target.x, 0 },                _camera ); }
vec2_t ScreenManager::getBot()   const { return GetScreenToWorld2D({ _camera.target.x, getZmdHeight()   }, _camera ); }
vec2_t ScreenManager::getLeft()  const { return GetScreenToWorld2D({ 0,                _camera.target.y }, _camera ); }
vec2_t ScreenManager::getRight() const { return GetScreenToWorld2D({ getZmdWidth(),    _camera.target.y }, _camera ); }