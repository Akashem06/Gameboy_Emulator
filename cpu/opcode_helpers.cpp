#include "cpu.hpp"
#include "opcode_handler.hpp"

void OpcodeHandler::opcode_nop() {
  /* Do nothing */
}

/* LD */

void OpcodeHandler::opcode_ld(RegisterPair &dest) {
  dest.set(cpu->get_word_from_pc());
}

void OpcodeHandler::opcode_ld(Address dest, Register8 source) {
  cpu->mem_ctrl->write(dest, source.get());
}

void OpcodeHandler::opcode_ld(Register8 dest) {
  dest.set(cpu->get_byte_from_pc());
}

void OpcodeHandler::opcode_ld(Register8 dest, Register8 source) {
  dest.set(source.get());
}

void OpcodeHandler::opcode_ld(Register8 dest, Address source) {
  dest.set(cpu->mem_ctrl->read(source));
}

void OpcodeHandler::opcode_ld(Address dest) {
  cpu->mem_ctrl->write(dest, cpu->get_byte_from_pc());
}

void OpcodeHandler::opcode_ld(Address dest, Register16 source) {
  cpu->mem_ctrl->write(dest, source.get());
}

void OpcodeHandler::opcode_ld(Address dest, RegisterPair source) {
  cpu->mem_ctrl->write(dest, source.get());
}

void OpcodeHandler::opcode_ld(RegisterPair dest, RegisterPair source) {
  dest.set(source.get());
}

void OpcodeHandler::opcode_ld(RegisterPair &dest, RegisterPair &source) {
  dest.set(source.get());
}

void OpcodeHandler::opcode_ld_to_addr(Register8 source) {
  cpu->mem_ctrl->write(cpu->hl.get(), source.get());
}

void OpcodeHandler::opcode_ld_from_addr(Register8 dest) {
  u16 pc = cpu->get_word_from_pc();
  dest.set(cpu->mem_ctrl->read(pc));
}

/* LDHL */

void OpcodeHandler::opcode_ldhl() {
  u16 reg = cpu->sp.get();
  i8 value = cpu->get_signed_byte_from_pc();

  u8 sp_low = static_cast<u8>(reg & 0xFFU);
  u8 val_u8 = static_cast<u8>(value);

  cpu->set_subtract(false);
  cpu->set_zero(false);
  cpu->set_half_carry(((sp_low & 0x0FU) + (val_u8 & 0x0FU)) > 0x0FU);
  cpu->set_carry((sp_low + val_u8) > 0xFFU);

  cpu->hl.set(static_cast<u16>(reg + value));
}

/* LDI */

void OpcodeHandler::opcode_ldi(Address target, Register8 source) {
  cpu->mem_ctrl->write(target, source.get());
  cpu->hl.increment();
}

void OpcodeHandler::opcode_ldi(Register8 target, Address source) {
  target.set(cpu->mem_ctrl->read(source));
  cpu->hl.increment();
}

/* LDD */

void OpcodeHandler::opcode_ldd(Address target, Register8 source) {
  cpu->mem_ctrl->write(target, source.get());
  cpu->hl.decrement();
}

void OpcodeHandler::opcode_ldd(Register8 target, Address source) {
  target.set(cpu->mem_ctrl->read(source));
  cpu->hl.decrement();
}

/* LDH */

void OpcodeHandler::opcode_ldh_into_data() {
  u8 a = (cpu->af.get() & 0xFF00U) >> 8U;
  u8 offset = cpu->get_byte_from_pc();

  Address address = 0xFF00U + offset;

  cpu->mem_ctrl->write(address, a);
}

void OpcodeHandler::opcode_ldh_into_c() {
  u8 a = (cpu->af.get() & 0xFF00U) >> 8U;
  u8 c = cpu->bc.get() & 0xFFU;

  Address address = 0xFF00U + c;

  cpu->mem_ctrl->write(address, a);
}

