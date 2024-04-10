#include "BezierSpline.h"
#include <cmath>

int BezierSpline::binomial_coefficient(int n, int k) 
{
    if (k < 0 || k > n) 
    {
        return 0;
    }
    if (k == 0 || k == n) 
    {
        return 1;
    }
    k = std::min(k, n - k);
    int coeff = 1;
    for (int i = 0; i < k; ++i) 
    {
        coeff *= (n - i);
        coeff /= (i + 1);
    }
    return coeff;
}

double BezierSpline::bernstein_polynomial(int i, int n, double t) 
{
    return binomial_coefficient(n, i) * std::pow(t, i) * std::pow(1 - t, n - i);
}

Eigen::Vector2d BezierSpline::Spezier(const std::vector<Eigen::Vector2d>& segment_points, double t) 
{
    int n = segment_points.size() - 1;
    Eigen::Vector2d point(0, 0);
    for (int i = 0; i <= n; ++i) 
    {
        double bernstein = bernstein_polynomial(i, n, t);
        point += segment_points[i] * bernstein;
    }
    return point;
}

std::vector<Eigen::Vector2d> BezierSpline::generalized_bezier_spline(const std::vector<Eigen::Vector2d>& points, int points_per_spline, int num_interpolated_points_per_segment) 
{   
    std::vector<Eigen::Vector2d> interpolated_points;
    Eigen::Vector2d direction(0, 0);
    
    for (size_t i = 0; i < points.size() - points_per_spline; i += points_per_spline - 1) 
    {
        std::vector<Eigen::Vector2d> segment_points(points.begin() + i, points.begin() + i + points_per_spline);
        
        if (i != 0) 
        {
            Eigen::Vector2d p1 = segment_points[0];
            Eigen::Vector2d adjusted_p2 = p1 + direction;
            segment_points[1] = adjusted_p2;
        }

        direction = segment_points.back() - segment_points[segment_points.size() - 2];

        for (int j = 0; j < num_interpolated_points_per_segment; ++j) 
        {
            double t = static_cast<double>(j) / (num_interpolated_points_per_segment - 1);
            interpolated_points.push_back(Spezier(segment_points, t));
        }
    }

    return interpolated_points;
}

std::vector<Eigen::Vector2d> BezierSpline::apply_convolution_filter(const std::vector<Eigen::Vector2d>& points, const std::vector<double>& filter) 
{
    std::vector<Eigen::Vector2d> convolved_points;
    int filter_size = filter.size();
    int padding_size = (filter_size - 1) / 2;

    for (size_t i = 0; i < points.size(); ++i) 
    {
        Eigen::Vector2d convolved_point(0, 0);

        //If not enough points before or after in the points list to do the full convolution
        //Just add point as it is. Affects the beginning and the end of points list.
        bool in_convolution_range = (i >= padding_size) && (i < points.size() - padding_size);
        
        if (in_convolution_range) 
        {
            //Point value is convolved with points next to it according to filter values.
            for (int j = 0; j < filter_size; ++j) 
            {
                int index = i + j - padding_size;
                convolved_point += points[index] * filter[j];
            }
        }
        else 
        {
            // If the point is not in the convolution range, add it directly to the convolved points
            convolved_point = points[i];
        }
        
        convolved_points.push_back(convolved_point);
    }

    return convolved_points;
}


