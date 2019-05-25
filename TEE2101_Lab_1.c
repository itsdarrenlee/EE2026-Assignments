// Q1
// this code will calculate the area and perimeter of a circle from a user provided radius.
// PI is defined to be 3.14159

#include <stdio.h>

#define PI 3.14f
#define rad 0.59 // changed include to define

int main() {

    // variable declaration
    float area, perm; // removed declaration for rad because it is a defined global constant

    // prompt user for radius input
    printf("radius of circle: %f\n", rad); // included an extra "

    // calculate area and perimeter
    area=PI*rad*rad;
    perm=2*PI*rad; // set the p of perm to lowercase

    // output of area and perimeter
    printf("Area of circle: %f \nPerimeter of circle: %f\n", area, perm);
    return 0;
}

// Q2
/* This code will calculate the capacitance of a capacitor as the area of the plates A and
the distance between the plates d increase, for up to 5 iterations */

#include <stdio.h>
#include <math.h>

#define EP (8.54 * pow(10,-12)) // define permittivity of free space as a global constant

int main() {

    // initial variable declaration
    float distance, area, cap_value, initial_cap, percent_loss;

    distance = 0.4; // user defined
    area = 0.44; // user defined
    cap_value = (1 * EP * area)/distance; // calculate capacitance
    initial_cap = cap_value; // variable to keep track of initial capacitance

    // print output
    printf("Value of Epsilion: %12.6e\n\n", EP);
    printf("Current value of distance=%f\n", distance);
    printf("Current value of Area=%f\n", area);
    printf("Cap value = %11.5e farads with d = %.4f m, A=%.5f m^2\n", cap_value, distance, area);
    printf("===============\n\n");

    // recompute output
    distance = distance * 1.10;
    area = area * 1.05;
    cap_value = (1 * EP * area)/distance;

    printf("Current value of distance=%f\n", distance);
    printf("Current value of Area=%f\n", area);
    printf("Cap value = %11.5e farads with d = %.4f m, A=%.5f m^2\n", cap_value, distance, area);
    printf("===============\n\n");

    distance = distance * 1.10;
    area = area * 1.05;
    cap_value = (1 * EP * area)/distance;

    printf("Current value of distance=%f\n", distance);
    printf("Current value of Area=%f\n", area);
    printf("Cap value = %11.5e farads with d = %.4f m, A=%.5f m^2\n", cap_value, distance, area);
    printf("===============\n\n");

    distance = distance * 1.10;
    area = area * 1.05;
    cap_value = (1 * EP * area)/distance;

    printf("Current value of distance=%f\n", distance);
    printf("Current value of Area=%f\n", area);
    printf("Cap value = %11.5e farads with d = %.4f m, A=%.5f m^2\n", cap_value, distance, area);
    printf("===============\n\n");

    distance = distance * 1.10;
    area = area * 1.05;
    cap_value = (1 * EP * area)/distance;

    printf("Current value of distance=%f\n", distance);
    printf("Current value of Area=%f\n", area);
    printf("Cap value = %11.5e farads with d = %.4f m, A=%.5f m^2\n", cap_value, distance, area);
    printf("===============\n\n");

    distance = distance * 1.10;
    area = area * 1.05;
    cap_value = (1 * EP * area)/distance;

    printf("Current value of distance=%f\n", distance);
    printf("Current value of Area=%f\n", area);
    printf("Cap value = %11.5e farads with d = %.4f m, A=%.5f m^2\n", cap_value, distance, area);

    // calculate percent loss comparing initial capacitance and current capacitance value
    percent_loss = ((initial_cap - cap_value) / initial_cap) * 100;
    printf("Percentage loss in Cap=%.6f with 10 percent cumulative increase in d and 5 percent cummulative increase in A\n", percent_loss);

return 0;
}

// Q3
/* this code will calculate length of given string, printing it out in normal and reversed
orientation */

#include <stdio.h>
#include <string.h>

char str[21] = "MALAYALAM"; // user defined string

int main() {

    // variable declaration
    int str_length;

    // determine string length & printing
    str_length = strlen(str);
    printf("%s %d\n", str, str_length);

    // print string in reverse
    printf("%s", _strrev(str));

    printf("\n");

    return 0;
}