void OpcodeHandler::opcode_ldh_into_a() {
  u8 offset = cpu->get_byte_from_pc();

  Address address = 0xFF00U + offset;

  u8 value = cpu->mem_ctrl->read(address);
  cpu->af.set((value & 0xFFU) << 8U);
}

void OpcodeHandler::opcode_ldh_c_into_a() {
  u8 c = cpu->bc.get() & 0xFFU;

  Address address = 0xFF00U + c;

  u8 value_from_mem = cpu->mem_ctrl->read(address);
  cpu->af.set((value_from_mem << 8U) | (cpu->af.get() & 0x00FFU));
}

/* INC */

void OpcodeHandler::opcode_inc(RegisterPair &target) {
  target.increment();
}

void OpcodeHandler::opcode_inc(Register8 &target) {
  u8 old_val = target.get();
  target.increment();
  u8 result = target.get();

  cpu->set_zero(result == 0U);
  cpu->set_subtract(false);
  cpu->set_half_carry((old_val & 0xFU) == 0xFU);
}

void OpcodeHandler::opcode_inc(Address target) {
  u8 value = cpu->mem_ctrl->read(target);
  u8 result = static_cast<u8>(value + 1U);
  cpu->mem_ctrl->write(target, result);

  cpu->set_zero(result == 0U);
  cpu->set_subtract(false);
  cpu->set_half_carry((value & 0xFU) == 0xFU);
}

/* DEC */

void OpcodeHandler::opcode_dec(RegisterPair &target) {
  target.decrement();
}

void OpcodeHandler::opcode_dec(Register8 &target) {
  u8 old_val = target.get();
  target.decrement();
  u8 result = target.get();

  cpu->set_zero(result == 0U);
  cpu->set_subtract(true);
  cpu->set_half_carry((old_val & 0x0FU) == 0x00U);
}

void OpcodeHandler::opcode_dec(Address target) {
  u8 value = cpu->mem_ctrl->read(target);
  u8 result = static_cast<u8>(value - 1U);
  cpu->mem_ctrl->write(target, result);

  cpu->set_zero(result == 0U);
  cpu->set_subtract(true);
  cpu->set_half_carry((value & 0x0FU) == 0x00U);
}

/* ADD HL */

void OpcodeHandler::opcode_add_hl(RegisterPair &source) {
  u16 reg = cpu->hl.get();
  u16 src_val = source.get();
  u32 result = reg + src_val;

  cpu->set_subtract(false);
  cpu->set_half_carry(((reg & 0x07FFU) + (src_val & 0x07FFU)) > 0x07FFU);
  cpu->set_carry(result > 0xFFFFU);

  cpu->hl.set(static_cast<u16>(result));
}

void OpcodeHandler::opcode_add_hl(Register16 &source) {
  u16 reg = cpu->hl.get();
  u16 src_val = source.get();
  u32 result = reg + src_val;

  cpu->set_subtract(false);
  cpu->set_half_carry(((reg & 0x07FFU) + (src_val & 0x07FFU)) > 0x07FFU);
  cpu->set_carry(result > 0xFFFFU);

  cpu->hl.set(static_cast<u16>(result));
}

void OpcodeHandler::opcode_stop() {}

void OpcodeHandler::opcode_jr() {
  i8 offset = cpu->get_signed_byte_from_pc();

  u16 old_pc = cpu->pc.get();
  u16 new_pc = static_cast<u16>(old_pc + offset);
  cpu->pc.set(new_pc);
}

void OpcodeHandler::opcode_jr(Condition condition) {
  if (cpu->is_condition(condition)) {
    opcode_jr();
  } else {
    /* Consume unused argument */
    cpu->get_signed_byte_from_pc();
  }
}

