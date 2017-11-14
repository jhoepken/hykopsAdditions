#include "pointListCrossSection.h"

pointListCrossSection::pointListCrossSection(const std::vector<std::tuple<double, double> >& points)
:
    points_(points)
{}

const std::tuple<double, double> pointListCrossSection::pointAt(const int runner)
{
    return points_[runner];
}

bool pointListCrossSection::isClosed()
{
    return true;
}
