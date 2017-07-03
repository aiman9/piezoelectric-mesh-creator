// QrDraw includes
//#include <QrDraw.h>
//#include <QrDraw_DrawTestSuite.h>
 
// OCCT includes
#include "include.hxx"


static int anglePiezo(Draw_Interpretor& di, Standard_Integer, const char**)
{
  gp_Pnt centerPnt(0, 0, 0);
  gp_Dir axis = gp::DZ();  

  //initializing parameters
  Standard_Real radius=0.;
  Standard_Real height=0.;
  Standard_Real angle=0.;

  //Now reading input parameters from the file
  string line;
  double a;
  ifstream myfile("angleinput.txt");
  
  if(getline(myfile,line)){
	a=atof(line.c_str());
	radius=a;
  }
  if(getline(myfile,line)){
	a=atof(line.c_str());
	height=a;
  }
  if(getline(myfile,line)){
	a=atof(line.c_str());
	angle=M_PI*a/180;
  }
  else cout<<"Input Error";
 
  //Create face of bottom disk
  TopoDS_Face myFaceProfile = Utilities::MakeDisk(centerPnt, axis, radius); 
  
  //Extrude the base disk to form the cylinder
  gp_Vec aPrismVec(0, 0, height);
  TopoDS_Shape neck = BRepPrimAPI_MakePrism(myFaceProfile, aPrismVec);
 
  //Define the three faces of the cylinder
  TopoDS_Face bottomFace;
  TopoDS_Face topFace;
  TopoDS_Face coat;

  Handle(Geom_Plane) bottomPlane, topPlane;
  Handle(Geom_CylindricalSurface) cyl;
  Standard_Real zMin = 0.;
 
  for(TopExp_Explorer aFaceExplorer(neck, TopAbs_FACE) ; aFaceExplorer.More() ; aFaceExplorer.Next()){
      TopoDS_Face aFace = TopoDS::Face(aFaceExplorer.Current());
      Handle(Geom_Surface) aSurface = BRep_Tool::Surface(aFace);
 
      cout << aSurface->DynamicType() << endl;
 
      if(aSurface->DynamicType() == STANDARD_TYPE(Geom_Plane))//Plane Surface
      {
        Handle(Geom_Plane) aPlane = Handle(Geom_Plane)::DownCast(aSurface);
        gp_Pnt aPnt = aPlane->Location();

        if(aPnt.Z() == 0.)//Base surface
        {
          //zMax = aPnt.Z();
          bottomPlane = aPlane;
          bottomFace = aFace;
        }
        else //top surface
        {
	  	  topFace = aFace;
	  	  topPlane = aPlane;
		}
      }
      else if(aSurface->DynamicType() == STANDARD_TYPE(Geom_CylindricalSurface))//Cylinder surface
      {
        Handle(Geom_CylindricalSurface) aPlane = Handle(Geom_CylindricalSurface)::DownCast(aSurface);
        cyl = aPlane;
		coat = aFace;
      }
  }

  //creating bottom Electrode surface and non-Electrode surface
  TopoDS_Face bottomElectrode = Utilities::MakeDisk(centerPnt, axis, radius, angle, 0.);
  TopoDS_Face bottomSurface = Utilities::MakeDisk(centerPnt, axis, radius, (2*M_PI-angle), angle);

  //creting top electrode and non-Electrode surface
  gp_Pnt centerTop(0, 0, height);
  TopoDS_Face topElectrode = Utilities::MakeDisk(centerTop, axis, radius, angle, M_PI);
  TopoDS_Face topSurface = Utilities::MakeDisk(centerTop, axis, radius, (2*M_PI-angle), (M_PI+angle));

  //sewing required surfaces together to obtain finalShape
  BRepBuilderAPI_Sewing Sewing;
    Sewing.Add(topElectrode);
    Sewing.Add(topSurface);
    Sewing.Add(coat);
    Sewing.Add(bottomElectrode);
    Sewing.Add(bottomSurface);
    Sewing.Perform();
    TopoDS_Shape finalShape = Sewing.SewedShape();
 
  DBRep::Set("finalShape", finalShape);
  //DBRep::Set("result", result);
  //DBRep::Set("topFace", topFace);
  //DBRep::Set("coat", coat);
  //DBRep::Set("bottomFace", bottomFace);
 
 
  cout << "Sewing completed" << endl;
 
  StepWriter("anglecylinder.stp", finalShape);
 
}








