#include "cpu.hpp"
#include "log.hpp"
#include "gameboy.hpp"

#define ZERO_FLAG_BIT_OFFSET 7U
#define SUBTRACTION_FLAG_BIT_OFFSET 6U
#define HALF_CARRY_FLAG_BIT_OFFSET 5U
#define CARRY_FLAG_BIT_OFFSET 4U

u8 CPU::fetch8() {
  u8 return_val = gameboy->get_memory_controller().read(pc.get());
  pc.increment();
  return return_val;
}

u16 CPU::fetch16() {
  u16 low = fetch8();
  u16 high = fetch8();

  return (high << 8U) | low;
}

u8 CPU::read8(u16 address) {
  u8 result = gameboy->get_memory_controller().read(address);
  return result;
}

u16 CPU::read16(u16 address) {
  u16 low = read8(address);
  u16 high = read8(address + 1U);

  return (high << 8U) | low;
}

void CPU::write8(u16 address, u8 value) {
  gameboy->get_memory_controller().write(address, value);
}

void CPU::write16(u16 address, u16 value) {
  write8(address, static_cast<u8>(value & 0xFFU));
  write8(address + 1U, static_cast<u8>((value >> 8U) & 0xFFU));
}

u32 CPU::execute(u8 opcode) {
  Cycles instruction_cycles;
  if (opcode == 0xCB) {
    u8 cb_opcode = fetch8(); // Fetch the CB opcode
    instruction_cycles = opcode_handler.handle_cb_opcode(cb_opcode);
  } else {
    instruction_cycles = opcode_handler.handle_opcode(opcode);
  }

  return instruction_cycles;
}

bool CPU::handle_interrupt(interrupts::flags flag, interrupts::vector vector, u8 fired_interrupts) {
  if (!((fired_interrupts & static_cast<u8>(flag)) == static_cast<u8>(flag))) {
    return false;
  }

  interrupt_flag.set(interrupt_flag.get() & ~(static_cast<u8>(flag)));
  stack_push_16(pc.get());
  pc.set(static_cast<u16>(vector));
  interrupts_enabled = false;

  return true;
}

void CPU::handle_interrupts() {
  u8 fired_interrupts = interrupt_flag.get() & interrupt_enabled_reg.get();

  if (!fired_interrupts) {
    return;
  }

  if (!interrupts_enabled) {
    return;
  }

  // Acknowledge interrupt by setting IME to false (interrupts are disabled after one is handled)
  interrupts_enabled = false;
  
  bool handled_interrupt = false;

  // Interrupts are prioritized. The order here matters.
  // VBlank (bit 0) -> LCDC Stat (bit 1) -> Timer (bit 2) -> Serial (bit 3) -> Joypad (bit 4)
  log_debug("fired_interrupts: %u\r\n", fired_interrupts);
  handled_interrupt = handle_interrupt(interrupts::flags::vblank, interrupts::vector::vblank, fired_interrupts);
  if (handled_interrupt) {
    return;
  }

  handled_interrupt = handle_interrupt(interrupts::flags::lcdc_status, interrupts::vector::lcdc_status, fired_interrupts);
  if (handled_interrupt) {
    return;
  }

  handled_interrupt = handle_interrupt(interrupts::flags::timer, interrupts::vector::timer, fired_interrupts);
  if (handled_interrupt) {
    return;
  }

  handled_interrupt = handle_interrupt(interrupts::flags::serial, interrupts::vector::serial, fired_interrupts);
  if (handled_interrupt) {
    return;
  }

  handled_interrupt = handle_interrupt(interrupts::flags::joypad, interrupts::vector::joypad, fired_interrupts);
  if (handled_interrupt) {
    return;
  }
}

u8 CPU::get_byte_from_pc() {
  u8 byte = gameboy->get_memory_controller().read(pc.get());
  pc.increment();
  return byte; // No cycle addition here, as fetch8() is the primary byte fetch mechanism
}

i8 CPU::get_signed_byte_from_pc() {
  u8 byte = get_byte_from_pc();
  return static_cast<i8>(byte);
}

u16 CPU::get_word_from_pc() {
  u8 low_byte = get_byte_from_pc();
  u8 high_byte = get_byte_from_pc();

  return ((u16)(high_byte) << 8U) | (low_byte);
}

bool CPU::is_condition(Condition condition) {
  bool should_branch;

  switch (condition) {
    case Condition::C:
      should_branch = get_carry();
      break;
    case Condition::NC:
      should_branch = !get_carry();
      break;
    case Condition::Z:
      should_branch = get_zero();
      break;
    case Condition::NZ:
      should_branch = !get_zero();
      break;
    default: // Should not happen
      should_branch = false;
      break;
  }

  branch_taken = should_branch;
  return should_branch;
}

