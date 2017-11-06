#include "Export.h"

#include "HSurfaceIdentifier.h"
#include "HLoft.h"
#include "CoordinateTransformation.h"
#include "LoftElementSupport.h"
#include "tesselation/Tesselation.h"
#include "tesselation/Triangle.h"
#include "../hykops_core/CoordinateTransformation.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <QDebug>

using namespace std;


/**
 * Export a HComposition to coloured STL format
 * @brief Export::exportSTL
 * @param filename the filename of the STL file
 * @param composition the composition
 * @return 0 if success
 */
int Export::exportSTL(QString filename, HComposition *composition){
    FILE *fp = fopen( filename.toLatin1(), "w" ); // Open file for writing
    int nu = 50;
    int nv = 50;

    // loop through all components of the composition
    foreach(HComponent *comp, *(composition->getHComponents()))
    {
        // loop through all lofts of the component
        foreach(HLoft *loft, *(comp->getHLofts()))
        {
            // loop through all surfaces of the loft
            foreach(HSurfaceIdentifier *ident, *(loft->getHSurfaceIdentifications()))
            {
                writeSTLSurface(fp, loft, ident, nu, nv);
            }
        }
    }
    fclose(fp);
    return 0;
}

/**
 * Export HComponent to coloured STL format
 * @brief Export::exportSTL
 * @param filename the filename of the STL file
 * @param component the component to export
 * @param nu the number of equidistant points in loft direction
 * @param nv the number of equidistant points in the direction of the curves
 * @return 0 if success
 */
int Export::exportSTL(QString filename, HComponent *component, int nu, int nv){

    FILE *fp = fopen( filename.toLatin1(), "w" ); // Open file for writing

// loop through all lofts of the component
    foreach(HLoft *loft, *(component->getHLofts()))
    {        
// loop through all surfaces of the loft
        foreach(HSurfaceIdentifier *ident, *(loft->getHSurfaceIdentifications()))
        {
            writeSTLSurface(fp, loft, ident, nu, nv);
        }
    }
    fclose(fp);
    return 0;
}

/**
 * Export HLoft to coloured STL format
 * @brief Export::exportSTL
 * @param filename the filename of the STL file
 * @param ident the surface identifier
 * @param loft the loft to export
 * @return 0 if success
 */
int Export::exportSTL(QString filename, HLoft* loft, HSurfaceIdentifier* ident)
{
    FILE *fp = fopen( filename.toLatin1(), "w" ); // Open file for writing
    writeSTLSurface(fp, loft, ident);
    fclose(fp);
    return 0;
}

int Export::exportSTL(QString filename, HLoft *loft, HSurfaceIdentifier *ident, double maxuSize_, double maxvSize_, double maxRatio_, double maxSkew_, double curvatureFactor_, double minSize_, double maxSize_, int maxRecursionDepth_)
{
    FILE *fp = fopen( filename.toLatin1(), "w" ); // Open file for writing
    writeSTLSurface(fp, loft, ident, maxuSize_, maxvSize_, maxRatio_, maxSkew_, curvatureFactor_, minSize_, maxSize_, maxRecursionDepth_);
    fclose(fp);
    return 0;
}

int Export::exportSTL(QString filename, HComponent* component, double maxuSize_, double maxvSize_, double maxRatio_, double maxSkew_, double curvatureFactor_, double minSize_, double maxSize_, int maxRecursionDepth_)
{
    FILE *fp = fopen( filename.toLatin1(), "w" ); // Open file for writing

    for(int il = 0; il < component->getHLofts()->size(); il++)
    {
        HLoft* loft = component->getHLofts()->at(il);
        for(int is = 0; is < loft->getHSurfaceIdentifications()->size(); is++)
        {
            HSurfaceIdentifier* ident = loft->getHSurfaceIdentifications()->at(is);
            writeSTLSurface(fp, loft, ident, maxuSize_, maxvSize_, maxRatio_, maxSkew_, curvatureFactor_, minSize_, maxSize_, maxRecursionDepth_);
        }
    }
    fclose(fp);
    return 0;
}

