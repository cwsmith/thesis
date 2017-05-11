#ifndef RDTSC_H
#define RDTSC_H
#include <stdlib.h>
typedef size_t chefioTime;
/* return the cycle count */
void chefio_time(chefioTime* t);
/* determine the reference clock frequency */
size_t chefio_getCyclesPerMicroSec();
/* return elapsed time in micro seconds*/
size_t chefio_time_diff(chefioTime* start, chefioTime* end, size_t cpus);
#endif
