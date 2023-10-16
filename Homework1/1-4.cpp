#include "EquationSolver.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

int main() {
    //Bisection Method
    std::cout << "Bisection Method:" << std::endl;
    EquationSolver* bisectionSolver = new BisectionSolver();
    //x^(-1) - tan(x) on [0, π/2]
    auto equation1 = [](double x) { return 1.0 / x - tan(x); };
    double x0_1 = 0.0;
    double x1_1 = M_PI / 2.0; // Using the manual PI constant
    double epsilon = 0.001;
    double result1 = bisectionSolver->solve(equation1, x0_1, x1_1, epsilon);

    std::cout << "Root of x^(-1) - tan(x) on [0, π/2]: " << result1 << std::endl;

    //x^(-1) - 2^x on [0, 1]
    auto equation2 = [](double x) { return 1.0 / x - pow(2, x); };
    double x0_2 = 0.1;  // Avoid division by zero at x=0
    double x1_2 = 1.0;
    double result2 = bisectionSolver->solve(equation2, x0_2, x1_2, epsilon);

    std::cout << "Root of x^(-1) - 2^x on [0, 1]: " << result2 << std::endl;

    //2^(-x) + e^x + 2 cos(x) - 6 on [1, 3]
    auto equation3 = [](double x) { return pow(2, -x) + exp(x) + 2 * cos(x) - 6; };
    double x0_3 = 1.0;
    double x1_3 = 3.0;
    double result3 = bisectionSolver->solve(equation3, x0_3, x1_3, epsilon);

    std::cout << "Root of 2^(-x) + e^x + 2 cos(x) - 6 on [1, 3]: " << result3 << std::endl;

    //(x^3 + 4x^2 + 3^x + 5)/(2x^3 - 9x^2 + 18x - 2) on [0, 4]
    auto equation4 = [](double x) { return (x * x * x + 4 * x * x + pow(3, x) + 5) / (2 * x * x * x - 9 * x * x + 18 * x - 2); };
    double x0_4 = 0.01;  // Avoid division by zero at x=0
    double x1_4 = 4.0;
    double result4 = bisectionSolver->solve(equation4, x0_4, x1_4, epsilon);

    std::cout << "Root of (x^3 + 4x^2 + 3^x + 5)/(2x^3 - 9x^2 + 18x - 2) on [0, 4]: " << result4 << std::endl << std::endl;

    delete bisectionSolver;

    //Newton's Method
    std::cout << "Newton's Method:" << std::endl;
    EquationSolver* newtonSolver = new NewtonSolver();
    // Function: x = tan(x)
    auto equation5 = [](double x) { return x - tan(x); };

    // Initial guesses for roots
    double x0_5_1 = 4.5;
    double x0_5_2 = 7.7;

    // Tolerance for convergence
    double epsilon5 = 0.0001;
    double result5_1 = newtonSolver->solve(equation5, x0_5_1, x0_5_1 + 1, epsilon5);
    double result5_2 = newtonSolver->solve(equation5, x0_5_2, x0_5_2 + 1, epsilon5);

    std::cout << "Root of x = tan(x) near 4.5: " << result5_1 << std::endl;
    std::cout << "Root of x = tan(x) near 7.7: " << result5_2 << std::endl << std::endl;

    delete newtonSolver;

    //Secant Method
    std::cout << "Newton's Method:" << std::endl;
    EquationSolver* secantSolver = new SecantSolver();
    //sin(x/2) - 1
    auto equation6 = [](double x) { return sin(x / 2.0) - 1.0; };
    double x0_6 = 0.0;
    double x1_6 = M_PI / 2.0;
    double result6 = secantSolver->solve(equation5, x0_6, x1_6, epsilon);

    std::cout << "Root of sin(x/2) - 1 using Secant: " << result6 << std::endl;

    //e^x - tan(x)
    auto equation7 = [](double x) { return exp(x) - tan(x); };
    double x0_7 = 1.0;
    double x1_7 = 1.4;
    double result7 = secantSolver->solve(equation6, x0_6, x1_6, epsilon);

    std::cout << "Root of e^x - tan(x) using Secant: " << result7 << std::endl;

    //x^3 - 12x^2 + 3x + 1
    auto equation8 = [](double x) { return x * x * x - 12 * x * x + 3 * x + 1; };
    double x0_8 = 0.0;
    double x1_8 = -0.5;
    double result8 = secantSolver->solve(equation7, x0_7, x1_7, epsilon);

    std::cout << "Root of x^3 - 12x^2 + 3x + 1 using Secant: " << result8 << std::endl;

    delete secantSolver;

    return 0;
}