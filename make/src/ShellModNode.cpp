//
//  ShellModNode.cpp
//  shellMod
//
//  Created by Hunyadi János on 2015. 01. 03..
//  Copyright (c) 2015. Janos Hunyadi. All rights reserved.
//

#include "ShellModNode.h"

MObject		shellModNode::aInMesh;
MObject		shellModNode::aOutMesh;
MObject		shellModNode::aOffsetZ;
MObject		shellModNode::aSegments;
MObject		shellModNode::aCapTop;
MObject		shellModNode::aCapBottom;
MObject		shellModNode::aSmoothNormals;
MObject		shellModNode::aReverseNormals;
MObject		shellModNode::aStraightenEdges;
MObject		shellModNode::aStraightenEdgesAngle;
MObject		shellModNode::aAutoSegments;
MObject		shellModNode::aProfilePresets;
MObject		shellModNode::aSmoothSubdiv;
MObject		shellModNode::aBulge;
MObject		shellModNode::aCurveRamp;
MObject		shellModNode::aBevelEdgesAngle;

MObject		shellModNode::aGenerateUVs;

MObject		shellModNode::aChamferEdges;
MObject		shellModNode::aChamferEdgeFactor;

//MObject		shellModNode::aShadingOverride;

MObject		shellModNode::aUVOffsetU;
MObject		shellModNode::aUVOffsetV;
MObject		shellModNode::aUVOffsetUAuto;
MObject		shellModNode::aUVOffsetUAutoPadding;

MObject		shellModNode::aUVTranslateU;
MObject		shellModNode::aUVTranslateV;
MObject		shellModNode::aUVRotate;
MObject		shellModNode::aUVScaleU;
MObject		shellModNode::aUVScaleV;



MObject		shellModNode::aOutputComponents;

MObject		shellModNode::aDisableBaseMeshOverride;
MObject		shellModNode::aDisableOutputMeshOverride;


MObject		shellModNode::aPresetFolderPath;
MString     shellModNode::pluginLoadPath;

MTypeId		shellModNode::id(0x00123940);



bool m_isDuplicating; // Callback hack

shellModNode::shellModNode() {}

MStatus shellModNode::checkPresetFolder()
{
	MString s_path = shellModNode::pluginLoadPath + "/shellMod.cfg";


	s_readPluginPath.clear();




	if (ifstream(s_path.asChar())) // If "pshellMod.cfg" exists
	{
		string line;

		ifstream myfile(s_path.asChar());
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				istringstream iss(line);
				s_readPluginPath = line.c_str();
			}

			myfile.close();

			MGlobal::displayInfo(MString() + "[ShellMod] pshellMod.cfg path: " + s_readPluginPath);
			o_presetPath.setRawFullName(s_readPluginPath);



		}

		if (s_readPluginPath.length() == 0) {

			MGlobal::displayWarning(MString() + "[ShellMod] pshellMod.cfg is empty!");
		}

		return MStatus::kSuccess;
	}



	else // If "pshellMod.cfg" does not exist
	{

		ofstream fout(s_path.asChar());
		MGlobal::displayInfo(MString() + "[ShellMod] Writing default pshellMod.cfg to folder: " + s_path);

		//        MString pPath = getenv ("MAYA_PRESET_PATH");
		//        
		//        MStringArray pPathA;
		//        pPath.split(':', pPathA);
		//        pPath = pPathA[0];
		//        
		//        
		//        MString s_osType;
		//        MGlobal::executeCommand( "about -os", s_osType);
		//        
		//        
		//        if (s_osType == "mac") {
		//            pPath = "/Users/Shared/Autodesk/maya/";
		//        }

		MString s_path = shellModNode::pluginLoadPath + "/";

		//        fout <<  MString(pPath).asChar();

		fout << s_path.asChar();

		s_readPluginPath = s_path;


		return MStatus::kSuccess;


	}



	return MStatus::kSuccess;
}




void* shellModNode::creator()
{

	return new shellModNode();

}

shellModNode::~shellModNode()
{
	MMessage::removeCallbacks(m_callbackIDs);
	m_callbackIDs.clear();
}



void shellModNode::postConstructor()
{
	MStatus status;

	MObject oSelf = thisMObject();

	m_mayaVer = MGlobal::mayaVersion();

	// delete callback
	MCallbackId callbackID;
	callbackID = MNodeMessage::addNodeAboutToDeleteCallback(oSelf, aboutToDeleteCB, this);
	m_callbackIDs.append(callbackID);

	// duplicate pre callback
	callbackID = MModelMessage::addBeforeDuplicateCallback(shellModNode::preDuplicateCB, this);
	m_callbackIDs.append(callbackID);

	// duplicate post callback
	callbackID = MModelMessage::addAfterDuplicateCallback(shellModNode::postDuplicateCB, this);
	m_callbackIDs.append(callbackID);

	// object added to scene callback
	callbackID = MDGMessage::addNodeAddedCallback(shellModNode::nodeAddedCB, "dagNode", this);
	m_callbackIDs.append(callbackID);


	// Check preset folder
	shellModNode::checkPresetFolder();

	setExistWithoutOutConnections(false);
	setExistWithoutInConnections(false);

}

void shellModNode::nodeAddedCB(MObject& node, void* clientData)
{

	if (m_isDuplicating)
	{
		MFnDagNode mfDgN(node);
		MPlug p_out_overrideEnabled = mfDgN.findPlug("overrideEnabled", false);
		p_out_overrideEnabled.setBool(false);

		//MGlobal::displayInfo(MString() + "[ShellMod] DuSetting output mesh overrides! " );
	}


}

void shellModNode::preDuplicateCB(void* clientData)
{
	m_isDuplicating = true;
	//MGlobal::displayWarning("preDuplicateCB!!");

}

void shellModNode::postDuplicateCB(void* clientData)
{
	m_isDuplicating = false;
	//MGlobal::displayWarning("Duplicating!!");

}

void shellModNode::aboutToDeleteCB(MObject& node, MDGModifier& modifier, void* pUserPtr)
{
	MFnDependencyNode nodeFn(node);
	MGlobal::displayInfo(MString("[ShellMod] About to delete callback for node: ") + nodeFn.name());


	// Find the output mesh connected to the node
	MPlug worldP = nodeFn.findPlug("outMesh");

	MFnDagNode mfDgN(worldP.node());

	MPlugArray destPlugs;
	worldP.connectedTo(destPlugs, false, true);

	if (destPlugs.length() != 0)
	{
		MPlug destPlug = destPlugs[0];

		mfDgN.setObject(destPlug.node());


		MPlug p_out_overrideEnabled = mfDgN.findPlug("overrideEnabled", false);
		p_out_overrideEnabled.setBool(false);

		MGlobal::displayInfo(MString("[ShellMod] Deleting / Setting output mesh overrides: ") + mfDgN.partialPathName());
	}

	else
	{
		MGlobal::displayInfo(MString() + "[ShellMod] Deleting / No connection, or wrong connection to output mesh: ");
	}

}

