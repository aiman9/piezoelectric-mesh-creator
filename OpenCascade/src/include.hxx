#include <DBRep.hxx>
#include <DrawTrSurf.hxx>
#include <gp_Circ2d.hxx>
#include <gp_Pln.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2d_Circle.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <Geom_Geometry.hxx>
#include <Geom_Curve.hxx>
#include <Geom_Circle.hxx>
#include <Geom_Plane.hxx>
#include <GCE2d_MakeCircle.hxx>
#include <GccEnt.hxx>
#include <Geom2dAdaptor_Curve.hxx>
#include <Geom2dGcc_QualifiedCurve.hxx>
#include <Geom2dGcc_Circ2d2TanRad.hxx>
#include <Geom2dGcc_Lin2d2Tan.hxx>
#include <GeomAPI.hxx>
#include <Precision.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS_Solid.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Edge.hxx>
#include <TopExp_Explorer.hxx>
#include <TopExp.hxx>
#include <TopTools_ListIteratorOfListOfShape.hxx>
#include <TopTools_ListOfShape.hxx>
#include <TopTools_IndexedDataMapOfShapeListOfShape.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepOffsetAPI_DraftAngle.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>
#include <BRepTools.hxx>
#include <BRepTools_WireExplorer.hxx>
#include <BRepLProp_SLProps.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepFeat_MakeCylindricalHole.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <BRepFeat_SplitShape.hxx>
#include <BRepOffsetAPI_MakeThickSolid.hxx>
#include <GProp_GProps.hxx>
#include <BRepGProp.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <Geom_BezierCurve.hxx>
#include <gp_Circ.hxx>
#include <BRepOffsetAPI_MakePipe.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>
#include <ShapeBuild_Edge.hxx>
#include <TCollection_AsciiString.hxx>
#include <Geom2d_BezierCurve.hxx>
#include <Law_BSpFunc.hxx>
#include <Law_BSpline.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <TColgp_HArray1OfPnt2d.hxx>
#include <TColStd_HArray1OfReal.hxx>
#include <Geom2dAPI_Interpolate.hxx>
#include <GCPnts_AbscissaPoint.hxx>
#include <GeomAPI_IntCS.hxx>
#include <BRepBuilderAPI_Sewing.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRep_Builder.hxx>
#include <TColgp_HArray2OfPnt2d.hxx>
#include <OSD_Timer.hxx>
#include <gp_Ax2.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <Geom_BSplineCurve.hxx>
#include <GeomConvert.hxx>
#include <GeomConvert_CompCurveToBSplineCurve.hxx>
#include <OSD_Timer.hxx>
#include <vector>
#include <STEPControl_Writer.hxx>
#include <STEPControl_StepModelType.hxx>
#include <GCPnts_TangentialDeflection.hxx>
#include <GCPnts_UniformAbscissa.hxx>
#include <GeomAPI_ProjectPointOnSurf.hxx>
#include <ShapeAnalysis_Surface.hxx>
#include <GeomAbs_Shape.hxx>
#include <BRepExtrema_DistShapeShape.hxx>
#include <BRepAlgo_Section.hxx>
#include <GeomAPI_IntSS.hxx>
#include <IntTools_EdgeFace.hxx>
#include <IntTools_EdgeEdge.hxx>
#include <IntTools_FaceFace.hxx>
#include <TopoDS_Iterator.hxx>
#include <GeomAPI_ProjectPointOnSurf.hxx>
#include <BRepPrimAPI_MakeRevol.hxx>
#include <BRepSweep_Rotation.hxx>
#include <gp_Trsf.hxx>
#include <Sweep_NumShape.hxx>
#include <TopLoc_Location.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <TopAbs_ShapeEnum.hxx>
#include <NCollection_Sequence.hxx>
#include <BRepBuilderAPI_MakeShell.hxx>
#include <BRepBuilderAPI_MakeSolid.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <Geom_RectangularTrimmedSurface.hxx>
#include <Geom_CylindricalSurface.hxx>
#include <BRepLib.hxx>
#include <GeomProjLib.hxx>
#include <math.hxx>
#include <math_TrigonometricFunctionRoots.hxx>
#include <gp_Cylinder.hxx>
#include <STEPControl_Reader.hxx>
#include <IFSelect_ReturnStatus.hxx>
#include <IFSelect_PrintCount.hxx>
#include <Geom_Line.hxx>
#include <GC_MakeCircle.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <GC_MakeSegment.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
 
using namespace std;

