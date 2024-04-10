#include <fstream>
#include <Eigen/Dense>
#include <vector>
#include <iomanip>
#include <string>
#include "BezierSpline.h"
#include <iostream>


std::vector<Eigen::Vector2d> ReadPointsFromFile(const std::string& file_path) 
{
    std::vector<Eigen::Vector2d> points;
    std::ifstream file(file_path);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        double x, y;
        char comma;

        if (!(iss >> x >> comma >> y)) 
        {
            // Handle the error if parsing fails
            continue;
        }

        if (comma != ',') 
        {
            // Handle the error if the format is incorrect
            continue;
        }

        points.emplace_back(x, y);
    }

    return points;
}

void WritePointsToFile(const std::vector<Eigen::Vector2d>& points, const std::string& file_path) 
{
    std::ofstream file(file_path);
    if (!file.is_open()) {
        return;
    }

    int precision = 6;
    file << std::fixed << std::setprecision(precision);

    for (const auto& point : points) {
        file << point.x() << ", " << point.y() << std::endl;
    }
}

int main() 
{
    std::string file_path = "points.txt";
    std::vector<Eigen::Vector2d> points = ReadPointsFromFile(file_path);

    BezierSpline spline;

    //Convolution values. a list of (0.2,0.6,0.2) would mean that every point value would be 60% of its own value and 20% of the point values next to it.
    //The more values, the more points are convolved. List should contain odd number of values.
    std::vector<double> filter = {0.05,0.05,0.05,0.05,0.1, 0.1, 0.1, 0.1, 0.1,0.1,0.05,0.05,0.05,0.05};

    //Apply convolution to points before B-spline.
    points = spline.apply_convolution_filter(points, filter);
    int points_per_spline = 30;
    int num_interpolated_points_per_segment = 29; 
    std::vector<Eigen::Vector2d>  interpolated_points = spline.generalized_bezier_spline(points,points_per_spline, num_interpolated_points_per_segment);
    std::cout << points.size() << std::endl;
    std::cout << interpolated_points.size() << std::endl;
    std::string output_file_path = "interpolated_points.txt";
    WritePointsToFile(interpolated_points, output_file_path);

    return 0;
}