void OpcodeHandler::opcode_daa() {
  u8 a = (cpu->af.get() & 0xFF00U) >> 8U;

  u16 correction = cpu->get_carry() ? 0x60U : 0x00U;

  if (cpu->get_half_carry() || (!cpu->get_subtract() && ((a & 0x0FU) > 9))) {
    correction |= 0x06U;
  }

  if (cpu->get_carry() || (!cpu->get_subtract() && (a > 0x99U))) {
    correction |= 0x60U;
  }

  if (cpu->get_subtract()) {
    a = static_cast<u8>(a - correction);
  } else {
    a = static_cast<u8>(a + correction);
  }

  cpu->af.set((a & 0xFFU) << 8U);

  if (((correction << 2U) & 0x100U) != 0U) {
    cpu->set_carry(true);
  }

  cpu->set_half_carry(false);
  cpu->set_zero(a == 0U);
}

/* SCF */

void OpcodeHandler::opcode_scf() {
  cpu->set_carry(true);
  cpu->set_half_carry(false);
  cpu->set_subtract(false);
}

/* CCF */

void OpcodeHandler::opcode_ccf() {
  cpu->set_carry(!cpu->get_carry());
  cpu->set_half_carry(false);
  cpu->set_subtract(false);
}

void OpcodeHandler::opcode_halt() {
  cpu->halted = true;
}

/* ADD */

void OpcodeHandler::_opcode_add(u8 reg, u8 value) {
  u16 result = reg + value;

  cpu->af.set((result & 0xFFU) << 8U);
  cpu->set_zero((result & 0xFFU) == 0U);
  cpu->set_subtract(false);
  cpu->set_half_carry(((reg & 0xFU) + (value & 0xFU)) > 0xFU);
  cpu->set_carry(result > 0xFFU);
}

void OpcodeHandler::opcode_add_a(Register8 source) {
  _opcode_add(((cpu->af.get() >> 8U) & 0xFFU), source.get());
}

void OpcodeHandler::opcode_add_a(Address source) {
  _opcode_add(((cpu->af.get() >> 8U) & 0xFFU), cpu->mem_ctrl->read(source));
}

void OpcodeHandler::opcode_add_a() {
  _opcode_add(((cpu->af.get() >> 8U) & 0xFFU), cpu->get_byte_from_pc());
}

/* ADC */

void OpcodeHandler::_opcode_adc(u8 value) {
  u8 reg = (cpu->af.get() >> 8U) & 0xFFU;
  u8 carry = cpu->get_carry() ? 1 : 0;

  u16 result = reg + value + carry;

  cpu->af.set((result & 0xFFU) << 8U);
  cpu->set_zero((result & 0xFFU) == 0U);
  cpu->set_subtract(false);
  cpu->set_half_carry(((reg & 0xFU) + (value & 0xFU) + carry) > 0xFU);
  cpu->set_carry(result > 0xFFU);
}

void OpcodeHandler::opcode_adc(Register8 source) {
  _opcode_adc(source.get());
}

void OpcodeHandler::opcode_adc(Address source) {
  _opcode_adc(cpu->mem_ctrl->read(source));
}

void OpcodeHandler::opcode_adc() {
  _opcode_adc(cpu->get_byte_from_pc());
}

/* SUB */

void OpcodeHandler::_opcode_sub(u8 value) {
  u8 reg = (cpu->af.get() >> 8U) & 0xFFU;

  u8 result = static_cast<u8>(reg - value);

  cpu->af.set((result & 0xFFU) << 8U);
  cpu->set_zero(result == 0U);
  cpu->set_subtract(true);
  cpu->set_half_carry(((reg & 0xFU) - (value & 0xFU)) < 0);
  cpu->set_carry(reg < value);
}

void OpcodeHandler::opcode_sub(Register8 source) {
  _opcode_sub(source.get());
}

void OpcodeHandler::opcode_sub(Address source) {
  _opcode_sub(cpu->mem_ctrl->read(source));
}

void OpcodeHandler::opcode_sub() {
  _opcode_sub(cpu->get_byte_from_pc());
}

