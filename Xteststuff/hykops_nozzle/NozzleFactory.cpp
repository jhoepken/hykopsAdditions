#include "NozzleFactory.h"

#include <math.h>
#include "CompositionFactory.h"
#include "AssembleFactory.h"
#include "HLoft.h"
#include "HLinearLoftPath.h"
#include "NozzleInterface.h"
#include "SplineKeys.h"

HComponent* NozzleFactory::createEmptyNozzle(HComposition* composition, QString name, QString description, double xref, double yref, double zref, double radius)
{
    HComponent *nozzle = new HComponent;
    composition->getHComponents()->append(nozzle);
    nozzle->setHParent(composition);
    nozzle->setName(name);
    nozzle->setDescription(description);
    nozzle->setType("de.hykops.nozzle.default");

    HCoordinateSystem3D *cos = AssembleFactory::createCoordinateSystem3DCartesian(nozzle, xref, yref, zref, 1.,1.,1.,0.,0.,0.);
    AssembleFactory::setComponentCoordinateSystem(nozzle, cos);

    HLoft *ring = new HLoft;
    nozzle->getHLofts()->append(ring);
    ring->setHParent(nozzle);
    ring->setName("ring loft");
    ring->setDescription("Default ring loft");

//    QString key = QString::fromLatin1(SplineKeys::LOFTINTERPOLATIONKEY);
//    QString value = QString::fromLatin1(SplineKeys::HERMITE);
//    ring->getParameters()->insert(key, value);



    HCoordinateSystem3D *ring_cos = AssembleFactory::createCoordinateSystem3DPolar(ring, 0., 0., 0., 1., 0., 0., 0., 0., 1.);

    AssembleFactory::addLoftCoordinateSystem(ring, ring_cos);


    HLinearLoftPath *path = new HLinearLoftPath;
    path->setHParent(ring);
    ring->setHLoftPath(path);
    path->setDenominator("RING_LOFT");

    HCoordinateSystem3D *loftPath_cos =  AssembleFactory::createCoordinatesSystem3DAffine(composition,
                                                                                          0., 0., 0., /*-origin*/
                                                                                          1., 0., 0., /*-x1-axis*/
                                                                                          0., 1., 0., /*-x2-axis*/
                                                                                          0., 0., 1.  /*-x3-axis*/);
    AssembleFactory::setLoftPathCoordinateSystem(path, loftPath_cos);


    HPoint3D *orig = AssembleFactory::createHPoint3D(path, 0.,0.,(0. + radius));
    path->setOrigin(orig);

    double circum = (2. * M_PI);

    HPoint3D *axis = AssembleFactory::createHPoint3D(path, 0., circum, 0.);
    path->setLoftPathVector(axis);

    HPoint3D *xi = AssembleFactory::createHPoint3D(path, 1., 0., 0.);
    path->setLoftPathXi(xi);

    HPoint3D *eta = AssembleFactory::createHPoint3D(path, 0., 0., 1.);
    path->setLoftPathEta(eta);

    return nozzle;
}


