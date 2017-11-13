//#include "HPoint3D.h"
//#include "AssembleFactory.h"
//#include "HComposition.h"
//#include "HComponent.h"
//#include "HLoft.h"
//#include "HLoftElement.h"
//#include "HCurve2D.h"
//#include "HCoordinateSystem3D.h"
//#include "LoftElementSupport.h"
//#include "CoordinateTransformation.h"
//#include "Export.h"
//#include "SurfaceUtil.h"
//#include "PFFParser.h"
//#include "CompositionSerializer.h"
//#include "CompositionFactory.h"
//#include "tesselation/Tesselation.h"
//#include "tesselation/Triangle.h"
#include "RudergeoParser.h"
//#include "RudderFactory.h"
//#include <fstream>
//#include <sstream>
#include <iostream>
#include "genericDuct.h"
//#include "../hykops_core/C_Interface.h"
//#include "../serializeemf/domwriter.h"

using namespace std;

int main()
{
    cout << "Lit, fam" << endl;
    genericDuct<int,float> duct(1, 2.0);

    if(true)
    {
        HComposition* composition = CompositionFactory::create("Rudergeo", "Rudergeo composition");
        RudergeoParser* rp = new RudergeoParser();
        char* filename = "/tmp/libs/Rudergeo2.out";
        char* loftspline = "HERMITE";
        char* profilespline = "LINEAR"; // Problem: bei anderem als linear absturz oder kaputte geometrie...
        QString name = QString::fromLatin1(filename);
        QString description = QString::fromLatin1(filename);
        double bulbHeight = 2.05;
        HComponent* comp = rp->parse(composition, filename, loftspline, profilespline, name, description, bulbHeight);

        double maxUSize = 0.1;
        double maxVSize = 0.1;
        double maxRatio = 2.;
        double maxSkew = .0 * (3.14159/180.);
        double curvatureFactor = .05; // gross: nur da verfeinern, wo krümmung. In verbindung mit hoher rekursionstiefe sinnvoll
        double minSize = 5.e-5;
        double maxSize = 5.e-1;
        int recursionDepth = 9;

        Export::exportSTL("/tmp/libs/rudder.stl", composition, maxUSize, maxVSize, maxRatio, maxSkew, curvatureFactor, minSize, maxSize, recursionDepth );

    }
}
