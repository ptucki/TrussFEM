#ifndef UUID_H
#define UUID_H

#include <array>
#include <string>
#include <utility>
#include <iostream>
#include <format>

#define UUID_FORMAT_TEMPLATE "{:02x}{:02x}{:02x}{:02x}-{:02x}{:02x}-{:02x}{:02x}-{:02x}{:02x}-{:02x}{:02x}{:02x}{:02x}{:02x}{:02x}"
#define UUID_GENERATED_ARRAY_SIZE 2

class UUID
{
  using array_type = std::array<uint64_t, UUID_GENERATED_ARRAY_SIZE>;

public:

  UUID();
  ~UUID() = default;
  UUID(const UUID& obj);
  UUID(UUID&& obj) noexcept;
  UUID& operator=(const UUID& rhs);
  UUID& operator=(UUID&& rhs) noexcept;

  std::string ToString() const;
  bool IsValid() const;

  bool operator==(const UUID& rhs) const;
  bool operator!=(const UUID& rhs) const;
  friend std::ostream& operator<<(std::ostream& os, const UUID& uuid);

private:

  template<typename Array, std::size_t... Idx>
  static decltype(auto) unpack_array(const Array& arr, std::index_sequence<Idx...>)
  {
    return std::format(UUID_FORMAT_TEMPLATE, arr[Idx]...);
  }

  array_type gen_;
};



#endif // !UUID_H