int Export::exportSTL(QString filename, HComposition* composition, double maxuSize_, double maxvSize_, double maxRatio_, double maxSkew_, double curvatureFactor_, double minSize_, double maxSize_, int maxRecursionDepth_)
{
    FILE *fp = fopen( filename.toLatin1(), "w" ); // Open file for writing
    for(int ic = 0; ic < composition->getHComponents()->size(); ic++)
    {
        HComponent* comp = composition->getHComponents()->at(ic);
        for(int il = 0; il < comp->getHLofts()->size(); il++)
        {
            HLoft* loft = comp->getHLofts()->at(il);
            for(int is = 0; is < loft->getHSurfaceIdentifications()->size(); is++)
            {
                HSurfaceIdentifier* ident = loft->getHSurfaceIdentifications()->at(is);
                writeSTLSurface(fp, loft, ident, maxuSize_, maxvSize_, maxRatio_, maxSkew_, curvatureFactor_, minSize_, maxSize_, maxRecursionDepth_);
            }
        }
    }
    fclose(fp);
    return 0;
}

/**
 * Export equidistant 3D-point-patterns of a component
 * @brief Export::exportTXT
 * @param filename the filename of the text file
 * @param component the component to export
 * @param nu the number of equidistant points in loft direction
 * @param nv the number of equidistant points in the direction of the curves
 * @return 0 if success
 */
int Export::exportTXT(QString filename, HComponent *component, int nu, int nv)
{
    FILE *fp = fopen( filename.toLatin1(), "w" ); // Open file for writing

// loop through all lofts of the component
    foreach(HLoft *loft, *(component->getHLofts()))
    {
// loop through all surfaces of the loft
        foreach(HSurfaceIdentifier *ident, *(loft->getHSurfaceIdentifications()))
        {
            writeTXTSurface(fp, loft, ident, nu, nv);
        }
    }
    fclose(fp);
    return 0;
}

/**
 * Write an STL pattern to a given FILE for a given HLoft and surface identifier
 * @brief Export::writeSTLSurface
 * @param fp the FILE (must be open)
 * @param loft the loft to export
 * @param ident the surface identifier to export
 * @param nu the number of equidistant points in loft direction
 * @param nv the number of equidistant points in the direction of the curves
 * @return 0 if success
 */
int Export::writeSTLSurface(FILE *fp, HLoft *loft, HSurfaceIdentifier *ident, int nu, int nv)
{
    QString compName = loft->getHComponent()->getName();
    QString loftName = loft->getName();
    QString surfName = ident->getName();
    QVector3D p1, p2, p3;
    CoordinateTransformation::clearReverseMap();
    fprintf(fp, "solid %s\n", surfName.trimmed().toLatin1().constData());

    for(int i = 0; i < (nu-1); i++) // loftwise
    {
        double u0 = ((double)(i))/((double)(nu-1));
        double u1 = ((double)(i+1))/((double)(nu-1));
        double um = (u0+u1)/2.;
        for(int j = 0; j < (nv-1); j++) // "chord"wise
        {
            double v0 = ((double)(j))/((double)(nv-1));
            double v1 = ((double)(j+1))/((double)(nv-1));
            double vm = (v0+v1)/2.;

            // TODO: remove this, only for testing!
            v0 = v0 * v0; // quadratic cluster on leading edge
            v1 = v1 * v1; // quadratic cluster on leading edge
            vm = vm * vm; // quadratic cluster on leading edge

            // facet 1
            p1 = CoordinateTransformation::toGlobalCoordinate(loft, ident, u0, v0, false);
            p2 = CoordinateTransformation::toGlobalCoordinate(loft, ident, um, vm, false);
            p3 = CoordinateTransformation::toGlobalCoordinate(loft, ident, u1, v0, false);
            writeSTLFacet(fp, p1, p2, p3);

            // facet 2
            p1 = CoordinateTransformation::toGlobalCoordinate(loft, ident, u0, v1, false);
            p2 = CoordinateTransformation::toGlobalCoordinate(loft, ident, um, vm, false);
            p3 = CoordinateTransformation::toGlobalCoordinate(loft, ident, u0, v0, false);
            writeSTLFacet(fp, p1, p2, p3);

            // facet 3
            p1 = CoordinateTransformation::toGlobalCoordinate(loft, ident, u1, v1, false);
            p2 = CoordinateTransformation::toGlobalCoordinate(loft, ident, um, vm, false);
            p3 = CoordinateTransformation::toGlobalCoordinate(loft, ident, u0, v1, false);
            writeSTLFacet(fp, p1, p2, p3);

            // facet 4
            p1 = CoordinateTransformation::toGlobalCoordinate(loft, ident, u1, v0, false);
            p2 = CoordinateTransformation::toGlobalCoordinate(loft, ident, um, vm, false);
            p3 = CoordinateTransformation::toGlobalCoordinate(loft, ident, u1, v1, false);
            writeSTLFacet(fp, p1, p2, p3);
        }
    }
    fprintf(fp, "endsolid %s\n", surfName.trimmed().toLatin1().constData());

    return 0;
}