/* SBC */

void OpcodeHandler::_opcode_sbc(u8 value) {
  u8 reg = (cpu->af.get() >> 8U) & 0xFFU;
  u8 carry = cpu->get_carry() ? 1 : 0;

  int result = reg - value - carry;

  cpu->af.set((static_cast<u8>(result) & 0xFFU) << 8U);
  cpu->set_zero((result & 0xFFU) == 0U);
  cpu->set_subtract(true);
  cpu->set_half_carry(((reg & 0xFU) - (value & 0xFU) - carry) < 0);
  cpu->set_carry(result < 0);
}

void OpcodeHandler::opcode_sbc(Register8 source) {
  _opcode_sbc(source.get());
}

void OpcodeHandler::opcode_sbc(Address source) {
  _opcode_sbc(cpu->mem_ctrl->read(source));
}

void OpcodeHandler::opcode_sbc() {
  _opcode_sbc(cpu->get_byte_from_pc());
}

/* AND */

void OpcodeHandler::_opcode_and(u8 value) {
  u8 reg = (cpu->af.get() >> 8U) & 0xFFU;

  u8 result = reg & value;

  cpu->af.set((result & 0xFFU) << 8U);
  cpu->set_zero(result == 0U);
  cpu->set_subtract(false);
  cpu->set_half_carry(true);
  cpu->set_carry(false);
}

void OpcodeHandler::opcode_and(Register8 source) {
  _opcode_and(source.get());
}

void OpcodeHandler::opcode_and(Address source) {
  _opcode_and(cpu->mem_ctrl->read(source));
}

void OpcodeHandler::opcode_and() {
  _opcode_and(cpu->get_byte_from_pc());
}

/* XOR */

void OpcodeHandler::_opcode_xor(u8 value) {
  u8 reg = (cpu->af.get() >> 8U) & 0xFFU;

  u8 result = reg ^ value;

  cpu->af.set((result & 0xFFU) << 8U);
  cpu->set_zero(result == 0U);
  cpu->set_subtract(false);
  cpu->set_half_carry(false);
  cpu->set_carry(false);
}

void OpcodeHandler::opcode_xor(Register8 source) {
  _opcode_xor(source.get());
}

void OpcodeHandler::opcode_xor(Address source) {
  _opcode_xor(cpu->mem_ctrl->read(source));
}

void OpcodeHandler::opcode_xor() {
  _opcode_xor(cpu->get_byte_from_pc());
}

/* OR */

void OpcodeHandler::_opcode_or(u8 value) {
  u8 reg = (cpu->af.get() >> 8U) & 0xFFU;

  u8 result = reg | value;

  cpu->af.set((result & 0xFFU) << 8U);
  cpu->set_zero(result == 0U);
  cpu->set_subtract(false);
  cpu->set_half_carry(false);
  cpu->set_carry(false);
}

void OpcodeHandler::opcode_or(Register8 source) {
  _opcode_or(source.get());
}

void OpcodeHandler::opcode_or(Address source) {
  _opcode_or(cpu->mem_ctrl->read(source));
}

void OpcodeHandler::opcode_or() {
  _opcode_or(cpu->get_byte_from_pc());
}

/* CP */

void OpcodeHandler::_opcode_cp(u8 value) {
  u8 reg = (cpu->af.get() >> 8U) & 0xFFU;

  u8 result = static_cast<u8>(reg - value);

  cpu->set_zero(result == 0U);
  cpu->set_subtract(true);
  cpu->set_half_carry(((reg & 0xFU) - (value & 0xFU)) < 0);
  cpu->set_carry(reg < value);
}

void OpcodeHandler::opcode_cp(Register8 source) {
  _opcode_cp(source.get());
}

void OpcodeHandler::opcode_cp(Address source) {
  _opcode_cp(cpu->mem_ctrl->read(source));
}

