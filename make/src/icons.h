#ifndef ICONS_H
#define ICONS_H

#include "icons_repo.h"

void writeIcon_binary(MString path, MString filename, const unsigned char output[], int char_size)
{

	ofstream myfile;

	myfile.open(MString(path + filename).asChar(), ios::out | ios::binary);
	myfile.write((char *)output, char_size);
	myfile.close();
	MGlobal::displayInfo(MString() + "[ShellMod] Created icon: " + path + filename);


}



void icons_data_write()
{


	MString path;
	MGlobal::executeCommand("internalVar -userBitmapsDir", path);
	MGlobal::displayInfo(MString() + "[ShellMod] Icons path: " + path);

	std::string c_path = path.asChar();

	writeIcon_binary(path, "shellModNode_Refresh.png", __shellModNode_Refresh_png, 17788);
	writeIcon_binary(path, "shellModNode_Trash.png", __shellModNode_Trash_png, 17794);
	writeIcon_binary(path, "shellModNode_Preset.png", __shellModNode_Preset_png, 17751);
	writeIcon_binary(path, "shellModNode_Plus.png", __shellModNode_Plus_png, 17772);
	writeIcon_binary(path, "shellModNode_Minus.png", __shellModNode_Minus_png, 17741);
	writeIcon_binary(path, "shellModNode_Plane.png", __shellModNode_Plane_png, 4429);
	writeIcon_binary(path, "shellModNode_CCLogo.png", __shellModNode_CCLogo_png, 19052);
	writeIcon_binary(path, "shellModNode_Apply.png", __shellModNode_Apply_png, 17762);
	writeIcon_binary(path, "shellModNode_Add.png", __shellModNode_Add_png, 19433);
	writeIcon_binary(path, "out_shellMod.png", __out_shellMod_png, 18945);
	writeIcon_binary(path, "shellModNode.png", __shellModNode_png, 18734);



}

#endif