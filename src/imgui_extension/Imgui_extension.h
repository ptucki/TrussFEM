#ifndef MY_IMGUI_EXTENSION_H
#define MY_IMGUI_EXTENSION_H
#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"

namespace ImGuiEX
{

  bool InputText(
    const char* label,
    std::string* str,
    const std::string& placeholder,
    bool* input_text_state,
    ImGuiInputTextFlags flags = 0,
    ImGuiInputTextCallback callback = nullptr,
    void* user_data = nullptr);

}

#endif // !MY_IMGUI_EXTENSION_H
