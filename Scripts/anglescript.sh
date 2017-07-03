#! /bin/bash

cd ~/OpenCascade
./make.sh
./run.sh anglecommand.ccd
cd ~
exec < OpenCascade/mshElSz.txt
read size
gmsh -clscale $size -3 gmsh/anglecylinder.geo
gmsh gmsh/anglecylinder.msh
