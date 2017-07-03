#! /bin/bash

cd ~/OpenCascade
./make.sh
./run.sh ringcommand.ccd
cd ~
exec < OpenCascade/mshElSz.txt
read size
gmsh -clscale $size -3 gmsh/ringcylinder.geo
gmsh gmsh/ringcylinder.msh
