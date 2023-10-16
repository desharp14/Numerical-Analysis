#ifndef EQUATION_SOLVER_H
#define EQUATION_SOLVER_H

#include <iostream>
#include <functional>

class EquationSolver {
public:
    virtual double solve(std::function<double(double)> equation, double x0, double x1, double epsilon) = 0;
};

class BisectionSolver : public EquationSolver {
public:
    double solve(std::function<double(double)> equation, double x0, double x1, double epsilon) override {
        double xMid;
        while ((x1 - x0) > epsilon) {
            xMid = (x0 + x1) / 2.0;
            if (equation(xMid) == 0.0) {
                return xMid;
            }
            else if (equation(x0) * equation(xMid) < 0) {
                x1 = xMid;
            }
            else {
                x0 = xMid;
            }
        }
        return xMid;
    }
};

class NewtonSolver : public EquationSolver {
public:
    double solve(std::function<double(double)> equation, double x0, double x1, double epsilon) override {
        double x = x0;
        while (std::abs(equation(x)) > epsilon) {
            double derivative = (equation(x + epsilon) - equation(x - epsilon)) / (2.0 * epsilon);
            x = x - equation(x) / derivative;
        }
        return x;
    }
};

class SecantSolver : public EquationSolver {
public:
    double solve(std::function<double(double)> equation, double x0, double x1, double epsilon) override {
        double x;
        while (std::abs(x1 - x0) > epsilon) {
            x = x1 - (equation(x1) * (x1 - x0)) / (equation(x1) - equation(x0));
            x0 = x1;
            x1 = x;
        }
        return x1;
    }
};

#endif
