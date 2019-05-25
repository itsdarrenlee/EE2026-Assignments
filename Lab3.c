#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

struct mydevice
{
    float cost;     // $10 to $50
    int cpu_cores;  // number of cores- 2 to 8- only even number of cores
    float current_rating;   // current 2 to 5mAmp
    float power_rating;     // power: 10 to 20 mJ
    int quantity;   // current stock - 0 to 10
};

#define ARR_SIZE 100// global constant for array of structure size
#define FIRST_5_DEVICES 5 // global constant for first 5 devices

// function declaration for questions
void Device_DB(struct mydevice * ptr);
void Printf_DB(struct mydevice* ptr);
void Search_Costly_Device(struct mydevice * ptr);
void Stock_Check(struct mydevice * ptr);

// sub function declaration
int int_range_rand(int higher, int lower);
float float_range_rand(float lower, float higher);

/************************************

            MAIN FUNCTION

*************************************/

int main(void)
{

    srand((unsigned int)time(NULL)); // function for generating rand

    struct mydevice database[100]; // array to hold 100 devices as type struct

    struct mydevice * my_db_ptr = NULL; // pointer to array of struct, set to NULL

    my_db_ptr = database; // direct my_db_ptr to point to array of structures

    Device_DB(my_db_ptr); // fill in values of array via Device_DB

    Printf_DB(my_db_ptr); // print values of array via Printf_DB

    Search_Costly_Device(my_db_ptr); //scrape through array of structures, return 1 if device > $30

    Stock_Check(my_db_ptr); //scrape through array of structures, return 1 if device qty < 5

}

/************************************

        QUESTION FUNCTIONS

*************************************/

void Device_DB(struct mydevice* ptr)
{
    for (int i = 0; i < ARR_SIZE; i++)
    {
      // Random setting of cost from $10 to $50
      ptr->cost = float_range_rand(10.00, 50.00);

      // Random setting of cpu_cores from 2 to 8, only even numbers
      int k = int_range_rand(2, 8);
      while (k % 2 != 0)
      {
        int m = rand() % 2; // modulo 2 rand() will result in only 0 or 1
        if (m == 1)
          k += 1; // increment k if m = 1
        else
          k -= 1; // decrement k if m != 1
      }
      ptr->cpu_cores = k; // input cpu_core values in struct

      // Random setting of current_rating from 2 to 5mAmp
      ptr->current_rating = float_range_rand(2.00, 5.00);

      // Random setting of power_rating from 10 to 20mJ
      ptr->power_rating = float_range_rand(10.00, 20.00);

      // Random setting of quantity from 0 to 10
      ptr->quantity = int_range_rand(0, 10);

      ptr++; // increment pointer to point at next struct in array
    }
}

void Printf_DB(struct mydevice* ptr)
{
  for (int i = 0; i < FIRST_5_DEVICES; i++)
  {
    // access and prints value in struct via "->" operator
    printf("The cost of device %d is: $%.2f.\n", i, ptr->cost); // prints cost of device
    printf("Device %d has: %d cpu cores.\n", i, ptr->cpu_cores); // prints cpu cores of device
    printf("The current rating of device %d is: %.3f mAmp.\n", i, ptr->current_rating); // prints current rating of device
    printf("The power rating of device %d is: %.3f mJ.\n", i, ptr->power_rating); // prints power rating of device
    printf("The total quantity of device %d is: %d.\n", i, ptr->quantity); // prints quantity of device
    printf("----------\n"); // prints out --- for easier viewing

    ptr++; // increment pointer to point at next struct in array
  }
}

void Search_Costly_Device(struct mydevice * ptr)
{
  printf("Devices: ");
  for (int i = 0; i < ARR_SIZE; i++)
  {

    if (ptr->cost > 30.00) // access cost field of struct, check if > $30
      printf("%d, ", i);

    ptr++; // increment pointer to point at next struct in array
  }
  printf("cost less than $30.\n\n");
}

void Stock_Check(struct mydevice * ptr)
{
  for (int i = 0; i < ARR_SIZE; i++)
  {
    // switch statement for checking if for quantities below 55
    switch(ptr->quantity) {
      case 0:
        printf("Device %d has a quantity of 0.\n", i);
        break;
      case 1:
        printf("Device %d has a quantity of 1.\n", i);
        break;
      case 2:
        printf("Device %d has a quantity of 2.\n", i);
        break;
      case 3:
        printf("Device %d has a quantity of 3.\n", i);
        break;
      case 4:
        printf("Device %d has a quantity of 4.\n", i);
        break;
      default: // if quantity is not any of the above cases, break out of switch statement
        break;
    }
  ptr++; // increment pointer to point at next struct in array
  }
}

/************************************

        SUB FUNCTIONS

*************************************/

int int_range_rand(int lower, int higher)
{
    // rand() % (max_number + 1 - minimum_number) + minimum_number
    return rand() % (higher + 1 - lower) + lower; // to obtain randomized integer value
}

float float_range_rand(float lower, float higher)
{
    // cast rand() to double, divide value by RAND_MAX (also casted to double). Float final result to get random float value
    float k = ((float)((double) rand() /(double)RAND_MAX));

    // return float no in range between higher and lower
    return lower + k * (higher - lower);
}
