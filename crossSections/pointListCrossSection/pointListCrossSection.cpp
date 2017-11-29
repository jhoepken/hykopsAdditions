#include <cmath>
#include <algorithm>
#include <numeric>
#include <iostream>

#include "pointListCrossSection.h"

double pointListCrossSection::interpolate
(
    const std::tuple<double, double>& startPoint,
    const std::tuple<double, double>& endPoint
) const
{
    const double length
        (
            std::sqrt
            (
                std::pow
                (
                    std::get<0>(endPoint) -
                    std::get<0>(startPoint),
                    2
                ) +
                std::pow
                (
                    std::get<1>(endPoint) -
                    std::get<1>(startPoint),
                    2
                )
            )
        );
    return length;
}

pointListCrossSection::pointListCrossSection(const std::vector<std::tuple<double, double> >& points)
:
    points_(points)
{}

const std::tuple<double, double> pointListCrossSection::pointAt(const int runner)
{
    return points_[runner];
}

bool pointListCrossSection::isClosed() const
{
    if(
        (std::abs(std::get<0>(points_[0]) - std::get<0>(points_.back())) <= 1e-6) &&
        (std::abs(std::get<1>(points_[0]) - std::get<1>(points_.back())) <= 1e-6)
      )
    {
        return true;
    }
    else
    {
        return false;
    }
}

double pointListCrossSection::length() const
{
    double length(0.0);

    std::vector<std::tuple<double, double> > shiftedPoints(points_);
    std::rotate(shiftedPoints.begin(), shiftedPoints.begin() + 1, shiftedPoints.end());

    for(auto& p1 : points_)
    {
        const std::tuple<double, double>& p2(shiftedPoints[&p1-&points_[0]]);
        length += interpolate(p1, p2);
        //std::cout<< interpolate(p1, p2) << " -- " << length << std::endl;
    }

    return length;
}

std::tuple<double, double> pointListCrossSection::operator[](double runner) const
{
    const double lTotal(length());

    const double lTarget(lTotal*runner);

    double length(0.0);

    int firstElement(-1.0);

    bool detector(false);

    std::vector<std::tuple<double, double> > shiftedPoints(points_);
    std::rotate(shiftedPoints.begin(), shiftedPoints.begin() + 1, shiftedPoints.end());

    for(auto& p1 : points_)
    {
        const std::tuple<double, double>& p2(shiftedPoints[&p1-&points_[0]]);
        length += interpolate(p1, p2);

        if( (interpolate(p1, p2) >= lTarget) && !detector)
        {
            length += interpolate(p1, p2);
            firstElement++;
        }

        std::cout<< interpolate(p1, p2) << " -- " << length << std::endl;
    }

    return {1,1};
}
