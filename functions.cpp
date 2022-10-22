#include "functions.h"

double get_determinant(double *array, int n)
{
    return array[0] * (array[n + 1] * array[n * 2 + 2] - array[n + 2] * array[n * 2 + 1])
         - array[1] * (array[n] * array[n * 2 + 2] - array[n + 2] * array[n * 2])
         + array[2] * (array[n] * array[n * 2 + 1] - array[n * 2] * array[n + 1]);
}

int doublecmp(double number1, double number2)
{
    return abs(number1 - number2) <= 0.0001 ? 0 : number1 > number2 ? 1 : -1;
}

std::pair<double, double> solve_quadtratic(double a, double b, double c)
{
    double D = pow(b, 2) - 4 * a * c;
        
    if(doublecmp(D, 0) < 0)
    {
        return {NAN, NAN};
    } 

    else 
    {
        D = sqrt(D);
        
        if (doublecmp(D, 0) == 0)
        {
            double coeff = (-b + D) / 2 / a;

            return {coeff, coeff};
        }

        else
        {
            double coeff_1 = (-b + D) / 2 / a;
            double coeff_2 = (-b - D) / 2 / a;     

            return {coeff_1, coeff_2};
        }
    }
}