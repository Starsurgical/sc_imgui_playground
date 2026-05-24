#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_mixer/SDL_mixer.h>

#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>

#include "test.h"
#include "theme.h"

SDL_Window* g_mainwindow = nullptr;
static SDL_Renderer* g_renderer = nullptr;
static MIX_Mixer* g_mixer = nullptr;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
    return SDL_APP_FAILURE;
  }

  if (!MIX_Init()) {
    return SDL_APP_FAILURE;
  }

  if (!SDL_CreateWindowAndRenderer("Hello ImGui", 2560, 1440, SDL_WINDOW_RESIZABLE, &g_mainwindow, &g_renderer)) {
    return SDL_APP_FAILURE;
  }
  
  g_mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
  if (!g_mixer) return SDL_APP_FAILURE;

  SDL_SetRenderVSync(g_renderer, 1);

  ImGui::CreateContext();
  InitThemesGlobal();

  ImGui_ImplSDL3_InitForSDLRenderer(g_mainwindow, g_renderer);
  ImGui_ImplSDLRenderer3_Init(g_renderer);
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  ImGui_ImplSDLRenderer3_NewFrame();
  ImGui_ImplSDL3_NewFrame();
  ImGui::NewFrame();

  GluesTheme();
  ImGui::Begin("Glues");
  RenderGluesTest();
  ImGui::End();

  GameTheme();
  ImGui::Begin("Game");
  RenderGameTest();
  ImGui::End();

  ImGui::Render();
  SDL_SetRenderDrawColor(g_renderer, 30, 30, 30, 255);
  SDL_RenderClear(g_renderer);
  ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), g_renderer);
  SDL_RenderPresent(g_renderer);

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  ImGui_ImplSDL3_ProcessEvent(event);
  if (event->type == SDL_EVENT_QUIT) return SDL_APP_SUCCESS;
  if (event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_ESCAPE) return SDL_APP_SUCCESS;
  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  ImGui_ImplSDLRenderer3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  ImGui::DestroyContext();
  SDL_DestroyRenderer(g_renderer);
  SDL_DestroyWindow(g_mainwindow);
  MIX_Quit();
  SDL_Quit();
}
