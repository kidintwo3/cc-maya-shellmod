//
//  ShellModCommand.cpp
//  shellMod
//
//  Created by Hunyadi János on 2015. 01. 03..
//  Copyright (c) 2015. Janos Hunyadi. All rights reserved.
//

#include "ShellModCommand.h"
#include "ShellModNode.h"
#include "DagUtils.h"
#include "Utils.h"

ShellModCommand::ShellModCommand()
{
}


void* ShellModCommand::creator()
{
	return new ShellModCommand;
}


bool ShellModCommand::isUndoable() const
{
	return true;
}

MSyntax ShellModCommand::newSyntax()
{
	MSyntax syntax;

	syntax.addFlag( "-a", "-addObjects" );
	syntax.addFlag( "-r", "-remove", MSyntax::kString );

	syntax.addFlag( "-sp", "-savePreset", MSyntax::kString  );
	syntax.addFlag( "-lp", "-loadPreset", MSyntax::kString  );

	syntax.addFlag( "-sm", "-shellModNode", MSyntax::kString  );
	syntax.addFlag( "-pp", "-presetPath", MSyntax::kString  );

	syntax.setObjectType( MSyntax::kSelectionList, 1, 1 );
	syntax.useSelectionAsDefault( true );

	syntax.enableEdit( false );
	syntax.enableQuery( false );

	return syntax;
}

