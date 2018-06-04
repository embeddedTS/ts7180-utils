#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <assert.h>
#include <string.h>

#include "fpga.h"

static int twifd;

int get_model()
{
   FILE *proc;
   char mdl[256];
   char *ptr;

   proc = fopen("/proc/device-tree/model", "r");
   if (!proc) {
      perror("model");
      return 0;
   }
   fread(mdl, 256, 1, proc);
   ptr = strstr(mdl, "TS-");
   return strtoull(ptr+3, NULL, 16);
}

void usage(char **argv) {
   fprintf(stderr,
      "Usage: %s [OPTIONS] ...\n"
      "Technologic Systems PWM Utility\n"
      "\n"

      "\n",
      argv[0]
   );
}

int main(int argc, char **argv)
{
   volatile unsigned int *pwmregs;
   int devmem, model, i;

   static struct option long_options[] = {

      { "help", 0, 0, 'h' },
      { 0, 0, 0, 0 }
   };


   model = get_model();

   printf("model=%04X\n", model);

   twifd = fpga_init();

   if(twifd == -1) {
      perror("Can't open FPGA I2C bus");
      return 1;
   }

   devmem = open("/dev/mem", O_RDWR|O_SYNC);
   if (devmem < 0) {
      fprintf(stderr, "Error:  Can't open /dev/mem\n");
      return 1;
   }

   pwmregs = (unsigned int *) mmap(0, 4096,
        PROT_READ | PROT_WRITE, MAP_SHARED, devmem, 0x020f0000);

   if (pwmregs == MAP_FAILED) {
        fprintf(stderr, "Error:  Can't mmap PWM registers\n");
      return 1;
   }

       printf("pwmregs = 0x%08X\n", pwmregs);

   fflush(stdout);
   sleep(3);

   for(i=0; i < 6; i++) {
      printf("0x%08X\n", pwmregs[i]);
   }

   close(twifd);

   return 0;
}
