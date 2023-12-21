#include "imgui_extension.h"

namespace ImGuiEX
{
  bool InputText(const char* label, std::string* str, const std::string& placeholder, bool* input_text_state, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
  {
    struct DataPack
    {
      bool* clear;
      void* user_data;
      ImGuiInputTextCallback callback;
    };

    callback = callback == nullptr ? [](ImGuiInputTextCallbackData* data) -> int { return 0; } : callback;
    DataPack temp{ input_text_state, user_data, callback};

    auto func = [](ImGuiInputTextCallbackData* data) -> int {
      auto data_pack = static_cast<DataPack*>(data->UserData);

      if (*(data_pack->clear) == true)
      {
        data->DeleteChars(0, data->BufTextLen);
        *data_pack->clear = false;
      }

      data->UserData = data_pack->user_data;
      return data_pack->callback(data);
    };

    *str = str->empty() ? placeholder : *str;

    flags |= ImGuiInputTextFlags_CallbackAlways;
    if (*input_text_state)
    {
      ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_TextDisabled]);
    }
    else
    {
      ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_Text]);
    }

    auto result = ImGui::InputText(label, str, flags, func, static_cast<void*>(&temp));

    ImGui::PopStyleColor();

    if (ImGui::IsItemActive())
    {
      *input_text_state = false;
    }
    else if (ImGui::IsItemDeactivated() && (str->empty() || *str == placeholder))
    {
      *str = placeholder;
      *input_text_state = true;
    }

    if ((flags & ImGuiInputTextFlags_EnterReturnsTrue) && ImGui::IsKeyPressed(ImGuiKey_Enter, true))
    {
      *input_text_state = true;
    }

    return result;
  }
}