int Export::writeSTLSurface(FILE *fp, HLoft *loft, HSurfaceIdentifier *ident)
{
    return writeSTLSurface(fp, loft, ident, 0.5, 0.5, 3., 1.5, 5., 1.e-3, 5.e-3, 7);
}

/**
 * Write an STL pattern to a given FILE for a given HLoft and surface identifier via delaunay-triangulation
 * @brief Export::writeSTLSurface
 * @param fp the FILE (must be open)
 * @param loft the loft to export
 * @param ident the surface identifier to export
 * @return 0 if success
 */
int Export::writeSTLSurface(FILE *fp, HLoft *loft, HSurfaceIdentifier *ident, double maxuSize_, double maxvSize_, double maxRatio_, double maxSkew_, double curvatureFactor_, double minSize_, double maxSize_, int maxRecursionDepth_)
{
    qDebug("start seeding points...");
    Tesselation* t = new Tesselation(loft, ident, maxuSize_, maxvSize_, maxRatio_, maxSkew_, curvatureFactor_, minSize_, maxSize_, maxRecursionDepth_);
    qDebug("finished\n");
    QList<Triangle> tl = t->getTriangleList();


    QString compName = loft->getHComponent()->getName();
    QString loftName = loft->getName();
    QString surfName = ident->getName();
    QVector3D p1, p2, p3;
    CoordinateTransformation::clearReverseMap();
    fprintf(fp, "solid %s\n", surfName.trimmed().toLatin1().constData());
    for(int i = 0; i < tl.size(); i++)
    {
        Triangle tri = tl.at(i);

        QPointF uv1 = t->getDelaunayPoints().at(tri.at(0)).toPoint();
        QPointF uv2 = t->getDelaunayPoints().at(tri.at(1)).toPoint();
        QPointF uv3 = t->getDelaunayPoints().at(tri.at(2)).toPoint();
        p1 = CoordinateTransformation::toGlobalCoordinate(loft, ident, uv1.x(), uv1.y(), false);
        p2 = CoordinateTransformation::toGlobalCoordinate(loft, ident, uv2.x(), uv2.y(), false);
        p3 = CoordinateTransformation::toGlobalCoordinate(loft, ident, uv3.x(), uv3.y(), false);
        writeSTLFacet(fp, p1, p2, p3);
    }

    fprintf(fp, "endsolid %s\n", surfName.trimmed().toLatin1().constData());
    delete t;
    return 0;
}



/**
 * Write a single facet to a file
 * @brief Export::writeSTLFacet
 * @param fp the FILE (must be open)
 * @param p1 the 1st vertex
 * @param p2 the 2nd vertex
 * @param p3 the 3rd vertex
 * @return 0 if success
 */
