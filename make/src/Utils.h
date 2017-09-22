#ifndef UTILS_H
#define UTILS_H


#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>


#include <algorithm>
#include <iostream>
#include <iterator>

#include <maya/MString.h>
#include <maya/MStringArray.h>
#include <maya/MFloatArray.h>
#include <maya/MRampAttribute.h>


//void compileImagePNGtoBinary(char * filename, char * output)
//{
//    
//    FILE * file = fopen(filename, "rb");
//    FILE * out = fopen(output, "w");
//    
//    unsigned char buffer[32];
//    size_t count;
//    fprintf(out, "#pragma once \n\n static unsigned char TEXT_PNG_BYTES[] = { ");
//    while(!feof(file)){
//        count = fread(buffer, 1, 32, file);
//        
//        for(int n = 0; n < count; ++n){
//            fprintf(out, "0x%02X, ", buffer[n]);
//        };
//    };
//    fprintf(out, "};");
//    fclose(file);
//    fclose(out);
//    
//    // compileImagePNGtoBinary("/Users/hunyadijanos/Desktop/shellModNode_Plane.png", "/Users/hunyadijanos/Desktop/shellModNode_Plane.txt");
//    
//    
//}

//void create_preset_folder(MString &s_pathName)
//{
//    
//    MString pPath = getenv ("PATH");
//    
//    MString s_path = pPath + "shellMod.cfg";
//    
//    ofstream fout( s_pathName.asChar() );
//    
//    
//    
//    if(!fout.is_open())
//    {
//        
//        MGlobal::displayWarning(MString() + "[ShellMod] pshellMod.cfg allready in preset folder: " + s_pathName);
//        
//        
//    }
//    
//    if (fout.is_open()) {
//        MGlobal::displayInfo(MString() + "[ShellMod] Writing pshellMod.cfg to preset folder: " + s_pathName);
//        fout << s_path.asChar();
//    }
//    
//    
//}

void convert_mel()
{
	//	std::string sFile = "/temp/dir/to/myscript.py";
	//	char *cFile = (char*)(sFile).c_str();
	//	std::ofstream outFile(cFile);
	//	outFile.write((char *)myscript, sizeof(myscript)); // myscript is the converted code i included in the build
	//	outFile.close();
}



void load_rampData(MRampAttribute &a_curveAttribute, MString &s_pathName, MString &s_presetName, MString &s_shellmodNodeName)
{

	MStatus status;

	MFloatArray	m_curve_positions_file;
	MFloatArray	m_curve_values_file;

	MStringArray s_lines;
	MString s_f_presetName;
	MString s_f_posValues;
	MString s_f_weightValues;

	MString s_path = s_pathName;
	s_pathName += s_presetName + ".smp";

	ifstream infile(s_pathName.asChar());

	string line;
	while (getline(infile, line))
	{
		istringstream iss(line);
		s_lines.append(line.c_str());
	}

	if (s_lines.length() == 3)
	{
		s_f_presetName = s_lines[0];
		s_f_posValues = s_lines[1];
		s_f_weightValues = s_lines[2];

		MGlobal::displayInfo(MString() + "[ShellMod] Preset name: " + s_f_presetName);
		MGlobal::displayInfo(MString() + "[ShellMod] Preset position values: " + s_f_posValues);
		MGlobal::displayInfo(MString() + "[ShellMod] Preset weight values: " + s_f_weightValues);

		// pos values
		MStringArray s_f_posValuesA;
		s_f_posValues.split(',', s_f_posValuesA);

		for (int i = 0; i < s_f_posValuesA.length(); i++)
		{
			m_curve_positions_file.append(s_f_posValuesA[i].asFloat());
		}

		// weight values
		MStringArray s_f_weightValuesA;
		s_f_weightValues.split(',', s_f_weightValuesA);

		for (int i = 0; i < s_f_weightValuesA.length(); i++)
		{
			m_curve_values_file.append(s_f_weightValuesA[i].asFloat());
		}




		// Clear ramp
		


		MIntArray m_curve_interps;

		for (int i = 0; i < m_curve_positions_file.length(); i++)
		{
			m_curve_interps.append(MRampAttribute::kLinear);
		}

		a_curveAttribute.setRamp(m_curve_values_file, m_curve_positions_file, m_curve_interps);



	}


	//a_curveAttribute.setValueAtIndex(<#float value#>, <#unsigned int index#>)


	//vector<float> myVec; // assume this was a filled vector
	//MFloatArray mayaArray(&myVec[0], myVec.size());

	// cmake --build . --config Release
	// cmake -G "Xcode" -DMAYA_VERSION=2014 ../../../
	// cd /Volumes/Backup_Programming/Maya/_BUILD/shellMod/build/osx/2014

}

void save_rampData(MRampAttribute &a_curveAttribute, MString &s_pathName, MString &s_presetName)
{

	// Curve data
	MIntArray					m_curve_indices;
	MIntArray					m_curve_interps;
	MFloatArray					m_curve_positions;
	MFloatArray					m_curve_values;

	a_curveAttribute.sort(true);
	a_curveAttribute.getEntries(m_curve_indices, m_curve_positions, m_curve_values, m_curve_interps ); // get ramp data

	

	// Bubble sort! (Might be useful later)

	//float swapHolder_pos = -1.0;
	//float swapHolder_val = -1.0;
	//int aend = m_curve_positions.length()-1;
	//int alength = aend;

	//for (int c = alength-1; c > 0; c--) // Bubble Sort the array
	//{
	//	for (int i = 0; i < aend; i++)
	//	{
	//		if (m_curve_positions[i] > m_curve_positions[ i + 1 ])
	//		{
	//			swapHolder_pos = m_curve_positions[i + 1];
	//			m_curve_positions[i + 1] = m_curve_positions[i];
	//			m_curve_positions[i] = swapHolder_pos;

	//			swapHolder_val = m_curve_values[i + 1];
	//			m_curve_values[i + 1] = m_curve_values[i];
	//			m_curve_values[i] = swapHolder_val;
	//		}
	//	}

	//	aend --;
	//}


	MString s_curve_positions, s_curve_values;
	for (int i = 0; i < m_curve_values.length(); i++) // Create array of weight values
	{
		s_curve_values += MString() + m_curve_values[i];

		if (i != m_curve_values.length()-1) {
			s_curve_values += ",";
		}

	}


	for (int i = 0; i < m_curve_values.length(); i++) // Create array of position values
	{
		s_curve_positions += MString() + m_curve_positions[i];

		if (i != m_curve_positions.length()-1) {
			s_curve_positions += ",";
		}

	}

	s_curve_positions.asChar();




	MString s_path = s_pathName;
	s_pathName += s_presetName + ".smp";

	ofstream fout( s_pathName.asChar() );


	if(fout.is_open()) //Create file
	{

		MGlobal::displayInfo(MString() + "[ShellMod] Writing preset to disk: " + s_pathName);

		fout << s_presetName.asChar();
		fout << endl;
		fout << s_curve_positions.asChar();
		fout << endl;
		fout << s_curve_values.asChar();


	}


	else //file could not be opened
	{
		MGlobal::displayWarning(MString() + "[ShellMod] File could not be opened: " + s_pathName);
	}


	// Example MEL command:
	// shellModCommand -sp "test" -pp "/Users/hunyadijanos/Desktop/" -sm "shellModNode1";

}


// ----------------------



#endif