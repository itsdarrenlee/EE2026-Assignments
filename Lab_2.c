#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define ARR_SIZE 100
#define MAX_ARR_VAL 11

/************************************

        FUNCTION DECLARATION

*************************************/

int flip(); // flip counter
void rand_no_generator(int arr[], int range); // fill up input array with random values
int max(int arr[], int range); // find max no from input array
int min(int arr[], int range); // find min no from input array
int zero_counter(int arr[], int range); // count no of zeroes in input array
void zero_indices_count(int arr[], int range); // print location of zeroes in input array
int first_half_count(int arr[], int range); // count no of zeroes in first half of input array
int second_half_count(int arr[], int range); // count no of zeroes in second half of input array
int zero_bias_count(int arr[], int zero_arr[], int range); // count no of negative values in input array, update input array to zero array, change neg values in zero arr to zero
void array_print(int arr[], int range); // print the values of input array
float percent_diff(int a, int b, int range); // calculate % difference for a and b
void comparator(int first_no, int second_no, int first_half, int sec_half); // print signal with more zeroes
int diff_print(int a, int b); // returns diff between a and b


/************************************

        MAIN FUNCTION

*************************************/


int main(void)
{
    // function for generating rand
    srand((unsigned int)time(NULL));

    /***********

    PART I, SIGNAL A

    **********/

    /***** SIGNAL GENERATION *****/

    //initializing array to store random numbers
    int Signal_A[ARR_SIZE];

    // executing rand number generator
    rand_no_generator(Signal_A, ARR_SIZE);

    /***** MAX AND MIN SEARCH OPERATION *****/

    // Finding max and min values by linear search with O(n) time complexity
    int max_a, min_a;
    max_a = max(Signal_A, ARR_SIZE);
    min_a = min(Signal_A, ARR_SIZE);
    printf("Min: %d\n", min_a);
    printf("Max: %d\n", max_a);

    /***** ZERO COUNT OPERATION *****/

    // print indices where value is 0 for array signal a
    printf("Zero at indices: ");
    zero_indices_count(Signal_A, ARR_SIZE);
    printf("\n");

    // print total no of zeroes for array signal a
    int signal_a_zeroes = zero_counter(Signal_A, ARR_SIZE);
    printf("Total zero count = %d\n", signal_a_zeroes);

    // print total no of zeroes for first half for array signal a
    int first_half_zeroes_a = first_half_count(Signal_A, ARR_SIZE);
    printf("Total zero count_A_0_49 = %d\n", first_half_zeroes_a);

    // print total no of zeroes for second half for array signal a
    int second_half_zeroes_a = second_half_count(Signal_A, ARR_SIZE);
    printf("Total zero count_A_50_99 = %d\n", second_half_zeroes_a);


    /***** FILTERING OPERATION *****/

    // creating a new array called zero bias a
    int Zero_Bias_A[ARR_SIZE];

    // copy values of signal a to zero bias a, print total no of neg values in array zero bias a, update neg values to become 0
    printf("Number of negative values: %d\n", zero_bias_count(Signal_A, Zero_Bias_A, ARR_SIZE));

    // print array zero bias a
    array_print(Zero_Bias_A, ARR_SIZE);
    printf("\n==========================\n\n");

    /***********

    PART II, SIGNAL B

    **********/

    //initializing array to store random numbers
    int Signal_B[ARR_SIZE];

    // executing rand number generator
    rand_no_generator(Signal_B, ARR_SIZE);

    /***** MAX AND MIN SEARCH OPERATION *****/

    // Finding max and min values by linear search with O(n) time complexity
    int max_b, min_b;
    max_b = max(Signal_B, ARR_SIZE);
    min_b = min(Signal_B, ARR_SIZE);
    printf("Min: %d\n", min_b);
    printf("Max: %d\n", max_b);

    /***** ZERO COUNT OPERATION *****/

    // print indices where value is 0 for array signal b
    printf("Zero at indices: ");
    zero_indices_count(Signal_B, ARR_SIZE);
    printf("\n");

    // print total no of zeroes for array signal b
    int signal_b_zeroes = zero_counter(Signal_B, ARR_SIZE);
    printf("Total zero count = %d\n", signal_b_zeroes);

    // print total no of zeroes for first half for array signal b
    int first_half_zeroes_b = first_half_count(Signal_B, ARR_SIZE);
    printf("Total zero count_A_0_49 = %d\n", first_half_zeroes_b);

    // print total no of zeroes for second half for array signal b
    int second_half_zeroes_b = second_half_count(Signal_B, ARR_SIZE);
    printf("Total zero count_A_50_99 = %d\n", second_half_zeroes_b);


    /***** FILTERING OPERATION *****/

    // creating a new array called zero bias b
    int Zero_Bias_B[ARR_SIZE];

    // copy values of signal b to zero bias b, print total no of neg values in array zero bias b, update neg values to become 0
    printf("Number of negative values: %d\n", zero_bias_count(Signal_B, Zero_Bias_B, ARR_SIZE));

    // print array zero bias b
    array_print(Zero_Bias_B, ARR_SIZE);
    printf("\n==========================\n\n");

    /*****

    PART I

    *****/

    // printing % difference in zero counts for signal a and b to 2 decimal figures
    printf("Zero counts of Signal A and Signal B differ by: ");
    printf("%.2f%%\n", percent_diff(signal_a_zeroes, signal_b_zeroes, ARR_SIZE));

    /*****

    PART II

    *****/

    // comparing first half and second half zero count of signal a and b
    comparator(first_half_zeroes_a, first_half_zeroes_b, 0, 49);
    comparator(second_half_zeroes_a, second_half_zeroes_b, 50, 99);

    /*****

    PART III

    *****/
    // printing difference between max and min values of signal a and b
    printf("Difference between minimum values of signal A and signal B is %d\n", diff_print(min_a, min_b));
    printf("Difference between maximum values of signal A and signal B is %d\n", diff_print(max_a, max_b));

return 0;
}



