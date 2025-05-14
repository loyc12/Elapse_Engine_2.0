#include <raylib.h>
#include "../../../incs/engine.hpp"

// ================================ CAMERA METHODS

fixed_t ScreenMngr::getZmdWidth()  const { return _screenMngr.x / _camera.zoom; } // returns the width of the camera view in world units
fixed_t ScreenMngr::getZmdHeight() const { return _screenMngr.y / _camera.zoom; } // returns the height of the camera view in world units

vec2_t ScreenMngr::getSize()     const { return _screenMngr; }
vec2_t ScreenMngr::getCenter()   const { return _camera.target; }
vec2_t ScreenMngr::getOrigin()   const { return GetScreenToWorld2D({ 0, 0 }, _camera ); } // returns the origin of the camera view in world units

vec2_t ScreenMngr::getTopLeft()  const { return GetScreenToWorld2D({ 0,             0 },              _camera ); }
vec2_t ScreenMngr::getTopRight() const { return GetScreenToWorld2D({ getZmdWidth(), 0 },              _camera ); }
vec2_t ScreenMngr::getBotLeft()  const { return GetScreenToWorld2D({ 0,             getZmdHeight() }, _camera ); }
vec2_t ScreenMngr::getBotRight() const { return GetScreenToWorld2D({ getZmdWidth(), getZmdHeight() }, _camera ); }

vec2_t ScreenMngr::getTop()   const { return GetScreenToWorld2D({ _camera.target.x, 0 },                _camera ); }
vec2_t ScreenMngr::getBot()   const { return GetScreenToWorld2D({ _camera.target.x, getZmdHeight()   }, _camera ); }
vec2_t ScreenMngr::getLeft()  const { return GetScreenToWorld2D({ 0,                _camera.target.y }, _camera ); }
vec2_t ScreenMngr::getRight() const { return GetScreenToWorld2D({ getZmdWidth(),    _camera.target.y }, _camera ); }