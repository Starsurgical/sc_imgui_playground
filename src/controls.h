#pragma once

void Text(const char* text);
void Combo(const char* label, int* current_item, const char* const items[], int items_count);
void Slider(const char* label, int* v, int v_min, int v_max);
void RadioButton(const char* label, int* v, int v_button);
bool SCRadioButton(const char* label, bool active);
bool SCRadioButton(const char* label, int* v, int v_button);
bool SCCheckbox(const char* label, bool* v);