void OpcodeHandler::opcode_cp() {
  _opcode_cp(cpu->get_byte_from_pc());
}

/* CPL */
void OpcodeHandler::opcode_cpl() {
  u8 a = (cpu->af.get() >> 8U) & 0xFFU;
  a = ~a;
  cpu->af.set((a << 8U) | (cpu->af.get() & 0x00FFU));

  cpu->set_subtract(true);
  cpu->set_half_carry(true);
}

void OpcodeHandler::opcode_pop(RegisterPair &dest) {
  u16 value = cpu->stack_pop_16();
  dest.set(value);
}

void OpcodeHandler::opcode_jp(Condition condition) {
  if (cpu->is_condition(condition)) {
    opcode_jp();
  } else {
    /* Skip unused word argument */
    cpu->get_word_from_pc();
  }
}

void OpcodeHandler::opcode_jp() {
  u16 address = cpu->get_word_from_pc();
  cpu->pc.set(address);
}

/* CALL */

void OpcodeHandler::opcode_call() {
  u16 address = cpu->get_word_from_pc();
  cpu->stack_push_16(cpu->pc.get());
  cpu->pc.set(address);
}

void OpcodeHandler::opcode_call(Condition condition) {
  if (cpu->is_condition(condition)) {
    u16 address = cpu->get_word_from_pc();
    cpu->stack_push_16(cpu->pc.get());
    cpu->pc.set(address);
  } else {
    /* Skip unusued word argument */
    cpu->get_word_from_pc();
  }
}

void OpcodeHandler::opcode_push(RegisterPair &source) {
  cpu->stack_push_16(source.get());
}

void OpcodeHandler::opcode_rst(rst::vector rst_vector) {
  cpu->stack_push_16(cpu->pc.get());
  cpu->pc.set(static_cast<u16>(rst_vector));
}

void OpcodeHandler::opcode_ret() {
  cpu->stack_pop_16();
}

void OpcodeHandler::opcode_ret(Condition condition) {
  if (cpu->is_condition(condition)) {
    opcode_ret();
  }
}

void OpcodeHandler::opcode_reti() {
  opcode_ret();
  opcode_ei();
}

void OpcodeHandler::opcode_add_sp() {
  u16 sp_val = cpu->sp.get();
  i8 value = cpu->get_signed_byte_from_pc();

  u16 result_for_flags = static_cast<u16>((sp_val & 0xFFU) + (value & 0xFFU));
  u16 result_for_half_flags = static_cast<u16>((sp_val & 0xFU) + (value & 0xFU));

  cpu->sp.set(static_cast<u16>(sp_val + value));

  cpu->set_zero(false);
  cpu->set_subtract(false);
  cpu->set_half_carry(result_for_half_flags > 0xFU);
  cpu->set_carry(result_for_flags > 0xFFU);
}

void OpcodeHandler::opcode_jp(Address source) {
  (void)source;
  cpu->pc.set(cpu->hl.get());
}

/* DI */

void OpcodeHandler::opcode_di() {
  cpu->interrupts_enabled = false;
}

/* EI */

void OpcodeHandler::opcode_ei() {
  cpu->interrupts_enabled = true;
}

/* RLC */

u8 OpcodeHandler::_opcode_rlc(u8 value) {
  u8 carry = value & (1U << 7U);

  u8 result = static_cast<u8>(value << 1U);
  result |= (carry);
  cpu->set_subtract(false);
  cpu->set_zero(result == 0U);
  cpu->set_half_carry(false);
  cpu->set_carry(carry);

  return result;
}

void OpcodeHandler::opcode_rlc(Register8 &target) {
  u8 result = _opcode_rlc(target.get());
  target.set(result);
}

void OpcodeHandler::opcode_rlc(Address target) {
  u8 result = _opcode_rlc(cpu->mem_ctrl->read(target));
  cpu->mem_ctrl->write(target, result);
}

