#define _USE_MATH_DEFINES
#include <cmath>

#include "NozzleInterface.h"

#include "Epsilon.h"
#include "HComponent.h"
#include "HLoftPath.h"
#include "HLinearLoftPath.h"
#include "HCoordinateSystem3D.h"
#include "HCoordinateSystem3DAffine.h"
#include "HPoint3D.h"
#include "CoordinateTransformation.h"
#include "MapKeys.h"
#include "NozzleProfile.h"
#include "AssembleFactory.h"

double NozzleInterface::getNozzleRadius(HLoft* loft){
    if(loft->getHCoordinateSystems3D()->size() > 0)
    {
    	HLoftPath* path = loft->getHLoftPath();
    				if (HLoftPath *path = dynamic_cast<HLoftPath*>(path)) {
    					HPoint3D* orig = path->getHLoftCoordinateSystem()->getOrigin();
    					return orig->getX3();
    				}
    			}
    			return 0.;
    }


void NozzleInterface::setNozzleRadius(HLoft* loft, double NozzleRadius){
    if(loft->getHCoordinateSystems3D()->size() > 0)
    {
    	HLoftPath* path = loft->getHLoftPath();
    	if (HLoftPath *path = dynamic_cast<HLoftPath*>(path))
        {
    		HPoint3D *orig = AssembleFactory::createHPoint3D(path, 0.,0.,(0. + NozzleRadius));
        	path->getHLoftCoordinateSystem()->setOrigin(orig);
        }
    }
}

double NozzleInterface::getDiffusorAngle(HLoft* loft){
	HLoftPath* blade = loft->getHLoftPath();
				if (HLoftPath *blade = dynamic_cast<HLoftPath*>(blade)) {
					{
						int np = loft->getHLoftElements()->size();
						double angle = 0.;

						if (np > 0) {
							for (int i = 0; i < np; i++) {
								HLoftElement* element = loft->getHLoftElements()->at(i);
								angle += NozzleProfile::getDiffusorAngle(element);     // finden und erstellen--------------------------------------------------
							}
							angle /= np;
						}
						return angle;
					}
				}
			return 0.;
}

void NozzleInterface::setDiffusorAngle(HLoft* loft, double alpha){
	double oldAlpha = getDiffusorAngle(loft);
	double scale = alpha / oldAlpha;
		for (int i=0; i<loft->getHLoftElements()->length();i++) {
			double angle = NozzleProfile::getDiffusorAngle(loft->getHLoftElements()->at(i));  // -------------------------------------------------------------------------------------------
			NozzleProfile::setDiffusorAngle(loft->getHLoftElements()->at(i), (angle * scale)); //---------------------------------------------------------------------------------------------
}
}

double NozzleInterface::getChordlength(HLoft* loft){
	HLoftPath* blade = loft->getHLoftPath();
				if (HLoftPath *blade = dynamic_cast<HLoftPath*>(blade)) {
					{
						int np = loft->getHLoftElements()->size();
						double chord = 0.;
						if (np > 0) {
							for (int i = 0; i < np; i++) {
								HLoftElement* element = loft->getHLoftElements()->at(i);
								double l = NozzleProfile::getChordlength(element);//----------------------------------------------------------------------------
								chord += l;
							}
							chord /= np;
						}
						return chord;
					}
				}
			return 0.;
}


void NozzleInterface::setChordlength(HLoft* loft, double chord) {
		double oldChord = NozzleProfile::getChordlength(loft->getHLoftElements()->at(0));
		double f = chord / oldChord;
		for (int i = 0; i < loft->getHLoftElements()->size(); i++) {
			HLoftElement* element = loft->getHLoftElements()->at(i);
			double lChord = NozzleProfile::getChordlength(element); //-----------------------------------------
			double newChord = lChord * f;
			NozzleProfile::setChordlength(element, newChord);
		}
	}





