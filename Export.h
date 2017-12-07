#ifndef EXPORT_H
#define EXPORT_H

#include "HComposition.h"
#include "HComponent.h"
#include "HSurfaceIdentifier.h"
#include "HLoft.h"
#include "tesselation/Tesselation.h"

#include <iostream>

using namespace std;

/*
 * Remarks:
 * This must not be a class, especially when considering it in an OOP fashion.
 * Either write a base class that handles the export in any format and derive
 * STL etc. from it or *only* implement functions that write stl files. The
 * static stuff will lead to problems during production, this is not Java :).
 * What about the constructor? Destructor?
 */
class Export
{
public:
//! Export a composition to coloured STL
    static int exportSTL(QString filename, HComposition *composition);
//! export a component to coloured STL
    static int exportSTL(QString filename, HComponent *component, int nu, int nv);
//! export a loft to coloured STL
    static int exportSTL(QString filename, HLoft* loft, HSurfaceIdentifier* ident);
//! export a loft to coloured STL with mesh parameters
    static int exportSTL(QString filename, HLoft *loft, HSurfaceIdentifier *ident, double maxuSize_, double maxvSize_, double maxRatio_, double maxSkew_, double curvatureFactor_, double minSize_, double maxSize_, int maxRecursionDepth_);
//! export a component to coloured STL with mesh parameters
    static int exportSTL(QString filename, HComponent* component, double maxuSize_, double maxvSize_, double maxRatio_, double maxSkew_, double curvatureFactor_, double minSize_, double maxSize_, int maxRecursionDepth_);
//! export a composition to coloured STL with mesh parameters
    static int exportSTL(QString filename, HComposition* composition, double maxuSize_, double maxvSize_, double maxRatio_, double maxSkew_, double curvatureFactor_, double minSize_, double maxSize_, int maxRecursionDepth_);
//! export a point cloud of a component to a text file
    static int exportTXT(QString filename, HComponent *component, int nu, int nv);
//! export a loft to ftr file
    static int exportFTR(QString filename, HComposition *composition, double maxuSize_, double maxvSize_, double maxRatio_, double maxSkew_, double curvatureFactor_, double minSize_, double maxSize_, int maxRecursionDepth_);

private:
//! write a given loft and surface identifier to a corresponding STL section
    static int writeSTLSurface(FILE *fp, HLoft *loft, HSurfaceIdentifier *ident, int nu, int nv);
//! write a given loft and surface identifier to a corresponding STL section via delaunay triangulation
    static int writeSTLSurface(FILE *fp, HLoft *loft, HSurfaceIdentifier *ident);
//! write a given loft and surface identifier to a corresponding STL section via delaunay triangulation with refinement parameters
    static int writeSTLSurface(FILE *fp, HLoft *loft, HSurfaceIdentifier *ident, double maxuSize_, double maxvSize_, double maxRatio_, double maxSkew_, double curvatureFactor_, double minSize_, double maxSize_, int maxRecursionDepth_);
//! write a single STL facet
    static int writeSTLFacet(FILE *fp, QVector3D p1, QVector3D p2, QVector3D p3);
//! write a point cloud of a loft and surface identifier to a text file
    static int writeTXTSurface(FILE *fp, HLoft *loft, HSurfaceIdentifier *ident, int nu, int nv);
//! get triangle points in 3D coordinates
    static vector<vector<float>> GetTriangleCoordinates(HComposition *composition, double maxuSize_, double maxvSize_, double maxRatio_, double maxSkew_, double curvatureFactor_, double minSize_, double maxSize_, int maxRecursionDepth_);
//! reduce 3D points to unique point list
    static vector<vector<float>> getSinglePointList(vector<vector<float>> PointList);
//! index 3D points to list
    static vector<vector<int>> getIndexList(vector<vector<float>> SinglePoints, vector<vector<float>> PointList);

};

#endif // EXPORT_H
