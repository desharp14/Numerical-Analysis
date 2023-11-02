#include <iostream>
#include <vector>

double interpolate(double x, const std::vector<double>& xData, const std::vector<double>& yData) {
    int n = xData.size();
    double result = 0.0;

    std::vector<std::vector<double>> dividedDifferences(n, std::vector<double>(n, 0.0));

    for (int i = 0; i < n; i++) {
        dividedDifferences[i][0] = yData[i];
    }

    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            dividedDifferences[i][j] = (dividedDifferences[i + 1][j - 1] - dividedDifferences[i][j - 1]) / (xData[i + j] - xData[i]);
        }
    }

    for (int i = 0; i < n; i++) {
        double term = dividedDifferences[0][i];
        for (int j = 0; j < i; j++) {
            term *= (x - xData[j]);
        }
        result += term;
    }

    return result;
}

int main() {
    std::vector<double> xData = { 0, 6, 10, 13, 17, 20, 28 };
    std::vector<double> yData1 = { 6.67, 17.3, 42.7, 37.3, 30.1, 29.3, 28.7 };
    std::vector<double> yData2 = { 6.67, 16.1, 18.9, 15.0, 10.6, 9.44, 8.89 };

    std::vector<double> approximatedData1;
    std::vector<double> approximatedData2;

    for (int x = 0; x <= 28; x++) {
        approximatedData1.push_back(interpolate(x, xData, yData1));
        approximatedData2.push_back(interpolate(x, xData, yData2));
    }

    double futureX = 43;

    double prediction1 = interpolate(futureX, xData, yData1);
    double prediction2 = interpolate(futureX, xData, yData2);

    std::cout << "Prediction for Sample 1 after 43 units of time: " << prediction1 << std::endl;
    std::cout << "Prediction for Sample 2 after 43 units of time: " << prediction2 << std::endl;

    if (prediction1 < 0 && prediction2 < 0) {
        std::cout << "Both samples are predicted to decline after 15 more units of time." << std::endl;
    }
    else {
        std::cout << "Both samples are not predicted to decline after 15 more units of time." << std::endl;
    }

    return 0;
}
