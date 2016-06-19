//
//  AETemplates.h
//  shellMod
//
//  Created by Hunyadi János on 2015. 01. 03..
//  Copyright (c) 2015. Janos Hunyadi. All rights reserved.
//

#ifndef MELSCRIPTS_H
#define MELSCRIPTS_H

#include <maya/MString.h>


MString mel_AETemplate()
{
	MString s_aeTemplate = MString() +  "//deleteUI AttrEdshellModNodeFormLayout;\n" +
		"global proc AEshellModNodeTemplate( string $nodeName )\n" +
		"{\n" +
		"\n" +
		"editorTemplate -beginScrollLayout;\n" +
		"\n" +
		"editorTemplate -beginLayout \"ShellMod 1shape settings\" -collapse 0;\n" +
		"editorTemplate -addControl \"offsetZ\";\n" +
		"editorTemplate -addControl \"chaserEdgeWeight\";\n" +
		"editorTemplate -addControl \"segments\";\n" +
		"editorTemplate -addControl \"straightenEdgesAngle\";\n" +
		"editorTemplate -addControl \"smoothMeshSubdiv\";\n" +
		"\n" +
		"editorTemplate -addSeparator;\n" +
		"\n" +
		"editorTemplate -addControl \"chaserEdges\";\n" +
		"editorTemplate -addControl \"capTop\";\n" +
		"editorTemplate -addControl \"capBottom\";\n" +
		"editorTemplate -addControl \"smoothNormals\";\n" +
		"editorTemplate -addControl \"reverseNormals\";\n" +
		"editorTemplate -addControl \"straightenEdges\";\n" +
		"editorTemplate -addControl \"autoSegments\";\n" +
		"\n" +
		"editorTemplate -addSeparator;\n" +
		"editorTemplate -addControl \"baseMeshDisplayOverride\";\n" +
		"\n" +
		"\n" +
		"AEaddRampControl( $nodeName + \".profileRamp\" );\n" +
		"editorTemplate -addControl \"profileStrength\";\n" +
		"\n" +
		"\n" +
		"editorTemplate -addSeparator;\n" +
		"editorTemplate -label \"Built in Presets\" -addControl \"profilePresets\";\n" +
		"\n" +
		"editorTemplate -callCustom \"AE_preset_ShellMod_create\" \"AE_preset_ShellMod_edit\" \"profilePresets\";\n" +
		"editorTemplate -callCustom \"AE_presetList_ShellMod_create\" \"AE_presetList_ShellMod_edit\" \"\";\n" +
		"\n" +
		"editorTemplate -endLayout;\n" +
		"\n" +
		"\n" +
		"\n" +
		"editorTemplate -beginLayout \"UV options\" -collapse 0;\n" +
		"editorTemplate -addControl \"uvOffsetU\";\n" +
		"editorTemplate -addControl \"uvOffsetV\";\n" +
		"editorTemplate  -label \"Auto U Offset\" -addControl \"uvOffsetUAutoOffset\";\n" +
		"editorTemplate  -label \"Auto U Offset Padding\" -addControl \"uvOffsetUAutoOffsetPadding\";\n" +
		"\n" +
		"editorTemplate -endLayout;\n" +
		"\n" +
		"editorTemplate -beginLayout \"Global settings\" -collapse 0;\n" +
		"editorTemplate -callCustom \"AE_del_ShellMod_create\" \"AE_del_ShellMod_edit\" \"\";\n" +
		"\n" +
		"editorTemplate -endLayout;\n" +
		"\n" +
		"editorTemplate -beginLayout \"Plug-in Info\" -collapse 1;\n" +
		"editorTemplate -callCustom \"AE_website_create\" \"AE_website_edit\" \"\";\n" +
		"editorTemplate -endLayout;\n" +
		"\n" +
		"editorTemplate -suppress \"inMesh\";\n" +
		"\n" +
		"AEdependNodeTemplate $nodeName;\n" +
		"editorTemplate -addExtraControls;\n" +
		"editorTemplate -endScrollLayout;\n" +
		"\n" +
		"\n" +
		"}\n" +
		"global proc AE_preset_ShellMod_set(int $id, string $attr)\n" +
		"{\n" +
		"}\n" +
		"global proc AE_set_ProfileType(int $i_type, string $s_nodeName)\n" +
		"{\n" +
		"    setAttr ($s_nodeName + \".profilePresets \" ) $i_type;\n" +
		"}\n" +
		"global proc AE_preset_ShellMod_create(string $attrName)\n" +
		"{\n" +
		"    string $nodeName[];\n" +
		"    tokenize($attrName, \".\", $nodeName);\n" +
		"    \n" +
		"setUITemplate -pst attributeEditorPresetsTemplate;\n" +
		"    \n" +
		"    \n" +
		"    separator -height 10 -style \"in\";\n" +
		"    \n" +
		"    gridLayout -numberOfColumns 21 -cellWidthHeight 18 18 -bgc 0.2 0.2 0.2;\n" +
		"    iconTextButton -iol \"cu\" -image \"shellModNode_Preset.png\" -c (\"AE_set_ProfileType(0,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon0\";\n" +
		"    iconTextButton -iol \"2\" -image \"shellModNode_Preset.png\" -c (\"AE_set_ProfileType(1,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon1\";\n" +
		"    iconTextButton -iol \"3\" -image \"shellModNode_Preset.png\" -c (\"AE_set_ProfileType(2,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon2\";\n" +
		"    iconTextButton -iol \"4\" -image \"shellModNode_Preset.png\" -c (\"AE_set_ProfileType(3,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon3\";\n" +
		"    iconTextButton -iol \"5\" -image \"shellModNode_Preset.png\" -c (\"AE_set_ProfileType(4,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon4\";\n" +
		"    iconTextButton -iol \"6\" -image \"shellModNode_Preset.png\" -c (\"AE_set_ProfileType(5,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon5\";\n" +
		"    iconTextButton -iol \"7\" -image \"shellModNode_Preset.png\" -c (\"AE_set_ProfileType(6,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon6\";\n" +
		"    iconTextButton -iol \"8\" -image \"shellModNode_Preset.png\" -c (\"AE_set_ProfileType(7,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon7\";\n" +
		"    iconTextButton -iol \"9\" -image \"shellModNode_Preset.png\" -c (\"AE_set_ProfileType(8,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon8\";\n" +
		"    iconTextButton -iol \"10\" -image \"shellModNode_Preset.png\" -c (\"AE_set_ProfileType(9,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon9\";\n" +
		"    iconTextButton -iol \"11\" -image \"shellModNode_Preset.png\" -c (\"AE_set_ProfileType(10,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon10\";\n" +
		"    iconTextButton -iol \"12\" -image \"shellModNode_Preset.png\" -c (\"AE_set_ProfileType(11,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon11\";\n" +
		"    iconTextButton -iol \"13\" -image \"shellModNode_Preset.png\" -c (\"AE_set_ProfileType(12,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon12\";\n" +
		"    iconTextButton -iol \"14\" -image \"shellModNode_Preset.png\" -c (\"AE_set_ProfileType(13,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon13\";\n" +
		"    iconTextButton -iol \"15\" -image \"shellModNode_Preset.png\" -c (\"AE_set_ProfileType(14,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon14\";\n" +
		"    iconTextButton -iol \"16\" -image \"shellModNode_Preset.png\" -c (\"AE_set_ProfileType(15,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon15\";\n" +
		"    iconTextButton -iol \"17\" -image \"shellModNode_Preset.png\" -c (\"AE_set_ProfileType(16,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon16\";\n" +
		"    iconTextButton -iol \"18\" -image \"shellModNode_Preset.png\" -c (\"AE_set_ProfileType(17,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon17\";\n" +
		"    iconTextButton -iol \"19\" -image \"shellModNode_Preset.png\" -c (\"AE_set_ProfileType(18,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon18\";\n" +
		"    iconTextButton -iol \"20\" -image \"shellModNode_Preset.png\" -c (\"AE_set_ProfileType(19,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon19\";\n" +
		"setParent ..;\n" +
		"\n" +
		"setUITemplate -ppt;\n" +
		"}\n" +
		"global proc AE_preset_ShellMod_edit(string $attrName)\n" +
		"{\n" +
		"    string $nodeName[];\n" +
		"    tokenize($attrName, \".\", $nodeName);\n" +
		"    \n" +
		"    iconTextButton -edit -c (\"AE_set_ProfileType(0,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon0\";\n" +
		"    iconTextButton -edit -c (\"AE_set_ProfileType(1,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon1\";\n" +
		"    iconTextButton -edit -c (\"AE_set_ProfileType(2,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon2\";\n" +
		"    iconTextButton -edit -c (\"AE_set_ProfileType(3,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon3\";\n" +
		"    iconTextButton -edit -c (\"AE_set_ProfileType(4,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon4\";\n" +
		"    iconTextButton -edit -c (\"AE_set_ProfileType(5,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon5\";\n" +
		"    iconTextButton -edit -c (\"AE_set_ProfileType(6,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon6\";\n" +
		"    iconTextButton -edit -c (\"AE_set_ProfileType(7,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon7\";\n" +
		"    iconTextButton -edit -c (\"AE_set_ProfileType(8,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon8\";\n" +
		"    iconTextButton -edit -c (\"AE_set_ProfileType(9,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon9\";\n" +
		"    iconTextButton -edit -c (\"AE_set_ProfileType(10,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon10\";\n" +
		"    iconTextButton -edit -c (\"AE_set_ProfileType(11,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon11\";\n" +
		"    iconTextButton -edit -c (\"AE_set_ProfileType(12,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon12\";\n" +
		"    iconTextButton -edit -c (\"AE_set_ProfileType(13,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon13\";\n" +
		"    iconTextButton -edit -c (\"AE_set_ProfileType(14,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon14\";\n" +
		"    iconTextButton -edit -c (\"AE_set_ProfileType(15,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon15\";\n" +
		"    iconTextButton -edit -c (\"AE_set_ProfileType(16,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon16\";\n" +
		"    iconTextButton -edit -c (\"AE_set_ProfileType(17,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon17\";\n" +
		"    iconTextButton -edit -c (\"AE_set_ProfileType(18,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon18\";\n" +
		"    iconTextButton -edit -c (\"AE_set_ProfileType(19,\" + \"\\\"\" + $nodeName[0] + \"\\\"\" + \")\") \"icon19\";\n" +
		"}\n" +
		"global proc AE_presetList_ShellMod_create(string $attrName)\n" +
		"{\n" +
		"    string $nodeName[];\n" +
		"    tokenize($attrName, \".\", $nodeName);\n" +
		"    \n" +
		"    // Crete preset list\n" +
		"    \n" +
		"    separator -height 10 -style \"in\";\n" +
		"textScrollList -allowMultiSelection false -h 120 \"sl_presets\";\n" +
		"    setParent ..;\n" +
		"    // Populate preset list\n" +
		"    \n" +
		"    \n" +
		"    string $sm_pr_path = eval(\"getAttr \" + $nodeName[0] + \".presetFolderPath\");\n" +
		"    \n" +
		"    string $enumFields_list[] = `getFileList -fs \"*.smp\" -folder $sm_pr_path`;\n" +
		"    \n" +
		"    string $enumName[];\n" +
		"    \n" +
		"    \n" +
		"    for( $i=0; $i<size($enumFields_list); ++$i )\n" +
		"{\n" +
		"    tokenize($enumFields_list[$i], \".\", $enumName);\n" +
		"    textScrollList -edit -append $enumName[0] \"sl_presets\";\n" +
		"}\n" +
		"    \n" +
		"    // Create add / remove preset icons\n" +
		"    separator -height 10 -style \"in\";\n" +
		"    \n" +
		"    rowLayout -numberOfColumns 5 -h 25 -adjustableColumn 4 -bgc 0.2 0.2 0.2;\n" +
		"    iconTextButton -w 20 -style \"iconAndTextHorizontal\" -image1 \"shellModNode_Apply.png\" -label \"apply preset\" -bgc 0.3 0.3 0.3 -c  (\"AE_apply_customProfile_ShellMod \" + $nodeName[0] ) \"pres_appl\";\n" +
		"iconTextButton -w 50 -style \"iconAndTextHorizontal\" -image1 \"shellModNode_Plus.png\" -label \"add\" -bgc 0.4 0.4 0.4 -c  (\"AE_add_customProfile_ShellMod \" + $nodeName[0] ) \"pres_add\";\n" +
		"iconTextButton  -w 90 -style \"iconAndTextHorizontal\" -image1 \"shellModNode_Minus.png\" -label \"remove\" -bgc 0.6 0.2 0.3 -c  (\"AE_remove_customProfile_ShellMod \" + $nodeName[0] ) \"pres_rem\";\n" +
		"textField -pht \"Untitled\" \"t_renamePreset\";\n" +
		"iconTextButton -w 80 -style \"iconAndTextHorizontal\" -image1 \"shellModNode_Refresh.png\" -label \"refresh\" -bgc 0.6 0.6 0.6 -c  (\"AE_refresh_customProfile_ShellMod \" + $nodeName[0] ) \"pres_refresh\";\n" +
		"\n" +
		"setParent ..;\n" +
		"\n" +
		"\n" +
		"    \n" +
		"}\n" +
		"global proc AE_presetList_ShellMod_edit(string $attrName)\n" +
		"{\n" +
		"    string $nodeName[];\n" +
		"    tokenize($attrName, \".\", $nodeName);\n" +
		"    \n" +
		"    iconTextButton -edit -c (\"AE_apply_customProfile_ShellMod \" + $nodeName[0] ) \"pres_appl\";\n" +
		"iconTextButton -edit -c (\"AE_add_customProfile_ShellMod \" + $nodeName[0] ) \"pres_add\";\n" +
		"iconTextButton -edit -c (\"AE_remove_customProfile_ShellMod \" + $nodeName[0] ) \"pres_rem\";\n" +
		"iconTextButton -edit -c (\"AE_refresh_customProfile_ShellMod \" + $nodeName[0] ) \"pres_refresh\";\n" +
		"    \n" +
		"}\n" +
		"// --------------\n" +
		"// Custom profile\n" +
		"global proc AE_refresh_customProfile_ShellMod(string $nodeName)\n" +
		"{\n" +
		"    \n" +
		"    string $sm_pr_path = eval(\"getAttr \" + $nodeName + \".presetFolderPath\");\n" +
		"    string $enumFields_list[] = `getFileList -fs \"*.smp\" -folder $sm_pr_path`;\n" +
		"    \n" +
		"    string $enumName[];\n" +
		"    \n" +
		"    textScrollList -edit -ra \"sl_presets\";\n" +
		"    \n" +
		"    for( $i=0; $i<size($enumFields_list); ++$i )\n" +
		"{\n" +
		"    tokenize($enumFields_list[$i], \".\", $enumName);\n" +
		"    textScrollList -edit -append $enumName[0] \"sl_presets\";\n" +
		"}\n" +
		"\n" +
		"float $pfR =  `getAttr ($nodeName+\".profileRamp[0].profileRamp_Position\")`;\n" +
		"setAttr ($nodeName+\".profileRamp[0].profileRamp_Position\") $pfR;\n" +
		"}\n" +
		"global proc AE_apply_customProfile_ShellMod(string $attrName)\n" +
		"{\n" +
		"    string $nodeName[];\n" +
		"    tokenize($attrName, \".\", $nodeName);\n" +
		"    //AE_set_ProfileType(0, $nodeName[0]);\n" +
		"   \n" +
		"    \n" +
		"    string $presetName[];\n" +
		"    $presetName = `textScrollList -query -si \"sl_presets\"`;\n" +
		"    \n" +
		"    if ($presetName[0] != \"\") \n" +
		"    {\n" +
		"        \n" +
		"        \n" +
		"        string $sm_pr_path = eval(\"getAttr \" + $nodeName[0] + \".presetFolderPath\");\n" +
		"          \n" +
		"        print $sm_pr_path;\n" +
		"        shellModCommand -lp $presetName -pp $sm_pr_path -sm $nodeName[0];\n" +
		"        \n" +
		"        textScrollList -edit -si $presetName \"sl_presets\";\n" +
		"        \n" +
		"        \n" +
		"    }\n" +
		"    \n" +
		"    setAttr ($nodeName[0] + \".profilePresets\") 0;\n" +
		"    AE_refresh_customProfile_ShellMod($nodeName[0]);\n" +
		"    \n" +
		"    \n" +
		"}\n" +
		"global proc AE_add_customProfile_ShellMod(string $attrName)\n" +
		"{\n" +
		"    string $nodeName[];\n" +
		"    tokenize($attrName, \".\", $nodeName);\n" +
		"    \n" +
		"    string $newPresetName;\n" +
		"    $newPresetName = `textField -query -tx \"t_renamePreset\"`;\n" +
		"    \n" +
		"    //int $s_count = `size $newPresetName`;\n" +
		"    if ($newPresetName == \"\") { $newPresetName = \"untitled\";}\n" +
		"    \n" +
		"    string $sm_pr_path = eval(\"getAttr \" + $nodeName[0] + \".presetFolderPath\");\n" +
		"    \n" +
		"    string $enumFields_list[] = `getFileList -fs \"*.smp\" -folder $sm_pr_path`;\n" +
		"    \n" +
		"    string $enumName[];\n" +
		"    \n" +
		"    int $isSame = 0;\n" +
		"    \n" +
		"    for( $i=0; $i<size($enumFields_list); ++$i )\n" +
		"{\n" +
		"    tokenize($enumFields_list[$i], \".\", $enumName);\n" +
		"    \n" +
		"    if($enumName[0] == $newPresetName)\n" +
		"    {\n" +
		"        string $conFirmVal = `confirmDialog -title (\"Overwrite \" + $newPresetName) -message \"Are you sure?\"\n" +
		"    -button \"Yes\" -button \"No\" -defaultButton \"Yes\"\n" +
		"    -cancelButton \"No\" -dismissString \"No\"`;\n" +
		"    \n" +
		"            if($conFirmVal == \"Yes\")\n" +
		"            {\n" +
		"                shellModCommand -sp $newPresetName -pp $sm_pr_path -sm $nodeName[0];\n" +
		"                $isSame = 1;\n" +
		"            }\n" +
		"            \n" +
		"            if($conFirmVal == \"No\")\n" +
		"            {\n" +
		"                $isSame = 1;\n" +
		"            }\n" +
		"    }\n" +
		"    \n" +
		"}\n" +
		"    \n" +
		"    if( $isSame == 0)\n" +
		"    {\n" +
		"        shellModCommand -sp $newPresetName -pp $sm_pr_path -sm $nodeName[0];\n" +
		"    }\n" +
		"    \n" +
		"    \n" +
		"    \n" +
		"    AE_refresh_customProfile_ShellMod($nodeName[0]);\n" +
		"    \n" +
		"}\n" +
		"global proc AE_remove_customProfile_ShellMod(string $attrName)\n" +
		"{\n" +
		"    string $nodeName[];\n" +
		"    tokenize($attrName, \".\", $nodeName);\n" +
		"    \n" +
		"    string $presetName[];\n" +
		"    $presetName = `textScrollList -query -si \"sl_presets\"`;\n" +
		"    \n" +
		"    if ($presetName[0] != \"\") \n" +
		"    {\n" +
		"        \n" +
		"        \n" +
		"        string $conFirmVal = `confirmDialog -title \"Delete\" -message \"Are you sure?\" -button \"Yes\" -button \"No\" -defaultButton \"Yes\" -cancelButton \"No\" -dismissString \"No\"`;\n" +
		"    \n" +
		"            if($conFirmVal == \"Yes\")\n" +
		"            {\n" +
		"                string $sm_pr_path = eval(\"getAttr \" + $nodeName[0] + \".presetFolderPath\");\n" +
		"                sysFile -delete ($sm_pr_path + $presetName[0] + \".smp\");\n" +
		"                AE_refresh_customProfile_ShellMod($nodeName[0]);\n" +
		"            }\n" +
		"            \n" +
		"            if($conFirmVal == \"No\")\n" +
		"            {\n" +
		"                \n" +
		"            }\n" +
		"        \n" +
		"        \n" +
		"        \n" +
		"    }\n" +
		"    \n" +
		"    \n" +
		"}\n" +
		"// ----------------------------\n" +
		"// Global window Create / Edit\n" +
		"global proc AE_del_ShellMod_create(string $attrName)\n" +
		"{\n" +
		"string $nodeName[];\n" +
		"    tokenize($attrName, \".\", $nodeName);\n" +
		"    iconTextButton -h 22 -style \"iconAndTextHorizontal\" -image1 \"shellModNode_Trash.png\" -label \"Remove ShellMod from selected object\"  -bgc 0.6 0.2 0.3 -c  (\"AE_remove_ShellMod \" + $nodeName[0] );\n" +
		"    \n" +
		"}\n" +
		"global proc AE_del_ShellMod_edit(string $attrName)\n" +
		"{\n" +
		"}\n" +
		"// ----------------------------\n" +
		"// Remove shellmod from object\n" +
		"global proc AE_remove_ShellMod(string $attrName)\n" +
		"{\n" +
		"shellModCommand -r;\n" +
		"}\n" +
		"global proc AE_launch_website()\n" +
		"{\n" +
		"    launch -web \"http://gumroad.com/creativecase\";\n" +
		"}\n" +
		"// ----------------------------\n" +
		"// Global window Create / Edit\n" +
		"global proc AE_website_create(string $attrName)\n" +
		"{\n" +
		"string $nodeName[];\n" +
		"    tokenize($attrName, \".\", $nodeName);\n" +
		"    \n" +
		"    string $sm_pr_path = eval(\"getAttr \" + $nodeName[0] + \".presetFolderPath\");\n" +
		"    \n" +
		"    rowLayout -numberOfColumns 3 -adjustableColumn 2 -bgc 0.2 0.2 0.2;\n" +
		"    text -al \"left\" -label \"Preset path\";\n" +
		"    textField -ed false -tx $sm_pr_path;\n" +
		"    iconTextButton -style \"iconOnly\" -image1 \"shellModNode_CCLogo.png\" -c \"AE_launch_website()\";\n" +
		"    setParent ..;\n" +
		"}\n" +
		"global proc AE_website_edit(string $attrName)\n" +
		"{\n" +
		"}\n";











	return s_aeTemplate;

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