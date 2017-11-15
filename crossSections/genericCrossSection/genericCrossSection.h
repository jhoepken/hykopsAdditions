#include <tuple>

#ifndef genericCrossSection_H
#define genericCrossSection_H

class genericCrossSection
{

public:

    virtual const std::tuple<double, double> pointAt(const int runner) = 0;

    virtual bool isClosed() const = 0;

    virtual std::tuple<double, double> operator[](double runner) const = 0;

    virtual double length() const = 0;
};

#endif