int Export::writeSTLFacet(FILE *fp, QVector3D p1, QVector3D p2, QVector3D p3)
{
// Geometric limit
    double max = 1.e9;
    p1.setX((p1.x() > max)?max:p1.x());
    p1.setY((p1.y() > max)?max:p1.y());
    p1.setZ((p1.z() > max)?max:p1.z());
    p2.setX((p2.x() > max)?max:p2.x());
    p2.setY((p2.y() > max)?max:p2.y());
    p2.setZ((p2.z() > max)?max:p2.z());
    p3.setX((p3.x() > max)?max:p3.x());
    p3.setY((p3.y() > max)?max:p3.y());
    p3.setZ((p3.z() > max)?max:p3.z());
    p1.setX((p1.x() < -max)?-max:p1.x());
    p1.setY((p1.y() < -max)?-max:p1.y());
    p1.setZ((p1.z() < -max)?-max:p1.z());
    p2.setX((p2.x() < -max)?-max:p2.x());
    p2.setY((p2.y() < -max)?-max:p2.y());
    p2.setZ((p2.z() < -max)?-max:p2.z());
    p3.setX((p3.x() < -max)?-max:p3.x());
    p3.setY((p3.y() < -max)?-max:p3.y());
    p3.setZ((p3.z() < -max)?-max:p3.z());

    QVector3D w1 = p1-p2;
    QVector3D w2 = p3-p2;
    QVector3D n = QVector3D::crossProduct(w1, w2);
    double l = n.length();
    if(l > 1.e-9)
    {
        n.setX(n.x()/l);
        n.setY(n.y()/l);
        n.setZ(n.z()/l);
    }
    l = n.length();
    fprintf(fp, "   facet normal %16.12f %16.12f %16.12f\n", n.x(), n.y(), n.z());
    fprintf(fp, "       outer loop\n");
    fprintf(fp, "           vertex %16.8f %16.8f %16.8f\n", p1.x(), p1.y(), p1.z());
    fprintf(fp, "           vertex %16.8f %16.8f %16.8f\n", p2.x(), p2.y(), p2.z());
    fprintf(fp, "           vertex %16.8f %16.8f %16.8f\n", p3.x(), p3.y(), p3.z());
    fprintf(fp, "       endloop\n");
    fprintf(fp, "   endfacet\n");
    return 0;
}

/**
 * Write point data to a text file
 * @brief Export::writeTXTSurface
 * @param fp the FILE (must be open)
 * @param loft the loft
 * @param ident the surface identifier
 * @param nu the number of equidistant points in loft direction
 * @param nv the number of equidistant points in the direction of the curves
 * @return 0 if success
 */
int Export::writeTXTSurface(FILE *fp, HLoft *loft, HSurfaceIdentifier *ident, int nu, int nv)
{
    QString compName = loft->getHComponent()->getName();
    QString loftName = loft->getName();
    QString surfName = ident->getName();
    QVector3D p;

// write equidistan points on uv-surface
    CoordinateTransformation::clearReverseMap();
    fprintf(fp, "# %s\n", surfName.trimmed().toLatin1().constData());
    for(int i = 0; i < (nu); i++)
    {
        double u0 = ((double)(i))/((double)(nu-1));
        for(int j = 0; j < (nv); j++)
        {
            double v0 = ((double)(j))/((double)(nv-1));
            double x, y, z;
            p = CoordinateTransformation::toGlobalCoordinate(loft, ident, u0, v0, false);
            x = p.x();
            y = p.y();
            z = p.z();
            fprintf(fp, "%16.8f %16.8f %16.8f\n", x, y, z);
        }
    }
    fprintf(fp, "\n");
    return 0;
}


//get 3D triangle coordinates
vector<float> Export::GetTriangleCoordinates(Tesselation* t, HLoft* loft,  HSurfaceIdentifier* ident)
{
	        QList<Triangle> tl = t->getTriangleList();
	        vector<float> PointList;
	        QVector3D p1, p2, p3;
	        float p1x, p1y, p1z, p2x, p2y, p2z, p3x, p3y, p3z;

	        for(int i = 0; i < tl.size(); i++)
	            {
	            Triangle tri = tl.at(i);
	            //transform 2D triangle coordinates to 3D
	                    QPointF uv1 = t->getDelaunayPoints().at(tri.at(0)).toPoint();
	                    QPointF uv2 = t->getDelaunayPoints().at(tri.at(1)).toPoint();
	                    QPointF uv3 = t->getDelaunayPoints().at(tri.at(2)).toPoint();
	                    p1 = CoordinateTransformation::toGlobalCoordinate(loft, ident, uv1.x(), uv1.y(), false);
	                    p2 = CoordinateTransformation::toGlobalCoordinate(loft, ident, uv2.x(), uv2.y(), false);
	                    p3 = CoordinateTransformation::toGlobalCoordinate(loft, ident, uv3.x(), uv3.y(), false);
	            //get 3D components
	                    p1x=p1.x();
	                    p1y=p1.y();
	                    p1z=p1.z();
	                    p2x=p2.x();
	                    p2y=p2.y();
	                    p2z=p2.z();
	                    p3x=p3.x();
	                    p3y=p3.y();
	                    p3z=p3.z();
	             //add 3D components to list
                        //point 1
	                    PointList.push_back(p1x);
	                    PointList.push_back(p1y);
	                    PointList.push_back(p1z);
                        //point 2
	                    PointList.push_back(p2x);
	                    PointList.push_back(p2y);
	                    PointList.push_back(p2z);
                        //point 3
	                    PointList.push_back(p3x);
	                    PointList.push_back(p3y);
	                    PointList.push_back(p3z);
	            }
	        return PointList;
}

