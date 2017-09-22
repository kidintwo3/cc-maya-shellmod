//
//  ShellModNode.h
//  shellMod
//
//  Created by Hunyadi János on 2015. 01. 03..
//  Copyright (c) 2015. Janos Hunyadi. All rights reserved.
//

#ifndef shellModNodeNODE_H
#define shellModNodeNODE_H


#ifdef __linux__ 
#if MAYA_API_VERSION >= 20180000
#include <maya/MCppCompat.h>
#endif
#endif

#include <maya/MPxNode.h>
#include <maya/MIOStream.h>

#include <maya/MGlobal.h>

#include <maya/MFnMesh.h>
#include <maya/MItMeshPolygon.h>
#include <maya/MItMeshEdge.h>
#include <maya/MItMeshVertex.h>

#include <maya/MSelectionList.h>
#include <maya/MDagPath.h>
#include <maya/MIntArray.h>
#include <maya/MPoint.h>
#include <maya/MUintArray.h>
#include <maya/MDoubleArray.h>
#include <maya/MPointArray.h>
#include <maya/MFloatPoint.h>
#include <maya/MFloatArray.h>
#include <maya/MFloatPointArray.h>
#include <maya/MItMeshEdge.h>
#include <maya/MItMeshPolygon.h>
#include <maya/MFnNurbsCurve.h>
#include <maya/MMeshIntersector.h>
#include <maya/MFnMeshData.h>

#include <maya/MFnTypedAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnEnumAttribute.h>

#include <maya/MFnMeshData.h>
#include <maya/MFnNurbsCurveData.h>
#include <maya/MFnComponentListData.h>
#include <maya/MFnTransform.h>
#include <maya/MFnStringData.h>
#include <maya/MMeshSmoothOptions.h>
#include <maya/MRampAttribute.h>

#include <maya/MUintArray.h>


#include <maya/MFnSingleIndexedComponent.h>
#include <maya/MNodeMessage.h>
#include <maya/MCallbackIdArray.h>

#include <maya/MPlugArray.h>
#include <maya/MMatrixArray.h>

#include <maya/MArrayDataHandle.h>

#include <maya/MFileObject.h>

#include <vector>
#include <cmath>
#include <math.h>
#include <sstream>
#include <string>
#include <iostream>
#include <time.h>
#include <ctime>
#include <fstream>
#include <stdlib.h>
#include <iomanip>

#include <limits>


#include "DagUtils.h"

#include <maya/MModelMessage.h>
#include <maya/MNodeMessage.h>
#include <maya/MDGMessage.h>

using namespace std;




class shellModNode : public MPxNode
{
public:

	shellModNode();
	virtual ~shellModNode();

	static  void*				creator();
	static  MStatus				initialize();

	virtual void				postConstructor();

	virtual MStatus				compute(const MPlug& plug, MDataBlock& data);

	static MObject				aInMesh;
	static MObject				aOutMesh;
	static MObject				aOffsetZ;
	static MObject				aSegments;
	static MObject				aAutoSegments;
	static MObject				aProfilePresets;
	static MObject				aCapTop;
	static MObject				aCapBottom;
	static MObject				aSmoothNormals;
	static MObject				aReverseNormals;
	static MObject				aStraightenEdges;
	static MObject				aStraightenEdgesAngle;
	static MObject				aSmoothSubdiv;

	static MObject				aBulge;
	static MObject				aCurveRamp;

	static MObject				aUVOffsetU;
	static MObject				aUVOffsetV;

	static MObject				aUVOffsetUAuto;
	static MObject				aUVOffsetUAutoPadding;
    
    static MObject				aPresetFolderPath;

	//static MObject				aDisplaySmoothMesh;

	static MObject				aDisableBaseMeshOverride;

	static MTypeId				id;

	static void					aboutToDeleteCB( MObject& node, MDGModifier& modifier, void* clientData );
	
    
    static MString              pluginLoadPath;

	

private:

	static void					preDuplicateCB(void* data);
	static void					postDuplicateCB(void* data);
	static void					nodeAddedCB(MObject& node, void* clientData);

