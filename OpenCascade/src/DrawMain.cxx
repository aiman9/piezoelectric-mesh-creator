// Created: 2003-04-19 
// 
// Copyright (c) 2003-2011 OPEN CASCADE SAS 
// 
// This file is part of commercial software by OPEN CASCADE SAS. 
// 
// This software is furnished in accordance with the terms and conditions 
// of the contract and with the inclusion of the this copyright notice. 
// This software or any other copy thereof may not be provided or otherwise 
// be made available to any third party. 
// No ownership title to the software is transferred hereby. 
// 
// OPEN CASCADE SAS makes no representation or warranties with respect to the 
// performance of this software, and specifically disclaims any responsibility 
// for any damages, special or consequential, connected with its use. 


// Include headers with imported definitions
#include <Draw.hxx>
#include <DBRep.hxx>
#include <DrawTrSurf.hxx>
#include <GeomliteTest.hxx>
#include <GeometryTest.hxx>
#include <BRepTest.hxx>

#include "MyCommands.hxx"


//=======================================================================
//function : Draw_InitAppli
//purpose  : Add all commands
//=======================================================================

void Draw_InitAppli (Draw_Interpretor &theCommands)
{
  // Add basic DRAW commands
  Draw::Commands(theCommands);
  DBRep::BasicCommands(theCommands);
  DrawTrSurf::BasicCommands(theCommands);

  // Add geometrical and topological commands
  GeomliteTest::AllCommands(theCommands);
  GeometryTest::AllCommands(theCommands);
  BRepTest::AllCommands(theCommands);

  // Add commands defined in MyCommands.cxx
  MyCommands_Commands(theCommands);
}

// Include DRAW standard 'main' procedure
#include <Draw_Main.hxx>
DRAW_MAIN