static int TripleRing(Draw_Interpretor& di, Standard_Integer, const char**)
{
  gp_Pnt centerPnt(0, 0, 0);
  gp_Dir axis = gp::DZ();
 
  Standard_Real radius = 30.;
  Standard_Real inrad = 10.;
  Standard_Real outrad = 20.;
  Standard_Real inradtop = 15.;
  Standard_Real outradtop = 25.;	
  Standard_Real height = 50.;

  string line;
  int a;
  ifstream myfile("ringinput.txt");
  for(int i=0;i<6;i++)
  {
	if(getline(myfile,line)){
	a=atoi(line.c_str());
	switch(i)
	{
	  case 0:
	  radius=a;
	  break;
	  case 1:
	  height=a;
	  break;
	  case 2:
	  inradtop=a;
	  break;
	  case 3:
	  outradtop=a;
	  break;
	  case 4:
	  inrad=a;
	  break;
	  case 5:
	  outrad=a;
	  break;
	}
	}
	else cout<<"Input Error";
  }
 
  TopoDS_Face myFaceProfile = Utilities::MakeDisk(centerPnt, axis, radius);

  //Defining top ring
  gp_Pnt topCenter(0,0,height);
  
  TopoDS_Face outDiskTop = Utilities::MakeDisk(topCenter, axis, outradtop);
  TopoDS_Face inDiskTop = Utilities::MakeDisk(topCenter, axis, inradtop);
  
  TopoDS_Shape topring = BRepAlgoAPI_Cut(outDiskTop, inDiskTop);

  //Defining bottom ring
  TopoDS_Face outDisk = Utilities::MakeDisk(centerPnt, axis, outrad);
  TopoDS_Face inDisk = Utilities::MakeDisk(centerPnt, axis, inrad);

  TopoDS_Shape bottomring = BRepAlgoAPI_Cut(outDisk, inDisk);
  
  //Extruding myFaceProfile to form a cylinder
  gp_Vec aPrismVec(0, 0, height); 
  TopoDS_Shape fullCyl = BRepPrimAPI_MakePrism(myFaceProfile, aPrismVec);
 
 //Defining variables to separate the surfaces of fullCyl
  TopoDS_Face bottomFace;
  TopoDS_Face topFace;
  TopoDS_Face coat;

  Handle(Geom_Plane) bottomPlane;
  Handle(Geom_Plane) topPlane;
  Handle(Geom_CylindricalSurface) cyl;
  Standard_Real zMin = 0.;
 
  for(TopExp_Explorer aFaceExplorer(fullCyl, TopAbs_FACE) ; aFaceExplorer.More() ; aFaceExplorer.Next())
  {
      TopoDS_Face aFace = TopoDS::Face(aFaceExplorer.Current());
      Handle(Geom_Surface) aSurface = BRep_Tool::Surface(aFace);
 
      cout << aSurface->DynamicType() << endl;
 
      if(aSurface->DynamicType() == STANDARD_TYPE(Geom_Plane))//if the surface is plane
      {
        Handle(Geom_Plane) aPlane = Handle(Geom_Plane)::DownCast(aSurface);
        gp_Pnt aPnt = aPlane->Location();

        if(aPnt.Z() == 0.)//at Z=0, hence bottomFace
        {
          //zMax = aPnt.Z();
          bottomPlane = aPlane;
      	  bottomFace = aFace;
        }
		else
		{
	  	topPlane = aPlane;
	  	topFace = aFace;
		}
      }
      else if(aSurface->DynamicType() == STANDARD_TYPE(Geom_CylindricalSurface))//Cylindrical surface
      {
        Handle(Geom_CylindricalSurface) aPlane = Handle(Geom_CylindricalSurface)::DownCast(aSurface);
        cyl = aPlane;
		coat = aFace;
      }
  }

  //Cutting the rings from top and bottom surfaces
  TopoDS_Shape bottomcut = BRepAlgoAPI_Cut(bottomFace, bottomring);
  TopoDS_Shape topcut = BRepAlgoAPI_Cut(topFace, topring);
 

  //Sewing the required surfaces together
  BRepBuilderAPI_Sewing Sewing;
    Sewing.Add(topcut);
    Sewing.Add(topring);
    Sewing.Add(coat);
    Sewing.Add(bottomcut);
    Sewing.Add(bottomring);
    Sewing.Perform();
    TopoDS_Shape finalShape = Sewing.SewedShape();
    
  DBRep::Set("finalShape", finalShape);
  
  cout << "Sewing completed" << endl;
 
  StepWriter("ringcylinder.stp", finalShape);
}




