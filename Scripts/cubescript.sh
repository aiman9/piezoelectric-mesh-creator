#! /bin/bash

cd ~/OpenCascade
./make.sh
./run.sh cubecommand.ccd
cd ~
exec < OpenCascade/mshElSz.txt
read size
gmsh -clscale $size -3 gmsh/cube1.geo
gmsh gmsh/cube1.msh
