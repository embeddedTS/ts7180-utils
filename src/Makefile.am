tshwctl_SOURCES = tshwctl.c fpga.c
tshwctl_LDFLAGS = -lm

load_fpga_SOURCES = load_fpga-ts7180.c load_fpga.c -o load_fpga gpiolib-fast.c ispvm.c
load_fpga_LDFLAGS = -mcpu=cortex-a9

silabs_SOURCES = silabs.c

get_opt_SOURCES = get-opt.c fpga.c

bin_PROGRAMS = tshwctl load_fpga silabs get-opt
