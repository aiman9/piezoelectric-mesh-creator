Merge "../OpenCascade/ringcylinder.stp";
//+
Surface Loop(1) = {4, 5, 6, 7, 1, 2, 3};
//+
Volume(0) = {1};
Physical Surface(0) = {1, 3};
//+
Physical Surface(1) = {6};
//+
Physical Surface(2) = {2};
//+
Physical Surface(3) = {5, 7};
//+
Physical Surface(4) = {4};
//+
Physical Volume(0) = {0};