/************************************

        SUB FUNCTIONS

*************************************/


int flip()
{
    int coin = rand() % 2; // modulo of rand will gen either 1, or 0
    if (coin == 0)
        return 0;
    else
        return 1;
}

void rand_no_generator(int arr[], int range)
{
    /* Generate random numbers in the ARR_SIZE specified*/
    for (int i = 0; i < range; i++)
    {
        // toss a coin here
        int toss = flip();

        // print negative number if heads
        if (toss > 0)
        {
            arr[i] = (-1) * (rand() % MAX_ARR_VAL);
        }
        // print positive number if tails
        else
        {
            arr[i] = (rand() % MAX_ARR_VAL);
        }
    }
    array_print(arr, ARR_SIZE);
}


int max(int arr[], int range)
{
    int max = 0;

    for (int i = 0; i < range; i++)
    {
        if (arr[i] > max) // check if current array value > max
        max = arr[i]; // set max to new current array if true
    }
    return max; // return max
}

int min(int arr[], int range)
{
    int min = 0;

    for (int i = 0; i < range; i++)
    {
        if (arr[i] < min) // check if current array value < min
        min = arr[i]; // set min to new current array if true
    }
    return min; // return min
}


int zero_counter(int arr[], int range)
{
    int count = 0;
    for (int i = 0; i < range; i++)
    {
      if (arr[i] == 0) // check if current array value == 0
      {
        count += 1; // add 1 to count
      }
    }
    return count; // return count
}

void zero_indices_count(int arr[], int range)
{
    int count = 0;
    for (int i = 0; i < range; i++)
    {
      if (arr[i] == 0) // check if current array value == 0
      {
         printf("%d, ", i); // print current i value
      }
    }
}

int first_half_count(int arr[], int range)
{
  int count = 0;
  for (int i = 0; i < (range / 2); i++) // only take up to first half
  {
    if (arr[i] == 0) // check if current array value == 0
    {
      count += 1; // add 1 to count
    }
  }
  return count; // return count
}

int second_half_count(int arr[], int range)
{
  int count = 0;
  for (int i = (range / 2); i < range; i++) // only take from first half
  {
    if (arr[i] == 0) // check if current array value == 0
    {
      count += 1; // add 1 to count
    }
  }
  return count; // return count
}

int zero_bias_count(int arr[], int zero_arr[], int range)
{
  int count = 0;
  for (int i = 0; i < range; i++)
  {
    // set empty array zero_arr to be identical to normal array
    zero_arr[i] = arr[i];
  }

  for (int i = 0; i < range; i++)
  {
    if (zero_arr[i] < 0) // check if zero array value is negative
    {
      count += 1; // add 1 to count
      zero_arr[i] = 0; // set negative value to 0
    }
  }
  return count; // return count
}

void array_print(int arr[], int range)
{
    printf("["); // print left square bracket

    for (int i = 0; i < range; i++)
    {
      printf("%d", arr[i]); // print array value
        if (i != range - 1) // check if current i is NOT range - 1
          printf(" "); // print space
        else
          printf("]\n"); // else print close square bracket
    }
}

float percent_diff(int a, int b, int range)
{
  // create float: percent_a/percent_b, divide a typecasted a by range,
  // multiply final answer by 100
  float percent_a = ((float)a / range) * 100;
  float percent_b = ((float)b / range) * 100;

  return fabs(percent_a - percent_b); // take floating absolute of difference
}

void comparator(int first_no, int second_no, int first_half, int sec_half)
{
  if (first_no > second_no) // check if more zeroes for first input
    printf("Signal A has more zeroes from interval %d to %d\n", first_half, sec_half);
  else if (first_no < second_no) // check if more zeroes for second input
    printf("Signal B has more zeroes from interval %d to %d\n", first_half, sec_half);
  else // else both have the same no of zeroes
    printf("Signal A has the same number of zeroes as Signal B from interval %d to %d\n", first_half, sec_half);
}

int diff_print(int a, int b)
{
  return abs(a-b); // print absolute value of difference between input a & b
}
