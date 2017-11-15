#include "genericDuct.h"

template<class CrossSection, class Rotation>
genericDuct<CrossSection, Rotation>::genericDuct
(
    const CrossSection& cross,
    const Rotation& rotation
)
:
    cross_(cross),
    rotation_(rotation)
{}
