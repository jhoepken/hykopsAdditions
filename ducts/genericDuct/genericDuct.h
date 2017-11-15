#include "HComponent.h"

#ifndef genericDuct_H
#define genericDuct_H

template<class CrossSection, class Rotation>
class genericDuct
:
    public HComponent
{

private:

    const CrossSection& cross_;

    const Rotation& rotation_;

    //- Disallow copy construction
    genericDuct();

public:

    genericDuct
    (
        const CrossSection& cross,
        const Rotation& rotation
    );

    inline const CrossSection& cross() const
    {
        return cross_;
    };

    inline const Rotation& rotation() const
    {
        return rotation_;
    };

};

#include "genericDuct.cpp"

#endif
