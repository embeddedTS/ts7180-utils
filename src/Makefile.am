tshwctl_SOURCES = tshwctl.c fpga.c
tshwctl_LDFLAGS = -lm

load_fpga_SOURCES = load_fpga-ts7180.c load_fpga.c -o load_fpga gpiolib-fast.c ispvm.c
load_fpga_LDFLAGS = -mcpu=cortex-a9

tsmicroctl_SOURCES = tsmicroctl.c
tsmicroctl_CPPFLAGS = -DCTL

get_opt_SOURCES = get-opt.c fpga.c

bin_PROGRAMS = tshwctl load_fpga tsmicroctl get-opt
