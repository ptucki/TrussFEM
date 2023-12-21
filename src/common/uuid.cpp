#include "Uuid.h"

#include <random>
#include <chrono>
#include <format>

UUID::UUID()
  : gen_{ 0 }
{
  auto tp = std::chrono::system_clock::now();
  std::mt19937_64 mt(tp.time_since_epoch().count());

  gen_[0] = static_cast<array_type::value_type>(mt());
  gen_[1] = static_cast<array_type::value_type>(mt());
}

UUID::UUID(const UUID& obj)
  : gen_{ 0 }
{
  auto tp = std::chrono::system_clock::now();
  std::mt19937_64 mt(tp.time_since_epoch().count());

  gen_[0] = static_cast<array_type::value_type>(mt());
  gen_[1] = static_cast<array_type::value_type>(mt());
}

UUID::UUID(UUID&& obj) noexcept
{
  this->gen_ = obj.gen_;
  obj.gen_ = { 0 };
}

UUID& UUID::operator=(const UUID& rhs)
{
  return *this;
}

UUID& UUID::operator=(UUID&& rhs) noexcept
{
  this->gen_ = rhs.gen_;
  rhs.gen_ = { 0 };

  return *this;
}

std::string UUID::ToString() const
{
  constexpr size_t size = UUID_GENERATED_ARRAY_SIZE * sizeof(array_type::value_type);
  std::array<uint8_t, size> arr{0};

  memcpy(&arr, &gen_[0], sizeof(array_type::value_type));
  memcpy(&arr[arr.size() / 2], &gen_[1], sizeof(array_type::value_type));

  return UUID::unpack_array(arr, std::make_index_sequence<size>{});
}

bool UUID::IsValid() const
{
  return (this->gen_[0] != 0 && this->gen_[1] != 0) ? true : false;;
}

bool UUID::operator==(const UUID& rhs) const
{
  return (this->gen_[0] == rhs.gen_[0] && this->gen_[1] == rhs.gen_[1]) ? true : false;
}

bool UUID::operator!=(const UUID& rhs) const
{
  return (this->gen_[0] != rhs.gen_[0] || this->gen_[1] != rhs.gen_[1]) ? true : false;
}

std::ostream& operator<<(std::ostream& os, const UUID& uuid)
{
  os << uuid.ToString();
  return os;
}
