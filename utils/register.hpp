#pragma once

#include "common.hpp"

class Register8 {
  friend class RegisterPair;

 public:
  Register8() = default;

  u8 get() const;
  void set(u8 new_value);

  void reset();

  bool check_bit(u8 bit) const;
  void set_bit_to(u8 bit, bool set);

  void increment();
  void decrement();

  bool operator==(u8 other) const;

 private:
  u8 val = 0x0U;
};

class Register16 {
 public:
  Register16() = default;

  u16 get() const;
  void set(u16 new_value);

  void reset();

  bool check_bit(u8 bit) const;
  void set_bit_to(u8 bit, bool set);

  void increment();
  void decrement();

  bool operator==(u16 other) const;

 private:
  u16 val = 0x0U;
};

class RegisterPair {
 public:
  RegisterPair(Register8 &high, Register8 &low);

  u16 get() const;

  void set(u16 word);

  void increment();
  void decrement();

  Register8 &get_hi_ref();
  Register8 &get_lo_ref();

 private:
  Register8 &high_ref;
  Register8 &low_ref;
};