static int Cube(Draw_Interpretor& di, Standard_Integer, const char**)
{

  //Default values
  Standard_Real Xlength=30.;
  Standard_Real Ylength=30.;
  Standard_Real height=20.;
  Standard_Real radius=5.;
  Standard_Real topX=10.;
  Standard_Real topY=15.;
  Standard_Real bottomX=20.;
  Standard_Real bottomY=15.;

  //input file values
  string line;
  double a;
  ifstream myfile("cubeinput.txt");
  
for(int i=0;i<8;i++)
  {
	if(getline(myfile,line)){
	a=atof(line.c_str());
	switch(i)
	{
	  case 0:
	  Xlength=a;
	  break;
	  case 1:
	  Ylength=a;
	  break;
	  case 2:
	  height=a;
	  break;
	  case 3:
	  radius=a;
	  break;
	  case 4:
	  topX=a;
	  break;
	  case 5:
	  topY=a;
	  break;
	  case 6:
	  bottomX=a;
	  break;
	  case 7:
	  bottomY=a;
	  break;
	}
	}
	else cout<<"Input Error";
  }

  gp_Pnt p1(0, 0, 0);
  TopoDS_Face base = Utilities::MakeRectXY(p1, Xlength, Ylength, 0);
 
  gp_Vec aPrismVec(0, 0, height);
 
  TopoDS_Shape cube = BRepPrimAPI_MakePrism(base, aPrismVec);
 
  TopoDS_Face bottomFace;
  TopoDS_Face topFace;
  TopoDS_Face coat [4];//defines an array to store each of the 4 walls of the cube

  Handle(Geom_Plane) bottomPlane, topPlane;
  int i=0;

 
  for(TopExp_Explorer aFaceExplorer(cube, TopAbs_FACE) ; aFaceExplorer.More() ; aFaceExplorer.Next()){
      TopoDS_Face aFace = TopoDS::Face(aFaceExplorer.Current());
      Handle(Geom_Surface) aSurface = BRep_Tool::Surface(aFace);
 
      cout << aSurface->DynamicType() << endl;
 
      if(aSurface->DynamicType() == STANDARD_TYPE(Geom_Plane)){
        Handle(Geom_Plane) aPlane = Handle(Geom_Plane)::DownCast(aSurface);
        gp_Pnt aPnt = aPlane->Location();
        if(aPnt.Z() == 0.)
        {
          //zMax = aPnt.Z();
	         if(i==4){
	         bottomPlane = aPlane;
           bottomFace = aFace;
	  }
	  else
	  coat[i]= aFace;
	  i++;
        }
	else
	{
	  topFace = aFace;
	  topPlane = aPlane;
	}
      }
      else cout<<"Unknown face type"<<endl;
  }

  gp_Pnt centerTop(topX, topY, height);
  gp_Pnt centerBottom(bottomX, bottomY, 0);
  gp_Dir axis = gp::DZ();

  TopoDS_Face topElectrode = Utilities::MakeDisk(centerTop, axis, radius);
  TopoDS_Shape topCut = BRepAlgoAPI_Cut(topFace, topElectrode);

  TopoDS_Face botDisk = Utilities::MakeDisk(centerBottom, axis,radius);
  TopoDS_Shape bottomcut = BRepAlgoAPI_Cut(bottomFace, botDisk);
  


  BRepBuilderAPI_Sewing Sewing;
    Sewing.Add(topCut);
    Sewing.Add(topElectrode);    
    for(i=0;i<4;i++)
    Sewing.Add(coat[i]);
    Sewing.Add(bottomcut);
    Sewing.Add(botDisk);
    Sewing.Perform();
    TopoDS_Shape finalCube = Sewing.SewedShape();
   
  DBRep::Set("finalCube", finalCube);
  DBRep::Set("bottomCut", bottomcut);
  DBRep::Set("bottomElectrode", botDisk);
  DBRep::Set("topCut", topCut);
  DBRep::Set("topElectrode", topElectrode);
  //DBRep::Set("bottomFace", bottomFace);
   
  StepWriter("cube.stp", finalCube);
}

