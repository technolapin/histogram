#include <stdio.h>
#include <stdlib.h>

#include "histogram.h"

int
main(void)
{

     int size = 5;
     Histogram histo = histo_new(size, 10, -10., 10.);

      histo_print(&histo);
     for (int i = 0; i < 40; ++i){
      histo_print(&histo);
     histo_push(&histo, 1);
      histo_print(&histo); printf("MED: %lf\n", histo_smart_median(&histo));
     histo_push(&histo, 2);
      histo_print(&histo); printf("MED: %lf\n", histo_smart_median(&histo));
     histo_push(&histo, 1);
      histo_print(&histo); printf("MED: %lf\n", histo_smart_median(&histo));
     histo_push(&histo, 7);
      histo_print(&histo); printf("MED: %lf\n", histo_smart_median(&histo));
     histo_push(&histo, 4);
      histo_print(&histo); printf("MED: %lf\n", histo_smart_median(&histo));
     histo_push(&histo, 5);
      histo_print(&histo); printf("MED: %lf\n", histo_smart_median(&histo));
     histo_push(&histo, 0);
      histo_print(&histo); printf("MED: %lf\n", histo_smart_median(&histo));
     }

     histo_free(&histo);
     return 0;
}
