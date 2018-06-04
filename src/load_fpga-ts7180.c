#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <inttypes.h>

#include "ispvm.h"
#include "gpiolib-fast.h"

volatile uint32_t *mx6gpio;

#define TDI			1<<3
#define TCK			1<<1
#define TMS			1<<2
#define TDO			1<<24

void sclock_ts7180()
{
	mx6gpio[(MX6_GPIO_BANK3 + GPDR)/4] |= TCK;
	mx6gpio[(MX6_GPIO_BANK3 + GPDR)/4] &= ~(TCK);
}

int readport_ts7180(void)
{
	return (mx6gpio[(MX6_GPIO_BANK3 + GPPSR)/4] & TDO) ? 1 : 0;
}

void writeport_ts7180(int pins, int val)
{
	uint8_t value = 0;
	if(pins & g_ucPinTDI)
		value |= TDI;
	if(pins & g_ucPinTCK)
		value |= TCK;
	if(pins & g_ucPinTMS)
		value |= TMS;

	if(val) {
		mx6gpio[(MX6_GPIO_BANK3 + GPDR)/4] |= value;
	} else {
		mx6gpio[(MX6_GPIO_BANK3 + GPDR)/4] &= ~value;
	}
}

void init_ts7180(void)
{
	mx6gpio = gpiofast_init();
	assert(mx6gpio != 0);

	mx6gpio[(MX6_GPIO_BANK3 + GPGDIR)/4] |= TCK | TDI | TMS;
	mx6gpio[(MX6_GPIO_BANK3 + GPGDIR)/4] &= ~(TDO);
	mx6gpio[(MX6_GPIO_BANK3 + GPDR)/4] |= TCK | TDI | TMS;
}

void restore_ts7180(void)
{
	mx6gpio[(MX6_GPIO_BANK3 + GPGDIR)/4] &= ~(TDI | TCK | TMS);
}

void udelay_imx6(unsigned int us)
{
	usleep(us);
	return;
}