IFSelect_ReturnStatus StepWriter(Standard_CString filename, TopoDS_Shape shape){
        STEPControl_Writer writer;
        STEPControl_StepModelType mode = STEPControl_StepModelType::STEPControl_AsIs;
        IFSelect_ReturnStatus stat = writer.Transfer(shape,mode);
        auto status = writer.Write(filename);
        return status;
}
class Utilities
{
public:
	static TopoDS_Face MakeRectXY(gp_Pnt v1, Standard_Real length, Standard_Real breadth, Standard_Real theta)
/*
	Returns a TopoDS_Face object in the shape of a Rectangle parallel to the XY Plane
	The rectangle is plotted beginning from one vertex v1, length and breadth as side parameters, inclined at an angle of theta to the X-axis
*/
{
	  theta=theta*M_PI/180;//converting degrees to radians

	  //defining the remaining vertice points of the rectangle 
	  gp_Pnt v2(v1.X()+length*cos(theta), v1.Y()+length*sin(theta), v1.Z());
	  gp_Pnt v4(v1.X()-breadth*sin(theta), v1.Y()+breadth*cos(theta), v1.Z());
	  gp_Pnt v3(v4.X()+length*cos(theta), v4.Y()+length*sin(theta), v1.Z());

	  //creating the 4 edges by connecting the points
	  Handle(Geom_TrimmedCurve) edge1    = GC_MakeSegment(v1, v2);
	  Handle(Geom_TrimmedCurve) edge2    = GC_MakeSegment(v2, v3);
	  Handle(Geom_TrimmedCurve) edge3    = GC_MakeSegment(v3, v4);
	  Handle(Geom_TrimmedCurve) edge4    = GC_MakeSegment(v4, v1);

	  //converting edges to Topo_DS edge
	  TopoDS_Edge bEdge1 = BRepBuilderAPI_MakeEdge(edge1);
	  TopoDS_Edge bEdge2 = BRepBuilderAPI_MakeEdge(edge2);
	  TopoDS_Edge bEdge3 = BRepBuilderAPI_MakeEdge(edge3);
	  TopoDS_Edge bEdge4 = BRepBuilderAPI_MakeEdge(edge4);
	 
	  TopoDS_Wire bWire = BRepBuilderAPI_MakeWire(bEdge1, bEdge2, bEdge3, bEdge4);
	 
	  TopoDS_Face Rect = BRepBuilderAPI_MakeFace(bWire);
	  return Rect;
	 
}
static TopoDS_Face MakeDisk(gp_Pnt centerPnt, gp_Dir axis, Standard_Real radius)
/*
	Returns a TopoDS_Face object in the shape of a complete disk
	Centered at centerPnt, perpendicular to axis, radius
*/
{
	gp_Ax2 ax2(centerPnt, axis);//defining axis of the circle

	Handle(Geom_Circle) base = GC_MakeCircle(ax2, radius);	//creating Geometrical Circle
	TopoDS_Edge aEdge1 = BRepBuilderAPI_MakeEdge(base);  
  	TopoDS_Wire aWire = BRepBuilderAPI_MakeWire(aEdge1);
  	TopoDS_Face myDisk = BRepBuilderAPI_MakeFace(aWire);	//finally creating required face
  	return myDisk;
}

static TopoDS_Face MakeDisk(gp_Pnt centerPnt, gp_Dir axis, Standard_Real radius, Standard_Real theta, Standard_Real startAngle)
/*
	Returns a TopoDS_Face object in the shape of a sector of a disk
	Centered at centerPnt, perpendicular to axis, radius, sector of angle theta, startAngle defines initial angle for sector on a disk
*/
{
	  gp_Ax2 ax2(centerPnt, axis);	//defining axis of the circle

	  Handle(Geom_Circle) base = GC_MakeCircle(ax2, radius);	//defining whole circle
	  gp_Pnt aPnt1, aPnt2;
	  base->D0(startAngle, aPnt1);	//choosing start point for the sector, on the circumference of the whole circle
	  base->D0(startAngle+theta, aPnt2);	//choosing end point for the sector, on the circumference of the whole circle
	 
	  Handle(Geom_TrimmedCurve) myArc = GC_MakeArcOfCircle(base->Circ(), aPnt1, aPnt2, true);	//define arc between points aPnt1 and aPnt2
	  Handle(Geom_TrimmedCurve) aSegment1    = GC_MakeSegment(aPnt1, centerPnt);
	  Handle(Geom_TrimmedCurve) aSegment2    = GC_MakeSegment(centerPnt, aPnt2);
	 
	  TopoDS_Edge arcEdge2 = BRepBuilderAPI_MakeEdge(myArc);
	  TopoDS_Edge arcEdge3 = BRepBuilderAPI_MakeEdge(aSegment1);
	  TopoDS_Edge arcEdge4 = BRepBuilderAPI_MakeEdge(aSegment2);
	 
	  TopoDS_Wire aWire5 = BRepBuilderAPI_MakeWire(arcEdge2,arcEdge3,arcEdge4);
	  TopoDS_Face myFaceProfile = BRepBuilderAPI_MakeFace(aWire5);	//finally creating required face
	  return myFaceProfile;
}

};