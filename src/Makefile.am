tshwctl_SOURCES = tshwctl.c fpga.c
tshwctl_LDFLAGS = -lm -Wall

load_fpga_SOURCES = load_fpga-ts7180.c load_fpga.c -o load_fpga ispvm.c
load_fpga_LDFLAGS = -mcpu=cortex-a9 -lgpiod -Wall

silabs_SOURCES = silabs.c

get_opt_SOURCES = get-opt.c fpga.c

bin_PROGRAMS = tshwctl load_fpga silabs get-opt