	MStatus						setupConneCtions(MPlug &inMeshPlug, MPlug &outMeshPlug);
	MStatus						doLcCheck();

	void						profilePresets(const int &m_profilePreset);

	void						clearData();
	MStatus						collectInputMeshes(MDataBlock& data);
	MStatus						collectPlugs(MDataBlock& data);

	MStatus						storeProfileCurveData();

	MStatus						mergeInputMeshes();
	MStatus						generateUVs();
	MStatus						extrudeMesh(MObject& o_mergedMesh);

	MStatus						setObjectSmoothness();
    
    MStatus                     checkPresetFolder();

	MPlug						p_in_overrideEnabled;
	MPlug						p_in_overrideShading;
	MPlug						p_out_overrideEnabled;

	MCallbackIdArray			m_callbackIDs;

	// Datablock
	MDataHandle					h_outputMesh;
    MDataHandle					h_outPresetPath;
    
    MString                     m_presetPath;
    
	int							m_displaySmoothMesh;

	bool						m_overrideShading;
	bool						m_deleteShellMod;
	double						m_weight;
	int							m_segments;
	bool						m_capTop;
	bool						m_capBottom;
	bool						m_smoothNorm;
	bool						m_reverseNormals;
	bool						m_straightEdges;
	double						m_straightEdgesAngle;
	bool						m_autoSegments;
	short						m_profilePreset;
	int							m_smoothMeshSubdiv;
	double						m_bulge;

	// Ramp attribute
	MRampAttribute				a_curveAttribute;

	// UV attributes
	double						m_uvOffsetU;
	double						m_uvOffsetV;
	bool						m_uvOffsetUAuto;
	double						m_uvOffsetUAutoPadding;

	// Extra attributes
	MPlug						p_inMesh;
	MPlug						p_outMesh;

	MPlug						p_smoothMeshPlug;
	MPlug						p_smoothLevelPlug;

	MObjectArray				m_inMeshArray;
	MMatrixArray				m_inMeshMatrixArray;

	int							m_isSmoothed;



	// Mesh generation attributes
	int							m_numInputMeshes;

	vector<int>					i_numVertices;
	int                         o_numVertices;

	vector<int>					i_numPolygons;
	int                         o_numPolygons;

	vector<MFloatPointArray>	i_vertexArray;
	MFloatPointArray		    o_vertexArray;

	vector<MIntArray>			i_polygonCounts;
	MIntArray					o_polygonCounts;

	vector<MIntArray>			i_polygonConnects;
	MIntArray					o_polygonConnects;

	vector<MVectorArray>		i_faceVertexNormals;
	MVectorArray				o_faceVertexNormals;

	bool						m_disableBaseMeshOverride;

	// UV's
	MFloatArray					o_uArrayA;
	MFloatArray					o_vArrayA;

	MFloatArray					n_uArrayA;
	MFloatArray					n_vArrayA;

	MIntArray					o_uvCountsA;
	MIntArray					o_uvIdsA;

	MString						o_defaultUVSetNameA;

	// Curve data
	MIntArray					m_curve_indices;
	MIntArray					m_curve_interps;
	MFloatArray					m_curve_positions;
	MFloatArray					m_curve_values;

	// Mesh Smooth options for first mesh
	MMeshSmoothOptions			o_smoothOptions;
	MObject						o_smoothMeshDataObj;
	//

	bool				isVal;

	MObject				o_inMesh;
	MObject				o_outMesh;


    MString             s_readPluginPath;
    MFileObject         o_presetPath;

	MString				m_mayaVer;

	MUintArray			m_crease_vert_ids;
	MDoubleArray		m_crease_vert_data;

	MUintArray			m_crease_edge_ids;
	MDoubleArray		m_crease_edge_data;


	MUintArray			m_crease_vert_ids_extruded;
	MDoubleArray		m_crease_vert_data_extruded;

	MUintArray			m_crease_edge_ids_extruded;
	MDoubleArray		m_crease_edge_data_extruded;


	vector<MIntArray>	m_vertConnA;

	//MCallbackId			cb_postDeleteID;

};

#endif