void OpcodeHandler::opcode_rlca() {
  u8 a = (cpu->af.get() & 0xFF00U) >> 8U;
  u8 result = _opcode_rlc(a);
  cpu->af.set((result << 8U) | (cpu->af.get() & 0x00FFU));
  cpu->set_zero(false);
}

/* RRC */

u8 OpcodeHandler::_opcode_rrc(u8 value) {
  u8 carry = value & (1U);

  u8 result = static_cast<u8>(value >> 1U);
  result |= (carry << 7U);
  cpu->set_subtract(false);
  cpu->set_zero(result == 0U);
  cpu->set_half_carry(false);
  cpu->set_carry(carry);

  return result;
}

void OpcodeHandler::opcode_rrc(Register8 &target) {
  u8 result = _opcode_rrc(target.get());
  target.set(result);
}

void OpcodeHandler::opcode_rrc(Address target) {
  u8 result = _opcode_rrc(cpu->mem_ctrl->read(target));
  cpu->mem_ctrl->write(target, result);
}

void OpcodeHandler::opcode_rrca() {
  u8 a = (cpu->af.get() & 0xFF00U) >> 8U;
  u8 result = _opcode_rrc(a);
  cpu->af.set((result << 8U) | (cpu->af.get() & 0x00FFU));
  cpu->set_zero(false);
}

/* RL */

u8 OpcodeHandler::_opcode_rl(u8 value) {
  u8 carry = cpu->get_carry();

  bool check_carry = value & (1U << 7U);

  u8 result = static_cast<u8>(value << 1U);
  result |= carry;
  cpu->set_subtract(false);
  cpu->set_zero(result == 0U);
  cpu->set_half_carry(false);
  cpu->set_carry(check_carry);

  return result;
}

void OpcodeHandler::opcode_rl(Register8 &target) {
  u8 result = _opcode_rl(target.get());
  target.set(result);
}

void OpcodeHandler::opcode_rl(Address target) {
  u8 result = _opcode_rl(cpu->mem_ctrl->read(target));
  cpu->mem_ctrl->write(target, result);
}

void OpcodeHandler::opcode_rla() {
  u8 a = (cpu->af.get() & 0xFF00U) >> 8U;
  u8 result = _opcode_rl(a);
  cpu->af.set((result << 8U) | (cpu->af.get() & 0x00FFU));
  cpu->set_zero(false);
}

/* RR */

u8 OpcodeHandler::_opcode_rr(u8 value) {
  u8 carry = cpu->get_carry();

  bool check_carry = value & (1U);
  cpu->set_carry(check_carry);

  u8 result = static_cast<u8>(value >> 1U);

  if (carry) {
    result |= (1U << 7U);
  }
  cpu->set_subtract(false);
  cpu->set_zero(result == 0U);
  cpu->set_half_carry(false);

  return result;
}

void OpcodeHandler::opcode_rr(Register8 &target) {
  u8 result = _opcode_rr(target.get());
  target.set(result);
}

void OpcodeHandler::opcode_rr(Address target) {
  u8 result = _opcode_rr(cpu->mem_ctrl->read(target));
  cpu->mem_ctrl->write(target, result);
}

void OpcodeHandler::opcode_rra() {
  u8 a = (cpu->af.get() & 0xFF00U) >> 8U;
  u8 result = _opcode_rr(a);
  cpu->af.set((result << 8U) | (cpu->af.get() & 0x00FFU));
  cpu->set_zero(false);
}

/* SLA */

u8 OpcodeHandler::_opcode_sla(u8 value) {
  u8 carry_bit = value & (1U << 7U);

  u8 result = static_cast<u8>(value << 1U);
  cpu->set_subtract(false);
  cpu->set_zero(result == 0U);
  cpu->set_half_carry(false);
  cpu->set_carry(carry_bit);

  return result;
}

