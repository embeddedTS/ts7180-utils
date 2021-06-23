#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <unistd.h>
#include <gpiod.h>

#include "ispvm.h"

struct gpiod_chip *chip;
struct gpiod_line *line_tck;
struct gpiod_line *line_tms;
struct gpiod_line *line_tdi;
struct gpiod_line *line_tdo;

#define CONSUMER "load_fpga"

void sclock_ts7180()
{
	gpiod_line_set_value(line_tck, 1);
	gpiod_line_set_value(line_tck, 0);
}

int readport_ts7180(void)
{
	return gpiod_line_get_value(line_tdo);
}

void writeport_ts7180(int pins, int val)
{
	if(pins & g_ucPinTDI)
		gpiod_line_set_value(line_tdi, val);
	if(pins & g_ucPinTMS)
		gpiod_line_set_value(line_tms, val);
	if(pins & g_ucPinTCK)
		gpiod_line_set_value(line_tck, val);
}

void init_ts7180(void)
{
	int ret;
	chip = gpiod_chip_open_by_number(2);
	assert(chip);
	line_tck = gpiod_chip_get_line(chip, 1);
	line_tms = gpiod_chip_get_line(chip, 2);
	line_tdi = gpiod_chip_get_line(chip, 3);
	line_tdo = gpiod_chip_get_line(chip, 24);
	assert(line_tck && line_tms && line_tdi && line_tdo);

	ret = gpiod_line_request_output(line_tck, CONSUMER, 1);
	ret |= gpiod_line_request_output(line_tms, CONSUMER, 1);
	ret |= gpiod_line_request_output(line_tdi, CONSUMER, 1);
	ret |= gpiod_line_request_input(line_tdo, CONSUMER);
	assert(!ret);
}

void restore_ts7180(void)
{
	gpiod_line_release(line_tck);
	gpiod_line_release(line_tms);
	gpiod_line_release(line_tdo);
	gpiod_line_release(line_tdi);
	gpiod_chip_close(chip);
}

void udelay_imx6(unsigned int us)
{
	usleep(us);
	return;
}
