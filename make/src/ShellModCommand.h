//
//  ShellModCommand.h
//  shellMod
//
//  Created by Hunyadi János on 2015. 01. 03..
//  Copyright (c) 2015. Janos Hunyadi. All rights reserved.
//

#ifndef SHELLMODCOMMAND_H
#define SHELLMODCOMMAND_H

#ifdef __linux__ 
    
#if MAYA_API_VERSION >= 20180000
	#include <maya/MCppCompat.h>
#endif
#include <maya/MArgDatabase.h>
#else
    #include <maya/MArgDataBase.h>
#endif





#include <maya/MDagPath.h>
#include <maya/MDGModifier.h>
#include <maya/MFnDagNode.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MFnIntArrayData.h>
#include <maya/MFnMesh.h>
#include <maya/MGlobal.h>
#include <maya/MIntArray.h>
#include <maya/MItDependencyGraph.h>
#include <maya/MMeshIntersector.h>
#include <maya/MObject.h>
#include <maya/MPlug.h>
#include <maya/MPointArray.h>
#include <maya/MPxCommand.h>
#include <maya/MSelectionList.h>
#include <maya/MSyntax.h>
#include <maya/MDagModifier.h>
#include <maya/MFnSet.h>
#include <maya/MDagPathArray.h>
#include <maya/MRampAttribute.h>

class ShellModCommand : public MPxCommand
{
public:
    ShellModCommand();
    virtual MStatus doIt( const MArgList& argList );
    virtual MStatus redoIt();
    virtual MStatus undoIt();
    virtual bool isUndoable() const;
    static void* creator();
    static MSyntax newSyntax();

	MStatus assignSameMaterial(MDagPath& inputShapeDagPath, MObject& outputShapeDagPath);
	MStatus assignInitialShadingGroup(MObject& oMesh);

private:

	MDagModifier m_DAGMod;
	MDGModifier m_DGMod;
	MFnDependencyNode m_DEPNode;

	MObject o_newMesh;
	MDagPath p_currSelShape;
    MDagPathArray p_currSelShapeA;



};


#endif