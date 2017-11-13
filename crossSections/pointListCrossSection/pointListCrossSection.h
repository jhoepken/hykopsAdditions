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

public:

    pointListCrossSection(std::vector<std::tuple<double, double> > points);

    const std::tuple<double, double> pointAt(const int runner);

};

#endif
