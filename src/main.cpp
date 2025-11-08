#define SDL_MAIN_USE_CALLBACKS

#include <exception>

#include "core/Game.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_main.h"

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    try {
        Game* game = new Game({
            1280, 720, "Pong Clone"
        });

        game->Initialize();

        *appstate = game;
    }
    catch (std::exception& e) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", e.what());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
    try {
        Game* game = static_cast<Game*>(appstate);
        if (!game->IsRunning()) {
            return SDL_APP_SUCCESS;
        }

        game->Update();
    }
    catch (std::exception& e) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", e.what());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    try {
        Game* game = static_cast<Game*>(appstate);
        game->OnEvent(*event);
    }
    catch (std::exception& e) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", e.what());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    try {
        Game* game = static_cast<Game*>(appstate);
        game->Shutdown();

        delete game;
    }
    catch (std::exception& e) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", e.what());
    }
}