void OpcodeHandler::opcode_sla(Register8 &target) {
  u8 result = _opcode_sla(target.get());
  target.set(result);
}

void OpcodeHandler::opcode_sla(Address target) {
  u8 result = _opcode_sla(cpu->mem_ctrl->read(target));
  cpu->mem_ctrl->write(target, result);
}

/* SRA */

u8 OpcodeHandler::_opcode_sra(u8 value) {
  u8 carry_bit = value & (1U);
  u8 top_bit = value & (1U << 7U);

  u8 result = static_cast<u8>(value >> 1U);
  result |= (top_bit << 7U);
  cpu->set_subtract(false);
  cpu->set_zero(result == 0U);
  cpu->set_half_carry(false);
  cpu->set_carry(carry_bit);

  return result;
}

void OpcodeHandler::opcode_sra(Register8 &target) {
  u8 result = _opcode_sra(target.get());
  target.set(result);
}

void OpcodeHandler::opcode_sra(Address target) {
  u8 result = _opcode_sra(cpu->mem_ctrl->read(target));
  cpu->mem_ctrl->write(target, result);
}

/* SWAP */

u8 OpcodeHandler::_opcode_swap(u8 value) {
  u8 lower_nibble = value & 0x0FU;
  u8 upper_nibble = (value & 0xF0U) >> 4U;

  u8 result = (lower_nibble << 4U) | (upper_nibble);
  cpu->set_subtract(false);
  cpu->set_zero(result == 0U);
  cpu->set_half_carry(false);
  cpu->set_carry(false);

  return result;
}

void OpcodeHandler::opcode_swap(Register8 &target) {
  u8 result = _opcode_swap(target.get());
  target.set(result);
}

void OpcodeHandler::opcode_swap(Address target) {
  u8 result = _opcode_swap(cpu->mem_ctrl->read(target));
  cpu->mem_ctrl->write(target, result);
}

/* SRL */

u8 OpcodeHandler::_opcode_srl(u8 value) {
  bool least_bit_set = (value & (1U)) == 1U;

  u8 result = (value >> 1U);
  cpu->set_subtract(false);
  cpu->set_zero(result == 0U);
  cpu->set_half_carry(false);
  cpu->set_carry(least_bit_set);

  return result;
}

void OpcodeHandler::opcode_srl(Register8 &target) {
  u8 result = _opcode_srl(target.get());
  target.set(result);
}

void OpcodeHandler::opcode_srl(Address target) {
  u8 result = _opcode_srl(cpu->mem_ctrl->read(target));
  cpu->mem_ctrl->write(target, result);
}

/* BIT */

void OpcodeHandler::opcode_bit(u8 bit, Register8 &target) {
  cpu->set_zero(!((target.get() & (1U << bit)) == 1U << bit));
  cpu->set_subtract(false);
  cpu->set_half_carry(true);
}

void OpcodeHandler::opcode_bit(u8 bit, Address target) {
  cpu->set_zero(!((cpu->mem_ctrl->read(target) & (1U << bit)) == 1U << bit));
  cpu->set_subtract(false);
  cpu->set_half_carry(true);
}

/* RES */

void OpcodeHandler::opcode_res(u8 bit, Register8 &target) {
  u8 result = (target.get()) & ~(1U << bit);
  target.set(result);
}

void OpcodeHandler::opcode_res(u8 bit, Address target) {
  u8 value = cpu->mem_ctrl->read(target);
  u8 result = (value) & ~(1U << bit);
  cpu->mem_ctrl->write(target, result);
}

/* SET */

void OpcodeHandler::opcode_set(u8 bit, Register8 &target) {
  u8 result = (target.get()) | (1U << bit);
  target.set(result);
}

void OpcodeHandler::opcode_set(u8 bit, Address target) {
  u8 value = cpu->mem_ctrl->read(target);
  u8 result = (value) | (1U << bit);
  cpu->mem_ctrl->write(target, result);
}
