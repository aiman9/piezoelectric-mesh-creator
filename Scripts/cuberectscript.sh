#! /bin/bash

cd ~/OpenCascade
./make.sh
./run.sh cuberect.ccd
cd ~
exec < OpenCascade/mshElSz.txt
read size
gmsh -clscale $size -3 gmsh/cuberect.geo
gmsh gmsh/cuberect.msh
