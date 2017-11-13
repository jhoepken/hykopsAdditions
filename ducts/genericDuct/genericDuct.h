#include "HComponent.h"

#ifndef genericDuct_H
#define genericDuct_H

template<class CrossSection, class Rotation>
class genericDuct
:
    public HComponent
{

private:

    //- Disallow copy construction
    genericDuct();

public:

    genericDuct
    (
        const CrossSection& cross,
        const Rotation& rotation
    );

};

#include "genericDuct.cpp"

#endif
