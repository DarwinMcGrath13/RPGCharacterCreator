// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <string>

SDL_Texture* LoadTexture(std::string path);

SDL_Texture* Graphics::LoadTexture(std::string path) { SDL_Texture* tex = nullptr; return tex; }

[11:02 AM] Dennis Hubley
Uint32 mPrevMouseState;    Uint32 mMouseState; int mMouseXPos; int mMouseYPos;

[11:04 AM] Dennis Hubley
#include "MathHelper.h"

[11:04 AM] Dennis Hubley
bool MouseButtonDown(MouseButton button); bool MouseButtonPressed(MouseButton button); bool MouseButtonReleased(MouseButton button);    Vector2 MousePosition();

[11:05 AM] Dennis Hubley
void Update(); void UpdatePrevInput();

[11:05 AM] Dennis Hubley
private:    InputManager();    ~InputManager();

[11:06 AM] Dennis Hubley
#include "InputManager.h"namespace SDLFramework {    InputManager * InputManager::sInstance = nullptr;    InputManager * InputManager::Instance() {if (sInstance == nullptr) {            sInstance = new InputManager();        }return sInstance;    }void InputManager::Release() {delete sInstance;        sInstance = nullptr;    }}

[11:07 AM] Dennis Hubley
bool InputManager::KeyDown(SDL_Scancode scancode) { return mKeyboardState[scancode]; }

[11:08 AM] Dennis Hubley
bool InputManager::KeyPressed(SDL_Scancode scancode) { return !mPrevKeyboardState[scancode] && mKeyboardState[scancode]; }bool InputManager::KeyReleased(SDL_Scancode scancode) { return mPrevKeyboardState[scancode] && !mKeyboardState[scancode]; }

[11:08 AM] Dennis Hubley
bool InputManager::MouseButtonDown(MouseButton button) { Uint32 mask = 0; switch (button) { case Left:        mask = SDL_BUTTON_LMASK; break; case Right:        mask = SDL_BUTTON_RMASK; break; case Middle:        mask = SDL_BUTTON_MMASK; break; case Back:        mask = SDL_BUTTON_X1MASK; break; case Forward:        mask = SDL_BUTTON_X2MASK; break; }return (mMouseState & mask) != 0; }

[11:10 AM] Dennis Hubley
bool InputManager::MouseButtonPressed(MouseButton button) {
	Uint32 mask = 0;

        switch (button) { case Left:            mask = SDL_BUTTON_LMASK;            break;        case Right:            mask = SDL_BUTTON_RMASK;            break;        case Middle:            mask = SDL_BUTTON_MMASK;            break;        case Back:            mask = SDL_BUTTON_X1MASK;            break;        case Forward:            mask = SDL_BUTTON_X2MASK;            break; }

								   return !(mPrevMouseState & mask) && (mMouseState & mask);
}

bool InputManager::MouseButtonReleased(MouseButton button) {
	Uint32 mask = 0;

        switch (button) { case Left:            mask = SDL_BUTTON_LMASK;            break;        case Right:            mask = SDL_BUTTON_RMASK;            break;        case Middle:            mask = SDL_BUTTON_MMASK;            break;        case Back:            mask = SDL_BUTTON_X1MASK;            break;        case Forward:            mask = SDL_BUTTON_X2MASK;            break; }

								   return (mPrevMouseState & mask) && !(mMouseState & mask);
}

