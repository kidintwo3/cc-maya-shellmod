//
//  AETemplates.h
//  clonerMulti
//
//  Created by Janos Hunyadi on 2018.07.05
//  Copyright (c) 2018. Janos Hunyadi. All rights reserved.
//


#ifndef MELSCRIPTS_H
#define MELSCRIPTS_H


#include <maya/MString.h>


MStringArray mel_AETemplate()
{


	// ---------------
	MStringArray s_aeTemplate_A;

	// ---------------
	MString s_aeTemplate_000 = "//deleteUI AttrEdshellModNodeFormLayout;\r\n"
		"global proc AEshellModNodeTemplate( string $nodeName )\r\n"
		"{\r\n"
		"\	editorTemplate -beginScrollLayout;\r\n"
		"\	\r\n"
		"\	editorTemplate -beginLayout \"ShellMod 1shape settings\" -collapse 0;\r\n"
		"\	editorTemplate -addControl \"offsetZ\";\r\n"
		"\	editorTemplate -addControl \"chaserEdgeWeight\";\r\n"
		"\	editorTemplate -addControl \"segments\";\r\n"
		"\	editorTemplate -addControl \"straightenEdgesAngle\";\r\n"
		"\	editorTemplate -addControl \"smoothMeshSubdiv\";\r\n"
		"\	editorTemplate -addSeparator;\r\n"
		"\	editorTemplate -addControl \"chamferEdges\";\r\n"
		"\	editorTemplate -addControl \"chamferEdgeFactor\";\r\n"
		"\	editorTemplate -addSeparator;\r\n"
		"\	editorTemplate -addControl \"capTop\";\r\n"
		"\	editorTemplate -addControl \"capBottom\";\r\n"
		"\	editorTemplate -addControl \"smoothNormals\";\r\n"
		"\	editorTemplate -addControl \"reverseNormals\";\r\n"
		"\	editorTemplate -addControl \"straightenEdges\";\r\n"
		"\	editorTemplate -addControl \"autoSegments\";\r\n"
		"\	\r\n"
		"\	editorTemplate -addSeparator;\r\n"
		"\	editorTemplate -addControl \"baseMeshDisplayOverride\";\r\n"
		"\	editorTemplate -addSeparator;\r\n"
		"\	editorTemplate -addControl \"outputMeshDisplayOverride\";\r\n"
		"\r\n"
		"\	AEaddRampControl( $nodeName + \".profileRamp\" );\r\n"
		"\	editorTemplate -addControl \"profileStrength\";\r\n"
		"\	\r\n"
		"\	editorTemplate -addSeparator;\r\n"
		"\	editorTemplate -label \"Built in Presets\" -addControl \"profilePresets\";\r\n"
		"\	\r\n"
		"\	editorTemplate -callCustom \"AE_preset_ShellMod_create\" \"AE_preset_ShellMod_edit\" \"profilePresets\";\r\n"
		"\	editorTemplate -callCustom \"AE_presetList_ShellMod_create\" \"AE_presetList_ShellMod_edit\" \"\";\r\n"
		"\	\r\n"
		"\	editorTemplate -endLayout;\r\n"
		"\r\n"
		"\	editorTemplate -beginLayout \"UV options\" -collapse 0;\r\n"
		"\	editorTemplate -addControl \"generateUVs\";\r\n"
		"\	editorTemplate -addSeparator;\r\n"
		"\	editorTemplate -addControl \"uvTranslateU\";\r\n"
		"\	editorTemplate -addControl \"uvTranslateV\";\r\n"
		"\	editorTemplate -addSeparator;\r\n"
		"\	editorTemplate -addControl \"uvRotate\";\r\n"
		"\	editorTemplate -addSeparator;\r\n"
		"\	editorTemplate -addControl \"uvScaleU\";\r\n"
		"\	editorTemplate -addControl \"uvScaleV\";\r\n"
		"\	editorTemplate -addSeparator;\r\n"
		"\	editorTemplate -addControl \"uvOffsetU\";\r\n"
		"\	editorTemplate -addControl \"uvOffsetV\";\r\n"
		"\	editorTemplate  -label \"Auto U Offset\" -addControl \"uvOffsetUAutoOffset\";\r\n"
		"\	editorTemplate  -label \"Auto U Offset Padding\" -addControl \"uvOffsetUAutoOffsetPadding\";\r\n"
		"\	\r\n"
		"\	editorTemplate -endLayout;\r\n"
		"\	\r\n"
		"\	editorTemplate -beginLayout \"Global settings\" -collapse 0;\r\n"
		"\	editorTemplate -callCustom \"AE_del_ShellMod_create\" \"AE_del_ShellMod_edit\" \"\";\r\n"
		"\	\r\n"
		"\	editorTemplate -endLayout;\r\n"
		"\	\r\n"
		"\	editorTemplate -beginLayout \"Plug-in Info\" -collapse 1;\r\n"
		"\	editorTemplate -callCustom \"AE_website_create\" \"AE_website_edit\" \"\";\r\n"
		"\	editorTemplate -endLayout;\r\n"
		"\	\r\n"
		"\	editorTemplate -suppress \"inMesh\";\r\n"
		"\	\r\n"
		"\	AEdependNodeTemplate $nodeName;\r\n"
		"\	editorTemplate -addExtraControls;\r\n"
		"\	editorTemplate -endScrollLayout;\r\n"
		"\	\r\n"
		"\	\r\n"
		"}\r\n"
		"global proc AE_preset_ShellMod_set(int $id, string $attr)\r\n"
		"{\r\n"
		"}\r\n"
		"\r\n"
		"global proc AE_set_ProfileType(int $i_type, string $s_nodeName)\r\n"
		"{\r\n"
		"    setAttr ($s_nodeName + \".profilePresets \" ) $i_type;\r\n"
		"}\r\n"
		"\r\n"
		"global proc AE_preset_ShellMod_create(string $attrName)\r\n"
		"{\r\n"
		"    string $nodeName[];\r\n"
		"    tokenize($attrName, \".\", $nodeName);\r\n"
		"    \r\n"
		"\	setUITemplate -pst attributeEditorPresetsTemplate;\r\n"
		"    \r\n"
		"    \r\n"
		"    separator -height 10 -style \"in\";\r\n"
		"    \r\n"
		"    gridLayout -numberOfColumns 21 -cellWidthHeight 18 18 -bgc 0.2 0.2 0.2;\r\n"
		"    iconTextButton -iol \"cu\" -image \"shellModNode_Preset.xmp\" -c (\"AE_set_ProfileType(0,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon0\";\r\n"
		"    iconTextButton -iol \"2\" -image \"shellModNode_Preset.xmp\" -c (\"AE_set_ProfileType(1,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon1\";\r\n"
		"    iconTextButton -iol \"3\" -image \"shellModNode_Preset.xmp\" -c (\"AE_set_ProfileType(2,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon2\";\r\n"
		"    iconTextButton -iol \"4\" -image \"shellModNode_Preset.xmp\" -c (\"AE_set_ProfileType(3,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon3\";\r\n"
		"    iconTextButton -iol \"5\" -image \"shellModNode_Preset.xmp\" -c (\"AE_set_ProfileType(4,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon4\";\r\n"
		"    iconTextButton -iol \"6\" -image \"shellModNode_Preset.xmp\" -c (\"AE_set_ProfileType(5,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon5\";\r\n"
		"    iconTextButton -iol \"7\" -image \"shellModNode_Preset.xmp\" -c (\"AE_set_ProfileType(6,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon6\";\r\n"
		"    iconTextButton -iol \"8\" -image \"shellModNode_Preset.xmp\" -c (\"AE_set_ProfileType(7,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon7\";\r\n"
		"    iconTextButton -iol \"9\" -image \"shellModNode_Preset.xmp\" -c (\"AE_set_ProfileType(8,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon8\";\r\n"
		"    iconTextButton -iol \"10\" -image \"shellModNode_Preset.xmp\" -c (\"AE_set_ProfileType(9,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon9\";\r\n"
		"    iconTextButton -iol \"11\" -image \"shellModNode_Preset.xmp\" -c (\"AE_set_ProfileType(10,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon10\";\r\n"
		"    iconTextButton -iol \"12\" -image \"shellModNode_Preset.xmp\" -c (\"AE_set_ProfileType(11,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon11\";\r\n"
		"    iconTextButton -iol \"13\" -image \"shellModNode_Preset.xmp\" -c (\"AE_set_ProfileType(12,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon12\";\r\n"
		"    iconTextButton -iol \"14\" -image \"shellModNode_Preset.xmp\" -c (\"AE_set_ProfileType(13,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon13\";\r\n"
		"    iconTextButton -iol \"15\" -image \"shellModNode_Preset.xmp\" -c (\"AE_set_ProfileType(14,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon14\";\r\n"
		"    iconTextButton -iol \"16\" -image \"shellModNode_Preset.xmp\" -c (\"AE_set_ProfileType(15,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon15\";\r\n"
		"    iconTextButton -iol \"17\" -image \"shellModNode_Preset.xmp\" -c (\"AE_set_ProfileType(16,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon16\";\r\n"
		"    iconTextButton -iol \"18\" -image \"shellModNode_Preset.xmp\" -c (\"AE_set_ProfileType(17,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon17\";\r\n"
		"    iconTextButton -iol \"19\" -image \"shellModNode_Preset.xmp\" -c (\"AE_set_ProfileType(18,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon18\";\r\n"
		"    iconTextButton -iol \"20\" -image \"shellModNode_Preset.xmp\" -c (\"AE_set_ProfileType(19,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon19\";\r\n"
		"\	setParent ..;\r\n"
		"\	\r\n"
		"\	setUITemplate -ppt;\r\n"
		"}\r\n"
		"\r\n"
		"global proc AE_preset_ShellMod_edit(string $attrName)\r\n"
		"{\r\n"
		"    string $nodeName[];\r\n"
		"    tokenize($attrName, \".\", $nodeName);\r\n"
		"    \r\n"
		"    iconTextButton -edit -c (\"AE_set_ProfileType(0,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon0\";\r\n"
		"    iconTextButton -edit -c (\"AE_set_ProfileType(1,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon1\";\r\n"
		"    iconTextButton -edit -c (\"AE_set_ProfileType(2,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon2\";\r\n"
		"    iconTextButton -edit -c (\"AE_set_ProfileType(3,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon3\";\r\n"
		"    iconTextButton -edit -c (\"AE_set_ProfileType(4,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon4\";\r\n"
		"    iconTextButton -edit -c (\"AE_set_ProfileType(5,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon5\";\r\n"
		"    iconTextButton -edit -c (\"AE_set_ProfileType(6,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon6\";\r\n"
		"    iconTextButton -edit -c (\"AE_set_ProfileType(7,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon7\";\r\n"
		"    iconTextButton -edit -c (\"AE_set_ProfileType(8,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon8\";\r\n"
		"    iconTextButton -edit -c (\"AE_set_ProfileType(9,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon9\";\r\n"
		"    iconTextButton -edit -c (\"AE_set_ProfileType(10,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon10\";\r\n"
		"    iconTextButton -edit -c (\"AE_set_ProfileType(11,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon11\";\r\n"
		"    iconTextButton -edit -c (\"AE_set_ProfileType(12,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon12\";\r\n"
		"    iconTextButton -edit -c (\"AE_set_ProfileType(13,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon13\";\r\n"
		"    iconTextButton -edit -c (\"AE_set_ProfileType(14,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon14\";\r\n"
		"    iconTextButton -edit -c (\"AE_set_ProfileType(15,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon15\";\r\n"
		"    iconTextButton -edit -c (\"AE_set_ProfileType(16,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon16\";\r\n"
		"    iconTextButton -edit -c (\"AE_set_ProfileType(17,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon17\";\r\n"
		"    iconTextButton -edit -c (\"AE_set_ProfileType(18,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon18\";\r\n"
		"    iconTextButton -edit -c (\"AE_set_ProfileType(19,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon19\";\r\n"
		"}\r\n"
		"\r\n"
		"global proc AE_presetList_ShellMod_create(string $attrName)\r\n"
		"{\r\n"
		"    string $nodeName[];\r\n"
		"    tokenize($attrName, \".\", $nodeName);\r\n"
		"    \r\n"
		"    // Crete preset list\r\n"
		"    \r\n"
		"    separator -height 10 -style \"in\";\r\n"
		"\	textScrollList -allowMultiSelection false -h 120 \"sl_presets\";\r\n"
		"    setParent ..;\r\n"
		"    // Populate preset list\r\n"
		"    \r\n"
		"    \r\n"
		"    string $sm_pr_path = eval(\"getAttr \" + $nodeName[0] + \".presetFolderPath\");\r\n"
		"    \r\n"
		"    string $enumFields_list[] = `getFileList -fs \"*.smp\" -folder $sm_pr_path`;\r\n"
		"    \r\n"
		"    string $enumName[];\r\n"
		"    \r\n"
		"    \r\n"
		"    for( $i=0; $i<size($enumFields_list); ++$i )\r\n"
		"\	{\r\n"
		"\	    tokenize($enumFields_list[$i], \".\", $enumName);\r\n"
		"\	    textScrollList -edit -append $enumName[0] \"sl_presets\";\r\n"
		"\	}\r\n"
		"    \r\n"
		"    // Create add / remove preset icons\r\n"
		"    separator -height 10 -style \"in\";\r\n"
		"    \r\n"
		"    rowLayout -numberOfColumns 5 -h 25 -adjustableColumn 4 -bgc 0.2 0.2 0.2;\r\n"
		"    iconTextButton -w 20 -style \"iconAndTextHorizontal\" -image1 \"shellModNode_Apply.xmp\" -label \"apply preset\" -bgc 0.3 0.3 0.3 -c  (\"AE_apply_customProfile_ShellMod \" + $nodeName[0] ) \"pres_appl\";\r\n"
		"\	iconTextButton -w 50 -style \"iconAndTextHorizontal\" -image1 \"shellModNode_Plus.xmp\" -label \"add\" -bgc 0.4 0.4 0.4 -c  (\"AE_add_customProfile_ShellMod \" + $nodeName[0] ) \"pres_add\";\r\n"
		"\	iconTextButton  -w 90 -style \"iconAndTextHorizontal\" -image1 \"shellModNode_Minus.xmp\" -label \"remove\" -bgc 0.6 0.2 0.3 -c  (\"AE_remove_customProfile_ShellMod \" + $nodeName[0] ) \"pres_rem\";\r\n"
		"\	textField -pht \"Untitled\" \"t_renamePreset\";\r\n"
		"\	iconTextButton -w 80 -style \"iconAndTextHorizontal\" -image1 \"shellModNode_Refresh.xmp\" -label \"refresh\" -bgc 0.6 0.6 0.6 -c  (\"AE_refresh_customProfile_ShellMod \" + $nodeName[0] ) \"pres_refresh\";\r\n"
		"\	\r\n"
		"\	setParent ..;\r\n"
		"\	\r\n"
		"\	\r\n"
		"    \r\n"
		"}\r\n"
		"\r\n"
		"global proc AE_presetList_ShellMod_edit(string $attrName)\r\n"
		"{\r\n"
		"    string $nodeName[];\r\n"
		"    tokenize($attrName, \".\", $nodeName);\r\n"
		"    \r\n"
		"    iconTextButton -edit -c (\"AE_apply_customProfile_ShellMod \" + $nodeName[0] ) \"pres_appl\";\r\n"
		"\	iconTextButton -edit -c (\"AE_add_customProfile_ShellMod \" + $nodeName[0] ) \"pres_add\";\r\n"
		"\	iconTextButton -edit -c (\"AE_remove_customProfile_ShellMod \" + $nodeName[0] ) \"pres_rem\";\r\n"
		"\	iconTextButton -edit -c (\"AE_refresh_customProfile_ShellMod \" + $nodeName[0] ) \"pres_refresh\";\r\n"
		"    \r\n"
		"}\r\n"
		"\r\n"
		"\r\n"
		"// --------------\r\n"
		;

	s_aeTemplate_A.append(s_aeTemplate_000);

	// ---------------
	// Row 000
	// ---------------

	MString s_aeTemplate_001 = "// Custom profile\r\n"
		"global proc AE_refresh_customProfile_ShellMod(string $nodeName)\r\n"
		"{\r\n"
		"    \r\n"
		"    string $sm_pr_path = eval(\"getAttr \" + $nodeName + \".presetFolderPath\");\r\n"
		"    string $enumFields_list[] = `getFileList -fs \"*.smp\" -folder $sm_pr_path`;\r\n"
		"    \r\n"
		"    string $enumName[];\r\n"
		"    \r\n"
		"    textScrollList -edit -ra \"sl_presets\";\r\n"
		"    \r\n"
		"    for( $i=0; $i<size($enumFields_list); ++$i )\r\n"
		"\	{\r\n"
		"\	    tokenize($enumFields_list[$i], \".\", $enumName);\r\n"
		"\	    textScrollList -edit -append $enumName[0] \"sl_presets\";\r\n"
		"\	}\r\n"
		"\	\r\n"
		"\	float $pfR =  `getAttr ($nodeName+\".profileRamp[0].profileRamp_Position\")`;\r\n"
		"\	setAttr ($nodeName+\".profileRamp[0].profileRamp_Position\") $pfR;\r\n"
		"}\r\n"
		"\r\n"
		"global proc AE_apply_customProfile_ShellMod(string $attrName)\r\n"
		"{\r\n"
		"    string $nodeName[];\r\n"
		"    tokenize($attrName, \".\", $nodeName);\r\n"
		"\	\r\n"
		"    string $presetName[];\r\n"
		"    $presetName = `textScrollList -query -si \"sl_presets\"`;\r\n"
		"    \r\n"
		"    if ($presetName[0] != \"\") \r\n"
		"    {\r\n"
		"        string $sm_pr_path = eval(\"getAttr \" + $nodeName[0] + \".presetFolderPath\");\r\n"
		"        shellModCommand -lp $presetName -pp $sm_pr_path -sm $nodeName[0];\r\n"
		"        textScrollList -edit -si $presetName \"sl_presets\";\r\n"
		"    }\r\n"
		"    \r\n"
		"    setAttr ($nodeName[0] + \".profilePresets\") 0;\r\n"
		"    AE_refresh_customProfile_ShellMod($nodeName[0]);\r\n"
		"    \r\n"
		"    \r\n"
		"}\r\n"
		"\r\n"
		"global proc AE_add_customProfile_ShellMod(string $attrName)\r\n"
		"{\r\n"
		"    string $nodeName[];\r\n"
		"    tokenize($attrName, \".\", $nodeName);\r\n"
		"    string $newPresetName;\r\n"
		"    $newPresetName = `textField -query -tx \"t_renamePreset\"`;\r\n"
		"    \r\n"
		"    //int $s_count = `size $newPresetName`;\r\n"
		"    if ($newPresetName == \"\") { $newPresetName = \"untitled\";}\r\n"
		"    \r\n"
		"    string $sm_pr_path = eval(\"getAttr \" + $nodeName[0] + \".presetFolderPath\");\r\n"
		"    string $enumFields_list[] = `getFileList -fs \"*.smp\" -folder $sm_pr_path`;\r\n"
		"    string $enumName[];\r\n"
		"    \r\n"
		"    int $isSame = 0;\r\n"
		"    \r\n"
		"    for( $i=0; $i<size($enumFields_list); ++$i )\r\n"
		"\	{\r\n"
		"\	    tokenize($enumFields_list[$i], \".\", $enumName);\r\n"
		"\	    \r\n"
		"\	    if($enumName[0] == $newPresetName)\r\n"
		"\	    {\r\n"
		"\	        string $conFirmVal = `confirmDialog -title (\"Overwrite \" + $newPresetName) -message \"Are you sure?\"\r\n"
		"    -button \"Yes\" -button \"No\" -defaultButton \"Yes\"\r\n"
		"    -cancelButton \"No\" -dismissString \"No\"`;\r\n"
		"    \r\n"
		"            if($conFirmVal == \"Yes\")\r\n"
		"            {\r\n"
		"                shellModCommand -sp $newPresetName -pp $sm_pr_path -sm $nodeName[0];\r\n"
		"                $isSame = 1;\r\n"
		"            }\r\n"
		"            \r\n"
		"            if($conFirmVal == \"No\")\r\n"
		"            {\r\n"
		"                $isSame = 1;\r\n"
		"            }\r\n"
		"\	    }\r\n"
		"\	    \r\n"
		"\	}\r\n"
		"    \r\n"
		"    if( $isSame == 0)\r\n"
		"    {\r\n"
		"        shellModCommand -sp $newPresetName -pp $sm_pr_path -sm $nodeName[0];\r\n"
		"    }\r\n"
		"    \r\n"
		"    AE_refresh_customProfile_ShellMod($nodeName[0]);\r\n"
		"    \r\n"
		"}\r\n"
		"\r\n"
		"global proc AE_remove_customProfile_ShellMod(string $attrName)\r\n"
		"{\r\n"
		"    string $nodeName[];\r\n"
		"    tokenize($attrName, \".\", $nodeName);\r\n"
		"    \r\n"
		"    string $presetName[];\r\n"
		"    $presetName = `textScrollList -query -si \"sl_presets\"`;\r\n"
		"    \r\n"
		"    if ($presetName[0] != \"\") \r\n"
		"    {\r\n"
		"\r\n"
		"        string $conFirmVal = `confirmDialog -title \"Delete\" -message \"Are you sure?\" -button \"Yes\" -button \"No\" -defaultButton \"Yes\" -cancelButton \"No\" -dismissString \"No\"`;\r\n"
		"    \r\n"
		"            if($conFirmVal == \"Yes\")\r\n"
		"            {\r\n"
		"                string $sm_pr_path = eval(\"getAttr \" + $nodeName[0] + \".presetFolderPath\");\r\n"
		"                sysFile -delete ($sm_pr_path + $presetName[0] + \".smp\");\r\n"
		"                AE_refresh_customProfile_ShellMod($nodeName[0]);\r\n"
		"            }\r\n"
		"            \r\n"
		"            if($conFirmVal == \"No\")\r\n"
		"            {\r\n"
		"                \r\n"
		"            }\r\n"
		"\r\n"
		"    }\r\n"
		"    \r\n"
		"    \r\n"
		"}\r\n"
		"\r\n"
		"// ----------------------------\r\n"
		"// Global window Create / Edit\r\n"
		"global proc AE_del_ShellMod_create(string $attrName)\r\n"
		"{\r\n"
		"\	string $nodeName[];\r\n"
		"    tokenize($attrName, \".\", $nodeName);\r\n"
		"    iconTextButton -h 22 -style \"iconAndTextHorizontal\" -image1 \"shellModNode_Trash.xmp\" -label \"Remove ShellMod from selected object\"  -bgc 0.6 0.2 0.3 -c  (\"AE_remove_ShellMod \" + $nodeName[0] );\r\n"
		"}\r\n"
		"\r\n"
		"global proc AE_del_ShellMod_edit(string $attrName)\r\n"
		"{\r\n"
		"}\r\n"
		"\r\n"
		"// ----------------------------\r\n"
		"// Remove shellmod from object\r\n"
		"global proc AE_remove_ShellMod(string $attrName)\r\n"
		"{\r\n"
		"shellModCommand -r;\r\n"
		"}\r\n"
		"\r\n"
		"global proc AE_launch_website()\r\n"
		"{\r\n"
		"    launch -web \"http://gumroad.com/creativecase\";\r\n"
		"}\r\n"
		"\r\n"
		"// ----------------------------\r\n"
		"// Global window Create / Edit\r\n"
		"global proc AE_website_create(string $attrName)\r\n"
		"{\r\n"
		"\	string $nodeName[];\r\n"
		"    tokenize($attrName, \".\", $nodeName);\r\n"
		"    \r\n"
		"    string $sm_pr_path = eval(\"getAttr \" + $nodeName[0] + \".presetFolderPath\");\r\n"
		"    \r\n"
		"    rowLayout -numberOfColumns 3 -adjustableColumn 2 -bgc 0.2 0.2 0.2;\r\n"
		"    text -al \"left\" -label \"Preset path\";\r\n"
		"    textField -ed false -tx $sm_pr_path;\r\n"
		"    iconTextButton -style \"iconOnly\" -image1 \"shellModNode_CCLogo.xmp\" -c \"AE_launch_website()\";\r\n"
		"\r\n"
		"    setParent ..;\r\n"
		"}\r\n"
		"\r\n"
		"global proc AE_website_edit(string $attrName)\r\n"
		"{\r\n"
		"}"
		;

	s_aeTemplate_A.append(s_aeTemplate_001);



	return s_aeTemplate_A;
}





