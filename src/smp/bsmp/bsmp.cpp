#include "../../base.h"

#include "core/core.cpp"
#include "memory/memory.cpp"
#include "timing/timing.cpp"

void bSMP::run() {
  exec();
}

void bSMP::power() {
  memset(spcram, 0x00, 65536);
  reset();
}

void bSMP::reset() {
  regs.pc = 0xffc0;
  regs.a  = 0x00;
  regs.x  = 0x00;
  regs.y  = 0x00;
  regs.sp = 0xef;
  regs.p  = 0x02;

  status.cycle_pos       = 0;
  status.clocks_executed = 0;

//$f1
  status.iplrom_enabled = true;

  t0.enabled = false;
  t1.enabled = false;
  t2.enabled = false;

  t0.stage1_ticks = 0;
  t1.stage1_ticks = 0;
  t2.stage1_ticks = 0;

  t0.stage2_ticks = 0;
  t1.stage2_ticks = 0;
  t2.stage2_ticks = 0;

  t0.stage3_ticks = 0;
  t1.stage3_ticks = 0;
  t2.stage3_ticks = 0;
}

bSMP::bSMP() {
  init_op_table();

  t0.cycle_frequency = 128; //1.024mhz /  8khz = 128
  t1.cycle_frequency = 128; //1.024mhz /  8khz = 128
  t2.cycle_frequency =  16; //1.024mhz / 64khz =  16

//targets not initialized/changed upon reset
  t0.target = 0;
  t1.target = 0;
  t2.target = 0;
}

bSMP::~bSMP() {}