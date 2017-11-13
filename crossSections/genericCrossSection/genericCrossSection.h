#include <tuple>

#ifndef genericCrossSection_H
#define genericCrossSection_H

class genericCrossSection
{

public:

    virtual const std::tuple<double, double> pointAt(const int runner) = 0;

};

#endif