MStatus ShellModCommand::assignSameMaterial(MDagPath& inputShapeDagPath, MObject& outputShapeDagPath)
{

	MStatus status;

	MString sMaterial;

	if (inputShapeDagPath.hasFn(MFn::kMesh))
	{
		// Find the Shading Engines Connected to the SourceNode
		MFnMesh fnMesh(inputShapeDagPath.node());

		// A ShadingGroup will have a MFnSet
		MObjectArray sets, comps;
		fnMesh.getConnectedSetsAndMembers(inputShapeDagPath.instanceNumber(), sets, comps, true);

		// Each set is a Shading Group. Loop through them
		for (unsigned int i = 0; i < sets.length(); ++i)
		{
			MFnDependencyNode fnDepSGNode(sets[i]);

			sMaterial = fnDepSGNode.name();
		}
	}


	MGlobal::displayInfo(MString() + "[Shellmod] Initial SG: " + sMaterial);

	MSelectionList sList;
	MGlobal::getSelectionListByName(sMaterial, sList);
	MObject oInitialShadingGroup;
	status = sList.getDependNode(0, oInitialShadingGroup);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	MFnSet fnShadingGroup(oInitialShadingGroup, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	status = fnShadingGroup.addMember(outputShapeDagPath);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	return MS::kSuccess;
}

MStatus ShellModCommand::assignInitialShadingGroup(MObject& oMesh)
{
	MStatus status;

	MSelectionList sList;
	MGlobal::getSelectionListByName("initialShadingGroup", sList);
	MObject oInitialShadingGroup;
	status = sList.getDependNode(0, oInitialShadingGroup);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	MFnSet fnShadingGroup(oInitialShadingGroup, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	status = fnShadingGroup.addMember(oMesh);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	return MS::kSuccess;
}

MStatus ShellModCommand::doIt( const MArgList& argList )
{
	MStatus status;

	MArgDatabase argData( syntax(), argList, &status );



	// -----------------------------------------------------------------------------------------
	// SAVE PRESET TO SHELLMOD
	// shellModCommand -sp "test" -sm "shellModNode1";
	if ( argData.isFlagSet( "-sp" ) )
	{

		MString s_presetName;
		MString s_shellmodNodeName;
		MString s_pPath;

		argData.getFlagArgument("-sp", 0, s_presetName);


		if (!argData.isFlagSet( "-sm" ))
		{
			MGlobal::displayError(MString() + "[Shellmod] No ShellMod name set for command (use the -sm flag to set)");
			return MStatus::kFailure;
		}

		argData.getFlagArgument("-sm", 0, s_shellmodNodeName);

		if (!argData.isFlagSet( "-pp" ))
		{
			MGlobal::displayError(MString() + "[Shellmod] Preset path name set for command (use the -pp flag to set)");
			return MStatus::kFailure;
		}

		argData.getFlagArgument("-pp", 0, s_pPath);


		// Find Shellmod from name
		MObject MObj;
		MSelectionList selList;
		selList.add(s_shellmodNodeName);
		selList.getDependNode(0,MObj);

		MFnDependencyNode mfDgN(MObj);

		MPlug a_curveAttribute = mfDgN.findPlug("profileRamp", status);

		MRampAttribute a_Ramp(a_curveAttribute);



		save_rampData(a_Ramp, s_pPath, s_presetName);

		return MStatus::kSuccess;
	}

	// -----------------------------------------------------------------------------------------
	// LOAD PRESET TO SHELLMOD
	// shellModCommand -lp "testName";
	else if ( argData.isFlagSet( "-lp" ) )
	{
		MString s_presetName;
		MString s_shellmodNodeName;
		MString s_pPath;

		argData.getFlagArgument("-lp", 0, s_presetName);

		if (!argData.isFlagSet( "-sm" ))
		{
			MGlobal::displayError(MString() + "[Shellmod] No ShellMod name set for command (use the -sm flag to set)");
			return MStatus::kFailure;
		}

		argData.getFlagArgument("-sm", 0, s_shellmodNodeName);

		if (!argData.isFlagSet( "-pp" ))
		{
			MGlobal::displayError(MString() + "[Shellmod] Preset path name set for command (use the -pp flag to set)");
			return MStatus::kFailure;
		}

		argData.getFlagArgument("-pp", 0, s_pPath);

		// Find Shellmod from name
		MObject MObj;
		MSelectionList selList;
		selList.add(s_shellmodNodeName);
		selList.getDependNode(0,MObj);

		MFnDependencyNode mfDgN(MObj);

		MPlug a_curveAttribute = mfDgN.findPlug("profileRamp", status);

		MRampAttribute a_Ramp(a_curveAttribute);


		// Clear the ramp than load the ramp
		//clear_rampData(a_Ramp, s_shellmodNodeName);

		// MGlobal::displayInfo(MString() + "[Shellmod]: " + s_pPath + ", " + s_presetName + ", " + s_shellmodNodeName);


		load_rampData(a_Ramp, s_pPath, s_presetName, s_shellmodNodeName);


		// Refresh plugs + AE Template
		MGlobal::executeCommand("dgdirty " + s_shellmodNodeName);
		MGlobal::executeCommand("refreshAE");


		return MStatus::kSuccess;
	}




	// ------------------------------------------------------------------------------------------------------
	// Get Selected Object
	MDagPathArray p_currSelTrA = getCurrSelectionDAGArray();


	if (p_currSelTrA.length() == 0)
	{
		MGlobal::displayWarning(MString() + "[Shellmod] No meshes selected");
		return MStatus::kFailure;
	}


	p_currSelShapeA.clear();
	for (int i = 0; i < p_currSelTrA.length(); i++)
	{
		p_currSelShape = p_currSelTrA[i];

		status = getShapeNodeFromTransformDAG(p_currSelShape);
		CHECK_MSTATUS_AND_RETURN_IT(status);

		p_currSelShapeA.append(p_currSelShape);

	}


	// -----------------------------------------------------------------------------------------
	// ADD SELECTED OBJECTS TO SHELLMOD
	// shellModCommand -a;
	if ( argData.isFlagSet( "-a" ) )
	{

		// Check if at least 2 objects are selected
		if (p_currSelShapeA.length() < 2)
		{
			MGlobal::displayError(MString() + "[Shellmod] Select source mesh with ShellMod, than target mesh to add");
			return MStatus::kFailure;
		}




		MFnDagNode dgNode(p_currSelShapeA[0]);

		MPlug aliasList = dgNode.findPlug( "worldMesh", status );
		CHECK_MSTATUS_AND_RETURN_IT(status);

		if (!aliasList[0].isConnected())
		{
			MGlobal::displayError(MString() + "[Shellmod] Shellmod node not found on first object (Select mesh with a ShellMod modifier first)");
			return MStatus::kFailure;
		}

		MPlug worldP = aliasList[0];
		MGlobal::displayInfo(MString() + "[Shellmod] Input mesh connected through plug: " + worldP.name());



		MFnDagNode mfDgN(worldP.node());


		MPlugArray destPlugs;
		worldP.connectedTo(destPlugs, false, true);

		if (!destPlugs[0].isConnected())
		{
			MGlobal::displayError(MString() + "[Shellmod] Shellmod node / connected nodes not found (Select mesh with a ShellMod modifier)");
			return MStatus::kFailure;
		}

		MPlug destPlug = destPlugs[0];

		MFnDependencyNode depN(destPlug.node());

		MGlobal::displayInfo(MString() + "[Shellmod] Connected ShellMod Node " + depN.name() );


		MPlug p_inMesh = depN.findPlug("inMesh", status);

		MGlobal::displayInfo(MString() + "[Shellmod] Number of meshes connected to " + depN.name() + ": " + p_inMesh.numConnectedElements() + " nodes" );

		// ----------------------


		MPlug p_outMesh = depN.findPlug("outMesh", status);
		MPlugArray destPlug_outMesh;
		p_outMesh.connectedTo(destPlug_outMesh, false, true);

		if (!destPlug_outMesh[0].isConnected())
		{
			MGlobal::displayError(MString() + "[Shellmod] No output mesh connected to " + depN.name() );
			return MStatus::kFailure;
		}
		MFnDependencyNode depNoutMesh(destPlug_outMesh[0].node());

		//MGlobal::displayInfo(MString() + "[Shellmod] " + depNoutMesh.name() );

		// ----------------------

		//MFnDependencyNode fnDepShellMod(o_shellModNode);

		for (int i = 1; i < p_currSelShapeA.length(); i++)
		{

			MFnDagNode fnDepSource( p_currSelShapeA[i].node() );
			MGlobal::displayInfo(MString() + "[Shellmod] Adding: " + fnDepSource.partialPathName() );

			if (fnDepSource.partialPathName() == depNoutMesh.name()) {
				MGlobal::displayWarning(MString() + "[Shellmod] Can't add shellMod output mesh (" + depN.name() + ") to itself! " );
				return MStatus::kFailure;
			}


		}

		MGlobal::displayInfo(MString() + "-------------" );

		for (int i = 1; i < p_currSelShapeA.length(); i++)
		{
			MFnDagNode fnDepSource( p_currSelShapeA[i].node() );
			MPlug plugSource = fnDepSource.findPlug( "worldMesh" );
			plugSource = plugSource.elementByLogicalIndex(0);

			MPlug plugTarget = depN.findPlug( "inMesh" );
			plugTarget = plugTarget.elementByLogicalIndex(plugTarget.numConnectedElements());

			MGlobal::displayInfo(MString() + "[Shellmod] connected: " + plugSource.name() + " -> " + plugTarget.name()  );

			status = m_DGMod.connect( plugSource, plugTarget );
			CHECK_MSTATUS_AND_RETURN_IT(status);
			m_DGMod.doIt();

			MObject o_temp = p_currSelShapeA[i].node() ;
			assignSameMaterial( p_currSelShapeA[0], o_temp );


			//// Set input mesh overrides
			//fnDepSource.findPlug("overrideEnabled", false, &status).setBool(true);
			//CHECK_MSTATUS_AND_RETURN_IT(status);

			//fnDepSource.findPlug("overrideShading", false, &status).setBool(false);
			//CHECK_MSTATUS_AND_RETURN_IT(status);



			//// Set smoothing boundry off
			//MPlug p_source_osdVertBoundary = fnDepSource.findPlug( "osdVertBoundary" );
			//p_source_osdVertBoundary.setInt(2);

			//// Find plugs for smoothing
			//MPlug p_source_dispSmooth = fnDepSource.findPlug( "displaySmoothMesh" );
			//MPlug p_subdiv = depN.findPlug( "smoothMeshSubdiv" );
			//MPlug p_dispSmooth = depN.findPlug( "displaySmoothMesh" );

			////MPlug p_inSmoothLevel = fnDepSource.findPlug( "smoothLevel", status );
			////CHECK_MSTATUS_AND_RETURN_IT(status);

			////// Connect smoothing plugs from input mesh
			////status = m_DGMod.connect( p_subdiv, p_inSmoothLevel );
			////CHECK_MSTATUS_AND_RETURN_IT(status);
			////m_DGMod.doIt();

			////if (!p_dispSmooth.isConnected())
			////{
			////	status = m_DGMod.connect( p_source_dispSmooth, p_dispSmooth );
			////	CHECK_MSTATUS_AND_RETURN_IT(status);
			////	m_DGMod.doIt();
			////}

		// Set input mesh overrides
			fnDepSource.findPlug("overrideEnabled", false, &status).setBool(true);
			CHECK_MSTATUS_AND_RETURN_IT(status);

			fnDepSource.findPlug("overrideShading", false, &status).setBool(false);
			CHECK_MSTATUS_AND_RETURN_IT(status);

            
#if MAYA_API_VERSION > 201500
            
            // Set  boundary smoothing off - OpenSubdiv
            MPlug p_source_osdVertBoundary = fnDepSource.findPlug( "osdVertBoundary" );
            p_source_osdVertBoundary.setInt(2);
            
#endif
            
            // Set boundary smoothing off - LEGACY Catmull Clark
            MPlug p_source_boundaryRule = fnDepSource.findPlug( "boundaryRule" );
            p_source_boundaryRule.setInt(0);



			// Find plugs for overrides
			MPlug p_shellmod_overrideShading = depN.findPlug( "baseMeshDisplayOverride" );
			MPlug p_source_override_enabled = fnDepSource.findPlug( "overrideEnabled" );
			MPlug p_subdiv = depN.findPlug( "smoothMeshSubdiv" );
			MPlug p_dispSmooth = fnDepSource.findPlug( "smoothLevel" );


			if (!p_source_override_enabled.isConnected())
			{

				status = m_DGMod.connect( p_shellmod_overrideShading, p_source_override_enabled );
				CHECK_MSTATUS_AND_RETURN_IT(status);
				m_DGMod.doIt();

			}


			if (!p_dispSmooth.isConnected())
			{

				status = m_DGMod.connect( p_subdiv, p_dispSmooth );
				CHECK_MSTATUS_AND_RETURN_IT(status);
				m_DGMod.doIt();

			}



		}




	}



	// -----------------------------------------------------------------------------------------
	// REMOVE SHELLMOD FROM SELECTED OBJECT
	// shellModCommand -r;
	else if ( argData.isFlagSet( "-r" ) )
	{

		MFnDagNode dgNode(p_currSelShapeA[0]);

		MPlug aliasList = dgNode.findPlug( "worldMesh", status );
		CHECK_MSTATUS_AND_RETURN_IT(status);

		if (!aliasList[0].isConnected())
		{
			MGlobal::displayError(MString() + "[Shellmod] Shellmod node / connected nodes not found (Select mesh with a ShellMod modifier)");
			return MStatus::kFailure;
		}

		MPlug worldP = aliasList[0];
		MGlobal::displayInfo(MString() + "[Shellmod] Input mesh connected through plug " + worldP.name());



		MFnDagNode mfDgN(worldP.node());


		MPlugArray destPlugs;
		worldP.connectedTo(destPlugs, false, true);

		if (!destPlugs[0].isConnected())
		{
			MGlobal::displayError(MString() + "[Shellmod] Shellmod node / connected nodes not found (Select mesh with a ShellMod modifier)");
			return MStatus::kFailure;
		}

		MPlug destPlug = destPlugs[0];

		MFnDependencyNode depN(destPlug.node());

		MGlobal::displayInfo(MString() + "[Shellmod] Connected ShellMod Node " + depN.name() );

		MPlug nodeMeshoutPlug = depN.findPlug("outMesh", status);
		CHECK_MSTATUS_AND_RETURN_IT(status);
		nodeMeshoutPlug.connectedTo(destPlugs, false, true);

		if (!destPlugs[0].isConnected())
		{
			MGlobal::displayError(MString() + "[Shellmod] Shellmod node / connected nodes not found (Select mesh with a ShellMod modifier)");
			return MStatus::kFailure;
		}




		// Reset shading overrides
		MPlug p_inMesh = depN.findPlug("inMesh", status);
		CHECK_MSTATUS_AND_RETURN_IT(status);

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

				MPlug p_in_overrideEnabled = inMesh_dn.findPlug("overrideEnabled", false, &status);
				CHECK_MSTATUS_AND_RETURN_IT(status);
				p_in_overrideEnabled.setBool(false);
			}
		}

		//
		MPlug destPlug2 = destPlugs[0];

		MFnDagNode mfDgN2(destPlug2.node());

		MGlobal::displayInfo(MString() + "[Shellmod] Connected Mesh Node " + mfDgN2.name() );

		status = m_DAGMod.deleteNode(mfDgN2.parent(0));
		CHECK_MSTATUS_AND_RETURN_IT(status);
		m_DAGMod.doIt();
	}





	// -----------------------------------------------------------------------------------------
	// CREATE AND CONNECT SEHLLMOD TO SELECTED OBJECTS
	else
	{
		//MPlugArray inSmoothLevelPA;

		for (int i = 0; i < p_currSelShapeA.length(); i++)
		{

			// Check if selection is allready connected to a shellmod
			MFnDagNode dgNode(p_currSelShapeA[i]);

			MPlug worldPlug = dgNode.findPlug( "worldMesh", status );
			CHECK_MSTATUS_AND_RETURN_IT(status);

			//inSmoothLevelPA.append( dgNode.findPlug( "smoothLevel", status ) );
			//CHECK_MSTATUS_AND_RETURN_IT(status);

			if (worldPlug[0].isConnected())
			{
				MGlobal::displayError(MString() + "[Shellmod] Node allready connected to outMesh plug");
				return MStatus::kFailure;
			}
		}

		// Create shellmod node
		MObject o_shellModNode = createNodeMaya(m_DEPNode,"shellModNode");




		// -----------------------------------------------------------------------------------------
		// Connect output world meshes to shellmod input array
		MFnDependencyNode fnDepShellMod(o_shellModNode);


		for (int i = 0; i < p_currSelShapeA.length(); i++)
		{
			MFnDagNode fnDepSource( p_currSelShapeA[i].node() );
			MPlug plugSource = fnDepSource.findPlug( "worldMesh" );
			plugSource = plugSource.elementByLogicalIndex(0);

			MPlug plugTarget = fnDepShellMod.findPlug( "inMesh" );
			plugTarget = plugTarget.elementByLogicalIndex(plugTarget.numConnectedElements());

			MGlobal::displayInfo(MString() + "[Shellmod] connected: " + plugSource.name() + " -> " + plugTarget.name()  );

			status = m_DGMod.connect( plugSource, plugTarget );
			CHECK_MSTATUS_AND_RETURN_IT(status);
			m_DGMod.doIt();


			// Set input mesh overrides
			fnDepSource.findPlug("overrideEnabled", false, &status).setBool(true);
			CHECK_MSTATUS_AND_RETURN_IT(status);

			fnDepSource.findPlug("overrideShading", false, &status).setBool(false);
			CHECK_MSTATUS_AND_RETURN_IT(status);


#if MAYA_API_VERSION > 201500
            
            // Set  boundary smoothing off - OpenSubdiv
            MPlug p_source_osdVertBoundary = fnDepSource.findPlug( "osdVertBoundary" );
            p_source_osdVertBoundary.setInt(2);
            
#endif
            
            // Set boundary smoothing off - LEGACY Catmull Clark
            MPlug p_source_boundaryRule = fnDepSource.findPlug( "boundaryRule" );
            p_source_boundaryRule.setInt(0);




			// Find plugs for overrides
			MPlug p_shellmod_overrideShading = fnDepShellMod.findPlug( "baseMeshDisplayOverride" );
			MPlug p_source_override_enabled = fnDepSource.findPlug( "overrideEnabled" );
			MPlug p_subdiv = fnDepShellMod.findPlug( "smoothMeshSubdiv" );
			MPlug p_dispSmooth = fnDepSource.findPlug( "smoothLevel" );


			if (!p_source_override_enabled.isConnected())
			{

				status = m_DGMod.connect( p_shellmod_overrideShading, p_source_override_enabled );
				CHECK_MSTATUS_AND_RETURN_IT(status);
				m_DGMod.doIt();

			}


			if (!p_dispSmooth.isConnected())
			{

				status = m_DGMod.connect( p_subdiv, p_dispSmooth );
				CHECK_MSTATUS_AND_RETURN_IT(status);
				m_DGMod.doIt();

			}



		}


		// -----------------------------------------------------------------------------------------
		// create output mesh and connect it to shellmod

		o_newMesh = createNodeMaya(m_DEPNode,"mesh");
		MFnDependencyNode fnDepshellModOutputMesh( o_newMesh );
		fnDepshellModOutputMesh.setName( "shellModNode_mesh#" );

		// Find shape node of output mesh
		MDagPath dag_outMeshTr;
		MDagPath dag_outMeshShape;
		MDagPath dag_outMesh;
		MSelectionList sel_list;
		sel_list.clear();
		sel_list.add(fnDepshellModOutputMesh.name());
		sel_list.getDagPath(0,dag_outMesh);
		dag_outMeshTr = dag_outMesh;
		dag_outMesh.extendToShape();
		dag_outMeshShape = dag_outMesh;

		MFnDependencyNode fnDepshellModOutputMeshShape( dag_outMeshShape.node() );

		MPlug p_shellModMultiNode_outMesh = fnDepShellMod.findPlug( "outMesh" );
		MPlug p_shellModMultiMesh_inMesh = fnDepshellModOutputMeshShape.findPlug( "inMesh" );

		MGlobal::displayInfo(MString() + "[Shellmod] connected: " + p_shellModMultiNode_outMesh.name() + " -> " + p_shellModMultiMesh_inMesh.name()  );

		status = m_DGMod.connect( p_shellModMultiNode_outMesh, p_shellModMultiMesh_inMesh );
		CHECK_MSTATUS_AND_RETURN_IT(status);
		m_DGMod.doIt();


		//		// Connect smooth level plug to inMesh
		//		status = m_DGMod.connect( p_shellModMultiNode_outMesh, p_shellModMultiMesh_inMesh );
		//		CHECK_MSTATUS_AND_RETURN_IT(status);
		//		m_DGMod.doIt();


		// -----------------------------------------------------------------------------------------
		// Assign same material as input 0 object
		assignSameMaterial(p_currSelShapeA[0], o_newMesh);

	}



	return redoIt();
}

MStatus ShellModCommand::redoIt()
{
	MStatus status;

	return MS::kSuccess;
}

MStatus ShellModCommand::undoIt()
{
	MStatus status;

	// Restore the initial state
	status = m_DGMod.undoIt();
	CHECK_MSTATUS_AND_RETURN_IT( status );

	status = m_DAGMod.undoIt();
	CHECK_MSTATUS_AND_RETURN_IT(status);


	// Set back overrides on all meshes
	for (int i = 0; i < p_currSelShapeA.length(); i++)
	{
		setPlugs(p_currSelShapeA[i].node(), "overrideEnabled", "false");
	}

	deleteNode(o_newMesh);

	return MS::kSuccess;
}