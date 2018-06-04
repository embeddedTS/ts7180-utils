#ifndef _LOAD_FPGA_TS7180_
#define _LOAD_FPGA_TS7180_

#include <stdint.h>

void init_ts7180(void);
void restore_ts7180(void);
int readport_ts7180(void);
void writeport_ts7180(int pins, int val);
void sclock_ts7180(void);
void udelay_imx6(unsigned int us);

#endif