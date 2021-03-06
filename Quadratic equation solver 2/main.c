#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <float.h>
#include <assert.h>
#include "unitTest.c"

/**
 *  @file
 *  @brief Main program file
 *  @author KMSprojects
 */

/** @defgroup const_strings Messages used in program
    @{
 */
const char *MSG_INCORRECT_COEFFICIENT = "This can't be coefficient. Give me normal coefficient:\n";     /**< Message displayed when an invalid coefficient is entered (isn't a number) */
const char *MSG_INFINITY_OF_ROOTS = "Equation has infinity of roots\n";                                 /**< Message displayed when equation has an infinite number of roots */
const char *MSG_NO_ROOTS = "Equation has no roots\n";                                                   /**< Message displayed if the equation hasn't got any roots */
const char *MSG_INCORRECT_CANCULATIONS = "Something went wrong with calculations\n";                    /**< Message displayed when the given number of roots is not determined by the program */
const char *MSG_ENTER_INSTRUCTION = "Give me coefficients of your equation ( ax2 + bx + c = 0):\n\n";   /**< Message displayed when user should enter coefficients of equation */
///@}

const int INFINITY_ = -1;/**< Determine of infinity number of roots (because always number of roots >= 0) */

/** @defgroup root_precision Precision of calculations
    @{
 */
const int ROOT_PRECISION_EXP = 6;/**< Count of digits after point in output */
const double ROOT_PRECISION = pow(0.1, ROOT_PRECISION_EXP + 1);/**< Precision with which the roots of the equation are calculated */
///@}


//QE - Quadratic Equation
void getCoefsOfQE (double *a, double *b, double *c);
int getRootsOfQE (double a, double b, double c, double *x1, double *x2);
void printRootsOfQE (int, double x1, double x2);
int iszero (double value);

/** @brief The main function
 *  @return always 0
 *  This function calls the functions of accepting coefficients, calculating roots and outputting the result.
 *  Also obtained coefficients and calculated roots are stored there.
 */
int main()
{
//    unitTest((int (*)(double, double, double, double*, double*))getRootsOfQE);

    double a = NAN, b = NAN, c = NAN;

    getCoefsOfQE (&a, &b, &c);

    int rCount = 0;
    double x1 = NAN, x2 = NAN;

    rCount = getRootsOfQE (a, b, c, &x1, &x2);

    printRootsOfQE (rCount, x1, x2);

    return 0;
}

/** @brief Gets one coefficient from input
 *
 *  @param [out] coeff Entered coefficient
 *  @param [in] name Name of coefficient, which user see
 *
 *  Function ask user to enter coefficient while it won't be number
 */
void getCoef (double *coeff, char name)
{
    assert (coeff);

    int noCoeff = true;
    while (noCoeff)
    {
        printf ("%c = ", name);
        if(!scanf ("%lf", coeff) || getchar() != '\n')
        {
            printf (MSG_INCORRECT_COEFFICIENT);
            while (getchar() != '\n')
                ;
        }
        else
            noCoeff = false;
    }
}

/** @brief Checks if a number is zero
 *
 * @param [in] value value to check
 * @return is value zero
 *
 * This function checks if @f$ |value| < 1 @f$ and then checks if \f$ |value|\cdot \f$ max bound of double \f$ <1 \f$ , else returns 0
 */
int iszero (double value)
{
    return (fabs (value) < 1) && (fabs (value * DBL_MAX) < 1);
}

/** @brief Gets coefficients from input
 *
 * @param [out] a, b, c coefficients of quadratic equation
 *
 * Function print @link MSG_ENTER_INSTRUCTION @endlink and three times call getCoef()
 */
void getCoefsOfQE (double *a, double *b, double *c)
{
    printf ("%s", MSG_ENTER_INSTRUCTION);
    getCoef (a, 'a');
    getCoef (b, 'b');
    getCoef (c, 'c');
}

/** @brief Calculate roots of quadratic equation
*
* @param [in] a, b, c coefficients of quadratic equation
* @param [out] x1, x2 roots of quadratic equation
* @return count of roots
*
* At first function calculate \f$ D \f$ - discriminant (\f$ D = b^2 - 4\cdot a\cdot c\f$). \n \n
* Then @b if \f$ D < 0 \f$ equation haven't got roots; \n \n
* @b If \f$ D < ( 2\cdot x\cdot \varepsilon)^2 \f$ @b
* \f$ \left( \text{that is we check} \dfrac{\sqrt{D}}{2\cdot a} < \varepsilon \right) \f$
* it can get \f$ c = 0 \f$ and calculate \f$ x = - \dfrac{d}{2\cdot a} \f$; \n \n
*
* @b If \f$ \left| a\cdot c^2 \right| < \varepsilon \cdot \left| b^3 \right| \f$
* \f$ \left( \text{that is we check} \left| \dfrac{a\cdot c^2}{b^3} \right| < \varepsilon \right) \f$
* it can get \f$ a = 0 \f$ and calculate \f$ x = - \dfrac{c}{b} \f$ which is easy to prove; \n \n
*
* @b If \f$ b = 0 \f$ it is return if \f$ c = 0 \f$ 0 else \link _INFINITY \endlink \n \n
*
* @b in @b other @b cases it calculate \f$ x_1 = \dfrac{- b - \sqrt D}{2\cdot a} \f$ , \f$ x_2 = \dfrac{- b + \sqrt D}{2\cdot a} \f$ \n \n
* (\f$ \varepsilon = \f$ \link ROOT_PRECISION \endlink)
 */
int getRootsOfQE (double a, double b, double c, double *x1, double *x2)
{
    assert (isfinite (a));
    assert (isfinite (b));
    assert (isfinite (c));

    assert (x1);
    assert (x2);

    double D = b * b - 4 * a * c;

    if (D < 0)
        return 0;

    // Check if sqrt (D) / (2 * a) < ROOT_PRECISION
    else if (D < pow(2 * a * ROOT_PRECISION, 2))
    {
        *x1 = -b / (2 * a);
        return 1;
    }
    else
    {
        //Check, can we calculate x1 = -c / b, using Taylor expansion
        if (fabs(a * c * c) < fabs(ROOT_PRECISION * b * b * b))
        {
            *x1 = -c / b;
            return 1;
        }
        else if (iszero(b))
        {
            return (iszero (c))? INFINITY_ : 0;
        }
        else
        {
            *x1 = (-b - sqrt(D)) / (2 * a);
            *x2 = (-b + sqrt(D)) / (2 * a);
            return 2;
        }
    }
}

/** @brief Print answer
 *
 * @param [in] rCount count of roots
 * @param [in] x1, x2 roots
 *
 * If \link rCount \endlink \f$ = 1 \f$ , it get \f$ x \f$ from \f$ x_1 \f$
 */
void printRootsOfQE (int rCount, double x1, double x2)
{
    assert (isfinite (x1));
    assert (isfinite (x2));

    switch (rCount)
    {
    case INFINITY_:
        printf ("%s", MSG_INFINITY_OF_ROOTS);
        break;
    case 0:
        printf ("%s", MSG_NO_ROOTS);
        break;
    case 1:
        printf ("x = %.*e\n", ROOT_PRECISION_EXP, x1);
        break;
    case 2:
        printf ("x1 = %.*e\n", ROOT_PRECISION_EXP, x1);
        printf ("x2 = %.*e\n", ROOT_PRECISION_EXP, x2);
        break;
    default:
        printf ("%s", MSG_INCORRECT_CANCULATIONS);
        break;
    }
}
