#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
//#include <imgui_internal.h>

#include <algorithm>
#include <limits>

void Text(const char* text) {
  ImGui::TextUnformatted(text);
}

void Combo(const char* label, int* current_item, const char* const items[], int items_count) {
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(4,6));
  ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(76, 196, 40, 255));
  ImGui::Combo(label, current_item, items, items_count);
  ImGui::PopStyleColor();
  ImGui::PopStyleVar();
}

void Slider(const char* label, int* v, int v_min, int v_max) {
  ImGui::PushStyleVar(ImGuiStyleVar_FramePadding,    ImVec2(4, 4));
  ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding,   8.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize,     8.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding,    16.0f);

  ImGui::PushFont(NULL, std::numeric_limits<float>::min());
  ImGui::SliderInt(label, v, v_min, v_max, "", ImGuiSliderFlags_NoInput);
  ImGui::PopFont();
  ImGui::PopStyleVar(4);
}

const float OPTION_SIZE = 32.0f;
static void FinishDrawControlText(bool highlighted, ImVec2& textSize, ImVec2& ctrlPos, ImVec2& ctrlSize, const char* label, const char* label_end) {
  if (highlighted) ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32_WHITE);
  ImGui::SetCursorPos(ctrlPos + ImVec2(OPTION_SIZE + ImGui::GetStyle().ItemInnerSpacing.x, (ctrlSize.y - textSize.y) / 2));
  ImGui::TextUnformatted(label, label_end);
  if (highlighted) ImGui::PopStyleColor();

  ImGui::SetCursorPos(ctrlPos + ImVec2(0, ctrlSize.y));
  ImGui::Dummy(ImVec2(0,0));
}

struct CtrlStats {
  bool hovered;
  bool pressed;
  bool active;
  bool held;
};

static CtrlStats InvisButton(const char* label, ImVec2 ctrlSize) {
  ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0);
  ImGui::InvisibleButton(label, ctrlSize, ImGuiButtonFlags_EnableNav);
  ImGui::PopStyleVar();

  CtrlStats result;
  result.active = ImGui::IsItemActive();
  result.hovered = ImGui::IsItemHovered();
  result.pressed = ImGui::IsItemDeactivated() && result.hovered;
  result.held = result.active && result.hovered;
  return result;
}

void SCCombo(const char* label, int* current_item, const char* const items[], int items_count) {
  static ImGuiID stored_id = 0;
  static bool stored_hovered = false;
  static int stored_selection = -1;

  const char* preview = items[0];
  if (*current_item >= 0 || *current_item < items_count) preview = items[*current_item];
  
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(4,6));
  ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(76, 196, 40, 255));

  ImGuiID id = ImGui::GetID(label);
  bool currently_highlighted = stored_id == id && stored_hovered;
  if (currently_highlighted) {
    ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(252, 0, 0, 255));
    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(180, 252, 116, 255));
  }

  bool opened = ImGui::BeginCombo(label, preview, ImGuiComboFlags_NoArrowButton);

  if (currently_highlighted) {
    ImGui::PopStyleColor();
  }

  bool hovered = ImGui::IsItemHovered();
  if (hovered || opened) {
    stored_id = id;
    stored_hovered = true;
  }

  // TODO arrow
  
  bool needs_selection_reset = true;
  if (opened) {
    for (int i = 0; i < items_count; i++) {
      ImGui::PushID(i);

      bool selected = i == *current_item;

      if (stored_selection == i) {
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(180, 252, 116, 255));
      }
      
      if (ImGui::Selectable(items[i], selected)) {
        *current_item = i;
      }

      if (stored_selection == i) {
        ImGui::PopStyleColor();
      }

      if (ImGui::IsItemHovered()) {
        stored_selection = i;
        needs_selection_reset = false;
      }

      if (selected) {
        ImGui::SetItemDefaultFocus();
      }
      ImGui::PopID();
    }
    ImGui::EndCombo();
    if (needs_selection_reset) {
      stored_selection = -1;
    }
  }

  if (currently_highlighted) {
    ImGui::PopStyleColor();
  }

  ImGui::PopStyleColor();
  ImGui::PopStyleVar();
}

