#ifndef MY_IMGUI_EXTENSION_H
#define MY_IMGUI_EXTENSION_H

#include <vector>
#include <array>
#include <string>
#include <format>
#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"

struct TableDataPack
{
  std::string& item;
  size_t row;
  size_t column;
  void* user_data;
};

template<size_t N>
using TableData = std::vector<std::array<std::string, N>>;

using DataHandlerCallback = bool(*)(TableDataPack& data);

template<class T>
using DataHandlerClassCallback = bool(T::*)(TableDataPack& data);

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

  template<size_t N>
  bool EditableTable(
    const char* id,
    const ::std::array<const char*, N>& column_header_names,
    TableData<N>& data,
    DataHandlerCallback on_input = nullptr,
    void* user_data = nullptr,
    ImGuiTableFlags flags = 0,
    const ImVec2& outer_size = ImVec2(0.0f, 0.0f),
    float inner_width = 0.0f)
  {
    bool data_changed = false;

    if (ImGui::BeginTable(std::format("##{}", id).c_str(), N, flags, outer_size, inner_width))
    {
      for (const auto& column : column_header_names) ImGui::TableSetupColumn(column);
      ImGui::TableHeadersRow();

      size_t current_row{ 0 };
      size_t current_column{ 0 };

      for (auto& row : data)
      {
        ImGui::TableNextRow();

        for (auto& cell : row)
        {
          auto input_text_label = std::format("##{}{}_{}", id, current_row, current_column);

          ImGui::TableSetColumnIndex(static_cast<int>(current_column));

          ImGui::SetNextItemWidth(-FLT_MIN);
          ImGui::PushStyleColor(ImGuiCol_FrameBg, ImColor().Value);
          if (ImGui::InputText(input_text_label.c_str(), cell.data(), cell.capacity(), ImGuiInputTextFlags_EnterReturnsTrue))
          {
            TableDataPack callback_data{ data[current_row][current_column], current_row, current_column, user_data };

            if (on_input != nullptr) data_changed = data_changed || on_input(callback_data);

            ImGui::PopStyleColor();
            break;
          }
          ImGui::PopStyleColor();
          current_column++;
        }
        current_column = 0;
        current_row++;

      }
      ImGui::EndTable();
    }
    return data_changed;
  }


  template<size_t N, class T>
  bool EditableTable(
    const char* id,
    const ::std::array<const char*, N>& column_header_names,
    TableData<N>& data,
    DataHandlerClassCallback<T> on_input,
    T* object,
    void* user_data = nullptr,
    ImGuiTableFlags flags = 0,
    const ImVec2& outer_size = ImVec2(0.0f, 0.0f),
    float inner_width = 0.0f)
  {
    bool data_changed = false;

    if (ImGui::BeginTable(std::format("##{}", id).c_str(), N, flags, outer_size, inner_width))
    {
      for (const auto& column : column_header_names) ImGui::TableSetupColumn(column);
      ImGui::TableHeadersRow();

      size_t current_row{ 0 };
      size_t current_column{ 0 };

      for (auto& row : data)
      {
        ImGui::TableNextRow();

        for (auto& cell : row)
        {
          auto input_text_label = std::format("##{}{}_{}", id, current_row, current_column);

          ImGui::TableSetColumnIndex(static_cast<int>(current_column));

          ImGui::SetNextItemWidth(-FLT_MIN);
          ImGui::PushStyleColor(ImGuiCol_FrameBg, ImColor().Value);
          if (ImGui::InputText(input_text_label.c_str(), cell.data(), cell.capacity(), ImGuiInputTextFlags_EnterReturnsTrue))
          {
            TableDataPack callback_data{ data[current_row][current_column], current_row, current_column, user_data };

            if (on_input != nullptr) data_changed = data_changed || (*object.*on_input)(callback_data);

            ImGui::PopStyleColor();
            break;
          }
          ImGui::PopStyleColor();
          current_column++;
        }
        current_column = 0;
        current_row++;

      }
      ImGui::EndTable();
    }
    return data_changed;
  }

}

#endif // !MY_IMGUI_EXTENSION_H
