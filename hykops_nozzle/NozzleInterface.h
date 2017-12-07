/*
 * NozzleInterface.h
 *
 *  Created on: Oct 25, 2017
 *      Author: lennart
 */

#ifndef HYKOPS_NOZZLE_NOZZLEINTERFACE_H_
#define HYKOPS_NOZZLE_NOZZLEINTERFACE_H_


#include <QVector3D>
#include "HPoint3D.h"
#include "HLoft.h"
#include "HLoftElement.h"

/**
 * @brief The PropellerInterface class Convenience food for standard propeller geometries
 */
class NozzleInterface
{
    public:
//! returns the absolute nozzle radius defined by the coordinate system of the loft
    double getNozzleRadius(HLoft* loft);
//! sets the nozzle radius
    void setNozzleRadius(HLoft* loft, double NozzleRadius);
//! returns the diffusor angle of the nozzle
    double getDiffusorAngle(HLoft* loft);
//! returns the diffusor angle of the nozzle
    void setDiffusorAngle(HLoft* loft, double alpha);
//! returns the nozzle's chord length
    double getChordlength(HLoft* loft);
//! sets the nozzle's chord length
    void setChordlength(HLoft* loft, double chord);
};

#endif /* HYKOPS_NOZZLE_NOZZLEINTERFACE_H_ */
