# piezoelectric-mesh-creator
OpenCascade code to generate piezoelectric crystals with variable electrode shapes and convert it to a .stp file, as well as the gmsh .geo files to import from the stp file and add properties to generate the appropriate mesh.

---------------------------------------------------------------------------------------------------------------------------------
The Project comprises of 3 folders: namely OpenCascade, gmsh, and Scripts.

Brief description of each:
1) OpenCascade -  Within the /src directory, contains the code to build the piezoelectric structure. Also contains the saved .stp files, input parameter .txt files, .ccd files for commands, and the necessary scripts such as make.sh, run.sh etc to build the OpenCascade project.

2) gmsh - contains the .geo files that create the gmsh version of the piezoelectric, after importing the required stp file. Also contains sample .msh files that have subsequently been created.

3) Scripts - contains bash scripts to automate the creation and meshing of the piezoelectics, as well as C programs to change the input parameters

For further description, read on:
---------------------------------------------------------------------------------------------------------------------------------
1) OpenCascade: Consists of two directories, and additional files:
      i) /src: (directory)
      MyCommands.cxx contains the source code for the creation of 4 different electrode/piezoelectric configurations, as well as the names of the new user commands to access the respective functions.
      include.hxx is a header file containing the class Utilities which has some static user defined functions used in MyCommands.cxx
      Further files such as MyCommands.hxx etc describe necessary utilities for the usage of OpenCascade.
      
      ii) /Linux: (directory) Contains the compiled object codes, as well as the runnable application 'Exercise'.
      
      iii) Scripts: Bash scripts such as make.sh and run.sh perform the compilation and execution of the project respectively.
      
      iv) .stp files: There are 4 sample .stp files (result of execution of the OpenCascade methods in MyCommands.cxx). They will be overwritten on execution with new parameters.
      
      v) .txt files:
      Four of these, such as ringinput.txt etc, contain the input parameters for the creation of the respective stp files. For eg, ringinput.txt defines parameters such as outer radius, height etc for the triple ring electrode.
      mshElSz.txt contains the value of the mesh element size while meshing the respective .geo file.      
      
      vi) .ccd files: Provide few basic commands for the automatic execution upon running run.sh. For example, it is sufficient to type the command: "$./run.sh ringcommand.ccd" for the execution of code and creation of the triple ring electrode step file.
      
     
2) gmsh: Contains 4 .geo files and their corresponding sample mesh files:
      i)  anglecylinder.geo is the file for the variable angle sector electrode on a cylindrical ceramic.
      ii) ringcylinder.geo is the file for the triple ring electrode on cylindrical ceramic.
      iii) cube1.geo is the file for the configuration of a cuboidal ceramic with a complete disk electrode on the top & bottom.
      iv) cuberect.geo is the file for the configuration of a cuboidal ceramic with a rectangular electrode on the top & bottom.
      
3) Scripts: Contains bash scripts, C programs (for input) and their source code.

    i) C programs: These must be executed in order to change the input parameters for a particular configuration. They take user input and write to the .txt files in the directory OpenCascade/ in the desired format. Note: Executing 'ChangeElementSize' alters the mesh element size input parameter in 'mshElSz.txt'.
    
    ii) Bash scripts: Each of the four scripts anglescript.sh, ringscript.sh etc, are bash scripts to automate the creation of the mesh file from scratch. They 'make' the project again, run the method to create the corresponding .stp file, and create an updated .msh file.
    

---------------------------------------------------------------------------------------------------------------------------------
Execution instructions:

1) Change input parameters by executing respective input program in /Scripts
2) Change mesh element size if required by executing ChangeElementSize in /Scripts
3) Execute the bash script for the desired configuration from /Scripts. For example, execute ringscript.sh to create the triple ring electrode configuration.

Alternatively, the commands from the bash script can be executed manually.
