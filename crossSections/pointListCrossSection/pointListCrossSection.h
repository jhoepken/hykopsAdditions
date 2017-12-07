#include <vector>

#include "../genericCrossSection/genericCrossSection.h"

#ifndef pointListCrossSection_H
#define pointListCrossSection_H

class pointListCrossSection
:
    public genericCrossSection
{
private:

    const std::vector<std::tuple<double, double> > points_;

    double interpolate
            (
                const std::tuple<double, double>& startPoint,
                const std::tuple<double, double>& endPoint
            ) const;

public:

    pointListCrossSection(const std::vector<std::tuple<double, double> >& points);

    const std::tuple<double, double> pointAt(const int runner);

    bool isClosed() const;

    double length() const;

    std::tuple<double, double> operator[](double runner) const;
};

#endif
