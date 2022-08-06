#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include <verilated_fst_c.h>
#include "Voneshot.h"

#define MAX_SIM       100
vluint64_t sim_unit = 0;
vluint64_t sim_time = 0;

uint8_t btn_state = 0;
uint8_t stable    = 0;
uint8_t stable_q  = 0;

void dut_clock(Voneshot *dut, VerilatedFstC *vtrace);
void set_random(Voneshot *dut);
void get_expected(Voneshot *dut);
void monitor_proc(Voneshot *dut);
void monitor_outputs(Voneshot *dut);

void initial(Voneshot *dut) {
}

void dut_clock(Voneshot *dut, VerilatedFstC *vtrace) {
  sim_time = sim_unit * 10 + 2;
  if (vtrace)
    vtrace->dump(sim_time); // Dump values to update inputs

  sim_time = sim_time + 3;
  dut->clk_i = 0;
  dut->eval();
  if (vtrace)
    vtrace->dump(sim_time); // Dump values after negedge

  monitor_outputs(dut);        // Values are "stable" to monitor

  sim_time = sim_time + 5;
  dut->clk_i = 1;
  dut->eval();
  if (vtrace) {
    vtrace->dump(sim_time); // Dump values after posedge
    //vtrace->flush();
  }
}

void set_random(Voneshot *dut) {
  dut->btn_i = rand()%2;
  dut->eval();
}

void get_expected(Voneshot *dut) {
  if (dut->btn_i)
    if (btn_state)
      stable = 0;
    else {
      btn_state = 1;
      stable = 1;
    }
  else {
    btn_state = 0;
    stable = 0;
  }
}

void monitor_proc(Voneshot *dut) {
  // One FSM DFF
  stable_q = stable;
}

void monitor_outputs(Voneshot *dut) {
  printf("@%3d: ", sim_unit);
  printf("RECV %1x : ", dut->stb_o);
  printf("EXPE %1x ", stable_q);

  if (stable_q == dut->stb_o)
    printf("\n");
  else
    printf("<= FAIL\n");
}

int main(int argc, char **argv, char **env) {
	// Call commandArgs first!
	Verilated::commandArgs(argc, argv);

  // Instantiate the design
	Voneshot *dut = new Voneshot;

  // Trace generating
  Verilated::traceEverOn(true);
  VerilatedFstC *vtrace = new VerilatedFstC;
  dut->trace(vtrace, 2); // trace down to 2 hierarchy
  vtrace->open("oneshot.fst");
  vtrace->dump(0);

  // Initial setups
  srand(time(NULL));
  initial(dut);
  dut->eval();

  // Check procedure
  while (sim_unit < MAX_SIM){
    dut_clock(dut, vtrace);
    set_random(dut);
    monitor_proc(dut);
    get_expected(dut);
    sim_unit++;
	}

  vtrace->close();
  delete dut;
  exit(EXIT_SUCCESS);
}
