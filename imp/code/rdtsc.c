#include <inttypes.h> /* PRIu64 */
#include <unistd.h> /* usleep */
#include <stdio.h>
#include "rdtsc.h"

#define MILLION 1000L*1000L

/* return the cycle count */
void chefio_time(chefioTime* t) {
  *t = _rdtsc(); //intel intrinsic
}
/* determine the reference clock frequency */
size_t chefio_getCyclesPerMicroSec() {
  const size_t usec = 5*MILLION;
  size_t cpus, cycles;
  chefioTime t0, t1; 
  chefio_time(&t0);
  /* Testing on Theta indicates that 5s is long enough
   * to get a stable value for the reference frequency.
   */
  usleep(usec);
  chefio_time(&t1);
  cycles = t1 - t0; 
  cpus = ((double)cycles)/(usec);
  fprintf(stderr, "cycles %" PRIu64 " us %" PRIu64 " cycles per micro second %" PRIu64"\n", cycles, usec, cpus);
  return cpus;
}
/*return elapsed time in micro seconds*/
size_t chefio_time_diff(chefioTime* start, chefioTime* end, size_t cpus) {
  size_t cycles = *end - *start;
  size_t us = ((double)cycles)/cpus;
  return us; 
}