MStatus shellModNode::setupConneCtions(MPlug &inMeshPlug, MPlug &outMeshPlug)
{

	MStatus status;

	// -----------------------------------------------
	// Collect output plug mesh's name



	//status = outMeshPlug.selectAncestorLogicalIndex(outMeshPlug.numElements());
	//CHECK_MSTATUS_AND_RETURN_IT(status);

	MPlugArray outputs_plugArr;
	outMeshPlug.connectedTo(outputs_plugArr, false, true, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	if (outputs_plugArr.length() > 0)
	{

		outMeshPlug = outputs_plugArr[0];
		MFnDependencyNode outMesh_dn(outMeshPlug.node());


		// ------------------------------

		MPlug p_out_overrideEnabled = outMesh_dn.findPlug("overrideEnabled", false, &status);
		CHECK_MSTATUS_AND_RETURN_IT(status);
		p_out_overrideEnabled.setBool(true);

		MPlug p_out_overrideDisplayType = outMesh_dn.findPlug("overrideDisplayType", false, &status);
		CHECK_MSTATUS_AND_RETURN_IT(status);
		p_out_overrideDisplayType.setInt(2);

	}



	return MS::kSuccess;
}

void shellModNode::profilePresets(const int &m_profilePreset)
{
	MStatus status;

	if (m_profilePreset == 1)
	{

		float pos[6] = { 0.0f,0.005f,0.01f,0.99f,0.995f,1.0f };
		float val[6] = { 0.0f,0.95f,1.0f,1.0f,0.95f,0.0f };
		m_curve_positions = MFloatArray(pos, (sizeof(pos) / sizeof(*pos)));
		m_curve_values = MFloatArray(val, (sizeof(val) / sizeof(*val)));
	}

	if (m_profilePreset == 2)
	{
		float pos[6] = { 0.0f,0.01f,0.02f,0.98f,0.99f,1.0f };
		float val[6] = { 0.0f,0.95f,1.0f,1.0f,0.95f,0.0f };
		m_curve_positions = MFloatArray(pos, (sizeof(pos) / sizeof(*pos)));
		m_curve_values = MFloatArray(val, (sizeof(val) / sizeof(*val)));
	}

	if (m_profilePreset == 3)
	{
		float pos[6] = { 0.0f,0.025f,0.05f,0.95f,0.975f,1.0f };
		float val[6] = { 0.0f,0.95f,1.0f,1.0f,0.95f,0.0f };
		m_curve_positions = MFloatArray(pos, (sizeof(pos) / sizeof(*pos)));
		m_curve_values = MFloatArray(val, (sizeof(val) / sizeof(*val)));
	}

	if (m_profilePreset == 4)
	{
		float pos[6] = { 0.0f,0.05f,0.1f,0.9f,0.95f,1.0f };
		float val[6] = { 0.0f,0.95f,1.0f,1.0f,0.95f,0.0f };
		m_curve_positions = MFloatArray(pos, (sizeof(pos) / sizeof(*pos)));
		m_curve_values = MFloatArray(val, (sizeof(val) / sizeof(*val)));
	}

	if (m_profilePreset == 5)
	{
		float pos[6] = { 0.0f,0.1f,0.2f,0.8f,0.9f,1.0f };
		float val[6] = { 0.0f,0.95f,1.0f,1.0f,0.95f,0.0f };
		m_curve_positions = MFloatArray(pos, (sizeof(pos) / sizeof(*pos)));
		m_curve_values = MFloatArray(val, (sizeof(val) / sizeof(*val)));
	}

	if (m_profilePreset == 6)
	{
		float pos[6] = { 0.0f,0.15f,0.3f,0.7f,0.85f,1.0f };
		float val[6] = { 0.0f,0.95f,1.0f,1.0f,0.95f,0.0f };
		m_curve_positions = MFloatArray(pos, (sizeof(pos) / sizeof(*pos)));
		m_curve_values = MFloatArray(val, (sizeof(val) / sizeof(*val)));
	}

	if (m_profilePreset == 7)
	{
		float pos[22] = { 0.0f,0.001f,0.02f,0.03f,0.04f,0.13f,0.14f,0.15f,0.17f,0.17f,0.18f,0.82f,0.83f,0.831558f,0.85f,0.86f,0.87f,0.96f,0.97f,0.98f,0.999f,1.0f };
		float val[22] = { 0.0f,0.04f,0.98f,1.0f,1.0f,1.0f,1.0f,0.98f,0.0f,0.04f,0.0f,0.0f,0.0f,0.04f,0.98f,1.0f,1.0f,1.0f,1.0f,0.98f,0.04f,0.0f };
		m_curve_positions = MFloatArray(pos, (sizeof(pos) / sizeof(*pos)));
		m_curve_values = MFloatArray(val, (sizeof(val) / sizeof(*val)));
	}

	if (m_profilePreset == 8)
	{
		float pos[12] = { 0.0f,0.000665779f,0.011984f,0.0312916f,0.331558f,0.52996f,0.705726f,0.864847f,0.948069f,0.98735f,0.998003f,1.0f };
		float val[12] = { 0.0f,0.953618f,0.988868f,0.998145f,1.0f,0.96846f,0.858998f,0.653061f,0.42115f,0.179963f,0.038961f,0.0f };
		m_curve_positions = MFloatArray(pos, (sizeof(pos) / sizeof(*pos)));
		m_curve_values = MFloatArray(val, (sizeof(val) / sizeof(*val)));
	}

	if (m_profilePreset == 9)
	{
		float pos[12] = { 0.0f,0.0186418f,0.15f,0.165f,0.18f,0.2f,0.8f,0.82f,0.835f,0.85f,0.98f,1.0f };
		float val[12] = { 0.0f,0.12f,0.95f,0.985f,1.0f,1.0f,1.0f,1.0f,0.985f,0.95f,0.12f,0.0f };
		m_curve_positions = MFloatArray(pos, (sizeof(pos) / sizeof(*pos)));
		m_curve_values = MFloatArray(val, (sizeof(val) / sizeof(*val)));
	}

	if (m_profilePreset == 10)
	{
		float pos[18] = { 0.0f,0.005f,0.01f,0.025f,0.14f,0.15f,0.16f,0.165f,0.18f,0.82f,0.835f,0.84f,0.85f,0.86f,0.975f,0.99f,0.995f,1.0f };
		float val[18] = { 0.0f,0.16f,0.19f,0.2f,0.2f,0.2f,0.95f,0.985f,1.0f,1.0f,0.985f,0.959184f,0.2f,0.2f,0.2f,0.19f,0.16f,0.0f };
		m_curve_positions = MFloatArray(pos, (sizeof(pos) / sizeof(*pos)));
		m_curve_values = MFloatArray(val, (sizeof(val) / sizeof(*val)));
	}

	if (m_profilePreset == 11)
	{
		float pos[21] = { 0,0.026,0.037,0.0585,0.19,0.38,0.63,0.795,0.815,0.82,0.822672,0.825,0.83,0.95,0.957,0.959,0.959514,0.96,0.973279,0.98,1 };
		float val[21] = { 0,0.06,0.073,0.1,0.25,0.46,0.73,0.89,0.9,0.91,0.92757,0.996,1,0.998,0.995,0.98,0.92757,0.9,0.899533,0.895,0 };
		m_curve_positions = MFloatArray(pos, (sizeof(pos) / sizeof(*pos)));
		m_curve_values = MFloatArray(val, (sizeof(val) / sizeof(*val)));
	}

	if (m_profilePreset == 12)
	{
		float pos[12] = { 0,0.01,0.0199734,0.47,0.48,0.49,0.51,0.52,0.53,0.98,0.99,1 };
		float val[12] = { 0,0.03,0.05,0.98,1,1,1,1,0.98,0.05,0.03,0 };
		m_curve_positions = MFloatArray(pos, (sizeof(pos) / sizeof(*pos)));
		m_curve_values = MFloatArray(val, (sizeof(val) / sizeof(*val)));
	}

	if (m_profilePreset == 13)
	{
		float pos[16] = { 0,0.00732357,0.0173103,0.275,0.285,0.305,0.33,0.35,0.65,0.67,0.695,0.715,0.725,0.9827,0.9927,1 };
		float val[16] = { 0,0.05,0.09,0.91,0.94,0.98,1,1,1,1,0.98,0.94,0.91,0.09,0.05,0 };
		m_curve_positions = MFloatArray(pos, (sizeof(pos) / sizeof(*pos)));
		m_curve_values = MFloatArray(val, (sizeof(val) / sizeof(*val)));
	}

	if (m_profilePreset == 14)
	{
		float pos[21] = { 0,0.00133156,0.00532623,0.0133156,0.033,0.06,0.095,0.14,0.19,0.24,0.29,0.8,0.85,0.89,0.92,0.95,0.9747,0.98735,0.991345,0.996671,1 };
		float val[21] = { 0,0.235622,0.423006,0.560297,0.7,0.8,0.9,0.96,0.99,1,1,1,1,0.995,0.98,0.94,0.862709,0.747681,0.601113,0.397032,0 };
		m_curve_positions = MFloatArray(pos, (sizeof(pos) / sizeof(*pos)));
		m_curve_values = MFloatArray(val, (sizeof(val) / sizeof(*val)));
	}

	if (m_profilePreset == 15)
	{
		float pos[27] = { 0,0.00133156,0.013,0.036,0.07,0.115,0.17,0.235,0.315,0.41,0.515,0.63,0.72,0.795,0.815,0.82,0.830892,0.846205,0.86285,0.90213,0.945406,0.964048,0.973369,0.98,0.98269,0.998,1 };
		float val[27] = { 0,0.044484,0.19,0.32,0.44,0.54,0.625,0.695,0.76,0.81,0.85,0.877,0.886,0.89,0.9,0.91,0.939502,0.97331,0.991103,1,0.992883,0.97153,0.939502,0.895,0.86121,0.0777,0 };
		m_curve_positions = MFloatArray(pos, (sizeof(pos) / sizeof(*pos)));
		m_curve_values = MFloatArray(val, (sizeof(val) / sizeof(*val)));
	}


	if (m_profilePreset == 16)
	{
		float pos[42] = { 0,0.00466045,0.025,0.035,0.0875,0.1,0.125,0.135,0.19,0.2,0.225,0.235,0.29,0.3,0.325,0.335,0.39,0.4,0.425,0.435,0.49,0.5,0.525,0.535,0.59,0.6,0.625,0.637,0.69,0.7,0.725,0.735,0.79,0.8,0.825,0.835,0.89,0.9,0.925,0.935,0.99,1 };
		float val[42] = { 0,0.200371,0.98,1,1,0.98,0,0,0,0,0.98,1,1,0.98,0,0,0,0,0.98,1,1,0.98,0,0,0,0,0.98,1,1,0.98,0,0,0,0,0.98,1,1,0.98,0,0,0,0 };
		m_curve_positions = MFloatArray(pos, (sizeof(pos) / sizeof(*pos)));
		m_curve_values = MFloatArray(val, (sizeof(val) / sizeof(*val)));
	}

	if (m_profilePreset == 17)
	{
		float pos[19] = { 0,0.00771605,0.153549,0.1666,0.177469,0.324074,0.3333,0.341821,0.486883,0.5,0.511574,0.656636,0.666,0.676698,0.819444,0.833,0.844136,0.993056,1 };
		float val[19] = { 0,0.05,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0.05,0 };
		m_curve_positions = MFloatArray(pos, (sizeof(pos) / sizeof(*pos)));
		m_curve_values = MFloatArray(val, (sizeof(val) / sizeof(*val)));
	}

	if (m_profilePreset == 18)
	{
		float pos[50] = { 0,0.000665779,0.0153129,0.0399467,0.0446072,0.0499334,0.0685752,0.0732357,0.0778961,0.0792277,0.0905459,0.0905459,0.0932091,0.0998668,0.118509,0.123835,0.127164,0.128495,0.148469,0.149134,0.150466,0.156458,0.173103,0.177097,0.181092,0.183089,0.193742,0.194407,0.195073,0.202397,0.221039,0.227031,0.229694,0.231691,0.245672,0.247004,0.24767,0.25233,0.275633,0.280959,0.283622,0.284953,0.3,0.305593,0.306258,0.320905,0.95739,0.9747,0.992676,1 };
		float val[50] = { 0,0.25603,0.788497,0.8,0.961039,1,1,0.962894,0.829314,0.8,0.8,0.831169,0.961039,1,1,0.959184,0.834879,0.8,0.8,0.836735,0.962894,1,1,0.96475,0.840445,0.8,0.8,0.840445,0.962894,1,1,0.96475,0.842301,0.8,0.8,0.844156,0.962894,1,1,0.962894,0.844156,0.8,0.8,0.773655,0.666048,0.664193,0.667904,0.667904,0.649351,0.606679 };
		m_curve_positions = MFloatArray(pos, (sizeof(pos) / sizeof(*pos)));
		m_curve_values = MFloatArray(val, (sizeof(val) / sizeof(*val)));
	}

	if (m_profilePreset == 19)
	{
		float pos[14] = { 0,0.008,0.0655864,0.075,0.09,0.28,0.29,0.3,0.365,0.372685,0.4,0.969136,0.992284,1 };
		float val[14] = { 0,0.1,0.96,0.99,1,0.998145,0.99,0.96,0.16,0.1,0.1,0.1,0.0538033,0 };
		m_curve_positions = MFloatArray(pos, (sizeof(pos) / sizeof(*pos)));
		m_curve_values = MFloatArray(val, (sizeof(val) / sizeof(*val)));
	}

}

void shellModNode::clearData()
{

}

MStatus shellModNode::collectPlugs(MDataBlock& data)
{
	MStatus status;

	h_outputMesh = data.outputValue(aOutMesh, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	h_outPresetPath = data.outputValue(aPresetFolderPath, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	//    MPlug p = MPlug( aPresetFolderPath, shellModNode::aPresetFolderPath );
	//    m_presetPath = p.asString();

	m_presetPath = data.inputValue(aPresetFolderPath, &status).asString();
	CHECK_MSTATUS_AND_RETURN_IT(status);

	m_weight = data.inputValue(aOffsetZ, &status).asDouble();
	CHECK_MSTATUS_AND_RETURN_IT(status);


	m_segments = data.inputValue(aSegments, &status).asInt();
	CHECK_MSTATUS_AND_RETURN_IT(status);



	m_capTop = data.inputValue(aCapTop, &status).asBool();
	CHECK_MSTATUS_AND_RETURN_IT(status);

	m_capBottom = data.inputValue(aCapBottom, &status).asBool();
	CHECK_MSTATUS_AND_RETURN_IT(status);

	m_smoothNorm = data.inputValue(aSmoothNormals, &status).asBool();
	CHECK_MSTATUS_AND_RETURN_IT(status);

	m_reverseNormals = data.inputValue(aReverseNormals, &status).asBool();
	CHECK_MSTATUS_AND_RETURN_IT(status);

	m_straightEdges = data.inputValue(aStraightenEdges, &status).asBool();
	CHECK_MSTATUS_AND_RETURN_IT(status);

	m_straightEdgesAngle = data.inputValue(aStraightenEdgesAngle, &status).asDouble();
	CHECK_MSTATUS_AND_RETURN_IT(status);





	m_chamferEdges = data.inputValue(aChamferEdges, &status).asBool();
	CHECK_MSTATUS_AND_RETURN_IT(status);

	m_chamferEdgeFactor = data.inputValue(aChamferEdgeFactor, &status).asDouble();
	CHECK_MSTATUS_AND_RETURN_IT(status);

	m_autoSegments = data.inputValue(aAutoSegments, &status).asBool();
	CHECK_MSTATUS_AND_RETURN_IT(status);

	m_profilePreset = data.inputValue(aProfilePresets, &status).asShort();
	CHECK_MSTATUS_AND_RETURN_IT(status);

	m_smoothMeshSubdiv = data.inputValue(aSmoothSubdiv, &status).asInt();
	CHECK_MSTATUS_AND_RETURN_IT(status);

	m_bulge = data.inputValue(aBulge, &status).asDouble();
	CHECK_MSTATUS_AND_RETURN_IT(status);


	//m_displaySmoothMesh = data.inputValue(aDisplaySmoothMesh, &status).asInt();
	//CHECK_MSTATUS_AND_RETURN_IT(status)

	// Ramp attribute

	a_curveAttribute = MRampAttribute(this->thisMObject(), aCurveRamp, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	// UV attributes

	m_uvOffsetU = data.inputValue(aUVOffsetU, &status).asDouble();
	CHECK_MSTATUS_AND_RETURN_IT(status);

	m_uvOffsetV = data.inputValue(aUVOffsetV, &status).asDouble();
	CHECK_MSTATUS_AND_RETURN_IT(status);


	m_uvTranslateU = data.inputValue(aUVTranslateU, &status).asDouble();
	CHECK_MSTATUS_AND_RETURN_IT(status);

	m_uvTranslateV = data.inputValue(aUVTranslateV, &status).asDouble();
	CHECK_MSTATUS_AND_RETURN_IT(status);

	m_uvRotate = data.inputValue(aUVRotate, &status).asDouble();
	CHECK_MSTATUS_AND_RETURN_IT(status);

	m_uvScaleU = data.inputValue(aUVScaleU, &status).asDouble();
	CHECK_MSTATUS_AND_RETURN_IT(status);

	m_uvScaleV = data.inputValue(aUVScaleV, &status).asDouble();
	CHECK_MSTATUS_AND_RETURN_IT(status);

	m_uvOffsetUAuto = data.inputValue(aUVOffsetUAuto, &status).asBool();
	CHECK_MSTATUS_AND_RETURN_IT(status);

	m_generateUVs = data.inputValue(aGenerateUVs, &status).asBool();
	CHECK_MSTATUS_AND_RETURN_IT(status);

	m_uvOffsetUAutoPadding = data.inputValue(aUVOffsetUAutoPadding, &status).asDouble();
	CHECK_MSTATUS_AND_RETURN_IT(status);

	m_disableBaseMeshOverride = data.inputValue(aDisableBaseMeshOverride, &status).asBool();
	CHECK_MSTATUS_AND_RETURN_IT(status);

	m_disableOutputMeshOverride = data.inputValue(aDisableOutputMeshOverride, &status).asBool();
	CHECK_MSTATUS_AND_RETURN_IT(status);

	// Bevel

	m_bevelEdgesAngle = data.inputValue(aBevelEdgesAngle, &status).asDouble();
	CHECK_MSTATUS_AND_RETURN_IT(status);


	return MStatus::kSuccess;
}



MStatus shellModNode::collectInputMeshes(MDataBlock& data)
{

	MStatus status;

	// Clear mobject and matrix array
	m_inMeshArray.clear();
	m_inMeshMatrixArray.clear();

	// Check if input and output mesh is plugged in
	p_inMesh = MPlug(this->thisMObject(), aInMesh);
	p_outMesh = MPlug(this->thisMObject(), aOutMesh);




	MArrayDataHandle h_inMeshes = data.inputArrayValue(aInMesh);

	for (unsigned int i = 0; i < h_inMeshes.elementCount(); i++)
	{
		status = h_inMeshes.jumpToArrayElement(i);
		CHECK_MSTATUS_AND_RETURN_IT(status);

		MObject m_inMesh = h_inMeshes.inputValue(&status).asMesh();

		if (m_inMesh.apiType() == MFn::kMeshData)
		{
			m_inMeshArray.append(m_inMesh);

			MMatrix trMat = h_inMeshes.inputValue(&status).geometryTransformMatrix();
			CHECK_MSTATUS_AND_RETURN_IT(status);

			m_inMeshMatrixArray.append(trMat);

		}

	}


	//  MGlobal::displayInfo(MString() + "m_inMeshArray: " + m_inMeshArray.length() );


	if (m_inMeshArray.length() == 0)
	{
		MGlobal::displayWarning(MString() + "[ShellMod] - No input / or / output meshes connected");
		return MS::kFailure;
	}



	MIntArray isSubdivA;

	// Iterate trhrough input meshes and collect Subdivision status
	for (unsigned int i = 0; i < p_inMesh.numElements(); i++)
	{

		MPlug p_curr = p_inMesh.elementByLogicalIndex(i, &status);
		CHECK_MSTATUS_AND_RETURN_IT(status);


		if (p_curr.isConnected())
		{
			status = p_inMesh.selectAncestorLogicalIndex(0);
			CHECK_MSTATUS_AND_RETURN_IT(status);

			MPlugArray inputs_plugArr;
			p_inMesh.connectedTo(inputs_plugArr, true, false, &status);
			CHECK_MSTATUS_AND_RETURN_IT(status);



			for (int i = 0; i < inputs_plugArr.length(); i++)
			{

				if (inputs_plugArr[i].isConnected())
				{
					MPlug inMeshPlug = inputs_plugArr[i];

					MFnDependencyNode inMesh_dn(inMeshPlug.node());

					MPlug p_displaySmoothMesh = inMesh_dn.findPlug("displaySmoothMesh", &status);
					CHECK_MSTATUS_AND_RETURN_IT(status);


					m_isSmoothed = p_displaySmoothMesh.asInt();

					// collect smooth plugs on all objects
					isSubdivA.append(m_isSmoothed);



				}

			}

		}

	}




	// If one of the input objects is smoothed  -> smooth all
	// Set global smoothing
	bool isSmooth = false;

	for (unsigned i = 0; i < isSubdivA.length(); i++)
	{
		if (isSubdivA[i] == 2)
		{
			isSmooth = true;
		}
	}

	if (isSmooth) { m_isSmoothed = 2; }
	else { m_isSmoothed = 0; }


	m_numInputMeshes = m_inMeshArray.length();


	return MStatus::kSuccess;
}

MStatus shellModNode::mergeInputMeshes()
{
	MStatus status;

	// Setup mesh creation vector arrays for all meshes
	i_numVertices.resize(m_numInputMeshes);
	i_numPolygons.resize(m_numInputMeshes);
	i_vertexArray.resize(m_numInputMeshes);
	i_polygonCounts.resize(m_numInputMeshes);
	i_polygonConnects.resize(m_numInputMeshes);



	for (int m = 0; m < m_numInputMeshes; m++)
	{

		//// Collect mesh data
		MFnMesh mfnMesh(m_inMeshArray[m]);

		i_numVertices[m] = mfnMesh.numVertices();
		i_numPolygons[m] = mfnMesh.numPolygons();


		mfnMesh.getPoints(i_vertexArray[m], MSpace::kWorld);
		mfnMesh.getVertices(i_polygonCounts[m], i_polygonConnects[m]);


	}

	// Allocate memory for vector
	int id = 0;
	int len_o_vertexArray = 0;
	int len_o_polygonCounts = 0;
	int len_o_polygonConnects = 0;

	for (int m = 0; m < m_numInputMeshes; m++)
	{
		id = m;
		for (unsigned v = 0; v < i_vertexArray[id].length(); v++) {
			len_o_vertexArray += 1;
		}
		for (unsigned v = 0; v < i_polygonCounts[id].length(); v++) {
			len_o_polygonCounts += 1;
		}
		for (unsigned v = 0; v < i_polygonConnects[id].length(); v++) {
			len_o_polygonConnects += 1;
		}

	}

	//
	o_numVertices = 0;
	o_numPolygons = 0;
	o_vertexArray.clear();
	o_polygonCounts.clear();
	o_polygonConnects.clear();

	o_vertexArray.setLength(len_o_vertexArray);
	o_polygonCounts.setLength(len_o_polygonCounts);
	o_polygonConnects.setLength(len_o_polygonConnects);

	for (int m = 0; m < m_numInputMeshes; m++)
	{
		id = m;

		// numVertices
		o_numVertices += i_numVertices[id];

		// numPolygons
		o_numPolygons += i_numPolygons[id];
	}

	int idOffset = 0;
	int polycOffset = 0;
	int polyConnOffset = 0;

	for (int m = 0; m < m_numInputMeshes; m++)
	{

		id = m;

#pragma omp parallel for
		// vertexArray
		for (int v = 0; v < i_vertexArray[id].length(); v++) {
			MFloatPoint currP = i_vertexArray[id][v];

			MFloatPoint currentPoint(currP.x, currP.y, currP.z, currP.w);



			//currentPoint *= m_rotMatArray[m];

			//if (m_worldSpaceInput) { currentPoint *= m_inMeshMatrixArray[id]; }

			//currentPoint += m_posVecArray[m];

			o_vertexArray.set(currentPoint, v + idOffset);
		}
#pragma omp parallel for
		// polygonCounts
		for (int v = 0; v < i_polygonCounts[id].length(); v++) {
			o_polygonCounts.set(i_polygonCounts[id][v], v + polycOffset);
		}



#pragma omp parallel for
		// polygonConnects
		for (int v = 0; v < i_polygonConnects[id].length(); v++) {
			o_polygonConnects.set(i_polygonConnects[id][v] + idOffset, v + polyConnOffset);


		}



		// Offsets for loops

		idOffset += i_vertexArray[id].length();
		polycOffset += i_polygonCounts[id].length();
		polyConnOffset += i_polygonConnects[id].length();



	}





	// Flip normals ---------------------------------------------------------------------------- TEMP !!!!!!

	if (m_reverseNormals)
	{


		MIntArray revFCA;
		int co = o_polygonCounts.length() - 1;
		for (unsigned i = 0; i < o_polygonCounts.length(); i++)
		{
			revFCA.append(o_polygonCounts[co]);
			co -= 1;
		}


		MIntArray revPCA;
		co = o_polygonConnects.length() - 1;
		for (unsigned i = 0; i < o_polygonConnects.length(); i++)
		{
			revPCA.append(o_polygonConnects[co]);
			co -= 1;
		}





		o_polygonConnects = revPCA;
		o_polygonCounts = revFCA;


	}

	if (m_generateUVs)
	{



		if (m_reverseNormals)
		{


			MIntArray revUVCA;
			int co = o_uvCountsA.length() - 1;
			for (unsigned i = 0; i < o_uvCountsA.length(); i++)
			{
				revUVCA.append(o_uvCountsA[co]);
				co -= 1;
			}

			MIntArray revUVIDA;
			co = o_uvIdsA.length() - 1;
			for (unsigned i = 0; i < o_uvIdsA.length(); i++)
			{
				revUVIDA.append(o_uvIdsA[co]);
				co -= 1;
			}


			o_uvCountsA = revUVCA;
			o_uvIdsA = revUVIDA;

		}



	}


	return MS::kSuccess;
}





MStatus shellModNode::generateUVs() {
	MStatus status;


	// Clear arrays
	o_uArrayA.clear();
	o_vArrayA.clear();
	o_uvCountsA.clear();
	o_uvIdsA.clear();

	// Setup vectors for gathering base data from meshes
	//MString				defaultUVSetName;
	MFloatArray         in_uArray;
	MFloatArray         in_vArray;
	MIntArray           in_uvCounts;
	MIntArray           in_uvIds;

	//vector <MString>		v_defaultUVSetName;
	vector <MFloatArray>	v_in_uArray;
	vector <MFloatArray>	v_in_vArray;
	vector <MIntArray>		v_in_uvCounts;
	vector <MIntArray>		v_in_uvIds;

	int vecSize = m_inMeshArray.length();

	//v_defaultUVSetName.resize(vecSize);
	v_in_uArray.resize(vecSize);
	v_in_vArray.resize(vecSize);
	v_in_uvCounts.resize(vecSize);
	v_in_uvIds.resize(vecSize);



	for (int i = 0; i < m_inMeshArray.length(); i++)
	{

		MFnMesh mFnA(m_inMeshArray[i]);


		//status = mFnA.getCurrentUVSetName(defaultUVSetName);
		//CHECK_MSTATUS_AND_RETURN_IT(status);

		status = mFnA.getUVs(in_uArray, in_vArray);
		CHECK_MSTATUS_AND_RETURN_IT(status);

		//status = mFnA.getAssignedUVs(in_uvCounts, in_uvIds, &defaultUVSetName);
		status = mFnA.getAssignedUVs(in_uvCounts, in_uvIds);
		CHECK_MSTATUS_AND_RETURN_IT(status);


		//v_defaultUVSetName[i] = defaultUVSetName;
		//o_defaultUVSetNameA = defaultUVSetName;
		v_in_uArray[i] = in_uArray;
		v_in_vArray[i] = in_vArray;
		v_in_uvCounts[i] = in_uvCounts;
		v_in_uvIds[i] = in_uvIds;


	}




	// Calculate the outpout array size

	int id = 0;
	int len_uArray = 0;
	int len_vArray = 0;
	int len_uvCounts = 0;
	int len_uvIds = 0;
	for (int m = 0; m < m_numInputMeshes; m++)
	{
		id = m;

		len_uArray += v_in_uArray[id].length();
		len_vArray += v_in_vArray[id].length();
		len_uvCounts += v_in_uvCounts[id].length();
		len_uvIds += v_in_uvIds[id].length();

	}



	// Set output Array length

	o_uArrayA.setLength(len_uArray);
	o_vArrayA.setLength(len_vArray);
	o_uvCountsA.setLength(len_uvCounts);
	o_uvIdsA.setLength(len_uvIds);

	int o_uArrayA_offset = 0;
	int o_vArrayA_offset = 0;
	int o_uvCountsA_offset = 0;
	int o_uvIdsA_offset = 0;

	id = 0;

	float off_tileU = 0.0;
	float off_tileV = 0.0;

	for (int m = 0; m < m_numInputMeshes; m++)
	{
		id = m;
#pragma omp parallel for
		for (int v = 0; v < v_in_uArray[id].length(); v++) {
			o_uArrayA.set(v_in_uArray[id][v] + off_tileU, v + o_uArrayA_offset);
		}
#pragma omp parallel for
		for (int v = 0; v < v_in_vArray[id].length(); v++) {
			o_vArrayA.set(v_in_vArray[id][v] + off_tileV, v + o_vArrayA_offset);
		}
#pragma omp parallel for
		for (int v = 0; v < v_in_uvCounts[id].length(); v++) {
			o_uvCountsA.set(v_in_uvCounts[id][v], v + o_uvCountsA_offset);
		}
#pragma omp parallel for
		for (int v = 0; v < v_in_uvIds[id].length(); v++) {
			o_uvIdsA.set(v_in_uvIds[id][v] + o_uArrayA_offset, v + o_uvIdsA_offset);
		}

		o_uArrayA_offset += v_in_uArray[id].length();
		o_vArrayA_offset += v_in_vArray[id].length();
		o_uvCountsA_offset += v_in_uvCounts[id].length();
		o_uvIdsA_offset += v_in_uvIds[id].length();






		// Stack UV's


		//if (m_stackUV)
		//{
		//	off_tileU = m_uvOffsetU*m + m_rndOffsetU[m];
		//	off_tileV = m_uvOffsetV + m_rndOffsetV[m];
		//}



		//MGlobal::displayInfo(MString() + "m_rndOffsetXA[m]: " +  m_rndOffsetXA[m]);

	}


	return MS::kSuccess;
}





MStatus shellModNode::storeProfileCurveData()
{
	MStatus status;

	// Get curve data

	//MRampAttribute curveAttribute(this->thisMObject(), aCurveRamp, &status);
	//CHECK_MSTATUS_AND_RETURN_IT(status);

	a_curveAttribute.getEntries(m_curve_indices, m_curve_positions, m_curve_values, m_curve_interps);

	// Bubble Sort array

	float swapHolder_pos = -1.0;
	float swapHolder_val = -1.0;
	int aend = m_curve_positions.length() - 1;
	int alength = aend;

	for (int c = alength - 1; c > 0; c--)
	{
		for (int i = 0; i < aend; i++)
		{
			if (m_curve_positions[i] > m_curve_positions[i + 1])
			{
				swapHolder_pos = m_curve_positions[i + 1];
				m_curve_positions[i + 1] = m_curve_positions[i];
				m_curve_positions[i] = swapHolder_pos;

				swapHolder_val = m_curve_values[i + 1];
				m_curve_values[i + 1] = m_curve_values[i];
				m_curve_values[i] = swapHolder_val;
			}
		}

		aend--;
	}



	//m_curve_positions.remove(m_curve_positions.length());
	//m_curve_values.remove(m_curve_values.length());

	//m_curve_positions.remove(0);
	//m_curve_values.remove(0);

	return MS::kSuccess;

}

float shellModNode::getNormalizedFactorOfEdge(MItMeshEdge& itEdge, int edge, float distance, int originVertex)
{
	MPoint edge0vert0, edge0vert1;
	double length;
	int prevIndex;
	itEdge.setIndex(edge, prevIndex);
	itEdge.getLength(length);
	float factor = distance / length;
	if (factor > 1.0)
		factor = 1.0;
	if (itEdge.index(1) == originVertex)
		factor = 1 - factor;

	return factor;

}

void shellModNode::createChamfer(MObject& o_mergedMesh, MFnMesh &meshFn, MItMeshVertex &vIt, int vertexIndex, float offset)
{
	MIntArray placements;
	MIntArray edgeIDs;
	MFloatArray edgeFactors;
	MFloatPointArray internalPoints;
	MIntArray edges;
	int prevIndex;
	MItMeshEdge itEdge(o_mergedMesh, MObject::kNullObj);

	vIt.setIndex(vertexIndex, prevIndex);
	vIt.getConnectedEdges(edges);



	float fRadius = 0.1;

	float edgeFactor0 = shellModNode::getNormalizedFactorOfEdge(itEdge, edges[0], (fRadius * offset), vertexIndex);
	edgeFactors.append(edgeFactor0);
	edgeIDs.append(edges[0]);
	placements.append((int)MFnMesh::kOnEdge);

	//float edgeFactor1 = shellModNode::getNormalizedFactorOfEdge(itEdge, edges[1], (fRadius * -offset), vertexIndex);
	//edgeFactors.append(edgeFactor1);
	//edgeIDs.append(edges[1]);
	//placements.append((int)MFnMesh::kOnEdge);

	//MFloatPoint point1(0.0f,0.0f,0.0f);
	//internalPoints.append( point1 );
	//MGlobal::displayInfo( MString("Edges: " )+ edges[0] );

	//for (int e = 1; e < edges.length(); e++)
	//{
	//	//MGlobal::displayInfo( MString("Edges: " )+ edges[e] );
	//	placements.append((int)MFnMesh::kOnEdge);
	//	edgeIDs.append(edges[e]);
	//	edgeFactors.append(shellModNode::getNormalizedFactorOfEdge(itEdge, edges[e], (fRadius* offset), vertexIndex));
	//	//internalPoints.append( point1 );
	//}

	//placements.append((int)MFnMesh::kOnEdge);
	//edgeIDs.append(edges[0]);
	//edgeFactors.append(edgeFactor0);
	////internalPoints.append( point1 );

	meshFn.split(placements, edgeIDs, edgeFactors, internalPoints);
}

MPoint shellModNode::rotate_point(float cx, float cy, float angle, MPoint p)
{
	float s = sin(angle);
	float c = cos(angle);

	// translate point back to origin:
	p.x -= cx;
	p.y -= cy;

	// rotate point
	float xnew = p.x * c + p.y * s;
	float ynew = -p.x * s + p.y * c;

	// translate point back:
	p.x = xnew;
	p.y = ynew;

	return p;
}


MStatus shellModNode::extrudeMesh(MObject& o_mergedMesh)
{
	MStatus status;


	// set all mesh iterators
	MFnMesh mFn(o_mergedMesh);

	MItMeshVertex  mItVert(o_mergedMesh);
	MItMeshPolygon  mItPoly(o_mergedMesh);


	MFloatVector trVec(0.0, 0.0, 0.0);

	MIntArray numv, vertexCountA, vertexIdListA;
	MPointArray vertPoints, oldvertPoints, allVerts;

	MIntArray polygonVerts, connVertices, connFaces;
	MPoint currP;
	MVector currN;

	MVector offsetVec;
	MPoint offsetP;


	vector<MIntArray> edgeLoopVertsA;
	edgeLoopVertsA.clear();
	edgeLoopVertsA.resize(2);



	//

	vector<MPointArray> oldPolyPointsA;
	MVectorArray		oldPolyNormalA;
	MVectorArray		oldVertNormalA;

	oldPolyPointsA.clear();
	oldPolyNormalA.clear();
	oldVertNormalA.clear();

	m_vertConnA.clear();

	m_bevelEdgeArray.clear();

	MIntArray hardVerts, hardPolys, faceIDs;

	//// Store all the points of the original mesh


	//
	//
	//
	// Chamfer corners
	//
	//

	if (m_chamferEdges)
	{




		MIntArray placements;
		MIntArray edgeIDs;
		MFloatArray edgeFactors;
		MFloatPointArray internalPoints;

		bool found = false;


		mItVert.reset();

		for (; !mItVert.isDone(); mItVert.next())
		{


			if (mItVert.onBoundary())
			{

				MIntArray connVerts;
				mItVert.getConnectedVertices(connVerts);

				if (connVerts.length() == 2 || connVerts.length() == 4)
				{
					MPoint vertA;
					MPoint vertB;

					int vertAId;
					int vertBId;

					bool vertA_found = false;
					bool vertB_found = false;

					for (int i = 0; i < connVerts.length(); i++)
					{

						int previndex = 0;

						MItMeshVertex itVerts_border(o_mergedMesh);
						itVerts_border.setIndex(connVerts[i], previndex);

						if (itVerts_border.onBoundary())
						{

							if (!vertA_found)
							{
								vertA = itVerts_border.position();
								vertA_found = true;
								vertAId = itVerts_border.index();
								continue;
							}

							if (!vertB_found)
							{
								vertB = itVerts_border.position();
								vertB_found = true;
								vertBId = itVerts_border.index();
								continue;
							}

							if (vertA_found && vertB_found)
							{
								break;
							}

						}

					}

					if (vertA_found && vertB_found)
					{

						MIntArray connEdges;
						mItVert.getConnectedEdges(connEdges);

						if (connEdges.length() == 2 || connEdges.length() == 4 || connEdges.length() == 3)
						{

							int edgeAId;
							int edgeBId;

							bool edgeA_found = false;
							bool edgeB_found = false;

							MItMeshEdge itEdge_border(o_mergedMesh);

							for (int ce = 0; ce < connEdges.length(); ce++)
							{

								int previndex_edge = 0;


								itEdge_border.setIndex(connEdges[ce], previndex_edge);

								if (itEdge_border.onBoundary())
								{


									if (!edgeA_found)
									{

										edgeA_found = true;
										edgeAId = itEdge_border.index();
										continue;
									}

									if (!edgeB_found)
									{

										edgeB_found = true;
										edgeBId = itEdge_border.index();
										continue;
									}

									if (edgeA_found && edgeB_found)
									{
										break;
									}

								}
							}

							if (edgeA_found && edgeB_found)
							{


								edgeFactors.clear();
								edgeIDs.clear();
								placements.clear();


								float edgeFactor0 = shellModNode::getNormalizedFactorOfEdge(itEdge_border, edgeAId, (m_chamferEdgeFactor), mItVert.index());
								edgeFactors.append(edgeFactor0);

								//edgeFactors.append(m_chamferEdgeFactor);

								edgeIDs.append(edgeAId);
								placements.append((int)MFnMesh::kOnEdge);

								mFn.split(placements, edgeIDs, edgeFactors, internalPoints);

								edgeFactors.clear();
								edgeIDs.clear();
								placements.clear();

								float edgeFactor1 = shellModNode::getNormalizedFactorOfEdge(itEdge_border, edgeBId, (m_chamferEdgeFactor), mItVert.index());
								edgeFactors.append(edgeFactor1);

								//edgeFactors.append(1.0 - m_chamferEdgeFactor);

								edgeIDs.append(edgeBId);
								placements.append((int)MFnMesh::kOnEdge);

								mFn.split(placements, edgeIDs, edgeFactors, internalPoints);

							}


						}




					}

				}



			}



		}

	}


	// Num verts

	int numVerts = mFn.numVertices();
	int numVertsBoundary = 0;

	// Store old UV's


	MFloatArray ouArray;
	MFloatArray ovArray;
	MIntArray ouvCounts;
	MIntArray ouvIds;


	//status = mFn.getCurrentUVSetName(o_defaultUVSetNameA);
	//CHECK_MSTATUS_AND_RETURN_IT(status);

	status = mFn.getUVs(ouArray, ovArray);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	/*status = mFn.getAssignedUVs(ouvCounts, ouvIds, &o_defaultUVSetNameA);*/
	status = mFn.getAssignedUVs(ouvCounts, ouvIds);
	CHECK_MSTATUS_AND_RETURN_IT(status);



	// Store all the points of the original mesh
	MPointArray oldVertPointsA;
	status = mFn.getPoints(oldVertPointsA, MSpace::kObject);
	CHECK_MSTATUS_AND_RETURN_IT(status);





	MPointArray boundaryPA;
	MIntArray boundaryIdA;

	mItVert.reset();

	// Store Boundary verts, and original object normals
	for (; !mItVert.isDone(); mItVert.next())
	{
		if (mItVert.onBoundary())
		{
			numVertsBoundary += 1;
			boundaryPA.append(mItVert.position());
			boundaryIdA.append(mItVert.index());
		}

		status = mItVert.getNormal(currN, MSpace::kObject);
		CHECK_MSTATUS_AND_RETURN_IT(status);

		oldVertNormalA.append(currN);

	}




	// Store all polygon points vert position, and all poly normals
	for (; !mItPoly.isDone(); mItPoly.next())
	{

		numv.append(mItPoly.index());


		mItPoly.getPoints(oldvertPoints, MSpace::kObject, &status);
		CHECK_MSTATUS_AND_RETURN_IT(status);
		oldPolyPointsA.push_back(oldvertPoints);

		MVector currN;

		status = mItPoly.getNormal(currN, MSpace::kObject);
		CHECK_MSTATUS_AND_RETURN_IT(status);
		oldPolyNormalA.append(currN);
	}



	// -----------------------------------------------------------------------------------------
	// DO EXTRUDE

	int segStart = 0;

	if (m_autoSegments)
	{
		m_segments = m_curve_positions.length();
		segStart = 1;
	}

	if (!m_autoSegments)
	{
		//m_segments += 1;
	}


	double straightEdgeRad = ((270.0 - m_straightEdgesAngle) * M_PI / 180);

	int numPoly = 0;
	int previndex = 0;

	int borderPolyCount = 0;
	numPoly = mFn.numPolygons();


	for (int seg = segStart; seg < m_segments; seg++) // Iterate trough numbers of extrusions
	{

		status = mFn.extrudeFaces(numv, 1, &trVec, true);
		CHECK_MSTATUS_AND_RETURN_IT(status);

		status = mFn.getPoints(vertPoints, MSpace::kObject);
		CHECK_MSTATUS_AND_RETURN_IT(status);

		status = mFn.getVertices(vertexCountA, vertexIdListA);
		CHECK_MSTATUS_AND_RETURN_IT(status);

		if (seg == 1)
		{
			borderPolyCount = mFn.numPolygons() - (numPoly * 2);
		}

		MIntArray m_vertConnA_segment;


		for (unsigned int i = 0; i < numv.length(); i++)
		{
			status = mFn.getPolygonVertices(i, polygonVerts);
			CHECK_MSTATUS_AND_RETURN_IT(status);


			//#pragma omp parallel for
			for (int j = 0; j < polygonVerts.length(); j++)
			{

				m_vertConnA_segment.append(polygonVerts[j]);


				status = mFn.getPoint(polygonVerts[j], currP, MSpace::kObject);
				CHECK_MSTATUS_AND_RETURN_IT(status);

				status = mFn.getVertexNormal(polygonVerts[j], false, currN, MSpace::kObject);
				CHECK_MSTATUS_AND_RETURN_IT(status);



				currN.normalize();

				MVector offVec;

				if (m_autoSegments)
				{
					offVec = -currN * ((m_curve_positions[seg] - m_curve_positions[seg - 1]) * m_weight);
					currP += offVec;
				}

				if (!m_autoSegments)
				{
					offVec = -currN * (m_weight / double(m_segments));
					currP += offVec;
				}


				MPoint vx1 = oldPolyPointsA[i][j];
				MPoint vx2 = currP;

				MVector vec1 = vx2 - vx1;
				vec1.normalize();

				MVector vec2 = -oldPolyNormalA[i];
				double ang = vec1.angle(vec2);
				double fac = 1.0 / cos(ang);



				if (m_autoSegments)
				{

					if (m_straightEdges)
					{





						if (fac >= 1.0 && fac <= straightEdgeRad)
						{
							vx2 = vx1 + fac * vec1 *  (m_weight * m_curve_positions[seg]);

						}


					}


				}



				if (!m_autoSegments)
				{
					if (m_straightEdges)
					{
						if (fac >= 1.0 && fac <= straightEdgeRad)
						{
							vx2 = vx1 + fac * vec1 * ((m_weight / m_segments) * double(seg + 1));
						}
					}
				}

				if (!m_straightEdges)
				{
					vx2 = currP;
				}



				vertPoints.set(vx2, polygonVerts[j]);

				//------------------------------------------------------------------------------


			}


		}


		m_vertConnA.push_back(m_vertConnA_segment);

		if (vertPoints.length() > 0)
		{
			status = mFn.setPoints(vertPoints, MSpace::kObject);
			CHECK_MSTATUS_AND_RETURN_IT(status);
		}





	}



	//mFn.updateSurface();



	// -----------------------------------------------------------------------------------------
	// PROFILE


	status = mFn.getPoints(allVerts, MSpace::kObject);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	oldPolyPointsA.clear();
	oldPolyNormalA.clear();
	mItPoly.reset();

	for (; !mItPoly.isDone(); mItPoly.next())
	{


		mItPoly.getPoints(oldvertPoints, MSpace::kObject, &status);
		CHECK_MSTATUS_AND_RETURN_IT(status);
		oldPolyPointsA.push_back(oldvertPoints);

		MVector currN;

		status = mItPoly.getNormal(currN, MSpace::kObject);
		CHECK_MSTATUS_AND_RETURN_IT(status);
		oldPolyNormalA.append(currN);
	}

	//------------------------------------------------------------------------------

	int startP = numPoly * 2;
	int endP = mFn.numPolygons();
	int segCount = 0;

	float rampPosition, curveRampValue;

	int co = 1;
	for (int i = startP; i < endP; i++)
	{
		//MGlobal::displayInfo(MString() + i);

		status = mFn.getPolygonVertices(i, polygonVerts);
		CHECK_MSTATUS_AND_RETURN_IT(status);

		for (int j = 0; j < polygonVerts.length(); j++)
		{
			status = mFn.getPoint(polygonVerts[j], currP, MSpace::kObject);
			CHECK_MSTATUS_AND_RETURN_IT(status);

			status = mFn.getVertexNormal(polygonVerts[j], false, currN, MSpace::kObject);
			CHECK_MSTATUS_AND_RETURN_IT(status);

			MPoint oldP = currP;



			if (m_autoSegments)
			{
				currP += -currN * (m_bulge * m_curve_values[segCount]);
			}

			if (!m_autoSegments)
			{

				rampPosition = (1.0f / float(m_segments)) * (float(segCount) * 2.0f);
				curveRampValue = (1.0f / float(m_segments)) * (float(segCount) * 2.0f);
				a_curveAttribute.getValueAtPosition(rampPosition, curveRampValue);
				currP += -currN * double(curveRampValue) * m_bulge;

			}



			if (m_straightEdges) // Straighten it
			{
				MPoint vx1 = oldPolyPointsA[i][j];
				MPoint vx2 = currP;

				MVector vec1 = vx2 - vx1;
				vec1.normalize();

				MVector vec2 = -oldPolyNormalA[i];
				double ang = vec1.angle(vec2);
				double fac = 1.0 / cos(ang);

				if (m_autoSegments)
				{
					if (fac >= 1.0 && fac <= straightEdgeRad)
					{
						currP = vx1 + fac * vec1 *  (m_bulge * m_curve_values[segCount]);
					}
				}

				if (!m_autoSegments)
				{
					if (fac >= 1.0 && fac <= straightEdgeRad)
					{
						currP = vx1 + fac * vec1 *  double(curveRampValue) * m_bulge;
					}
				}
			}

			if (polygonVerts[j] >= allVerts.length() - numVerts)
			{
				currP = oldP;
			}

			allVerts.set(currP, polygonVerts[j]);

		}

		if (co == borderPolyCount)
		{
			//MGlobal::displayInfo(MString() + "-----------");
			segCount += 1;
			co = 0;
		}

		co += 1;

	}


	status = mFn.setPoints(allVerts, MSpace::kObject);
	CHECK_MSTATUS_AND_RETURN_IT(status);







	// --------------------------------------------------------------------------
	// Cap top polygon




	MIntArray extractFacesA;

	if (!m_capTop)
	{

		for (int i = 0; i < numPoly; i++)
		{
			extractFacesA.append(i);
		}

	}

	if (!m_capBottom)
	{
		for (int i = numPoly; i < numPoly * 2; i++)
		{
			extractFacesA.append(i);
		}


	}

	if (!m_capTop || !m_capBottom)
	{
		MFloatVector translation(0.0, 0.0, 0.0);
		status = mFn.extractFaces(extractFacesA, &translation);
		CHECK_MSTATUS_AND_RETURN_IT(status);



		status = mFn.collapseFaces(extractFacesA);
		CHECK_MSTATUS_AND_RETURN_IT(status);


	}







	// ---------------------------------------------------------------------
	//	int nnumVertices = mFn.numVertices();
	int nnumPolygons = mFn.numPolygons();
	MFloatPointArray nvertexArray;
	MIntArray npolygonCounts;
	MIntArray npolygonConnects;

	status = mFn.getVertices(npolygonCounts, npolygonConnects);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	status = mFn.getPoints(nvertexArray, MSpace::kObject);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	int nNumVertecies = mFn.numVertices();


	// flip normals

	MIntArray tempArray;
	int count = 0;

	for (int i = 0; i < nnumPolygons; i++)
	{
		count = count + npolygonCounts[i];
		for (int j = 0; j < npolygonCounts[i]; j++) {
			if (j == 0) {
				tempArray.append(npolygonConnects[count - npolygonCounts[i]]);

			}
			else {
				tempArray.append(npolygonConnects[count - j]);

			}
		}


	}



	// Replace old array with reversed array (Flip uv's and normals)

	o_vertexArray = nvertexArray;
	o_numVertices = nNumVertecies;
	o_numPolygons = nnumPolygons;
	o_polygonCounts = npolygonCounts;
	o_polygonConnects = tempArray;


	if (m_generateUVs)
	{

		// UVs

		n_uArrayA.clear();
		n_vArrayA.clear();


		if (mFn.numUVs() > 0)
		{


			MIntArray nuvCounts;
			MIntArray nuvIds;

			status = mFn.getUVs(n_uArrayA, n_vArrayA);
			CHECK_MSTATUS_AND_RETURN_IT(status);




			//if (!status)
			//{
			//	MGlobal::displayWarning(MString() + "[ShellMod] - Could not get UVs");
			//	o_uvCountsA.clear();
			//	o_uArrayA.clear();
			//	o_vArrayA.clear();
			//	return MS::kSuccess;
			//}


			double centerU = 0.0;
			double centerV = 0.0;




			/*status = mFn.getAssignedUVs(nuvCounts, nuvIds, &o_defaultUVSetNameA);*/
			status = mFn.getAssignedUVs(nuvCounts, nuvIds);
			CHECK_MSTATUS_AND_RETURN_IT(status);

			o_uvIdsA = nuvIds;


	/*		if (!status)
			{
				MGlobal::displayWarning(MString() + "[ShellMod] - Could not get UVs on mesh");
				o_uvCountsA.clear();
				o_uArrayA.clear();
				o_vArrayA.clear();
				return MS::kSuccess;
			}*/


			// Pre transform UVs

			if (n_uArrayA.length() > 0)
			{

				for (int i = 0; i < n_uArrayA.length(); i++)
				{
					centerU += n_uArrayA[i];
					centerV += n_vArrayA[i];
				}

				centerU /= n_uArrayA.length();
				centerV /= n_vArrayA.length();

				MPoint rotUVP;
				double rotAxis = (m_uvRotate + 180.000)  * (M_PI / 180.0);

				for (int i = 0; i < n_uArrayA.length(); i++)
				{

					n_uArrayA[i] *= m_uvScaleU;
					n_vArrayA[i] *= m_uvScaleV;

					rotUVP = shellModNode::rotate_point(n_uArrayA[i], n_vArrayA[i], rotAxis, MPoint(centerU, centerV, 0.0));

					n_uArrayA[i] = rotUVP.x + centerU;
					n_vArrayA[i] = rotUVP.y + centerV;

					n_uArrayA[i] += m_uvTranslateU;
					n_vArrayA[i] += m_uvTranslateV;


				}

			}

			// ---------------------------------------------------------------------
			// If auto U UV Offset is turned on
			if (m_uvOffsetUAuto)
			{

				// Calculate min max U
				double uMin = n_uArrayA[0];
				double uMax = n_uArrayA[0];

#pragma omp parallel for
				for (int i = 0; i < n_uArrayA.length(); i++)
				{
					if (n_uArrayA[i] > uMax)
					{
						uMax = n_uArrayA[i];
					}
					else if (n_uArrayA[i] < uMin)
					{
						uMin = n_uArrayA[i];
					}
				}

				double uMinMaxDist = uMax - uMin;

				m_uvOffsetU = uMinMaxDist + m_uvOffsetUAutoPadding;

			}

			// Offset new UV's
			int uvAL = ouArray.length();

#pragma omp parallel for
			for (int i = uvAL; i < uvAL * 2; i++)
			{
				n_uArrayA[i] = n_uArrayA[i] + float(m_uvOffsetU);
				n_vArrayA[i] = n_vArrayA[i] + float(m_uvOffsetV);
			}


			// flip uvs

			MIntArray		n_ouvIds;

			int count = 0;


			if (nuvIds.length() > 0)
			{
				for (int i = 0; i < nnumPolygons; i++)
				{
					count = count + npolygonCounts[i];

					for (int j = 0; j < npolygonCounts[i]; j++) {
						if (j == 0) {

							if (count - npolygonCounts[i] < nuvIds.length())
							{
								n_ouvIds.append(nuvIds[count - npolygonCounts[i]]);
							}

						}
						else {
							if (count - npolygonCounts[i] < nuvIds.length())
							{
								n_ouvIds.append(nuvIds[count - j]);
							}
						}
					}


				}


				o_uvIdsA = n_ouvIds;

			}



			o_uvCountsA = nuvCounts;
			o_uArrayA = n_uArrayA;
			o_vArrayA = n_vArrayA;



		}

		else
		{
			o_uvCountsA.clear();
			o_uArrayA.clear();
			o_vArrayA.clear();
		}
	}


	return MS::kSuccess;
}

MStatus shellModNode::setObjectSmoothness()
{
	MStatus status;

	// Iterate trhrough input meshes and collect Subdivision status
	for (unsigned int i = 0; i < p_inMesh.numElements(); i++)
	{
		if (p_inMesh[i].isConnected())
		{
			MPlug inMeshPlug = p_inMesh[i];

			inMeshPlug.selectAncestorLogicalIndex(0);
			MPlugArray inputs_plugArr;
			inMeshPlug.connectedTo(inputs_plugArr, true, false);
			inMeshPlug = inputs_plugArr[0];

			MFnDependencyNode inMesh_dn(inMeshPlug.node());

			p_smoothMeshPlug = inMesh_dn.findPlug("displaySmoothMesh");
			MPlug p_displaySubdComps = inMesh_dn.findPlug("displaySubdComps");
			p_smoothLevelPlug = inMesh_dn.findPlug("smoothLevel");

			//MGlobal::displayInfo(MString() + p_smoothMeshPlug.info() );

			if (m_isSmoothed)
			{
				p_smoothMeshPlug.setBool(true);
				p_displaySubdComps.setInt(0);
			}

			else
			{
				p_smoothMeshPlug.setBool(false);
			}

		}
	}


	return MS::kSuccess;
}


MStatus shellModNode::compute(const MPlug& plug, MDataBlock& data)
{

	MStatus status;


	// check that the output mesh is connected
	MPlug p_outMesh_check = MPlug(this->thisMObject(), aOutMesh);
	MPlug p_outComponent = MPlug(this->thisMObject(), aOutputComponents);

	if (!p_outMesh_check.isConnected())
	{
		return MS::kSuccess;
	}


	// collect the input plug data
	status = collectPlugs(data);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	// Store curve data
	status = storeProfileCurveData();
	CHECK_MSTATUS_AND_RETURN_IT(status);

	// Set profile preset
	profilePresets(m_profilePreset);


	// Collect input meshes
	status = collectInputMeshes(data);
	CHECK_MSTATUS_AND_RETURN_IT(status);



	if (m_generateUVs)
	{
		// Merge uv's
		status = generateUVs();
		CHECK_MSTATUS_AND_RETURN_IT(status);
	}



	//


	// Merge input meshes
	status = mergeInputMeshes();
	CHECK_MSTATUS_AND_RETURN_IT(status);

	// --------------




	// -----------------------------------------------------------------------------------------------------------------------
	// Crete merged output mesh
	MFnMesh meshFn;

	MFnMeshData meshDataFn;
	MObject newMeshData = meshDataFn.create();

	// Create combined Meshes


	meshFn.create(o_numVertices, o_numPolygons, o_vertexArray, o_polygonCounts, o_polygonConnects, newMeshData, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	if (m_generateUVs)
	{

		status = meshFn.setUVs(o_uArrayA, o_vArrayA);
		CHECK_MSTATUS_AND_RETURN_IT(status);

		/*status = meshFn.assignUVs(o_uvCountsA, o_uvIdsA, &o_defaultUVSetNameA);*/
		status = meshFn.assignUVs(o_uvCountsA, o_uvIdsA);
		CHECK_MSTATUS_AND_RETURN_IT(status);
	}



	extrudeMesh(newMeshData);





	// -----------------------------------------------------------------------------------------------------------------------
	// Crete extruded output mesh
	MFnMesh ex_meshFn;

	// Set output mesh
	MFnMeshData ex_meshDataFn;
	MObject ex_newMeshData = ex_meshDataFn.create();

	if (o_polygonConnects.length() != 0)
	{
		ex_meshFn.create(o_numVertices, o_numPolygons, o_vertexArray, o_polygonCounts, o_polygonConnects, ex_newMeshData, &status);
		CHECK_MSTATUS_AND_RETURN_IT(status);
	}

	if (m_generateUVs)
	{

		status = ex_meshFn.setUVs(o_uArrayA, o_vArrayA);
		CHECK_MSTATUS_AND_RETURN_IT(status);

		/*status = ex_meshFn.assignUVs(o_uvCountsA, o_uvIdsA, &o_defaultUVSetNameA);*/
		status = ex_meshFn.assignUVs(o_uvCountsA, o_uvIdsA);
		CHECK_MSTATUS_AND_RETURN_IT(status);
	}


	// ------------------------------------------------------------------------------
	// Set edge smoothing globally
	for (int loop = 0; loop < ex_meshFn.numEdges(); loop++)
	{

		if (m_smoothNorm == true) { ex_meshFn.setEdgeSmoothing(loop, true); }
		if (m_smoothNorm == false) { ex_meshFn.setEdgeSmoothing(loop, false); }
	}

	status = ex_meshFn.cleanupEdgeSmoothing();
	CHECK_MSTATUS_AND_RETURN_IT(status);

	status = ex_meshFn.updateSurface();
	CHECK_MSTATUS_AND_RETURN_IT(status);



	// -----------------------------------------------------------------------------------------------------------------------
	// Set output mesh to datablock


	if (m_isSmoothed)
	{
		o_smoothOptions.setDivisions(m_smoothMeshSubdiv, &status);
		CHECK_MSTATUS_AND_RETURN_IT(status);


		o_smoothOptions.setBoundaryRule(MMeshSmoothOptions::kLegacy);
		CHECK_MSTATUS_AND_RETURN_IT(status);



		o_smoothOptions.setKeepBorderEdge(false);
		CHECK_MSTATUS_AND_RETURN_IT(status);


		ex_meshFn.generateSmoothMesh(ex_newMeshData, &o_smoothOptions, &status);
		CHECK_MSTATUS_AND_RETURN_IT(status);
		h_outputMesh.set(ex_newMeshData);

	}




	else
	{
		h_outputMesh.set(ex_newMeshData);
	}



	// Create output component list
	MDataHandle outComponentsHnd = data.outputValue(aOutputComponents);


	MFnComponentListData fnComponentList;
	MObject componentData = fnComponentList.create();

	MFnSingleIndexedComponent fnSingleComponent;
	MObject component = fnSingleComponent.create(MFn::kMeshEdgeComponent);
	fnSingleComponent.addElements(m_bevelEdgeArray);
	fnComponentList.add(component);

	p_outComponent.setMObject(fnComponentList.object());




	// setup connections
	status = setupConneCtions(p_inMesh, p_outMesh);
	CHECK_MSTATUS_AND_RETURN_IT(status);


	if (s_readPluginPath.length() != 0)
	{
		h_outPresetPath.setString(s_readPluginPath);
	}

	//


	return MStatus::kSuccess;
}

MStatus shellModNode::initialize()
{
	// local attribute initialization
	MStatus status;


	//

	MFnTypedAttribute tAttr;
	MFnNumericAttribute nAttr;
	MRampAttribute mAttr;
	MFnEnumAttribute eAttr;


	shellModNode::aInMesh = tAttr.create("inMesh", "inMesh", MFnNumericData::kMesh);
	tAttr.setStorable(false);
	tAttr.setKeyable(false);
	tAttr.setChannelBox(false);
	tAttr.setArray(true);
	tAttr.setDisconnectBehavior(MFnAttribute::kDelete);
	addAttribute(shellModNode::aInMesh);

	shellModNode::aOutMesh = tAttr.create("outMesh", "outMesh", MFnData::kMesh);
	tAttr.setStorable(false);
	tAttr.setWritable(false);
	tAttr.setReadable(true);
	addAttribute(shellModNode::aOutMesh);


	shellModNode::aCapTop = nAttr.create("capTop", "capTop", MFnNumericData::kBoolean);
	nAttr.setStorable(true);
	nAttr.setDefault(true);
	nAttr.setKeyable(true);
	nAttr.setChannelBox(true);
	addAttribute(shellModNode::aCapTop);

	//shellModNode::aDisplaySmoothMesh = nAttr.create("displaySmoothMesh", "displaySmoothMesh", MFnNumericData::kInt);
	////nAttr.setArray(true);
	//addAttribute(shellModNode::aDisplaySmoothMesh);


	shellModNode::aCapBottom = nAttr.create("capBottom", "capBottom", MFnNumericData::kBoolean);
	nAttr.setStorable(true);
	nAttr.setDefault(true);
	nAttr.setKeyable(true);
	nAttr.setChannelBox(true);
	addAttribute(shellModNode::aCapBottom);

	shellModNode::aSmoothNormals = nAttr.create("smoothNormals", "smoothNormals", MFnNumericData::kBoolean);
	nAttr.setStorable(true);
	nAttr.setDefault(false);
	nAttr.setKeyable(true);
	nAttr.setChannelBox(true);
	addAttribute(shellModNode::aSmoothNormals);

	shellModNode::aReverseNormals = nAttr.create("reverseNormals", "reverseNormals", MFnNumericData::kBoolean);
	nAttr.setDefault(false);
	nAttr.setKeyable(true);
	nAttr.setChannelBox(true);
	addAttribute(shellModNode::aReverseNormals);


	shellModNode::aStraightenEdges = nAttr.create("straightenEdges", "straightenEdges", MFnNumericData::kBoolean);
	nAttr.setStorable(true);
	nAttr.setDefault(true);
	nAttr.setKeyable(true);
	nAttr.setChannelBox(true);
	addAttribute(shellModNode::aStraightenEdges);

	shellModNode::aAutoSegments = nAttr.create("autoSegments", "autoSegments", MFnNumericData::kBoolean);
	nAttr.setStorable(true);
	nAttr.setDefault(true);
	nAttr.setKeyable(true);
	nAttr.setChannelBox(true);
	addAttribute(shellModNode::aAutoSegments);

	shellModNode::aChamferEdges = nAttr.create("chamferEdges", "chamferEdges", MFnNumericData::kBoolean);
	nAttr.setStorable(true);
	nAttr.setDefault(false);
	nAttr.setKeyable(true);
	nAttr.setChannelBox(true);
	status = addAttribute(shellModNode::aChamferEdges);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	shellModNode::aUVOffsetUAuto = nAttr.create("uvOffsetUAutoOffset", "uvOffsetUAutoOffset", MFnNumericData::kBoolean);
	nAttr.setStorable(true);
	nAttr.setDefault(false);
	nAttr.setKeyable(true);
	nAttr.setChannelBox(true);
	addAttribute(shellModNode::aUVOffsetUAuto);


	shellModNode::aGenerateUVs = nAttr.create("generateUVs", "generateUVs", MFnNumericData::kBoolean);
	nAttr.setStorable(true);
	nAttr.setDefault(false);
	nAttr.setKeyable(true);
	nAttr.setChannelBox(true);
	addAttribute(shellModNode::aGenerateUVs);

	shellModNode::aUVOffsetUAutoPadding = nAttr.create("uvOffsetUAutoOffsetPadding", "uvOffsetUAutoOffsetPadding", MFnNumericData::kDouble);
	nAttr.setStorable(true);
	nAttr.setDefault(0.01);
	nAttr.setMin(0.0);
	nAttr.setSoftMax(0.5);
	nAttr.setKeyable(true);
	nAttr.setChannelBox(true);
	addAttribute(shellModNode::aUVOffsetUAutoPadding);


	shellModNode::aDisableBaseMeshOverride = nAttr.create("baseMeshDisplayOverride", "baseMeshDisplayOverride", MFnNumericData::kBoolean);
	nAttr.setStorable(true);
	nAttr.setDefault(true);
	nAttr.setKeyable(true);
	nAttr.setChannelBox(true);
	addAttribute(shellModNode::aDisableBaseMeshOverride);


	shellModNode::aDisableOutputMeshOverride = nAttr.create("outputMeshDisplayOverride", "outputMeshDisplayOverride", MFnNumericData::kBoolean);
	nAttr.setStorable(true);
	nAttr.setDefault(true);
	nAttr.setKeyable(true);
	nAttr.setChannelBox(true);
	addAttribute(shellModNode::aDisableOutputMeshOverride);


	shellModNode::aOffsetZ = nAttr.create("offsetZ", "offsetZ", MFnNumericData::kDouble);
	nAttr.setStorable(true);
	nAttr.setDefault(1.0);
	nAttr.setMin(0.0);
	nAttr.setSoftMax(1.0);
	nAttr.setKeyable(true);
	nAttr.setChannelBox(true);
	addAttribute(shellModNode::aOffsetZ);


	shellModNode::aStraightenEdgesAngle = nAttr.create("straightenEdgesAngle", "straightenEdgesAngle", MFnNumericData::kDouble);
	nAttr.setStorable(true);
	nAttr.setDefault(1.0);
	nAttr.setMin(1.0);
	nAttr.setMax(270.0);
	nAttr.setKeyable(true);
	nAttr.setChannelBox(true);
	addAttribute(shellModNode::aStraightenEdgesAngle);

	shellModNode::aBevelEdgesAngle = nAttr.create("bevelEdgesAngle", "bevelEdgesAngle", MFnNumericData::kDouble);
	nAttr.setStorable(true);
	nAttr.setDefault(1.0);
	nAttr.setSoftMin(0.0);
	nAttr.setSoftMax(1.0);
	nAttr.setKeyable(true);
	nAttr.setChannelBox(true);
	addAttribute(shellModNode::aBevelEdgesAngle);


	shellModNode::aChamferEdgeFactor = nAttr.create("chamferEdgeFactor", "chamferEdgeFactor", MFnNumericData::kDouble);
	nAttr.setStorable(true);
	nAttr.setDefault(0.1);
	nAttr.setMin(0.0);
	nAttr.setMax(1.0);
	nAttr.setKeyable(true);
	nAttr.setChannelBox(true);
	status = addAttribute(shellModNode::aChamferEdgeFactor);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	shellModNode::aBulge = nAttr.create("profileStrength", "profileStrength", MFnNumericData::kDouble);
	nAttr.setStorable(true);
	nAttr.setDefault(0.25);
	nAttr.setSoftMin(-1.0);
	nAttr.setSoftMax(1.0);
	nAttr.setKeyable(true);
	nAttr.setChannelBox(true);
	addAttribute(shellModNode::aBulge);

	shellModNode::aUVOffsetU = nAttr.create("uvOffsetU", "uvOffsetU", MFnNumericData::kDouble);
	nAttr.setStorable(true);
	nAttr.setDefault(1.0);
	nAttr.setSoftMin(0.0);
	nAttr.setSoftMax(1.0);
	nAttr.setKeyable(true);
	nAttr.setChannelBox(true);
	addAttribute(shellModNode::aUVOffsetU);

	shellModNode::aUVOffsetV = nAttr.create("uvOffsetV", "uvOffsetV", MFnNumericData::kDouble);
	nAttr.setStorable(true);
	nAttr.setDefault(0.0);
	nAttr.setSoftMin(0.0);
	nAttr.setSoftMax(1.0);
	nAttr.setKeyable(true);
	nAttr.setChannelBox(true);
	addAttribute(shellModNode::aUVOffsetV);

	// UV Transforms
	shellModNode::aUVTranslateU = nAttr.create("uvTranslateU", "uvTranslateU", MFnNumericData::kDouble);
	nAttr.setStorable(true);
	nAttr.setDefault(0.0);
	nAttr.setSoftMin(0.0);
	nAttr.setSoftMax(1.0);
	nAttr.setKeyable(true);
	nAttr.setChannelBox(true);
	addAttribute(shellModNode::aUVTranslateU);

	shellModNode::aUVTranslateV = nAttr.create("uvTranslateV", "uvTranslateV", MFnNumericData::kDouble);
	nAttr.setStorable(true);
	nAttr.setDefault(0.0);
	nAttr.setSoftMin(0.0);
	nAttr.setSoftMax(1.0);
	nAttr.setKeyable(true);
	nAttr.setChannelBox(true);
	addAttribute(shellModNode::aUVTranslateV);

	shellModNode::aUVRotate = nAttr.create("uvRotate", "uvRotate", MFnNumericData::kDouble);
	nAttr.setStorable(true);
	nAttr.setDefault(0.0);
	nAttr.setSoftMin(0.0);
	nAttr.setSoftMax(360.0);
	nAttr.setKeyable(true);
	nAttr.setChannelBox(true);
	addAttribute(shellModNode::aUVRotate);


	shellModNode::aUVScaleU = nAttr.create("uvScaleU", "uvScaleU", MFnNumericData::kDouble);
	nAttr.setStorable(true);
	nAttr.setDefault(1.0);
	nAttr.setSoftMin(0.0);
	nAttr.setSoftMax(1.0);
	nAttr.setKeyable(true);
	nAttr.setChannelBox(true);
	addAttribute(shellModNode::aUVScaleU);

	shellModNode::aUVScaleV = nAttr.create("uvScaleV", "uvScaleV", MFnNumericData::kDouble);
	nAttr.setStorable(true);
	nAttr.setDefault(1.0);
	nAttr.setSoftMin(0.0);
	nAttr.setSoftMax(1.0);
	nAttr.setKeyable(true);
	nAttr.setChannelBox(true);
	addAttribute(shellModNode::aUVScaleV);

	shellModNode::aSmoothSubdiv = nAttr.create("smoothMeshSubdiv", "smoothMeshSubdiv", MFnNumericData::kInt);
	nAttr.setStorable(true);
	nAttr.setDefault(1);
	nAttr.setMin(1);
	nAttr.setSoftMax(3);
	nAttr.setKeyable(true);
	nAttr.setChannelBox(true);
	addAttribute(shellModNode::aSmoothSubdiv);

	shellModNode::aSegments = nAttr.create("segments", "segments", MFnNumericData::kInt);
	nAttr.setStorable(true);
	nAttr.setDefault(1);
	nAttr.setMin(1);
	nAttr.setSoftMax(10);
	nAttr.setKeyable(true);
	nAttr.setChannelBox(true);
	addAttribute(shellModNode::aSegments);


	shellModNode::aProfilePresets = eAttr.create("profilePresets", "profilePresets", 0);
	eAttr.setStorable(true);
	eAttr.addField("Custom", 0);
	eAttr.addField("ChaserEdge 1%", 1);
	eAttr.addField("ChaserEdge 2%", 2);
	eAttr.addField("ChaserEdge 5%", 3);
	eAttr.addField("ChaserEdge 10%", 4);
	eAttr.addField("ChaserEdge 20%", 5);
	eAttr.addField("ChaserEdge 30%", 6);
	eAttr.addField("Architectual 1", 7);
	eAttr.addField("Architectual 2", 8);
	eAttr.addField("Architectual 3", 9);
	eAttr.addField("Architectual 4", 10);
	eAttr.addField("Sci-Fi 1", 11);
	eAttr.addField("Sci-Fi 2", 12);
	eAttr.addField("Sci-Fi 3", 13);
	eAttr.addField("Sci-Fi 4", 14);
	eAttr.addField("Sci-Fi 5", 15);
	eAttr.addField("Pattern 1", 16);
	eAttr.addField("Pattern 2", 17);
	eAttr.addField("Bolt 1", 18);
	eAttr.addField("Bolt 2", 19);

	eAttr.setDefault(3);
	addAttribute(shellModNode::aProfilePresets);

	shellModNode::aCurveRamp = mAttr.createCurveRamp("profileRamp", "profileRamp");
	addAttribute(aCurveRamp);



	// Add text attributes.
	MFnStringData stringFn;
	MObject defaultText = stringFn.create("Unknown path");
	shellModNode::aPresetFolderPath = tAttr.create("presetFolderPath", "presetFolderPath", MFnData::kString, defaultText);
	tAttr.setKeyable(false);
	tAttr.setChannelBox(false);
	//tAttr.setUsedAsFilename(true);
	addAttribute(shellModNode::aPresetFolderPath);


	// Output components
	aOutputComponents = tAttr.create("outputComponents", "outputComponents", MFnData::kComponentList);
	addAttribute(shellModNode::aOutputComponents);


	attributeAffects(shellModNode::aInMesh, shellModNode::aOutputComponents);
	attributeAffects(shellModNode::aInMesh, shellModNode::aOutMesh);
	attributeAffects(shellModNode::aOffsetZ, shellModNode::aOutMesh);

	attributeAffects(shellModNode::aChamferEdges, shellModNode::aOutMesh);
	attributeAffects(shellModNode::aChamferEdgeFactor, shellModNode::aOutMesh);

	//	attributeAffects(shellModNode::aChaserEdgeWeight, shellModNode::aOutMesh);
	attributeAffects(shellModNode::aSegments, shellModNode::aOutMesh);
	//	attributeAffects(shellModNode::aChaserEdges, shellModNode::aOutMesh);
	attributeAffects(shellModNode::aCapTop, shellModNode::aOutMesh);
	attributeAffects(shellModNode::aCapBottom, shellModNode::aOutMesh);
	attributeAffects(shellModNode::aSmoothNormals, shellModNode::aOutMesh);
	attributeAffects(shellModNode::aReverseNormals, shellModNode::aOutMesh);
	attributeAffects(shellModNode::aStraightenEdges, shellModNode::aOutMesh);
	attributeAffects(shellModNode::aStraightenEdgesAngle, shellModNode::aOutMesh);
	attributeAffects(shellModNode::aAutoSegments, shellModNode::aOutMesh);
	attributeAffects(shellModNode::aProfilePresets, shellModNode::aOutMesh);
	attributeAffects(shellModNode::aSmoothSubdiv, shellModNode::aOutMesh);

	attributeAffects(shellModNode::aBulge, shellModNode::aOutMesh);
	attributeAffects(shellModNode::aCurveRamp, shellModNode::aOutMesh);



	attributeAffects(shellModNode::aUVOffsetU, shellModNode::aOutMesh);
	attributeAffects(shellModNode::aUVOffsetV, shellModNode::aOutMesh);

	attributeAffects(shellModNode::aUVTranslateU, shellModNode::aOutMesh);
	attributeAffects(shellModNode::aUVTranslateV, shellModNode::aOutMesh);
	attributeAffects(shellModNode::aUVRotate, shellModNode::aOutMesh);
	attributeAffects(shellModNode::aUVScaleU, shellModNode::aOutMesh);
	attributeAffects(shellModNode::aUVScaleV, shellModNode::aOutMesh);

	attributeAffects(shellModNode::aGenerateUVs, shellModNode::aOutMesh);

	attributeAffects(shellModNode::aUVOffsetUAuto, shellModNode::aOutMesh);
	attributeAffects(shellModNode::aUVOffsetUAutoPadding, shellModNode::aOutMesh);

	//attributeAffects(shellModNode::aDisplaySmoothMesh, shellModNode::aOutMesh);

	attributeAffects(shellModNode::aDisableBaseMeshOverride, shellModNode::aOutMesh);
	attributeAffects(shellModNode::aDisableOutputMeshOverride, shellModNode::aOutMesh);

	attributeAffects(shellModNode::aBevelEdgesAngle, shellModNode::aOutMesh);

	attributeAffects(shellModNode::aPresetFolderPath, shellModNode::aOutMesh);

	return MStatus::kSuccess;
}

