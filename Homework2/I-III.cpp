#include <iostream>
#include <vector>
#include <gnuplot-iostream.h>

//I: Subroutine to calculate the interpolation polynomial using Newton's formula
double newtonInterpolation(const std::vector<double>& x, const std::vector<double>& y, double x_val) {
    int n = x.size();
    double result = 0.0;

    std::vector<std::vector<double>> divided_differences(n, std::vector<double>(n, 0.0));

    for (int i = 0; i < n; i++) {
        divided_differences[i][0] = y[i];
    }

    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            divided_differences[i][j] = (divided_differences[i + 1][j - 1] - divided_differences[i][j - 1]) / (x[i + j] - x[i]);
        }
    }

    for (int i = 0; i < n; i++) {
        double term = divided_differences[0][i];
        for (int j = 0; j < i; j++) {
            term *= (x_val - x[j]);
        }
        result += term;
    }

    return result;
}

int main() {
    //II: Run the routine on the function f(x) = 1 /(1 + x^2) for different n values.
    std::vector<int> n_values = { 2, 4, 6, 8 };

    Gnuplot gp;
    gp << "set terminal png size 800,600\n";
    gp << "set output 'newton_interpolation.png'\n";
    gp << "set multiplot layout " << n_values.size() << ",1\n";

    for (int n : n_values) {
        std::vector<double> x;
        std::vector<double> y;

        for (int i = 0; i <= n; i++) {
            double x_i = -5.0 + 10.0 * i / n;
            double y_i = 1.0 / (1.0 + x_i * x_i);
            x.push_back(x_i);
            y.push_back(y_i);
        }

        std::vector<double> x_interp;
        std::vector<double> y_interp;

        for (double x_val = -5.0; x_val <= 5.0; x_val += 0.01) {
            double y_val = newtonInterpolation(x, y, x_val);
            x_interp.push_back(x_val);
            y_interp.push_back(y_val);
        }

        gp << "set title 'n = " << n << "'\n";
        gp << "plot '-' with lines title 'Interpolation', '-' with lines title 'Exact'\n";
        gp.send1d(std::make_tuple(x_interp, y_interp));
        gp.send1d(std::make_tuple(x, y));
    }

    gp << "unset multiplot\n";

    //III: Reuse the subroutine for Chebyshev interpolation
    std::vector<int> chebyshev_n_values = { 5, 10, 15, 20 };

    gp << "set output 'chebyshev_interpolation.png'\n";
    gp << "set multiplot layout " << chebyshev_n_values.size() << ",1\n";

    for (int n : chebyshev_n_values) {
        std::vector<double> x_chebyshev;
        std::vector<double> y_chebyshev;

        for (int i = 0; i <= n; i++) {
            double x_i = -1.0 + 2.0 * cos(M_PI * i / n);
            double y_i = 1.0 / (1.0 + 25.0 * x_i * x_i);
            x_chebyshev.push_back(x_i);
            y_chebyshev.push_back(y_i);
        }

        std::vector<double> x_interp_chebyshev;
        std::vector<double> y_interp_chebyshev;

        for (double x_val = -1.0; x_val <= 1.0; x_val += 0.01) {
            double y_val = newtonInterpolation(x_chebyshev, y_chebyshev, x_val);
            x_interp_chebyshev.push_back(x_val);
            y_interp_chebyshev.push_back(y_val);
        }

        gp << "set title 'Chebyshev Interpolation (n = " << n << ")'\n";
        gp << "plot '-' with lines title 'Interpolation', '-' with lines title 'Exact'\n";
        gp.send1d(std::make_tuple(x_interp_chebyshev, y_interp_chebyshev));
        gp.send1d(std::make_tuple(x_chebyshev, y_chebyshev));
    }

    gp << "unset multiplot\n";

    return 0;
}
