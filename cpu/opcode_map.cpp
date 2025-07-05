#include "gameboy.hpp"
#include "opcode_handler.hpp"

void OpcodeHandler::opcode_00() {
  opcode_nop();
}
void OpcodeHandler::opcode_01() {
  opcode_ld(gameboy->get_cpu().bc);
}
void OpcodeHandler::opcode_02() {
  opcode_ld(gameboy->get_cpu().bc.get(), gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_03() {
  opcode_inc(gameboy->get_cpu().bc);
}
void OpcodeHandler::opcode_04() {
  opcode_inc(gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_05() {
  opcode_dec(gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_06() {
  opcode_ld(gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_07() {
  opcode_rlca();
}
void OpcodeHandler::opcode_08() {
  u16 nn = gameboy->get_cpu().get_word_from_pc();
  opcode_ld(nn, gameboy->get_cpu().sp);
}
void OpcodeHandler::opcode_09() {
  opcode_add_hl(gameboy->get_cpu().bc);
}
void OpcodeHandler::opcode_0A() {
  opcode_ld(gameboy->get_cpu().af.get_hi_ref(), gameboy->get_cpu().bc.get());
}
void OpcodeHandler::opcode_0B() {
  opcode_dec(gameboy->get_cpu().bc);
}
void OpcodeHandler::opcode_0C() {
  opcode_inc(gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_0D() {
  opcode_dec(gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_0E() {
  opcode_ld(gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_0F() {
  opcode_rrca();
}
void OpcodeHandler::opcode_10() {
  opcode_stop();
}
void OpcodeHandler::opcode_11() {
  opcode_ld(gameboy->get_cpu().de);
}
void OpcodeHandler::opcode_12() {
  opcode_ld(gameboy->get_cpu().de.get(), gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_13() {
  opcode_inc(gameboy->get_cpu().de);
}
void OpcodeHandler::opcode_14() {
  opcode_inc(gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_15() {
  opcode_dec(gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_16() {
  opcode_ld(gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_17() {
  opcode_rla();
}
void OpcodeHandler::opcode_18() {
  opcode_jr();
}
void OpcodeHandler::opcode_19() {
  opcode_add_hl(gameboy->get_cpu().de);
}
void OpcodeHandler::opcode_1A() {
  opcode_ld(gameboy->get_cpu().af.get_hi_ref(), gameboy->get_cpu().de.get());
}
void OpcodeHandler::opcode_1B() {
  opcode_dec(gameboy->get_cpu().de);
}
void OpcodeHandler::opcode_1C() {
  opcode_inc(gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_1D() {
  opcode_dec(gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_1E() {
  opcode_ld(gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_1F() {
  opcode_rra();
}
void OpcodeHandler::opcode_20() {
  opcode_jr(Condition::NZ);
}
void OpcodeHandler::opcode_21() {
  opcode_ld(gameboy->get_cpu().hl);
}
void OpcodeHandler::opcode_22() {
  opcode_ldi(gameboy->get_cpu().hl.get(), gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_23() {
  opcode_inc(gameboy->get_cpu().hl);
}
void OpcodeHandler::opcode_24() {
  opcode_inc(gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_25() {
  opcode_dec(gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_26() {
  opcode_ld(gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_27() {
  opcode_daa();
}
void OpcodeHandler::opcode_28() {
  opcode_jr(Condition::Z);
}
void OpcodeHandler::opcode_29() {
  opcode_add_hl(gameboy->get_cpu().hl);
}
void OpcodeHandler::opcode_2A() {
  opcode_ldi(gameboy->get_cpu().af.get_hi_ref(), gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_2B() {
  opcode_dec(gameboy->get_cpu().hl);
}
void OpcodeHandler::opcode_2C() {
  opcode_inc(gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_2D() {
  opcode_dec(gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_2E() {
  opcode_ld(gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_2F() {
  opcode_cpl();
}
void OpcodeHandler::opcode_30() {
  opcode_jr(Condition::NC);
}
void OpcodeHandler::opcode_31() {
  opcode_ld(gameboy->get_cpu().sp.get());
}
void OpcodeHandler::opcode_32() {
  opcode_ldd(gameboy->get_cpu().hl.get(), gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_33() {
  opcode_inc(gameboy->get_cpu().sp.get());
}
void OpcodeHandler::opcode_34() {
  opcode_inc(gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_35() {
  opcode_dec(gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_36() {
  opcode_ld(gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_37() {
  opcode_scf();
}
void OpcodeHandler::opcode_38() {
  opcode_jr(Condition::C);
}
void OpcodeHandler::opcode_39() {
  opcode_add_hl(gameboy->get_cpu().sp);
}
void OpcodeHandler::opcode_3A() {
  opcode_ldd(gameboy->get_cpu().af.get_hi_ref(), gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_3B() {
  opcode_dec(gameboy->get_cpu().sp.get());
}
void OpcodeHandler::opcode_3C() {
  opcode_inc(gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_3D() {
  opcode_dec(gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_3E() {
  opcode_ld(gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_3F() {
  opcode_ccf();
}
void OpcodeHandler::opcode_40() {
  opcode_ld(gameboy->get_cpu().bc.get_hi_ref(), gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_41() {
  opcode_ld(gameboy->get_cpu().bc.get_hi_ref(), gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_42() {
  opcode_ld(gameboy->get_cpu().bc.get_hi_ref(), gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_43() {
  opcode_ld(gameboy->get_cpu().bc.get_hi_ref(), gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_44() {
  opcode_ld(gameboy->get_cpu().bc.get_hi_ref(), gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_45() {
  opcode_ld(gameboy->get_cpu().bc.get_hi_ref(), gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_46() {
  opcode_ld(gameboy->get_cpu().bc.get_hi_ref(), gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_47() {
  opcode_ld(gameboy->get_cpu().bc.get_hi_ref(), gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_48() {
  opcode_ld(gameboy->get_cpu().bc.get_lo_ref(), gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_49() {
  opcode_ld(gameboy->get_cpu().bc.get_lo_ref(), gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_4A() {
  opcode_ld(gameboy->get_cpu().bc.get_lo_ref(), gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_4B() {
  opcode_ld(gameboy->get_cpu().bc.get_lo_ref(), gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_4C() {
  opcode_ld(gameboy->get_cpu().bc.get_lo_ref(), gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_4D() {
  opcode_ld(gameboy->get_cpu().bc.get_lo_ref(), gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_4E() {
  opcode_ld(gameboy->get_cpu().bc.get_lo_ref(), gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_4F() {
  opcode_ld(gameboy->get_cpu().bc.get_lo_ref(), gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_50() {
  opcode_ld(gameboy->get_cpu().de.get_hi_ref(), gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_51() {
  opcode_ld(gameboy->get_cpu().de.get_hi_ref(), gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_52() {
  opcode_ld(gameboy->get_cpu().de.get_hi_ref(), gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_53() {
  opcode_ld(gameboy->get_cpu().de.get_hi_ref(), gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_54() {
  opcode_ld(gameboy->get_cpu().de.get_hi_ref(), gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_55() {
  opcode_ld(gameboy->get_cpu().de.get_hi_ref(), gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_56() {
  opcode_ld(gameboy->get_cpu().de.get_hi_ref(), gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_57() {
  opcode_ld(gameboy->get_cpu().de.get_hi_ref(), gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_58() {
  opcode_ld(gameboy->get_cpu().de.get_lo_ref(), gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_59() {
  opcode_ld(gameboy->get_cpu().de.get_lo_ref(), gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_5A() {
  opcode_ld(gameboy->get_cpu().de.get_lo_ref(), gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_5B() {
  opcode_ld(gameboy->get_cpu().de.get_lo_ref(), gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_5C() {
  opcode_ld(gameboy->get_cpu().de.get_lo_ref(), gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_5D() {
  opcode_ld(gameboy->get_cpu().de.get_lo_ref(), gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_5E() {
  opcode_ld(gameboy->get_cpu().de.get_lo_ref(), gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_5F() {
  opcode_ld(gameboy->get_cpu().de.get_lo_ref(), gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_60() {
  opcode_ld(gameboy->get_cpu().hl.get_hi_ref(), gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_61() {
  opcode_ld(gameboy->get_cpu().hl.get_hi_ref(), gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_62() {
  opcode_ld(gameboy->get_cpu().hl.get_hi_ref(), gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_63() {
  opcode_ld(gameboy->get_cpu().hl.get_hi_ref(), gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_64() {
  opcode_ld(gameboy->get_cpu().hl.get_hi_ref(), gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_65() {
  opcode_ld(gameboy->get_cpu().hl.get_hi_ref(), gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_66() {
  opcode_ld(gameboy->get_cpu().hl.get_hi_ref(), gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_67() {
  opcode_ld(gameboy->get_cpu().hl.get_hi_ref(), gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_68() {
  opcode_ld(gameboy->get_cpu().hl.get_lo_ref(), gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_69() {
  opcode_ld(gameboy->get_cpu().hl.get_lo_ref(), gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_6A() {
  opcode_ld(gameboy->get_cpu().hl.get_lo_ref(), gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_6B() {
  opcode_ld(gameboy->get_cpu().hl.get_lo_ref(), gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_6C() {
  opcode_ld(gameboy->get_cpu().hl.get_lo_ref(), gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_6D() {
  opcode_ld(gameboy->get_cpu().hl.get_lo_ref(), gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_6E() {
  opcode_ld(gameboy->get_cpu().hl.get_lo_ref(), gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_6F() {
  opcode_ld(gameboy->get_cpu().hl.get_lo_ref(), gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_70() {
  opcode_ld(gameboy->get_cpu().hl.get(), gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_71() {
  opcode_ld(gameboy->get_cpu().hl.get(), gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_72() {
  opcode_ld(gameboy->get_cpu().hl.get(), gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_73() {
  opcode_ld(gameboy->get_cpu().hl.get(), gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_74() {
  opcode_ld(gameboy->get_cpu().hl.get(), gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_75() {
  opcode_ld(gameboy->get_cpu().hl.get(), gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_76() {
  opcode_halt();
}
void OpcodeHandler::opcode_77() {
  opcode_ld(gameboy->get_cpu().hl.get(), gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_78() {
  opcode_ld(gameboy->get_cpu().af.get_hi_ref(), gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_79() {
  opcode_ld(gameboy->get_cpu().af.get_hi_ref(), gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_7A() {
  opcode_ld(gameboy->get_cpu().af.get_hi_ref(), gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_7B() {
  opcode_ld(gameboy->get_cpu().af.get_hi_ref(), gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_7C() {
  opcode_ld(gameboy->get_cpu().af.get_hi_ref(), gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_7D() {
  opcode_ld(gameboy->get_cpu().af.get_hi_ref(), gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_7E() {
  opcode_ld(gameboy->get_cpu().af.get_hi_ref(), gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_7F() {
  opcode_ld(gameboy->get_cpu().af.get_hi_ref(), gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_80() {
  opcode_add_a(gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_81() {
  opcode_add_a(gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_82() {
  opcode_add_a(gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_83() {
  opcode_add_a(gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_84() {
  opcode_add_a(gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_85() {
  opcode_add_a(gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_86() {
  opcode_add_a(gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_87() {
  opcode_add_a(gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_88() {
  opcode_adc(gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_89() {
  opcode_adc(gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_8A() {
  opcode_adc(gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_8B() {
  opcode_adc(gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_8C() {
  opcode_adc(gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_8D() {
  opcode_adc(gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_8E() {
  opcode_adc(gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_8F() {
  opcode_adc(gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_90() {
  opcode_sub(gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_91() {
  opcode_sub(gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_92() {
  opcode_sub(gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_93() {
  opcode_sub(gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_94() {
  opcode_sub(gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_95() {
  opcode_sub(gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_96() {
  opcode_sub(gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_97() {
  opcode_sub(gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_98() {
  opcode_sbc(gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_99() {
  opcode_sbc(gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_9A() {
  opcode_sbc(gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_9B() {
  opcode_sbc(gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_9C() {
  opcode_sbc(gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_9D() {
  opcode_sbc(gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_9E() {
  opcode_sbc(gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_9F() {
  opcode_sbc(gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_A0() {
  opcode_and(gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_A1() {
  opcode_and(gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_A2() {
  opcode_and(gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_A3() {
  opcode_and(gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_A4() {
  opcode_and(gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_A5() {
  opcode_and(gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_A6() {
  opcode_and(gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_A7() {
  opcode_and(gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_A8() {
  opcode_xor(gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_A9() {
  opcode_xor(gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_AA() {
  opcode_xor(gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_AB() {
  opcode_xor(gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_AC() {
  opcode_xor(gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_AD() {
  opcode_xor(gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_AE() {
  opcode_xor(gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_AF() {
  opcode_xor(gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_B0() {
  opcode_or(gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_B1() {
  opcode_or(gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_B2() {
  opcode_or(gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_B3() {
  opcode_or(gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_B4() {
  opcode_or(gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_B5() {
  opcode_or(gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_B6() {
  opcode_or(gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_B7() {
  opcode_or(gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_B8() {
  opcode_cp(gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_B9() {
  opcode_cp(gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_BA() {
  opcode_cp(gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_BB() {
  opcode_cp(gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_BC() {
  opcode_cp(gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_BD() {
  opcode_cp(gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_BE() {
  opcode_cp(gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_BF() {
  opcode_cp(gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_C0() {
  opcode_ret(Condition::NZ);
}
void OpcodeHandler::opcode_C1() {
  opcode_pop(gameboy->get_cpu().bc);
}
void OpcodeHandler::opcode_C2() {
  opcode_jp(Condition::NZ);
}
void OpcodeHandler::opcode_C3() {
  opcode_jp();
}
void OpcodeHandler::opcode_C4() {
  opcode_call(Condition::NZ);
}
void OpcodeHandler::opcode_C5() {
  opcode_push(gameboy->get_cpu().bc);
}
void OpcodeHandler::opcode_C6() {
  opcode_add_a();
}
void OpcodeHandler::opcode_C7() {
  opcode_rst(rst::vector::rst_0x00);
}
void OpcodeHandler::opcode_C8() {
  opcode_ret(Condition::Z);
}
void OpcodeHandler::opcode_C9() {
  opcode_ret();
}
void OpcodeHandler::opcode_CA() {
  opcode_jp(Condition::Z);
}
void OpcodeHandler::opcode_CB() { /* External Ops */ }
void OpcodeHandler::opcode_CC() {
  opcode_call(Condition::Z);
}
void OpcodeHandler::opcode_CD() {
  opcode_call();
}
void OpcodeHandler::opcode_CE() {
  opcode_adc();
}
void OpcodeHandler::opcode_CF() {
  opcode_rst(rst::vector::rst_0x08);
}
void OpcodeHandler::opcode_D0() {
  opcode_ret(Condition::NC);
}
void OpcodeHandler::opcode_D1() {
  opcode_pop(gameboy->get_cpu().de);
}
void OpcodeHandler::opcode_D2() {
  opcode_jp(Condition::NC);
}
void OpcodeHandler::opcode_D3() { /* Undefined */ }
void OpcodeHandler::opcode_D4() {
  opcode_call(Condition::NC);
}
void OpcodeHandler::opcode_D5() {
  opcode_push(gameboy->get_cpu().de);
}
void OpcodeHandler::opcode_D6() {
  opcode_sub();
}
void OpcodeHandler::opcode_D7() {
  opcode_rst(rst::vector::rst_0x10);
}
void OpcodeHandler::opcode_D8() {
  opcode_ret(Condition::C);
}
void OpcodeHandler::opcode_D9() {
  opcode_reti();
}
void OpcodeHandler::opcode_DA() {
  opcode_jp(Condition::C);
}
void OpcodeHandler::opcode_DB() { /* Undefined */ }
void OpcodeHandler::opcode_DC() {
  opcode_call(Condition::C);
}
void OpcodeHandler::opcode_DD() { /* Undefined */ }
void OpcodeHandler::opcode_DE() {
  opcode_sbc();
}
void OpcodeHandler::opcode_DF() {
  opcode_rst(rst::vector::rst_0x18);
}
void OpcodeHandler::opcode_E0() {
  opcode_ldh_into_data();
}
void OpcodeHandler::opcode_E1() {
  opcode_pop(gameboy->get_cpu().hl);
}
void OpcodeHandler::opcode_E2() {
  opcode_ldh_into_c();
}
void OpcodeHandler::opcode_E3() { /* Undefined */ }
void OpcodeHandler::opcode_E4() { /* Undefined */ }
void OpcodeHandler::opcode_E5() {
  opcode_push(gameboy->get_cpu().hl);
}
void OpcodeHandler::opcode_E6() {
  opcode_and();
}
void OpcodeHandler::opcode_E7() {
  opcode_rst(rst::vector::rst_0x20);
}
void OpcodeHandler::opcode_E8() {
  opcode_add_sp();
}
void OpcodeHandler::opcode_E9() {
  opcode_jp(gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_EA() {
  opcode_ld_to_addr(gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_EB() { /* Undefined */ }
void OpcodeHandler::opcode_EC() { /* Undefined */ }
void OpcodeHandler::opcode_ED() { /* Undefined */ }
void OpcodeHandler::opcode_EE() {
  opcode_xor();
}
void OpcodeHandler::opcode_EF() {
  opcode_rst(rst::vector::rst_0x28);
}
void OpcodeHandler::opcode_F0() {
  opcode_ldh_into_a();
}
void OpcodeHandler::opcode_F1() {
  opcode_pop(gameboy->get_cpu().af);
}
void OpcodeHandler::opcode_F2() {
  opcode_ldh_c_into_a();
}
void OpcodeHandler::opcode_F3() {
  opcode_di();
}
void OpcodeHandler::opcode_F4() { /* Undefined */ }
void OpcodeHandler::opcode_F5() {
  opcode_push(gameboy->get_cpu().af);
}
void OpcodeHandler::opcode_F6() {
  opcode_or();
}
void OpcodeHandler::opcode_F7() {
  opcode_rst(rst::vector::rst_0x30);
}
void OpcodeHandler::opcode_F8() {
  opcode_ldhl();
}
void OpcodeHandler::opcode_F9() {
  opcode_ld(gameboy->get_cpu().sp.get(), gameboy->get_cpu().hl);
}
void OpcodeHandler::opcode_FA() {
  opcode_ld_from_addr(gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_FB() {
  opcode_ei();
}
void OpcodeHandler::opcode_FC() { /* Undefined */ }
void OpcodeHandler::opcode_FD() { /* Undefined */ }
void OpcodeHandler::opcode_FE() {
  opcode_cp();
}
void OpcodeHandler::opcode_FF() {
  opcode_rst(rst::vector::rst_0x38);
}

/**
 * This section contains two-byte opcodes, which are triggered when prefixed with
 * the CB instruction above.
 */

void OpcodeHandler::opcode_CB_00() {
  opcode_rlc(gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_CB_01() {
  opcode_rlc(gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_CB_02() {
  opcode_rlc(gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_CB_03() {
  opcode_rlc(gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_CB_04() {
  opcode_rlc(gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_CB_05() {
  opcode_rlc(gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_CB_06() {
  opcode_rlc(gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_CB_07() {
  opcode_rlc(gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_CB_08() {
  opcode_rrc(gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_CB_09() {
  opcode_rrc(gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_CB_0A() {
  opcode_rrc(gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_CB_0B() {
  opcode_rrc(gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_CB_0C() {
  opcode_rrc(gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_CB_0D() {
  opcode_rrc(gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_CB_0E() {
  opcode_rrc(gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_CB_0F() {
  opcode_rrc(gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_CB_10() {
  opcode_rl(gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_CB_11() {
  opcode_rl(gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_CB_12() {
  opcode_rl(gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_CB_13() {
  opcode_rl(gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_CB_14() {
  opcode_rl(gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_CB_15() {
  opcode_rl(gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_CB_16() {
  opcode_rl(gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_CB_17() {
  opcode_rl(gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_CB_18() {
  opcode_rr(gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_CB_19() {
  opcode_rr(gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_CB_1A() {
  opcode_rr(gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_CB_1B() {
  opcode_rr(gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_CB_1C() {
  opcode_rr(gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_CB_1D() {
  opcode_rr(gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_CB_1E() {
  opcode_rr(gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_CB_1F() {
  opcode_rr(gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_CB_20() {
  opcode_sla(gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_CB_21() {
  opcode_sla(gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_CB_22() {
  opcode_sla(gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_CB_23() {
  opcode_sla(gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_CB_24() {
  opcode_sla(gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_CB_25() {
  opcode_sla(gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_CB_26() {
  opcode_sla(gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_CB_27() {
  opcode_sla(gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_CB_28() {
  opcode_sra(gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_CB_29() {
  opcode_sra(gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_CB_2A() {
  opcode_sra(gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_CB_2B() {
  opcode_sra(gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_CB_2C() {
  opcode_sra(gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_CB_2D() {
  opcode_sra(gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_CB_2E() {
  opcode_sra(gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_CB_2F() {
  opcode_sra(gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_CB_30() {
  opcode_swap(gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_CB_31() {
  opcode_swap(gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_CB_32() {
  opcode_swap(gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_CB_33() {
  opcode_swap(gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_CB_34() {
  opcode_swap(gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_CB_35() {
  opcode_swap(gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_CB_36() {
  opcode_swap(gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_CB_37() {
  opcode_swap(gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_CB_38() {
  opcode_srl(gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_CB_39() {
  opcode_srl(gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_CB_3A() {
  opcode_srl(gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_CB_3B() {
  opcode_srl(gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_CB_3C() {
  opcode_srl(gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_CB_3D() {
  opcode_srl(gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_CB_3E() {
  opcode_srl(gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_CB_3F() {
  opcode_srl(gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_CB_40() {
  opcode_bit(0, gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_CB_41() {
  opcode_bit(0, gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_CB_42() {
  opcode_bit(0, gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_CB_43() {
  opcode_bit(0, gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_CB_44() {
  opcode_bit(0, gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_CB_45() {
  opcode_bit(0, gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_CB_46() {
  opcode_bit(0, gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_CB_47() {
  opcode_bit(0, gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_CB_48() {
  opcode_bit(1, gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_CB_49() {
  opcode_bit(1, gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_CB_4A() {
  opcode_bit(1, gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_CB_4B() {
  opcode_bit(1, gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_CB_4C() {
  opcode_bit(1, gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_CB_4D() {
  opcode_bit(1, gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_CB_4E() {
  opcode_bit(1, gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_CB_4F() {
  opcode_bit(1, gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_CB_50() {
  opcode_bit(2, gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_CB_51() {
  opcode_bit(2, gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_CB_52() {
  opcode_bit(2, gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_CB_53() {
  opcode_bit(2, gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_CB_54() {
  opcode_bit(2, gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_CB_55() {
  opcode_bit(2, gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_CB_56() {
  opcode_bit(2, gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_CB_57() {
  opcode_bit(2, gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_CB_58() {
  opcode_bit(3, gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_CB_59() {
  opcode_bit(3, gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_CB_5A() {
  opcode_bit(3, gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_CB_5B() {
  opcode_bit(3, gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_CB_5C() {
  opcode_bit(3, gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_CB_5D() {
  opcode_bit(3, gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_CB_5E() {
  opcode_bit(3, gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_CB_5F() {
  opcode_bit(3, gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_CB_60() {
  opcode_bit(4, gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_CB_61() {
  opcode_bit(4, gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_CB_62() {
  opcode_bit(4, gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_CB_63() {
  opcode_bit(4, gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_CB_64() {
  opcode_bit(4, gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_CB_65() {
  opcode_bit(4, gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_CB_66() {
  opcode_bit(4, gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_CB_67() {
  opcode_bit(4, gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_CB_68() {
  opcode_bit(5, gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_CB_69() {
  opcode_bit(5, gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_CB_6A() {
  opcode_bit(5, gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_CB_6B() {
  opcode_bit(5, gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_CB_6C() {
  opcode_bit(5, gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_CB_6D() {
  opcode_bit(5, gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_CB_6E() {
  opcode_bit(5, gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_CB_6F() {
  opcode_bit(5, gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_CB_70() {
  opcode_bit(6, gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_CB_71() {
  opcode_bit(6, gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_CB_72() {
  opcode_bit(6, gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_CB_73() {
  opcode_bit(6, gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_CB_74() {
  opcode_bit(6, gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_CB_75() {
  opcode_bit(6, gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_CB_76() {
  opcode_bit(6, gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_CB_77() {
  opcode_bit(6, gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_CB_78() {
  opcode_bit(7, gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_CB_79() {
  opcode_bit(7, gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_CB_7A() {
  opcode_bit(7, gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_CB_7B() {
  opcode_bit(7, gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_CB_7C() {
  opcode_bit(7, gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_CB_7D() {
  opcode_bit(7, gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_CB_7E() {
  opcode_bit(7, gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_CB_7F() {
  opcode_bit(7, gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_CB_80() {
  opcode_res(0, gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_CB_81() {
  opcode_res(0, gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_CB_82() {
  opcode_res(0, gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_CB_83() {
  opcode_res(0, gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_CB_84() {
  opcode_res(0, gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_CB_85() {
  opcode_res(0, gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_CB_86() {
  opcode_res(0, gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_CB_87() {
  opcode_res(0, gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_CB_88() {
  opcode_res(1, gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_CB_89() {
  opcode_res(1, gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_CB_8A() {
  opcode_res(1, gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_CB_8B() {
  opcode_res(1, gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_CB_8C() {
  opcode_res(1, gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_CB_8D() {
  opcode_res(1, gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_CB_8E() {
  opcode_res(1, gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_CB_8F() {
  opcode_res(1, gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_CB_90() {
  opcode_res(2, gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_CB_91() {
  opcode_res(2, gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_CB_92() {
  opcode_res(2, gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_CB_93() {
  opcode_res(2, gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_CB_94() {
  opcode_res(2, gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_CB_95() {
  opcode_res(2, gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_CB_96() {
  opcode_res(2, gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_CB_97() {
  opcode_res(2, gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_CB_98() {
  opcode_res(3, gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_CB_99() {
  opcode_res(3, gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_CB_9A() {
  opcode_res(3, gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_CB_9B() {
  opcode_res(3, gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_CB_9C() {
  opcode_res(3, gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_CB_9D() {
  opcode_res(3, gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_CB_9E() {
  opcode_res(3, gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_CB_9F() {
  opcode_res(3, gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_CB_A0() {
  opcode_res(4, gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_CB_A1() {
  opcode_res(4, gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_CB_A2() {
  opcode_res(4, gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_CB_A3() {
  opcode_res(4, gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_CB_A4() {
  opcode_res(4, gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_CB_A5() {
  opcode_res(4, gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_CB_A6() {
  opcode_res(4, gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_CB_A7() {
  opcode_res(4, gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_CB_A8() {
  opcode_res(5, gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_CB_A9() {
  opcode_res(5, gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_CB_AA() {
  opcode_res(5, gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_CB_AB() {
  opcode_res(5, gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_CB_AC() {
  opcode_res(5, gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_CB_AD() {
  opcode_res(5, gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_CB_AE() {
  opcode_res(5, gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_CB_AF() {
  opcode_res(5, gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_CB_B0() {
  opcode_res(6, gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_CB_B1() {
  opcode_res(6, gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_CB_B2() {
  opcode_res(6, gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_CB_B3() {
  opcode_res(6, gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_CB_B4() {
  opcode_res(6, gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_CB_B5() {
  opcode_res(6, gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_CB_B6() {
  opcode_res(6, gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_CB_B7() {
  opcode_res(6, gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_CB_B8() {
  opcode_res(7, gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_CB_B9() {
  opcode_res(7, gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_CB_BA() {
  opcode_res(7, gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_CB_BB() {
  opcode_res(7, gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_CB_BC() {
  opcode_res(7, gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_CB_BD() {
  opcode_res(7, gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_CB_BE() {
  opcode_res(7, gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_CB_BF() {
  opcode_res(7, gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_CB_C0() {
  opcode_set(0, gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_CB_C1() {
  opcode_set(0, gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_CB_C2() {
  opcode_set(0, gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_CB_C3() {
  opcode_set(0, gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_CB_C4() {
  opcode_set(0, gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_CB_C5() {
  opcode_set(0, gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_CB_C6() {
  opcode_set(0, gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_CB_C7() {
  opcode_set(0, gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_CB_C8() {
  opcode_set(1, gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_CB_C9() {
  opcode_set(1, gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_CB_CA() {
  opcode_set(1, gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_CB_CB() {
  opcode_set(1, gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_CB_CC() {
  opcode_set(1, gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_CB_CD() {
  opcode_set(1, gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_CB_CE() {
  opcode_set(1, gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_CB_CF() {
  opcode_set(1, gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_CB_D0() {
  opcode_set(2, gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_CB_D1() {
  opcode_set(2, gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_CB_D2() {
  opcode_set(2, gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_CB_D3() {
  opcode_set(2, gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_CB_D4() {
  opcode_set(2, gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_CB_D5() {
  opcode_set(2, gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_CB_D6() {
  opcode_set(2, gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_CB_D7() {
  opcode_set(2, gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_CB_D8() {
  opcode_set(3, gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_CB_D9() {
  opcode_set(3, gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_CB_DA() {
  opcode_set(3, gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_CB_DB() {
  opcode_set(3, gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_CB_DC() {
  opcode_set(3, gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_CB_DD() {
  opcode_set(3, gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_CB_DE() {
  opcode_set(3, gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_CB_DF() {
  opcode_set(3, gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_CB_E0() {
  opcode_set(4, gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_CB_E1() {
  opcode_set(4, gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_CB_E2() {
  opcode_set(4, gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_CB_E3() {
  opcode_set(4, gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_CB_E4() {
  opcode_set(4, gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_CB_E5() {
  opcode_set(4, gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_CB_E6() {
  opcode_set(4, gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_CB_E7() {
  opcode_set(4, gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_CB_E8() {
  opcode_set(5, gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_CB_E9() {
  opcode_set(5, gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_CB_EA() {
  opcode_set(5, gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_CB_EB() {
  opcode_set(5, gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_CB_EC() {
  opcode_set(5, gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_CB_ED() {
  opcode_set(5, gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_CB_EE() {
  opcode_set(5, gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_CB_EF() {
  opcode_set(5, gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_CB_F0() {
  opcode_set(6, gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_CB_F1() {
  opcode_set(6, gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_CB_F2() {
  opcode_set(6, gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_CB_F3() {
  opcode_set(6, gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_CB_F4() {
  opcode_set(6, gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_CB_F5() {
  opcode_set(6, gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_CB_F6() {
  opcode_set(6, gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_CB_F7() {
  opcode_set(6, gameboy->get_cpu().af.get_hi_ref());
}
void OpcodeHandler::opcode_CB_F8() {
  opcode_set(7, gameboy->get_cpu().bc.get_hi_ref());
}
void OpcodeHandler::opcode_CB_F9() {
  opcode_set(7, gameboy->get_cpu().bc.get_lo_ref());
}
void OpcodeHandler::opcode_CB_FA() {
  opcode_set(7, gameboy->get_cpu().de.get_hi_ref());
}
void OpcodeHandler::opcode_CB_FB() {
  opcode_set(7, gameboy->get_cpu().de.get_lo_ref());
}
void OpcodeHandler::opcode_CB_FC() {
  opcode_set(7, gameboy->get_cpu().hl.get_hi_ref());
}
void OpcodeHandler::opcode_CB_FD() {
  opcode_set(7, gameboy->get_cpu().hl.get_lo_ref());
}
void OpcodeHandler::opcode_CB_FE() {
  opcode_set(7, gameboy->get_cpu().hl.get());
}
void OpcodeHandler::opcode_CB_FF() {
  opcode_set(7, gameboy->get_cpu().af.get_hi_ref());
}
