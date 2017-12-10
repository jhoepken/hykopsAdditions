#ifndef HYKOPS_NOZZLE_NOZZLEFACTORY_H_
#define HYKOPS_NOZZLE_NOZZLEFACTORY_H_

#include "AssembleFactory.h"
#include "HComponent.h"
#include "HComposition.h"
#include "HLoft.h"
#include "HHinge.h"
#include "SplineKeys.h"
#include "HCoordinateSystem3D.h"
#include "HLinearLoftPath.h"
#include "HComponent.h"
#include "HComposition.h"
#include "HPoint3D.h"


class NozzleFactory
{
public:
    static HComponent* createEmptyNozzle(HComposition* composition, QString name, QString description,  double xref, double yref, double zref, double radius);
private:
    NozzleFactory();
};



#endif /* HYKOPS_NOZZLE_NOZZLEFACTORY_H_ */
