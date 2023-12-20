#include "imgui_extension.h"

namespace ImGui
{
  bool InputText(const char* label, std::string* str, bool* clear_flag, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
  {
    static std::string back_up_str = "";
    struct DataPack
    {
      bool* clear;
      void* user_data;
      ImGuiInputTextCallback callback;
    };

    callback = callback == nullptr ? [](ImGuiInputTextCallbackData* data) -> int { return 0; } : callback;

    DataPack temp{ clear_flag, user_data, callback};

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

    auto result = ImGui::InputText(label, str, flags, func, static_cast<void*>(&temp));

    if (ImGui::IsItemDeactivated()) *clear_flag = true;
    return result;
  }
}
