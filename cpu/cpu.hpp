#pragma once

#include "common.hpp"
#include "interrupts.hpp"
#include "memory_controller.hpp"
#include "opcode_handler.hpp"
#include "register.hpp"

/* https://gbdev.io/pandocs/CPU_Registers_and_Flags.html */

class CPU {
 private:
  Register8 a; /**< Register A */
  Register8 f; /**< Register F */
  Register8 b; /**< Register B */
  Register8 c; /**< Register C */
  Register8 d; /**< Register D */
  Register8 e; /**< Register E */
  Register8 h; /**< Register H */
  Register8 l; /**< Register L */

  OpcodeHandler opcode_handler;

  u32 cycles = 0U;

  // --- Internal Helper Functions ---
  // Fetching
  u8 fetch8();                           // Fetch one byte from memory at PC
  u16 fetch16();                         // Fetch two bytes from memory at PC
  u8 read8(u16 address);                 // Read one byte from memory at address
  u16 read16(u16 address);               // Read two bytes from memory at address
  void write8(u16 address, u8 value);    // Write one byte to memory
  void write16(u16 address, u16 value);  // Write two bytes to memory

  // Instruction Execution
  void execute(u8 opcode);     // Execute the instruction at PC
  void execute_cb(u8 opcode);  // Execute CB-prefixed instructions

  // Interrupt Handling
  void handle_interrupts();  // Check and handle pending interrupts
  bool handle_interrupt(interrupts::flags flag, interrupts::vector vector, u8 fired_interrupts);
  void request_interrupt(u8 interrupt_bit);  // Request a specific interrupt

 public:
  MemoryController *mem_ctrl;

  Register8 interrupt_flag;
  Register8 interrupt_enabled_reg;
  bool interrupts_enabled = false;
  bool halted = false;
  bool branch_taken = false;

  RegisterPair af; /**< Accumlator & Flags */
  RegisterPair bc; /**< B - 8-bit HI, C - 8-bit LO */
  RegisterPair de; /**< D - 8-bit HI, E - 8-bit LO */
  RegisterPair hl; /**< H - 8-bit HI, L - 8-bit LO */
  Register16 sp;   /**< Stack Pointer */
  Register16 pc;   /**< Program Counter */

  CPU(MemoryController *mem_ctrl);

  void init();
  bool step();

  void set_zero(bool value);
  void set_subtract(bool value);
  void set_half_carry(bool value);
  void set_carry(bool value);
  bool get_zero();
  bool get_subtract();
  bool get_half_carry();
  bool get_carry();

  void stack_push_16(u16 value);
  u16 stack_pop_16();

  u8 get_byte_from_pc();
  i8 get_signed_byte_from_pc();
  u16 get_word_from_pc();

  bool is_condition(Condition condition);
};
