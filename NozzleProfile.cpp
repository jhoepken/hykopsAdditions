
//import de.hykops.lpd.core.sdk.CoordinateSystem3DSupport;
#include <cmath>

#include "../hykops_core/Epsilon.h"
#include "../hykops_data/HComponent.h"
#include "../hykops_data/HCoordinateSystem3DAffine.h"
#include "../hykops_data/HCoordinateSystem3D.h"
#include "../hykops_data/HLoftElement.h"
#include "../hykops_data/HPoint3D.h"
#include "../hykops_data/HLoft.h"
#include "NozzleProfile.h"
#include "NozzleInterface.h"

using namespace std;

double getRelRadius(HLoftElement* element) {
		HLoft* loft = element->getHLoft();
		double rNozzle = NozzleInterface::getNozzleRadius(loft);
		double x2OrigProfile = element->getLoftPlaneDefiningCoordinateSystem()->getOrigin()->getX2();
		if (std::abs(rNozzle) > Epsilon::NANO) {
			return (rNozzle + x2OrigProfile) / rNozzle;
		}
		return 1.;
	}


void setRelRadius(HLoftElement* element, double relRadius) {
		HLoft* loft = element->getHLoft();
		double rNozzle = NozzleInterface::getNozzleRadius(loft);
		double x2OrigProfile = relRadius * rNozzle - rNozzle;
		element->getLoftPlaneDefiningCoordinateSystem()->getOrigin()->setX2(x2OrigProfile);
	}


double getProfileAxialShift(HLoftElement element) {
		double x1OrigProfile = element.getLoftPlaneDefiningCoordinateSystem()->getOrigin()->getX1();
		return x1OrigProfile;
	}


void setProfileAxialShift(HLoftElement element, double axialShift) {
		element.getLoftPlaneDefiningCoordinateSystem()->getOrigin()->setX1(axialShift);
	}


double getDiffusorAngle(HLoftElement element) {
		HCoordinateSystem3D cos = element.getLoftPlaneDefiningCoordinateSystem();
		if (HCoordinateSystem3D *cos = dynamic_cast<HCoordinateSystem3DAffine*> (HCoordinateSystem3DAffine)) {
			HPoint3D xi = ((HCoordinateSystem3DAffine) cos).getX1();
			double alpha = std::atan2(xi.getX2(), xi.getX1());
			return alpha;
		}
		return 0.;
	}


void setDiffusorAngle(HLoftElement element, double alpha) {
		double chord = getChordlength(element);

		HCoordinateSystem3D cos = element.getLoftPlaneDefiningCoordinateSystem();
		HPoint3D horig = ((HCoordinateSystem3DAffine) cos).getOrigin();

		double xi1 = chord * std::cos(alpha);
		double xi2 = chord * std::sin(alpha);
		double xi3 = 0.;

		double z1 = 0.;
		double z2 = 0.;
		double z3 = 1.; // circum direction

		// length of eta: =CHORD!
		//Kreuzprodukt?
		double A [3]= {xi1, xi2, xi3};
		double B [3]= {z1, z2, z3};
		//double eta[] = de.fsg.tk.math.vec.VecOp.cross(new double[] { xi1, xi2, xi3 }, new double[] { z1, z2, z3 }); // was?-----------------------------------------

		double eta[] = {(A[1]*B[2]) - (A[2]*B[2]),  (A[2]*B[0] - A[0]*B[2], A[0]*B[1] - A[1]*B[0])};

		HCoordinateSystem3D planeCos = AssembleFactory::createCoordinatesSystem3DAffine(0, horig.getX1(), horig.getX2(), horig.getX3(), xi1, xi2, xi3, eta[0], eta[1], eta[2], z1, z2, z3);
		planeCos->setHParent(element);
		element->setLoftPlaneDefiningCoordinateSystem(planeCos);

	}


double getChordlength(HLoftElement element) {
		HCoordinateSystem3D cos = element.getLoftPlaneDefiningCoordinateSystem();
		if (HCoordinateSystem3D *cos = dynamic_cast<HCoordinateSystem3D*> (HCoordinateSystem3DAffine)) {
			HPoint3D xi = ((HCoordinateSystem3DAffine) cos).getX1();
			double chord = std::sqrt(std::pow(xi.getX1(), 2.) + std::pow(xi.getX2(), 2.));
			return chord;
		}
		return 0.;
	}


void setChordlength(HLoftElement element, double chord) {
		double oldChord = getChordlength(element);
		double f = chord / oldChord;

		HCoordinateSystem3D cos = element.getLoftPlaneDefiningCoordinateSystem();
		HPoint3D horig = ((HCoordinateSystem3DAffine) cos).getOrigin();

		HPoint3D xi = ((HCoordinateSystem3DAffine) cos).getX1();
		double xi1 = xi.getX1() * f;
		double xi2 = xi.getX2() * f;
		double xi3 = xi.getX3() * f;

		HPoint3D eta = ((HCoordinateSystem3DAffine) cos).getX2();
		double eta1 = eta.getX1() * f;
		double eta2 = eta.getX2() * f;
		double eta3 = eta.getX3() * f;

		HPoint3D z = ((HCoordinateSystem3DAffine) cos).getX3();
		double z1 = z.getX1();
		double z2 = z.getX2();
		double z3 = z.getX3();

		HCoordinateSystem3D planeCos = AssembleFactory::createCoordinateSystem3DAffine(0, horig.getX1(), horig.getX2(), horig.getX3(), xi1, xi2, xi3, eta1, eta2, eta3, z1, z2, z3);
		planeCos->setHParent(element);
		element->setLoftPlaneDefiningCoordinateSystem(planeCos);
	element->	}




