#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
//#include <imgui_internal.h>

#include <algorithm>
#include <limits>

void Text(const char* text) {
  ImGui::TextUnformatted(text);
}

void Combo(const char* label, int* current_item, const char* const items[], int items_count) {
  ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(76, 196, 40, 255));
  ImGui::Combo(label, current_item, items, items_count);
  ImGui::PopStyleColor();
}

void Slider(const char* label, int* v, int v_min, int v_max) {
  ImGui::PushStyleVar(ImGuiStyleVar_FramePadding,    ImVec2(4, 4));
  ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding,   8.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize,     8.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding,    16.0f);

  ImGui::PushFont(NULL, std::numeric_limits<float>::min());
  ImGui::SliderInt(label, v, v_min, v_max, "");
  ImGui::PopFont();
  ImGui::PopStyleVar(4);
}

void RadioButton(const char* label, int* v, int v_button) {
  ImGui::PushStyleVar(ImGuiStyleVar_FramePadding,    ImVec2(4, 4));
  ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding,   10.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing,     ImVec2(8, 4));

  ImGui::PushStyleColor(ImGuiCol_Text,            IM_COL32(220, 220, 60, 255));
  ImGui::PushStyleColor(ImGuiCol_FrameBg,         IM_COL32(0, 0, 0, 255));   // circle background (unchecked)
  ImGui::PushStyleColor(ImGuiCol_FrameBgHovered,  IM_COL32(0, 0, 0, 255));   // circle background hovered
  ImGui::PushStyleColor(ImGuiCol_FrameBgActive,   IM_COL32(0, 0, 0, 255));   // circle background clicked

  ImGui::RadioButton(label, v, v_button);

  ImGui::PopStyleColor(4);
  ImGui::PopStyleVar(3);
}

const float RADIO_SIZE = 32.0f;
bool SCRadioButton(const char* label, bool active) {
  ImVec2 pos = ImGui::GetCursorScreenPos();
  ImVec2 ctrlPos = ImGui::GetCursorPos();
  
  const char* label_end = label + std::strlen(label);
  ImVec2 textSize = ImGui::CalcTextSize(label, label_end);
  float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
  ImVec2 ctrlSize{ RADIO_SIZE + spacing + textSize.x, std::max(textSize.y, RADIO_SIZE) };

  ImGui::InvisibleButton(label, ctrlSize);

  bool hovered = ImGui::IsItemHovered();
  bool pressed = ImGui::IsItemClicked();
  bool held = ImGui::IsItemActive();
  ImDrawList* dl = ImGui::GetWindowDrawList();

  float radius = RADIO_SIZE / 2;
  ImVec2 center = pos + ImVec2(radius, ctrlSize.y / 2);
  auto borderColor = ImGui::GetColorU32(ImGuiCol_Border);

  float heldFactor = held ? 0.9f : 1.0f;
  dl->AddCircle(center, radius * heldFactor, borderColor);
  dl->AddCircleFilled(center, radius * 0.6f, IM_COL32_BLACK);
  dl->AddCircle(center, radius * 0.6f * heldFactor * heldFactor, borderColor);
  if (active) {
    dl->AddCircleFilled(center, radius * 0.4f * heldFactor * heldFactor * heldFactor, ImGui::GetColorU32(ImGuiCol_CheckMark));
  }

  if (hovered) ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32_WHITE);
  ImGui::SetCursorPos(ctrlPos + ImVec2(RADIO_SIZE + spacing, (ctrlSize.y - textSize.y) / 2));
  ImGui::TextUnformatted(label, label_end);
  if (hovered) ImGui::PopStyleColor();

  ImGui::SetCursorPos(ctrlPos + ImVec2(0, ctrlSize.y));
  return pressed;
}

bool SCRadioButton(const char* label, int* v, int v_button) {
  const bool pressed = SCRadioButton(label, *v == v_button);
  if (pressed) *v = v_button;
  return pressed;
}

bool SCCheckbox(const char* label, bool* v) {
  ImVec2 pos = ImGui::GetCursorScreenPos();
  ImVec2 ctrlPos = ImGui::GetCursorPos();
  
  const char* label_end = label + std::strlen(label);
  ImVec2 textSize = ImGui::CalcTextSize(label, label_end);
  float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
  ImVec2 ctrlSize{ RADIO_SIZE + spacing + textSize.x, std::max(textSize.y, RADIO_SIZE) };

  ImGui::InvisibleButton(label, ctrlSize);

  bool hovered = ImGui::IsItemHovered();
  bool pressed = ImGui::IsItemClicked();
  bool held = ImGui::IsItemActive();
  ImDrawList* dl = ImGui::GetWindowDrawList();

  float radius = RADIO_SIZE / 2;
  ImVec2 center = pos + ImVec2(radius, ctrlSize.y / 2);
  auto borderColor = ImGui::GetColorU32(ImGuiCol_Border);
  if (hovered) {
    borderColor = ImColor(12, 72, 204);
  }

  ImVec2 end = pos + ImVec2(RADIO_SIZE, RADIO_SIZE);

  if (*v) {
    dl->AddRectFilled(pos, end, ImColor(40, 24, 12));
  }
  else {
    dl->AddRectFilled(pos, end, IM_COL32_BLACK);
  }
  dl->AddRect(pos, end, borderColor);
  if (held) {
    dl->AddRect(pos + ImVec2(1, 1), end - ImVec2(1, 1), ImColor(96, 0, 0));
  }
  if (*v) {
    auto hilite = ImColor(72, 48, 24);
    dl->AddLine(pos + ImVec2(2, 2), end - ImVec2(2, 2), hilite, 5.5f);
    dl->AddLine(ImVec2(pos.x + 2, end.y - 2), ImVec2(end.x - 2, pos.y + 2), hilite, 5.5f);

    auto checkColor = ImGui::GetColorU32(ImGuiCol_CheckMark);
    dl->AddLine(pos + ImVec2(3, 3), end - ImVec2(3, 3), checkColor, 4.0f);
    dl->AddLine(ImVec2(pos.x + 3, end.y - 3), ImVec2(end.x - 3, pos.y + 3), checkColor, 4.0f);
  }

  if (hovered) ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32_WHITE);
  ImGui::SetCursorPos(ctrlPos + ImVec2(RADIO_SIZE + spacing, (ctrlSize.y - textSize.y) / 2));
  ImGui::TextUnformatted(label, label_end);
  if (hovered) ImGui::PopStyleColor();

  ImGui::SetCursorPos(ctrlPos + ImVec2(0, ctrlSize.y));
  if (pressed) {
    *v = !*v;
  }
  return pressed;
}
