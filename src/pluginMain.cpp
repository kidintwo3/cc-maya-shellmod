//
//  pluginMain.cpp
//  shellMod
//
//  Created by Creative Case on 2015. 01. 03.
//  Copyright (c) 2015. Creative Case. All rights reserved.
//

#include "ShellModNode.h"
#include "ShellModCommand.h"
#include "AETemplate.h"
#include "icons.h"


#include <maya/MFnPlugin.h>

MStatus initializePlugin( MObject obj )
{
	MStatus status;
    
    icons_data_write();

	//MGlobal::executeCommand( mel_deleteShelf() );


	MGlobal::executeCommand( mel_createShelf() );
	MGlobal::executeCommand( mel_AETemplate() );

	MFnPlugin fnPlugin( obj, "Creative Case", "2.04", "Any" );

	status = fnPlugin.registerCommand( "shellModCommand", ShellModCommand::creator, ShellModCommand::newSyntax );
	CHECK_MSTATUS_AND_RETURN_IT( status );


	status = fnPlugin.registerNode("shellModNode", shellModNode::id, shellModNode::creator, shellModNode::initialize);
	CHECK_MSTATUS_AND_RETURN_IT(status);

    shellModNode::pluginLoadPath = fnPlugin.loadPath(&status);
	CHECK_MSTATUS_AND_RETURN_IT(status);

    //fnPlugin.addMenuItem("Create ShellMod", "MayaWindow|mainMeshToolsMenu", "shellModCommand", "");
    //fnPlugin.addMenuItem("Add to ShellMod", "MayaWindow|mainMeshToolsMenu", "shellModCommand -a", "");
    //fnPlugin.addMenuItem("Plane with ShellMod", "MayaWindow|mainMeshToolsMenu", "shellModCommand -a", "");
    
	return MS::kSuccess;
}


MStatus uninitializePlugin( MObject obj )
{
	MStatus status;




	//MGlobal::executeCommand( mel_deleteShelf() );




	MFnPlugin fnPlugin( obj );

	status = fnPlugin.deregisterCommand( "shellModCommand" );
	CHECK_MSTATUS_AND_RETURN_IT( status );

	status = fnPlugin.deregisterNode(shellModNode::id);
	CHECK_MSTATUS_AND_RETURN_IT(status);

    
    //MStringArray myMenu;
    //myMenu.append( "Create ShellMod" );
    //myMenu.append( "Add to ShellMod" );
    //myMenu.append( "Plane with ShellMod" );
    //fnPlugin.removeMenuItem(myMenu);
    
	return MS::kSuccess;
}

