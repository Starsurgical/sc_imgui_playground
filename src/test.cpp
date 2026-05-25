#include <imgui.h>

#include "controls.h"

#include <iterator>

const char* gametypes[] = { "Melee", "Free for All", "One on One", "Use Map Settings", "Capture the Flag" };
int gametype_selected = 0;
const char* gamespeeds[] = { "Slowest", "Slower", "Slow", "Normal", "Fast", "Faster", "Fastest" };
int gamespeed_selected = 6;

void RenderGluesTest() {
  static int oneoff = (ImGui::SetNavCursorVisible(false), 1);
  ImGui::BeginTable("", 2);
  ImGui::TableNextRow();
  {
    ImGui::TableSetColumnIndex(0);
    Text("Game Type");
    
    ImGui::TableSetColumnIndex(1);
    SCCombo("##gametype", &gametype_selected, gametypes, std::size(gametypes));
  }

  ImGui::TableNextRow();
  {
    ImGui::TableSetColumnIndex(0);
    Text("");

    ImGui::TableSetColumnIndex(1);
  }

  ImGui::TableNextRow();
  {
    ImGui::TableSetColumnIndex(0);
    Text("Speed:");
    ImGui::SameLine();
    float align = ImGui::GetCursorPosX() + ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize(gamespeeds[gamespeed_selected]).x;
    ImGui::SetCursorPosX(align);
    Text(gamespeeds[gamespeed_selected]);

    ImGui::TableSetColumnIndex(1);
    ImGui::PushFont(nullptr, ImGui::GetStyle().FontSizeBase * 0.9f);
    Text("-");
    ImGui::SameLine();
    Slider("##gamespeed", &gamespeed_selected, 0, std::size(gamespeeds) - 1);
    ImGui::SameLine();
    Text("+");
    ImGui::PopFont();
  }
  ImGui::EndTable();
}

int gamma = 50;
bool color_cycling = true;
int portraits = 0;

void RenderGameTest() {
  static int oneoff = (ImGui::SetNavCursorVisible(false), 1);
  // title
  ImGui::PushFont(nullptr, ImGui::GetStyle().FontSizeBase * 1.5f);
  float x = (ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize("Video Options").x) / 2;
  ImGui::SetCursorPosX(x);
  Text("Video Options");
  ImGui::PopFont();

  Text("Gamma Correction");
  Slider("##gamma", &gamma, 0, 255);

  ImGui::Dummy(ImVec2(0, 16));
  SCCheckbox("Enable Color Cycling", &color_cycling);
  ImGui::Dummy(ImVec2(0, 22));

  ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(220, 220, 60, 255));
  SCRadioButton("Animating unit portraits", &portraits, 0);
  SCRadioButton("Still unit portraits", &portraits, 1);
  SCRadioButton("Disable unit portraits", &portraits, 2);
  ImGui::PopStyleColor();
}
