#include <tuple>

#ifndef genericCrossSection_H
#define genericCrossSection_H

class genericCrossSection
{

public:

    virtual const std::tuple<double, double> pointAt(const int runner) = 0;

    virtual bool isClosed() = 0;

};

#endif
