#include "pointListCrossSection.h"

pointListCrossSection::pointListCrossSection(const std::vector<std::tuple<double, double> >& points)
:
    points_(points)
{}

const std::tuple<double, double> pointListCrossSection::pointAt(const int runner)
{
    //(void) runner;
    return {1.0, -1.0};
    //return points_[0];
}
