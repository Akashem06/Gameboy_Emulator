#include "register.hpp"

// Register 8 Class

u8 Register8::get() const {
  return val;
}

void Register8::set(u8 new_value) {
  val = new_value;
}

void Register8::reset() {
  val = 0x00U;
}

bool Register8::check_bit(u8 bit) const {
  return (val & (1U << bit)) == (1U << bit);
}

void Register8::set_bit_to(u8 bit, bool set) {
  if (set) {
    val |= (1U << bit);
  } else {
    val &= ~(1U << bit);
  }
}

void Register8::increment() {
  val++;
}

void Register8::decrement() {
  val--;
}

// Register 16 Class

u16 Register16::get() const {
  return val;
}

void Register16::set(u16 new_value) {
  val = new_value;
}

void Register16::reset() {
  val = 0x0U;
}

bool Register16::check_bit(u8 bit) const {
  return (val & (1U << bit)) == (1U << bit);
}

void Register16::set_bit_to(u8 bit, bool set) {
  if (set) {
    val |= (1U << bit);
  } else {
    val &= ~(1U << bit);
  }
}

void Register16::increment() {
  val++;
}

void Register16::decrement() {
  val--;
}

// Register Pair Class

RegisterPair::RegisterPair(Register8 &high, Register8 &low) : high_ref(high), low_ref(low) {}

u16 RegisterPair::get() const {
  return (high_ref.get() << 8U) | low_ref.get();
}

void RegisterPair::set(u16 word) {
  high_ref.set((word >> 8U) & 0xFFU);
  low_ref.set(word & 0xFFU);
}

void RegisterPair::increment() {
  set(get() + 1U);
}

void RegisterPair::decrement() {
  set(get() - 1U);
}

Register8 &RegisterPair::get_hi_ref() {
  return high_ref;
}

Register8 &RegisterPair::get_lo_ref() {
  return low_ref;
}