static int CubeRect(Draw_Interpretor& di, Standard_Integer, const char**)
{

  //Default values
  Standard_Real Xlength=60.;
  Standard_Real Ylength=40.;
  Standard_Real height=20.;
  Standard_Real el=10.;
  Standard_Real eb=5.;

  //Taking file input
  string line;
  double a;
  ifstream myfile("cuberectinput.txt");
  
  for(int i=0;i<5;i++)
  {
  if(getline(myfile,line)){
  a=atof(line.c_str());
  switch(i)
  {
    case 0:
    Xlength=a;
    break;
    case 1:
    Ylength=a;
    break;
    case 2:
    height=a;
    break;
    case 3:
    el=a;
    break;
    case 4:
    eb=a;
    break;
  }
  }
  else cout<<"Input Error";
  }

  //defining origin as a point
  gp_Pnt p1(0, 0, 0);
  //defining base rectangle
  TopoDS_Face base = Utilities::MakeRectXY(p1, Xlength, Ylength, 0);

  //extruding base to form Cuboid
  gp_Vec aPrismVec(0, 0, height);
  TopoDS_Shape cube = BRepPrimAPI_MakePrism(base, aPrismVec);

  //defining Faces to separate surfaces of cube
  TopoDS_Face bottomFace;
  TopoDS_Face topFace;
  TopoDS_Face coat [4]; //Array containing the 4 adjoining vertical surfaces

  Handle(Geom_Plane) bottomPlane, topPlane;
  int i=0;
 
  for(TopExp_Explorer aFaceExplorer(cube, TopAbs_FACE) ; aFaceExplorer.More() ; aFaceExplorer.Next()){
      TopoDS_Face aFace = TopoDS::Face(aFaceExplorer.Current());
      Handle(Geom_Surface) aSurface = BRep_Tool::Surface(aFace);
 
      cout << aSurface->DynamicType() << endl;
 
      if(aSurface->DynamicType() == STANDARD_TYPE(Geom_Plane)){
        Handle(Geom_Plane) aPlane = Handle(Geom_Plane)::DownCast(aSurface);
        gp_Pnt aPnt = aPlane->Location();
        if(aPnt.Z() == 0.)
        {
          //zMax = aPnt.Z();
           if(i==4){
           bottomPlane = aPlane;
           bottomFace = aFace;
    }
    else
    coat[i]= aFace;
    i++;
        }
  else
  {
    topFace = aFace;
    topPlane = aPlane;
  }
      }
      else cout<<"Unknown face type"<<endl;
  }

  //Defining bottom electrode face and non-electrode surface
  TopoDS_Face bottomElectrode = Utilities::MakeRectXY(p1, el, eb, 0);
  TopoDS_Shape bottomCut = BRepAlgoAPI_Cut(bottomFace, bottomElectrode);

  //Defining top electrode face and non-electrode surface
  gp_Pnt topPnt((Xlength-el), (Ylength-eb), height);
  TopoDS_Face topElectrode = Utilities::MakeRectXY(topPnt, el, eb, 0);
  TopoDS_Shape topCut = BRepAlgoAPI_Cut(topFace, topElectrode);

  //Sewing required surfaces together
  BRepBuilderAPI_Sewing Sewing;
    Sewing.Add(topCut);
    Sewing.Add(topElectrode);    
    for(i=0;i<4;i++)
    Sewing.Add(coat[i]);
    Sewing.Add(bottomCut);
    Sewing.Add(bottomElectrode);
    Sewing.Perform();
    TopoDS_Shape finalCube = Sewing.SewedShape();
     
  DBRep::Set("finalCube", finalCube);
  DBRep::Set("bottomCut", bottomCut);
  DBRep::Set("bottomElectrode", bottomElectrode);
  DBRep::Set("topCut", topCut);
  DBRep::Set("topElectrode", topElectrode);
     
  StepWriter("cuberect.stp", finalCube);
}

void MyCommands_Commands (Draw_Interpretor &theCommands)
{
  const char *grp = "TUBstator commands";
 
  theCommands.Add("Piezo", "Piezo", __FILE__, anglePiezo, grp);
  theCommands.Add("Cube", "Cube", __FILE__, Cube, grp);
  theCommands.Add("Ring", "Ring", __FILE__, TripleRing, grp);
  theCommands.Add("CubeRect", "CubeRect", "src/Cuberect.cxx", CubeRect, grp); 
}