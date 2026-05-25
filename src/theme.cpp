#include <SDL3/SDL.h>
#include <imgui.h>

#include <optional>

extern SDL_Window* g_mainwindow;

static ImGuiStyle g_originalStyles;

void InitThemesGlobal() {
  auto& io = ImGui::GetIO();
  io.ConfigDragClickToInputText = false;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigNavCursorVisibleAlways = true;

  auto& style = ImGui::GetStyle();

  // General
  style.PopupBorderSize = 1.0f;
  style.FrameBorderSize = 1.0f;
  style.PopupRounding = 5.0f;
  style.FrameRounding = 5.0f;
  style.ItemSpacing = ImVec2(4, 8);

  // Slider
  style.GrabRounding = 10.0f;
  style.GrabMinSize = 5.0f;
  style.WindowPadding = ImVec2(32.0, 32.0);

  // Complete transparent stuff in SC
  style.Colors[ImGuiCol_WindowBg]           = ImColor(0, 0, 0, 0);
  style.Colors[ImGuiCol_ChildBg]            = ImColor(0, 0, 0, 0);
  style.Colors[ImGuiCol_PopupBg]            = ImColor(0, 0, 0, 0);
  style.Colors[ImGuiCol_ChildBg]            = ImColor(0, 0, 0, 0);
  style.Colors[ImGuiCol_Header]             = ImColor(0, 0, 0, 0);
  style.Colors[ImGuiCol_HeaderHovered]      = ImColor(0, 0, 0, 0);
  style.Colors[ImGuiCol_HeaderActive]       = ImColor(0, 0, 0, 0);
  style.Colors[ImGuiCol_FrameBg]            = ImColor(0, 0, 0, 0);
  style.Colors[ImGuiCol_FrameBgHovered]     = ImColor(0, 0, 0, 0);
  style.Colors[ImGuiCol_FrameBgActive]      = ImColor(0, 0, 0, 0);
  style.Colors[ImGuiCol_Button]             = ImColor(0, 0, 0, 0);
  style.Colors[ImGuiCol_ButtonHovered]      = ImColor(0, 0, 0, 0);
  style.Colors[ImGuiCol_ButtonActive]       = ImColor(0, 0, 0, 0);
  
  g_originalStyles = style;
}

void GluesTheme() {
  float dpi_scale = SDL_GetWindowDisplayScale(g_mainwindow);

  auto& style = ImGui::GetStyle();
  style = g_originalStyles;

  style.Colors[ImGuiCol_WindowBg]           = ImColor(0, 0, 0);
  style.Colors[ImGuiCol_ChildBg]            = ImColor(0, 0, 0);
  style.Colors[ImGuiCol_PopupBg]            = ImColor(0, 0, 0);
  style.Colors[ImGuiCol_Text]               = ImColor(164, 180, 248);
  style.Colors[ImGuiCol_TextDisabled]       = ImColor(88, 88, 88);
  style.Colors[ImGuiCol_Border]             = ImColor(108, 0, 0);
  style.Colors[ImGuiCol_SliderGrab]         = ImColor(252, 252, 76);
  style.Colors[ImGuiCol_SliderGrabActive]   = ImColor(252, 252, 76);
  style.Colors[ImGuiCol_CheckMark]          = ImColor(252, 252, 76);

  style.FontScaleDpi = dpi_scale;
  style.ScaleAllSizes(dpi_scale);
}

void GameTheme() {
  float dpi_scale = SDL_GetWindowDisplayScale(g_mainwindow);

  auto& style = ImGui::GetStyle();
  style = g_originalStyles;

  style.Colors[ImGuiCol_WindowBg]           = ImColor(0, 16, 52, 128);
  style.Colors[ImGuiCol_ChildBg]            = ImColor(0, 16, 52, 128);
  style.Colors[ImGuiCol_PopupBg]            = ImColor(0, 16, 52, 128);
  style.Colors[ImGuiCol_Text]               = ImColor(164, 180, 248);
  style.Colors[ImGuiCol_TextDisabled]       = ImColor(88, 88, 88);
  style.Colors[ImGuiCol_Border]             = ImColor(8, 52, 152);
  style.Colors[ImGuiCol_SliderGrab]         = ImColor(252, 252, 76);
  style.Colors[ImGuiCol_SliderGrabActive]   = ImColor(252, 252, 76);
  style.Colors[ImGuiCol_CheckMark]          = ImColor(252, 252, 76);

  style.FontScaleDpi = dpi_scale;
  style.ScaleAllSizes(dpi_scale);
}
