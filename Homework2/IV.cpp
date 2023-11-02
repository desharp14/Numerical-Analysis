#include <iostream>
#include <vector>

double interpolate(double t, const std::vector<double>& times, const std::vector<double>& displacements, const std::vector<double>& velocities) {
    double result = 0.0;

    for (size_t i = 0; i < times.size(); ++i) {
        double basis = 1.0;
        for (size_t j = 0; j < times.size(); ++j) {
            if (i != j) {
                basis *= (t - times[j]) / (times[i] - times[j]);
            }
        }

        double term = basis * (2 * t - times[i]);
        result += term * displacements[i] + basis * velocities[i];
    }

    return result;
}

int main() {
    std::vector<double> times = { 0, 3, 5, 8, 13 };
    std::vector<double> displacements = { 0, 225, 383, 623, 993 };
    std::vector<double> velocities = { 75, 77, 80, 74, 72 };

    double t = 10;

    double position = interpolate(t, times, displacements, velocities);
    double speed = interpolate(t, times, displacements, velocities);

    std::cout << "Position at t = 10 seconds: " << position << " feet" << std::endl;
    std::cout << "Speed at t = 10 seconds: " << speed << " feet per second" << std::endl;

    double speedLimit = 81.0;
    if (speed > speedLimit) {
        std::cout << "The vehicle exceeds the speed limit." << std::endl;
    }
    else {
        std::cout << "The vehicle does not exceed the speed limit." << std::endl;
    }

    return 0;
}
