#pragma once
#include <iostream>
#include <vector>

class String {
 public:
  String(size_t size = 0, char character = '\0');

  String(const char* character);

  String(const String& characters);

  void Clear();

  void Reserve(size_t new_capacity);

  void PushBack(char character);

  void PopBack();

  void Resize(size_t new_size);

  void Resize(size_t new_size, size_t character);

  void ShrinkToFit();

  void Swap(String& other);

  char& Front();

  const char& Front() const;

  char& Back();

  const char& Back() const;

  bool Empty() const;

  size_t Size() const;

  size_t Capacity() const;

  const char* Data() const;

  std::vector<String> Split(const String& delim = " ") const;

  String Join(const std::vector<String>& strings) const;

  String& operator=(const String& other);

  String& operator+=(const String& other);

  String& operator*=(size_t number);

  char& operator[](size_t index);

  const char& operator[](size_t index) const;

  ~String();

 private:
  static const size_t kAllocationMultiplayer = 2;
  static const size_t kErrorSizeValue = -1;
  char* buffer_;
  size_t size_;
  size_t capacity_;

  void ReserveMemory(size_t new_capacity);

  size_t Find(const String& sub, size_t start) const;
};

String operator+(const String& str_1, const String& str_2);

String operator*(const String& str, size_t number);

bool operator>(const String& str_1, const String& str_2);

bool operator==(const String& str_1, const String& str_2);

bool operator<(const String& str_1, const String& str_2);

bool operator>=(const String& str_1, const String& str_2);

bool operator<=(const String& str_1, const String& str_2);

bool operator!=(const String& str_1, const String& str_2);

std::ostream& operator<<(std::ostream& os, const String& other);
std::istream& operator>>(std::istream& is, String& other);