bool SCRadioButton(const char* label, bool on) {
  ImVec2 pos = ImGui::GetCursorScreenPos();
  ImVec2 ctrlPos = ImGui::GetCursorPos();
  
  const char* label_end = label + std::strlen(label);
  ImVec2 textSize = ImGui::CalcTextSize(label, label_end);
  float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
  ImVec2 ctrlSize{ OPTION_SIZE + spacing + textSize.x, std::max(textSize.y, OPTION_SIZE) };

  CtrlStats sel = InvisButton(label, ctrlSize);
  ImDrawList* dl = ImGui::GetWindowDrawList();

  float radius = OPTION_SIZE / 2;
  ImVec2 center = pos + ImVec2(radius, ctrlSize.y / 2);
  auto borderColor = ImGui::GetColorU32(ImGuiCol_Border);

  float heldFactor = sel.held ? 0.9f : 1.0f;
  dl->AddCircle(center, radius * heldFactor, borderColor);
  if (sel.held) {
    dl->AddCircle(center, radius - 0.5f, IM_COL32_BLACK, 0, 1.5f);
  }
  dl->AddCircleFilled(center, radius * 0.75f, IM_COL32_BLACK);
  dl->AddCircle(center, radius * 0.6f * heldFactor * heldFactor, borderColor);
  if (on) {
    dl->AddCircleFilled(center, radius * 0.4f * heldFactor * heldFactor * heldFactor, ImGui::GetColorU32(ImGuiCol_CheckMark));
  }

  FinishDrawControlText(sel.hovered || sel.active, textSize, ctrlPos, ctrlSize, label, label_end);
  return sel.pressed;
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
  ImVec2 ctrlSize{ OPTION_SIZE + ImGui::GetStyle().ItemInnerSpacing.x + textSize.x, std::max(textSize.y, OPTION_SIZE) };

  CtrlStats sel = InvisButton(label, ctrlSize);
  ImDrawList* dl = ImGui::GetWindowDrawList();

  float radius = OPTION_SIZE / 2;
  ImVec2 center = pos + ImVec2(radius, ctrlSize.y / 2);
  auto borderColor = ImGui::GetColorU32(ImGuiCol_Border);
  if (sel.hovered) {
    borderColor = ImColor(12, 72, 204);
  }

  ImVec2 end = pos + ImVec2(OPTION_SIZE, OPTION_SIZE);

  if (*v) {
    dl->AddRectFilled(pos, end, ImColor(40, 24, 12));
  }
  else {
    dl->AddRectFilled(pos, end, IM_COL32_BLACK);
  }
  dl->AddRect(pos, end, borderColor);
  if (sel.held) {
    dl->AddRect(pos + ImVec2(2, 2), end - ImVec2(2, 2), ImColor(96, 0, 0), 0, 2.0f);
  }
  if (*v) {
    auto hilite = ImColor(72, 48, 24);
    dl->AddLine(pos + ImVec2(2, 2), end - ImVec2(2, 2), hilite, 8.0f);
    dl->AddLine(ImVec2(pos.x + 2, end.y - 2), ImVec2(end.x - 2, pos.y + 2), hilite, 8.0f);
    dl->AddCircleFilled((pos + end) / 2, 8.0, hilite);

    auto checkColor = ImGui::GetColorU32(ImGuiCol_CheckMark);
    dl->AddLine(pos + ImVec2(3, 3), end - ImVec2(3, 3), checkColor, 4.0f);
    dl->AddLine(ImVec2(pos.x + 3, end.y - 3), ImVec2(end.x - 3, pos.y + 3), checkColor, 4.0f);
  }

  FinishDrawControlText(sel.hovered || sel.active, textSize, ctrlPos, ctrlSize, label, label_end);
  if (sel.pressed) {
    *v = !*v;
  }
  return sel.pressed;
}
