// Gmsh project created on Fri Jun  9 14:17:48 2017
Merge "../OpenCascade/anglecylinder.stp";
SetFactory("OpenCASCADE");

//+
Surface Loop(1) = {2, 3, 5, 4, 1};
//+
Volume(0) = {1};
//+
Physical Surface(0) = {1};
//+
Physical Surface(1) = {4};
//+
Physical Surface(2) = {2};
//+
Physical Surface(3) = {5};
//+
Physical Surface(4) = {3};
//+
Physical Volume(0) = {0};
