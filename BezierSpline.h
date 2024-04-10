#pragma once

#include <vector>
#include <Eigen/Dense>

class BezierSpline 
{
private:
    static int binomial_coefficient(int n, int k);
    static double bernstein_polynomial(int i, int n, double t);
    static Eigen::Vector2d Spezier(const std::vector<Eigen::Vector2d>& segment_points, double t);

public:
    std::vector<Eigen::Vector2d> apply_convolution_filter(const std::vector<Eigen::Vector2d>& points, const std::vector<double>& filter);
    std::vector<Eigen::Vector2d> generalized_bezier_spline(const std::vector<Eigen::Vector2d>& points, int points_per_spline, int num_interpolated_points_per_segment);
};