MString mel_createShelf()
{

	MString s_aeTemplate = MString() + "int $cc_doesShelfExist = `shelfLayout -query -ex \"CreativeCase\"`;\n" +
		"if ($cc_doesShelfExist == 1)\n" +
		"{\n" +
		"    \n" +
		"    string $shelfButtons[] = `shelfLayout -q -ca \"CreativeCase\"`;\n" +
		"    \n" +
		"    int $ex_b01,$ex_b02,$ex_b03 = 0;\n" +
		"    \n" +
		"    for( $i=0; $i<size($shelfButtons); ++$i )\n" +
		"{\n" +
		"    if( `control -exists $shelfButtons[$i]` == true)\n" +
		"    {\n" +
		"         if (`control -q -docTag $shelfButtons[$i]` == \"sm_createSmButton\") {$ex_b01 = 1;}\n" +
		"         if (`control -q -docTag $shelfButtons[$i]` == \"sm_addSmButton\") {$ex_b02 = 1;}\n" +
		"         if (`control -q -docTag $shelfButtons[$i]` == \"sm_createPlaneSmButton\") {$ex_b03 = 1;}\n" +
		"    }\n" +
		"    \n" +
		"}\n" +
		"if ($ex_b01 == 0) {shelfButton -p \"CreativeCase\" -dtg \"sm_createSmButton\" -annotation \"Add a ShellMod modifier to the selected objects\" -image1 \"shellModNode.png\" -command \"shellModCommand\";}\n" +
		"if ($ex_b02 == 0) {shelfButton -p \"CreativeCase\" -dtg \"sm_addSmButton\" -annotation \"Add the objects to the first selected ShellMod node\" -image1 \"shellModNode_Add.png\" -command \"shellModCommand -a\";}\n" +
		"if ($ex_b03 == 0) {shelfButton -p \"CreativeCase\" -dtg \"sm_createPlaneSmButton\" -annotation \"Creates a polygon plane with a ShellMod\" -image1 \"shellModNode_Plane.png\" -command \"polyPlane -sx 1 -sy 1 -w 5 -h 5;shellModCommand;move -y 1\";}\n" +
		"    \n" +
		"}\n" +
		"if ($cc_doesShelfExist == false)\n" +
		"{\n" +
		"    shelfLayout -cellWidth 33 -cellHeight 33 -p $gShelfTopLevel CreativeCase;\n" +
		"    shelfButton -p \"CreativeCase\" -dtg \"sm_createSmButton\" -annotation \"Add a ShellMod modifier to the selected objects\" -image1 \"shellModNode.png\" -command \"shellModCommand\";\n" +
		"    shelfButton -p \"CreativeCase\" -dtg \"sm_addSmButton\" -annotation \"Add the objects to the first selected ShellMod node\" -image1 \"shellModNode_Add.png\" -command \"shellModCommand -a\";\n" +
		"    shelfButton -p \"CreativeCase\" -dtg \"sm_createPlaneSmButton\" -annotation \"Creates a polygon plane with a ShellMod\" -image1 \"shellModNode_Plane.png\" -command \"polyPlane -sx 1 -sy 1 -w 5 -h 5;shellModCommand;move -y 1\";\n" +
		"};\n";

	return s_aeTemplate;
}

MString mel_deleteShelf()
{

	MString s_shelf =
		"int $cc_doesShelfExist;\
		$cc_doesShelfExist = `shelfLayout -query -ex \"CreativeCase\"`;\
		\
		if ($cc_doesShelfExist == true)\
		{\
		deleteUI CreativeCase;\
		}\
		";

	return s_shelf;
}

#endif