//split Pointlist to x y z and remove mutliple points
vector<vector<float>> Export::getSinglePointList(vector<float> PointList)
{
	vector<vector<float>> SinglePoints;
	// create List with x, y, z values
	vector<float> Xlist;
	vector<float> Ylist;
	vector<float> Zlist;

	for (int i=0; i<PointList.size(); i=i+3 ){
		Xlist.push_back(PointList.at(i));
		Ylist.push_back(PointList.at(i+1));
		Zlist.push_back(PointList.at(i+2));
	}
	//remove mutliple occuring points
	for (int i=0; i<Xlist.size(); i++){
		for (int j=i+1; j<Xlist.size(); j++){
			if((Xlist.at(i)==Xlist.at(j) && Ylist.at(i)==Ylist.at(j) && Zlist.at(i)==Zlist.at(j))){
				Xlist.erase(Xlist.begin()+j);
				Ylist.erase(Ylist.begin()+j);
				Zlist.erase(Zlist.begin()+j);
                //prevent any point from being skipped
				j=j-1;
			}
		}
	}

	//create x y z list with unique points
		SinglePoints.push_back(Xlist);
		SinglePoints.push_back(Ylist);
		SinglePoints.push_back(Zlist);

		return SinglePoints;

	}


//Index reference to unique point list
vector<int> Export::getIndexList(vector<vector<float>> SinglePoints, vector<float> PointList){
	// create index list
	vector<int> indexlist;

	for(int i=0; i<PointList.size(); i=i+3){
		for(int j=0; j<SinglePoints.at(0).size(); j++){
	//create points by index
			if((PointList.at(i)==SinglePoints.at(0).at(j) && PointList.at(i+1)==SinglePoints.at(1).at(j) && PointList.at(i+2)==SinglePoints.at(2).at(j))){
				indexlist.push_back(j);
	        }
		}
	}
	return indexlist;
}


//write ouput ftr file
int Export::exportFTR(HLoft *loft, HSurfaceIdentifier *ident, double maxuSize_, double maxvSize_, double maxRatio_, double maxSkew_, double curvatureFactor_, double minSize_, double maxSize_, int maxRecursionDepth_)
{

Tesselation* t = new Tesselation(loft, ident, maxuSize_, maxvSize_, maxRatio_, maxSkew_, curvatureFactor_, minSize_, maxSize_, maxRecursionDepth_);

//get unique points and indexlist
vector<float> PointList = GetTriangleCoordinates(t, loft, ident);
vector<vector<float>> SinglePoints= getSinglePointList(PointList);
vector<int> IndexList = getIndexList(SinglePoints, PointList);

//write output
FILE *fp = fopen("test.ftr", "w" ); // Open file for writing
fprintf(fp,"%d \n(\n",SinglePoints.at(0).size());
for(int i=0; i<SinglePoints.at(0).size();i++){
fprintf(fp, "(%f %f %f)\n", SinglePoints.at(0).at(i), SinglePoints.at(1).at(i), SinglePoints.at(2).at(i));
}

fprintf(fp,"\n%d \n(\n",IndexList.size());
for(int i=0; i<IndexList.size();i=i+3){
fprintf(fp, "((%d %d %d) )\n", IndexList.at(i), IndexList.at(i+1), IndexList.at(i+2));
	}

return 0;
}


