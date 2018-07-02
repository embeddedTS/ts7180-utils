#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <assert.h>

#include "fpga.h"

#define GPIO_3_BASE	0x020a4000
#define IOMUXC_BASE 0x020e0000

static int twifd;


int main(void)
{
	int devmem;
	int r31, r36, r37, r38;
	unsigned int original_pad_lcd_data18,
		original_pad_lcd_data22,
		original_mux_lcd_data18,
		original_mux_lcd_data22,
		original_gpio_gdir_3;

	volatile unsigned int *gpio_3_base;
	volatile unsigned int *iomuxc_base;

	if((twifd=fpga_init()) == -1) {
		perror("Can't open FPGA I2C bus");
		return 1;
	}

	devmem = open("/dev/mem", O_RDWR|O_SYNC);
	assert(devmem != -1);

	gpio_3_base = (unsigned int *) mmap(0, 4096,
	  PROT_READ | PROT_WRITE, MAP_SHARED, devmem, GPIO_3_BASE);

	if (gpio_3_base == MAP_FAILED) {
		fprintf(stderr, "Can't mmap gpio registers\n");
		exit(1);
	}


	iomuxc_base = (unsigned int *) mmap(0, 4096,
	  PROT_READ | PROT_WRITE, MAP_SHARED, devmem, IOMUXC_BASE);

	if (iomuxc_base == MAP_FAILED) {
		fprintf(stderr, "Can't mmap iomuxc registers\n");
		exit(1);
	}

	original_pad_lcd_data18 = iomuxc_base[0x3ec / 4];
	original_mux_lcd_data18 = iomuxc_base[0x160 / 4];

	original_pad_lcd_data22 = iomuxc_base[0x3fc / 4];
	original_mux_lcd_data22 = iomuxc_base[0x170 / 4];


	iomuxc_base[0x3ec / 4] = 0x0001b020;
	iomuxc_base[0x160 / 4] = 5;

	iomuxc_base[0x3fc / 4] = 0x0001b020;
	iomuxc_base[0x170 / 4] = 5;

	r31 = r36 = r37 = r38 = 0;

	original_gpio_gdir_3 = gpio_3_base[4 / 4];

	gpio_3_base[4 / 4] &= ~((1 << 23) | (1 << 27));	// make these pins inputs

	if (gpio_3_base[8 / 4] & (1 << 23))	// lcd_data18
		r38 = 1;

	if (gpio_3_base[8 / 4] & (1 << 27))	// lcd_data22
		r31 = 1;

	if (fpeek8(twifd, 47) & 4)
		r36 = 1;

	if (fpeek8(twifd, 48) & 4)
		r37 = 1;

	printf("R31=%d\nR36=%d\nR37=%d\nR38=%d\n",
		r31, r36, r37, r38);

	// restore it all....

	gpio_3_base[4 / 4] = original_gpio_gdir_3;

	iomuxc_base[0x3ec / 4] = original_pad_lcd_data18;
	iomuxc_base[0x160 / 4] = original_mux_lcd_data18;

	iomuxc_base[0x3fc / 4] = original_pad_lcd_data22;
	iomuxc_base[0x170 / 4] = original_mux_lcd_data22;

	return 0;
}