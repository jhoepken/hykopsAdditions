#include "../hykops_data/HPoint3D.h"
#include "../hykops_core/AssembleFactory.h"
#include "../hykops_data/HComposition.h"
#include "../hykops_data/HComponent.h"
#include "../hykops_data/HExternalGeometry.h"
#include "../hykops_data/HLoft.h"
#include "../hykops_data/HLoftElement.h"
#include "../hykops_data/HCurve2D.h"
#include "../hykops_data/HCurvePoint2D.h"
#include "../hykops_data/HCoordinateSystem3D.h"
#include "../hykops_core/LoftElementSupport.h"
#include "../hykops_core/CoordinateTransformation.h"
#include "../hykops_core/Export.h"
#include "../hykops_core/SurfaceUtil.h"
#include "../hykops_propeller/PropellerFactory.h"
#include "../hykops_nozzle/NozzleFactory.h"
#include "../hykops_propeller/PFFParser.h"
#include "../hykops_propeller/PropellerInterface.h"
#include "../hykops_core/CompositionSerializer.h"
#include "../hykops_core/CompositionFactory.h"
#include "../hykops_core/tesselation/Tesselation.h"
#include "../hykops_core/tesselation/Triangle.h"
#include "../hykops_core/ExternalSTLParser.h"
#include "../hykops_core/ESurfaceIdentifiers.h"
#include "../hykops_core/SurfaceIdentifierMapping.h"
#include "../hykops_core/Export.h"
#include <QtTest/QtTest>
#include "../Xteststuff/SIS.h"
#include "../Xteststuff/noztest.h"
#include <QString>

#include <fstream>
#include <sstream>
#include <iostream>
#include "../hykops_core/C_Interface.h"
#include "../serializeemf/domwriter.h"
#include "../hykops_data/uniquelist.h"

using namespace std;

class AddExampleNozzle {

	HComponent* createExampleNozzle(HComposition* composition, double xref, double yref, double zref, double radius, double chord) {
//, QString profileSeries, QString profileName
		QString abc;
		QString cde;

	HComponent* nozzle = NozzleFactory::createEmptyNozzle(composition, abc, cde, xref, yref, zref, radius);

	HLoft* ring = nozzle->getHLofts()->at(0);
	// HLoftPath axis = ring.getHLoftPath();

	QList<QPair<ProfileSide, ESurfaceIdentifiers>>  eIdent =SurfaceIdentifierMapping::getSides();

		for(int i=0; i<SurfaceIdentifierMapping::getSides().length();i++){ // stimmt das mit mapping?!
			HSurfaceIdentifier* ident;
			ident->setHParent(ring);
			//ident->setName(a);
			ring->getHSurfaceIdentifications()->append(ident);

		}

		double f = 1.; // 1= vollkreis
		int np = 37;
		for (int ip = 0; ip < np; ip++) {
			double coord = (((double) ip) / ((double) (np - 1)));
			coord *= f;

			double origX = 0. + chord / 2.;
			double origY = 0.;
			double origCircum = coord;

			double xi1 = -chord;
			double xi2 = 0.;
			double xi3 = 0.;

			double z1 = 0.;
			double z2 = 0.;
			double z3 = 1.; // circum direction

			double A [3]= {xi1, xi2, xi3};
			double B [3]= {z1, z2, z3};

			// length of eta: =CHORD!
			double eta[] = {(A[1]*B[2]) - (A[2]*B[2]),  (A[2]*B[0] - A[0]*B[2]), (A[0]*B[1] - A[1]*B[0])};

			HCoordinateSystem3D* planeCos = AssembleFactory::createCoordinatesSystem3DAffine(composition, origX,origY, origCircum, xi1, xi2, xi3, eta[0], eta[1], eta[2], z1, z2, z3);
			HLoftElement* plane = AssembleFactory::createLoftElement(ring, planeCos);

			for (int i=0; i<SurfaceIdentifierMapping::getSides().length();i++) {
				HCurve2D* curve;
				SurfaceIdentifierMapping::getSides().at(i);
				curve->setHParent(plane);
				//curve.set
				HSurfaceIdentifier* ident;// = SIS::getSurfaceIdentifierInstance(ring, SurfaceIdentifierMapping::getSides().at(i));
				if (ident != NULL) {
					curve->getHSurfaceIdentifiers()->append(ident); // reference
				} else {
					cout<<"No Surface identifier"<<endl;
				}
			}
		}
		return nozzle;

	}

};