void CPU::request_interrupt(u8 interrupt_bit) {
  u16 interrupt_reg_val = interrupt_flag.get();

  interrupt_reg_val |= 1U << interrupt_bit;

  interrupt_flag.set(interrupt_reg_val);
}

void CPU::set_zero(bool value) {
  u16 reg_val = af.get();

  if (value) {
    reg_val |= 1U << ZERO_FLAG_BIT_OFFSET;
  } else {
    reg_val &= ~(1U << ZERO_FLAG_BIT_OFFSET);
  }

  af.set(reg_val);
}

void CPU::set_subtract(bool value) {
  u16 reg_val = af.get();

  if (value) {
    reg_val |= 1U << SUBTRACTION_FLAG_BIT_OFFSET;
  } else {
    reg_val &= ~(1U << SUBTRACTION_FLAG_BIT_OFFSET);
  }

  af.set(reg_val);
}

void CPU::set_half_carry(bool value) {
  u16 reg_val = af.get();

  if (value) {
    reg_val |= 1U << HALF_CARRY_FLAG_BIT_OFFSET;
  } else {
    reg_val &= ~(1U << HALF_CARRY_FLAG_BIT_OFFSET);
  }

  af.set(reg_val);
}

void CPU::set_carry(bool value) {
  u16 reg_val = af.get();

  if (value) {
    reg_val |= 1U << CARRY_FLAG_BIT_OFFSET;
  } else {
    reg_val &= ~(1U << CARRY_FLAG_BIT_OFFSET);
  }

  af.set(reg_val);
}

bool CPU::get_zero() {
  return (af.get() & (1U << ZERO_FLAG_BIT_OFFSET)) == (1U << ZERO_FLAG_BIT_OFFSET);
}

bool CPU::get_subtract() {
  return (af.get() & (1U << SUBTRACTION_FLAG_BIT_OFFSET)) == (1U << SUBTRACTION_FLAG_BIT_OFFSET);
}

bool CPU::get_half_carry() {
  return (af.get() & (1U << HALF_CARRY_FLAG_BIT_OFFSET)) == (1U << HALF_CARRY_FLAG_BIT_OFFSET);
}

bool CPU::get_carry() {
  return (af.get() & (1U << CARRY_FLAG_BIT_OFFSET)) == (1U << CARRY_FLAG_BIT_OFFSET);
}

void CPU::stack_push_16(u16 value) {
  /* Stack grows downwards */
  sp.decrement();
  gameboy->get_memory_controller().write(sp.get(), static_cast<u8>((value >> 8U) & 0xFFU));

  sp.decrement();
  gameboy->get_memory_controller().write(sp.get(), static_cast<u8>(value & 0xFFU));
}

u16 CPU::stack_pop_16() {
  /* Stack pops upwards */
  u16 low_byte = gameboy->get_memory_controller().read(sp.get());
  sp.increment();

  u16 high_byte = gameboy->get_memory_controller().read(sp.get());
  sp.increment();

  return (high_byte << 8U) | low_byte;
}

CPU::CPU() : opcode_handler(), af(a, f), bc(b, c), de(d, e), hl(h, l) {}

void CPU::init() {
  af.set(0x01B0);
  bc.set(0x0013);
  de.set(0x00D8);
  hl.set(0x014D);
  sp.set(HIGH_RAM_START_ADDRESS);
  pc.set(PROGRAM_COUNTER_START_VALUE);

  interrupts_enabled = false;
  halted = false;
  branch_taken = false;
  cycles = 0U;

  interrupt_flag.set(0xE1U);
  interrupt_enabled_reg.set(0x00U);
  
  log_debug("PC On init: %u\r\n", pc.get());
}

u32 CPU::step() {
  branch_taken = false;

  if (halted) {
    u8 pending_interrupts = interrupt_flag.get() & interrupt_enabled_reg.get();
    if (pending_interrupts) {
      halted = false;
    } else {
      cycles += 4;
      return true;
    }
  }

  // Handle interrupts before fetching the next opcode (IME check is inside handle_interrupts)
  handle_interrupts();

  u8 opcode = fetch8(); // Fetching the opcode increments PC and adds 4 cycles
  return execute(opcode);      // This will now add the remaining cycles for the instruction
}

void CPU::set_gameboy(Gameboy *gb) {
  this->gameboy = gb;
}