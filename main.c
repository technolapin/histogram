#include <stdio.h>
#include <stdlib.h>

typedef struct Histogram
{
     float min;
     float max;
     int size;
     int lastest;
     int n_bins;
     int * entries;
     int * bins;
} Histogram;


// finds the first non-zero bin left of the given bin
int histo_bin_left_of(Histogram* histo, int bin)
{
     for (int i = bin-1; i >= 0; --i)
     {
	  if (histo->bins[i] > 0)
	       return i;
     }
     printf("ERROR: NO NON-ZERO BIN LEFT OF GIVEN BIN\n");
}

// finds the first non-zero bin right of the given bin
int histo_bin_right_of(Histogram* histo, int bin)
{
     for (int i = bin+1; i < histo->n_bins; ++i)
     {
	  if (histo->bins[i] > 0)
	       return i;
     }
     printf("ERROR: NO NON-ZERO BIN RIGHT OF GIVEN BIN\n");
}

int
histo_float_to_intern(Histogram* histo, float entry)
{
     return (int) ((entry-histo->min)/(histo->max-histo->min) * ((float) histo->n_bins));
}
float
histo_intern_to_float(Histogram* histo, int intern)
{
     return histo->min + ((float) intern)*(histo->max - histo->min)/((float) histo->n_bins);
}

Histogram
histo_new(int size, int n_bins, float min, float max)
{
     Histogram histo = {min, max, size, 0, n_bins, malloc(sizeof(int)*size), malloc(sizeof(int)*n_bins)};
     return histo;
}

// returns the index of the bin corresponding to that value
int
histo_get_bin(Histogram* histo, int value)
{
     return value;
}

void
histo_push_intern(Histogram* histo, int value)
{
     int i = histo->lastest;
     int old_value = histo->entries[i];
     histo->bins[histo_get_bin(histo, old_value)]--;
     histo->bins[histo_get_bin(histo, value)]++;
     histo->entries[i] = value;
     histo->lastest = (i+1) % histo->size;
}

void histo_push(Histogram* histo, float value)
{
     histo_push_intern(histo, histo_float_to_intern(histo, value));
}

void
histo_push_no_remove(Histogram* histo, int value)
{
     int i = histo->lastest;
     histo->entries[i] = value;
     histo->bins[histo_get_bin(histo, value)]++;
     histo->lastest = (i+1) % histo->size;
}

int
histo_stupid_median(Histogram* histo)
{
     int sum = 0;
     int i;
     for (i = 0; sum < (histo->size)/2; ++i)
     {
	  sum += histo->bins[i];
     }
     return histo_intern_to_float(histo, i-1);
}

void
histo_print(Histogram* histo)
{
     printf("ENTRIES: ");
     for (int i = 0; i < histo->size; ++i)
	  printf("%d ", histo->entries[i]);
     printf("\n");
     printf("BINS: ");
     for (int i = 0; i < histo->n_bins; ++i)
	  printf("%d ", histo->bins[i]);
     printf("\n");
     printf("MEDIAN: %d\n", histo_stupid_median(histo));
     printf("\n");
}



int
main(void)
{

     int size = 4;
     Histogram histo = histo_new(size, 10, 0., 10.);

     for (int i = 0; i < size; ++i)
	  histo_push_no_remove(&histo, 0);
     
     histo_print(&histo);
     histo_push(&histo, 1);
     histo_print(&histo);
     histo_push(&histo, 2);
     histo_print(&histo);
     histo_push(&histo, 1);
     histo_print(&histo);
     histo_push(&histo, 7);
     histo_print(&histo);
     histo_push(&histo, 4);
     histo_print(&histo);
     histo_push(&histo, 5);
     histo_print(&histo);
     histo_push(&histo, 0);
     histo_print(&histo);



     for (float f = 0.; f < 10.; f+=0.5)
     {
	  int i = histo_float_to_intern(&histo, f);
	  float f2 = histo_intern_to_float(&histo, f);
	  printf("%lf -> %d -> %lf\n", f, i, f2);
     }
     
     return 0;
}
