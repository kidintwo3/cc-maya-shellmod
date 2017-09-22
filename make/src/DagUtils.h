//
//  DagUtils.h
//  shellMod
//
//  Created by Hunyadi János on 2015. 01. 03..
//  Copyright (c) 2015. Janos Hunyadi. All rights reserved.
//

#ifndef DAGUTILS_H
#define DAGUTILS_H

#if MAYA_API_VERSION >= 20180000

#ifdef __linux__ 
#include <maya/MCppCompat.h>
#endif

#endif

#include <maya/MSelectionList.h>
#include <maya/MItSelectionList.h>
#include <maya/MItDag.h>
#include <maya/MString.h>
#include <maya/MGlobal.h>
#include <maya/MDagPath.h>
#include <maya/MPlug.h>
#include <maya/MFnDagNode.h>
#include <maya/MDGModifier.h>
#include <maya/MDagModifier.h>
#include <maya/MItDependencyNodes.h>
#include <maya/MDagPathArray.h>

//


MStatus				getShapeNodeFromTransformDAG(MDagPath& path);
MObject             createNodeCustom(MDGModifier& m_DAGMod, MString id);
MObject             createNodeMaya(MFnDependencyNode& m_DEPNode, MString id);
MSelectionList      listNodeType(MFn::Type mfn_nodeType);
bool                checkNodeExist(MSelectionList selList, MString searchString);
MDagPath            getDagFromString(MString nodeName);
MDagPath            getCurrSelectionDAG();
MDagPathArray		getCurrSelectionDAGArray();
MPlug               findPlug(MDagPath pathName, MString plugName);
MStatus             setPlugs(MObject obj, MString plug, MString value);
MStatus             connectPlug(MDagModifier& m_DAGMod, MObject objSource, MObject objTarget, MString plugSourceStr, MString plugTargetStr);
MStatus             deleteNode(MObject obj);
bool                checkMatExist(MString matName);

#endif
