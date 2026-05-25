#pragma once

void Text(const char* text);
void Slider(const char* label, int* v, int v_min, int v_max);
bool SCRadioButton(const char* label, bool active);
bool SCRadioButton(const char* label, int* v, int v_button);
bool SCCheckbox(const char* label, bool* v);
void SCCombo(const char* label, int* current_item, const char* const items[], int items_count);
