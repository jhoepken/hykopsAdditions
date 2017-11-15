#include <cmath>

#include "pointListCrossSection.h"

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
    return 0.0;
}

std::tuple<double, double> pointListCrossSection::operator[](double runner) const
{
    return {1,1};
}
