#include "cpp-23-24-string.hpp"

#include <cstring>

void String::ReserveMemory(size_t new_capacity) {
  char* new_buffer = new char[new_capacity + 1];
  memmove(new_buffer, buffer_, size_);
  delete[] buffer_;
  buffer_ = new_buffer;
  capacity_ = new_capacity;
}

size_t String::Find(const String& pattern, size_t start) const {
  const char* first_occur_ptr = strstr(buffer_ + start, pattern.buffer_);
  if (first_occur_ptr == nullptr) {
    return kErrorSizeValue;
  }

  return first_occur_ptr - buffer_;
}

String::String(size_t size, char character)
    : size_(size),
      capacity_(kAllocationMultiplayer * size),
      buffer_(new char[kAllocationMultiplayer * size + 1]) {
  for (size_t i = 0; i < size_; ++i) {
    buffer_[i] = character;
  }
  buffer_[size_] = '\0';
}

String::String(const char* characters)
    : size_(strlen(characters)),
      capacity_(kAllocationMultiplayer * strlen(characters)),
      buffer_(new char[kAllocationMultiplayer * strlen(characters) + 1]) {
  memmove(buffer_, characters, size_);
  buffer_[size_] = '\0';
}

String::String(const String& characters) : String(characters.Data()) {}

void String::Clear() { buffer_[size_ = 0] = '\0'; }

void String::PushBack(char character) {
  if (size_ == capacity_) {
    ReserveMemory(capacity_ * kAllocationMultiplayer + 1);
  }
  buffer_[size_++] = character;
  buffer_[size_] = '\0';
}

void String::PopBack() {
  if (size_ != 0) {
    buffer_[--size_] = '\0';
  }
}

void String::Resize(size_t new_size) {
  if (new_size > capacity_) {
    ReserveMemory(new_size * kAllocationMultiplayer);
  }
  size_ = new_size;
  buffer_[size_] = '\0';
}

void String::Resize(size_t new_size, size_t character) {
  if (new_size > capacity_) {
    ReserveMemory(new_size * kAllocationMultiplayer);
  }

  if (new_size > size_) {
    for (size_t i = size_; i < new_size; ++i) {
      buffer_[i] = character;
    }
  }
  size_ = new_size;
  buffer_[size_] = '\0';
}

void String::Reserve(size_t new_cap) {
  if (new_cap > capacity_) {
    ReserveMemory(new_cap);
  }
}

void String::ShrinkToFit() {
  if (capacity_ > size_) {
    ReserveMemory(size_);
  }
}

void String::Swap(String& other) {
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
  std::swap(buffer_, other.buffer_);
}

char& String::Front() { return buffer_[0]; }

const char& String::Front() const { return buffer_[0]; }

char& String::Back() { return Empty() ? buffer_[size_] : buffer_[size_ - 1]; }

const char& String::Back() const {
  return Empty() ? buffer_[size_] : buffer_[size_ - 1];
}

bool String::Empty() const { return size_ == 0; }

size_t String::Size() const { return size_; }

size_t String::Capacity() const { return capacity_; }

const char* String::Data() const { return buffer_; }

std::vector<String> String::Split(const String& delim) const {
  std::vector<String> result;
  if (Empty()) {
    result.push_back('\0');
    return result;
  }
  size_t start_index = 0;

  while (start_index < size_) {
    size_t delim_index = Find(delim, start_index);

    if (delim_index == kErrorSizeValue) {
      delim_index = size_;
    }

    size_t part_size = delim_index - start_index;
    String split_part(part_size);

    memmove(split_part.buffer_, buffer_ + start_index, part_size);
    result.push_back(split_part);

    start_index = delim_index + delim.Size();
  }

  if (!delim.Empty() && !Empty() && start_index == size_) {
    result.push_back('\0');
  }

  return result;
}

String String::Join(const std::vector<String>& strings) const {
  String result;
  const size_t kStringsCount = strings.size();

  if (kStringsCount != 0) {
    for (size_t i = 0; i < kStringsCount - 1; ++i) {
      result += strings[i] + *this;
    }

    result += strings[kStringsCount - 1];
  } else {
    result += '\0';
  }

  return result;
}

String& String::operator=(const String& other) {
  Resize(other.Size());
  memmove(buffer_, other.buffer_, other.Size());

  return *this;
}

bool operator>(const String& str_1, const String& str_2) {
  const size_t kMinSize =
      str_1.Size() > str_2.Size() ? str_2.Size() : str_1.Size();

  for (size_t i = 0; i < kMinSize; ++i) {
    if (str_1[i] != str_2[i]) {
      return str_1[i] > str_2[i];
    }
  }

  return str_1.Size() > str_2.Size();
}

bool operator==(const String& str_1, const String& str_2) {
  return !(str_1 > str_2) && !(str_2 > str_1);
}

bool operator<(const String& str_1, const String& str_2) {
  return !(str_1 > str_2) && !(str_1 == str_2);
}

bool operator>=(const String& str_1, const String& str_2) {
  return !(str_1 < str_2);
}

bool operator<=(const String& str_1, const String& str_2) {
  return !(str_1 > str_2);
}

bool operator!=(const String& str_1, const String& str_2) {
  return !(str_1 == str_2);
}

String operator+(const String& str_1, const String& str_2) {
  String result_string(str_1);

  result_string += str_2;

  return result_string;
}

String& String::operator+=(const String& other) {
  const size_t kNewSize = size_ + other.size_;
  if (capacity_ < kNewSize) {
    ReserveMemory(kAllocationMultiplayer * kNewSize);
  }
  memmove(buffer_ + size_, other.buffer_, other.size_);
  size_ += other.size_;
  buffer_[size_] = '\0';

  return *this;
}

String operator*(const String& str, size_t number) {
  String result_string(str);

  result_string *= number;

  return result_string;
}

String& String::operator*=(size_t number) {
  const size_t kNewSize = size_ * number;
  if (capacity_ < kNewSize) {
    ReserveMemory(kAllocationMultiplayer * kNewSize);
  }

  for (size_t i = 1; i < number; ++i) {
    memmove(buffer_ + i * size_, buffer_, size_);
  }
  size_ *= number;
  buffer_[size_] = '\0';

  return *this;
}

char& String::operator[](size_t index) { return buffer_[index]; }

const char& String::operator[](size_t index) const { return buffer_[index]; }

std::ostream& operator<<(std::ostream& os, const String& other) {
  os << other.Data();

  return os;
}

std::istream& operator>>(std::istream& is, String& other) {
  const size_t kMaxBufferSize = 1024;
  char* temp_buffer = new char[kMaxBufferSize];
  is >> temp_buffer;

  size_t length = strlen(temp_buffer);

  other.Resize(length);
  memmove(const_cast<char*>(other.Data()), temp_buffer, length);

  delete[] temp_buffer;

  return is;
}

String::~String() { delete[] buffer_; }