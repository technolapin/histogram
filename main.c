#include <stdio.h>
#include <stdlib.h>

typedef struct Histogram
{
     float min; // min value containable
     float max; // max value containable
     int size; // capacity
     int lastest; // oldest inserted value
     int n_bins; // number of bins
     int median_bin; // the bin containing the median
     int left; // the count of values left of the median
     int right; // the count of values right of the median
     int * entries; // the entries
     int * bins; // the bins
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
     Histogram histo = {min, max, size, 0, n_bins, 0, 0, 0, malloc(sizeof(int)*size), malloc(sizeof(int)*n_bins)};
     histo.bins[0] = size;
     return histo;
}

void
histo_decrease(Histogram* histo, int bin)
{
     histo->bins[bin]--;

     if (bin < histo->median_bin)
	  histo->left--;
     if (bin > histo->median_bin)
	  histo->right--;

     int m = (histo->size + 1)/2;
     if (histo->left >= m)
     {
	  int left_bin = histo_bin_left_of(histo, histo->median_bin);
	  histo->right += histo->bins[histo->median_bin];
	  histo->left -= histo->bins[left_bin];
	  histo->median_bin = left_bin;
     }
     else if (histo->left + histo->bins[histo->median_bin] < m)
     {
	  int right_bin = histo_bin_right_of(histo, histo->median_bin);
	  histo->left += histo->bins[histo->median_bin];
	  histo->right -= histo->bins[right_bin];
	  histo->median_bin = right_bin;
	  
     }
     

}

void
histo_increase(Histogram* histo, int bin)
{
     histo->bins[bin]++;

     if (bin < histo->median_bin)
	  histo->left++;
     if (bin > histo->median_bin)
	  histo->right++;


     int m = (histo->size + 1)/2;
     if (histo->left >= m)
     {
	  int left_bin = histo_bin_left_of(histo, histo->median_bin);
	  histo->right += histo->bins[histo->median_bin];
	  histo->left -= histo->bins[left_bin];
	  histo->median_bin = left_bin;
     }
     else if (histo->left + histo->bins[histo->median_bin] < m)
     {
	  int right_bin = histo_bin_right_of(histo, histo->median_bin);
	  histo->left += histo->bins[histo->median_bin];
	  histo->right -= histo->bins[right_bin];
	  histo->median_bin = right_bin;
	  
     }

}

void
histo_push_intern(Histogram* histo, int bin)
{
     int i = histo->lastest;
     int old_bin = histo->entries[i];
     histo_decrease(histo, old_bin);
     histo_increase(histo, bin);
     histo->entries[i] = bin;
     histo->lastest = (i+1) % histo->size;
}

void histo_push(Histogram* histo, float value)
{
     histo_push_intern(histo, histo_float_to_intern(histo, value));
}

float
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
     printf("MEDIAN: %lf\n", histo_stupid_median(histo));
     printf("QUICK MEDIAN: %lf\n", histo_intern_to_float(histo, histo->median_bin));
     printf("\n");
}



int
main(void)
{

     int size = 4;
     Histogram histo = histo_new(size, 20, -10., 10.);

     histo_print(&histo);
     for (int i = 0; i < size; ++i)
	  histo_push(&histo, 0);
     for (int i = 0; i < 40; ++i){
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
     }
     return 0;
}
