#include "CvtConfigGenerator.h"
#include "string"
#include "boost/filesystem.hpp"

CvtConfigGenerator::CvtConfigGenerator()
{
}

CvtConfigGenerator::CvtConfigGenerator(char* inputVideoName):m_inputVideoName(inputVideoName)
{
	getInfo();
	testGenerate(inputVideoName, m_width, m_height, 1);
	convertGenerate();
	batGenerate();
	runBatch();
}

void CvtConfigGenerator::convertGenerate(int width, int height) {

}

void CvtConfigGenerator::convertGenerate() {														//
	std::string dest[9] = { "ACP", "CISP", "CMP32", "COHP42", "EAC", "ECP", "our", "RSP", "TSP" };
	std::string shellDir = "C:\\VRTest\\sequence_cvt\\" + m_description + "\\shell";
	if (!boost::filesystem::exists(shellDir.c_str())) {
		boost::filesystem::create_directories(shellDir.c_str());
	}
	std::string erpShellDir = shellDir + "\\ERP.sh";
#pragma warning (disable : 4996)
	FILE* shellFile = fopen(erpShellDir.c_str(), "w");
	fprintf(shellFile, "#!/bin/bash\n");
	fprintf(shellFile, "for((i=1;i<10;++i))\n");
	fprintf(shellFile, "do\n");
	fprintf(shellFile, "	w=`expr %d \\* $i / 10`\n", m_width);
	fprintf(shellFile, "	h=`expr %d \\* $i / 10`\n", m_height);
	fprintf(shellFile, "	w1=`expr $w %% 8`\n");
	fprintf(shellFile, "	h1=`expr $h %% 8`\n");
	fprintf(shellFile, "	o=0\n");
	fprintf(shellFile, "	if [ \"$w1\" != $o ]\n");
	fprintf(shellFile, "	then \n");
	fprintf(shellFile, "		w=`expr 8 + $w / 8 \\* 8`\n");
	fprintf(shellFile, "	fi\n");
	fprintf(shellFile, "	if [ \"$h1\" != $o ]\n");
	fprintf(shellFile, "	then\n");
	fprintf(shellFile, "		h=`expr 8 + $h / 8 \\* 8`\n");
	fprintf(shellFile, "	fi\n");
	fprintf(shellFile, "	echo \"$w $h\"\n");
	fprintf(shellFile, "	pixel=${w}x${h}\n");
	fprintf(shellFile, "	echo \"$pixel\"\n");
	fprintf(shellFile, "	ffmpeg -f rawvideo -pix_fmt yuv420p -s:v %dx%d -r 30 -i ERP_%dx%d_30Hz_8b_420.yuv "
		"-s ${pixel} ERP_${pixel}_30Hz_8b_420.yuv \n", m_width, m_height, m_width, m_height );
	fprintf(shellFile, "done\n");
	fclose(shellFile);

	for (int i = 0; i < 9; ++i) {
		std::string cvtFileName = "360convert_ERP_" + dest[i] + "_test.cfg";
		std::string cvtOutputDir = "C:/VRTest/ERP_" + dest[i] + "/" + cvtFileName;
		std::string videoOutputDir = "C:\\VRTest\\sequence_cvt\\" + m_description;
		if (!boost::filesystem::exists(videoOutputDir.c_str())) {
			boost::filesystem::create_directories(videoOutputDir.c_str());
		}
#pragma warning (disable : 4996)
		FILE* file = fopen(cvtOutputDir.c_str(), "w");
		int width, height, h, w;
		width = height = h = w = 0;

		std::string acpShellDir;
		std::string cispShellDIr;
		std::string cmpShellDIr;
		std::string cohpShellDIr;
		std::string eacShellDIr;
		std::string ecpShellDir;
		std::string ourShellDir;
		std::string tspShellDir;

		switch (videoCommon.str2geo[dest[i]])
		{
		case VideoCommon::ACP:
			w = sqrt(m_height * m_width / 6);
			width = (w % 8) ? (8 + w / 8 * 8) : w;
			height = width;
			fprintf(file, "#======== File I/O =====================\n");
			fprintf(file, "OutputFile                    : C:\\VRTest\\sequence_cvt\\%s\\ACP.yuv\n", m_description.c_str());
			fprintf(file, "#RefFile                       : reference_file_name\n");
			fprintf(file, "#======== Unit definition ================\n");
			fprintf(file, "FaceSizeAlignment             : 1           # face size alignment;\n");
			fprintf(file, "\n");
			fprintf(file, "#=========== Misc. ============\n");
			fprintf(file, "InternalBitDepth              : 8          # codec operating bit-depth\n");
			fprintf(file, "\n");
			fprintf(file, "#============ 360 video settings ======================\n");
			fprintf(file, "InputGeometryType                 : 0                                   # 0: equirectangular; 1: cubemap; 2: equalarea; this should be in the cfg of per sequence.\n");
			fprintf(file, "SourceFPStructure                 : 1 1   0 0                           # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
			fprintf(file, "                                                                        # rotation degrees[0, 90, 180, 270] is anti-clockwise;\n");
			fprintf(file, "CodingGeometryType                : 9\n");
			fprintf(file, "CodingFPStructure                 : 2 3   4 0 0 0 5 0   3 180 1 270 2 0  # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
			fprintf(file, "                                                                        # rotation degrees[0, 90, 180] is anti-clockwise;\n");
			fprintf(file, "SVideoRotation                    : 0 0 0                               # rotation along X, Y, Z;                 \n");
			fprintf(file, "CodingFaceWidth                   : %d                                   # 0: automatic calculation;\n", width);
			fprintf(file, "CodingFaceHeight                  : %d                                   # 0: automatic calculation;\n", height);
			fprintf(file, "#ViewPortSettings                  : 80.0 80.0  -90.0  0.0               # view port settings: horizontal FOV [0,360], vertical FOV [0, 180], yaw [-180, 180], pitch [-90, 90]\n");
			fprintf(file, "SphFile                           : sphere_655362.txt\n");
			fprintf(file, "\n");
			fprintf(file, "### DO NOT ADD ANYTHING BELOW THIS LINE ###\n");
			fprintf(file, "### DO NOT DELETE THE EMPTY LINE BELOW ###\n");
			fprintf(file, "\n");
			fprintf(file, "\n");

			acpShellDir = shellDir + "\\ACP.sh";
			shellFile = fopen(acpShellDir.c_str(), "w");
			fprintf(shellFile, "#!/bin/bash\n");
			fprintf(shellFile, "for((i=1;i<10;++i))\n");
			fprintf(shellFile, "do\n");
			fprintf(shellFile, "	w=`expr %d \\* $i / 10`\n", width * 3);
			fprintf(shellFile, "	h=`expr %d \\* $i / 10`\n", height * 2);
			fprintf(shellFile, "	w1=`expr $w %% 8`\n");
			fprintf(shellFile, "	h1=`expr $h %% 8`\n");
			fprintf(shellFile, "	o=0\n");
			fprintf(shellFile, "	if [ \"$w1\" != $o ]\n");
			fprintf(shellFile, "	then \n");
			fprintf(shellFile, "		w=`expr 8 + $w / 8 \\* 8`\n");
			fprintf(shellFile, "	fi\n");
			fprintf(shellFile, "	if [ \"$h1\" != $o ]\n");
			fprintf(shellFile, "	then\n");
			fprintf(shellFile, "		h=`expr 8 + $h / 8 \\* 8`\n");
			fprintf(shellFile, "	fi\n");
			fprintf(shellFile, "	echo \"$w $h\"\n");
			fprintf(shellFile, "	pixel=${w}x${h}\n");
			fprintf(shellFile, "	echo \"$pixel\"\n");
			fprintf(shellFile, "	ffmpeg -f rawvideo -pix_fmt yuv420p -s:v %dx%d -r 30 -i ACP_%dx%d_30Hz_8b_420.yuv "
				"-s ${pixel} ACP_${pixel}_30Hz_8b_420.yuv \n", width * 3, height  * 2, width * 3, height * 2);
			fprintf(shellFile, "done\n");
			fclose(shellFile);
			break;
		case VideoCommon::CISP:
			h = sqrt(m_width * m_height * sqrt(3) / 20);
			w = sqrt(m_width * m_height / 5 / sqrt(3));
			width = (w % 8) ? (8 + w / 8 * 8) : w;
			height = (h % 8) ? (8 + h / 8 * 8) : h;
			fprintf(file, "#======== File I/O =====================\n");
			fprintf(file, "OutputFile                    : C:\\VRTest\\sequence_cvt\\%s\\CISP.yuv\n", m_description.c_str());
			fprintf(file, "\n");
			fprintf(file, "#======== Unit definition ================\n");
			fprintf(file, "FaceSizeAlignment             : 1           # face size alignment;\n");
			fprintf(file, "\n");
			fprintf(file, "#=========== Misc. ============\n");
			fprintf(file, "InternalBitDepth              : 8          # codec operating bit-depth\n");
			fprintf(file, "\n");
			fprintf(file, "#============ 360 video settings ======================\n");
			fprintf(file, "InputGeometryType                 : 0                                   # 0: equirectangular; 1: cubemap; 2: equalarea; this should be in the cfg of per sequence.\n");
			fprintf(file, "SourceFPStructure                 : 1 1   0 0                           # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
			fprintf(file, "                                                                        # rotation degrees[0, 90, 180, 270] is anti-clockwise;\n");
			fprintf(file, "CodingGeometryType                : 5\n");
			fprintf(file, "CodingFPStructure                 : 4 5   0 180 2 180 4 0 6 180 8 0   1 180 3 180 5 180 7 180 9 180    11 0 13 0 15 0 17 0 19 0   10 180 12 0 14 180 16 0 18 0      # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
			fprintf(file, "                                                                        # rotation degrees[0, 90, 180] is anti-clockwise;\n");
			fprintf(file, "CodingCompactFPStructure          : 1\n");
			fprintf(file, "\n");
			fprintf(file, "SVideoRotation                    : 0 0 0                               # rotation along X, Y, Z;                 \n");
			fprintf(file, "CodingFaceWidth                   : %d                                   # 0: automatic calculation;\n", width);
			fprintf(file, "CodingFaceHeight                  : %d                                   # 0: automatic calculation;\n", height);
			fprintf(file, "\n");
			fprintf(file, "### DO NOT ADD ANYTHING BELOW THIS LINE ###\n");
			fprintf(file, "### DO NOT DELETE THE EMPTY LINE BELOW ###\n");
			fprintf(file, "\n");
			fprintf(file, "\n");

			cispShellDIr = shellDir + "\\CISP.sh";
			shellFile = fopen(cispShellDIr.c_str(), "w");
			fprintf(shellFile, "#!/bin/bash\n");
			fprintf(shellFile, "for((i=1;i<10;++i))\n");
			fprintf(shellFile, "do\n");
			fprintf(shellFile, "	w=`expr REPLACE \\* $i / 10`\n");
			fprintf(shellFile, "	h=`expr REPLACE \\* $i / 10`\n");
			fprintf(shellFile, "	w1=`expr $w %% 8`\n");
			fprintf(shellFile, "	h1=`expr $h %% 8`\n");
			fprintf(shellFile, "	o=0\n");
			fprintf(shellFile, "	if [ \"$w1\" != $o ]\n");
			fprintf(shellFile, "	then \n");
			fprintf(shellFile, "		w=`expr 8 + $w / 8 \\* 8`\n");
			fprintf(shellFile, "	fi\n");
			fprintf(shellFile, "	if [ \"$h1\" != $o ]\n");
			fprintf(shellFile, "	then\n");
			fprintf(shellFile, "		h=`expr 8 + $h / 8 \\* 8`\n");
			fprintf(shellFile, "	fi\n");
			fprintf(shellFile, "	echo \"$w $h\"\n");
			fprintf(shellFile, "	pixel=${w}x${h}\n");
			fprintf(shellFile, "	echo \"$pixel\"\n");
			fprintf(shellFile, "	ffmpeg -f rawvideo -pix_fmt yuv420p -s:v REPLACExREPLACE -r 30 -i CISP_REPLACExREPLACE_30Hz_8b_420.yuv "
				"-s ${pixel} CISP_${pixel}_30Hz_8b_420.yuv \n");
			fprintf(shellFile, "done\n");
			fclose(shellFile);
			break;
		case VideoCommon::CMP32:
			w = sqrt(m_height * m_width / 6);
			width = (w % 8) ? (8 + w / 8 * 8) : w;
			height = width;
			fprintf(file, "#======== File I/O =====================\n");
			fprintf(file, "OutputFile                    : C:\\VRTest\\sequence_cvt\\%s\\CMP32.yuv\n", m_description.c_str());
			fprintf(file, "#RefFile                       : reference_file_name\n");
			fprintf(file, "#======== Unit definition ================\n");
			fprintf(file, "FaceSizeAlignment             : 1           # face size alignment;\n");
			fprintf(file, "\n");
			fprintf(file, "#=========== Misc. ============\n");
			fprintf(file, "InternalBitDepth              : 8          # codec operating bit-depth\n");
			fprintf(file, "\n");
			fprintf(file, "#============ 360 video settings ======================\n");
			fprintf(file, "InputGeometryType                 : 0                                   # 0: equirectangular; 1: cubemap; 2: equalarea; this should be in the cfg of per sequence.\n");
			fprintf(file, "SourceFPStructure                 : 1 1   0 0                           # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
			fprintf(file, "                                                                        # rotation degrees[0, 90, 180, 270] is anti-clockwise;\n");
			fprintf(file, "CodingGeometryType                : 1\n");
			fprintf(file, "CodingFPStructure                 : 2 3   4 0 0 0 5 0   3 180 1 270 2 0  # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
			fprintf(file, "                                                                        # rotation degrees[0, 90, 180] is anti-clockwise;\n");
			fprintf(file, "SVideoRotation                    : 0 0 0                               # rotation along X, Y, Z;                 \n");
			fprintf(file, "CodingFaceWidth                   : %d                                   # 0: automatic calculation;\n", width);
			fprintf(file, "CodingFaceHeight                  : %d                                   # 0: automatic calculation;\n", height);
			fprintf(file, "#ViewPortSettings                  : 80.0 80.0  -90.0  0.0               # view port settings: horizontal FOV [0,360], vertical FOV [0, 180], yaw [-180, 180], pitch [-90, 90]\n");
			fprintf(file, "SphFile                           : sphere_655362.txt\n");
			fprintf(file, "\n");
			fprintf(file, "### DO NOT ADD ANYTHING BELOW THIS LINE ###\n");
			fprintf(file, "### DO NOT DELETE THE EMPTY LINE BELOW ###\n");
			fprintf(file, "\n");
			fprintf(file, "\n");

			cmpShellDIr = shellDir + "\\CMP.sh";
			shellFile = fopen(cmpShellDIr.c_str(), "w");
			fprintf(shellFile, "#!/bin/bash\n");
			fprintf(shellFile, "for((i=1;i<10;++i))\n");
			fprintf(shellFile, "do\n");
			fprintf(shellFile, "	w=`expr %d \\* $i / 10`\n", width * 3);
			fprintf(shellFile, "	h=`expr %d \\* $i / 10`\n", height * 2);
			fprintf(shellFile, "	w1=`expr $w %% 8`\n");
			fprintf(shellFile, "	h1=`expr $h %% 8`\n");
			fprintf(shellFile, "	o=0\n");
			fprintf(shellFile, "	if [ \"$w1\" != $o ]\n");
			fprintf(shellFile, "	then \n");
			fprintf(shellFile, "		w=`expr 8 + $w / 8 \\* 8`\n");
			fprintf(shellFile, "	fi\n");
			fprintf(shellFile, "	if [ \"$h1\" != $o ]\n");
			fprintf(shellFile, "	then\n");
			fprintf(shellFile, "		h=`expr 8 + $h / 8 \\* 8`\n");
			fprintf(shellFile, "	fi\n");
			fprintf(shellFile, "	echo \"$w $h\"\n");
			fprintf(shellFile, "	pixel=${w}x${h}\n");
			fprintf(shellFile, "	echo \"$pixel\"\n");
			fprintf(shellFile, "	ffmpeg -f rawvideo -pix_fmt yuv420p -s:v %dx%d -r 30 -i CMP32_%dx%d_30Hz_8b_420.yuv "
				"-s ${pixel} CMP32_${pixel}_30Hz_8b_420.yuv \n", width * 3, height * 2, width * 3, height * 2);
			fprintf(shellFile, "done\n");
			fclose(shellFile);
			break;
		case VideoCommon::COHP42:
			h = sqrt(m_width * m_height * sqrt(3) / 8);
			w = sqrt(m_width * m_height / 2 / sqrt(3));
			width = (w % 8) ? (8 + w / 8 * 8) : w;
			height = (h % 8) ? (8 + h / 8 * 8) : h;
			fprintf(file, "#======== File I/O =====================\n");
			fprintf(file, "OutputFile                    : C:\\VRTest\\sequence_cvt\\%s\\COHP42.yuv\n", m_description.c_str());
			fprintf(file, "\n");
			fprintf(file, "#======== Unit definition ================\n");
			fprintf(file, "FaceSizeAlignment             : 1           # face size alignment;\n");
			fprintf(file, "\n");
			fprintf(file, "#=========== Misc. ============\n");
			fprintf(file, "InternalBitDepth              : 8          # codec operating bit-depth\n");
			fprintf(file, "\n");
			fprintf(file, "#============ 360 video settings ======================\n");
			fprintf(file, "InputGeometryType                 : 0                                   # 0: equirectangular; 1: cubemap; 2: equalarea; this should be in the cfg of per sequence.\n");
			fprintf(file, "SourceFPStructure                 : 1 1   0 0                           # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
			fprintf(file, "                                                                        # rotation degrees[0, 90, 180, 270] is anti-clockwise;\n");
			fprintf(file, "CodingGeometryType                : 3\n");
			fprintf(file, "CodingFPStructure                 : 4 2   2 270  3 90  6 90  7 270  0 270  1 90  4 90  5 270    # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
			fprintf(file, "                                                                        # rotation degrees[0, 90, 180] is anti-clockwise;\n");
			fprintf(file, "CodingCompactFPStructure          : 1\n");
			fprintf(file, "\n");
			fprintf(file, "\n");
			fprintf(file, "SVideoRotation                    : 0 0 0                               # rotation along X, Y, Z;                 \n");
			fprintf(file, "CodingFaceWidth                   : %d                                   # 0: automatic calculation;\n", width);
			fprintf(file, "CodingFaceHeight                  : %d  \n", height);
			fprintf(file, "\n");
			fprintf(file, "### DO NOT ADD ANYTHING BELOW THIS LINE ###\n");
			fprintf(file, "### DO NOT DELETE THE EMPTY LINE BELOW ###\n");
			fprintf(file, "\n");
			fprintf(file, "\n");

			cohpShellDIr = shellDir + "\\COHP.sh";
			shellFile = fopen(cohpShellDIr.c_str(), "w");
			fprintf(shellFile, "#!/bin/bash\n");
			fprintf(shellFile, "for((i=1;i<10;++i))\n");
			fprintf(shellFile, "do\n");
			fprintf(shellFile, "	w=`expr REPLACE \\* $i / 10`\n");
			fprintf(shellFile, "	h=`expr REPLACE \\* $i / 10`\n");
			fprintf(shellFile, "	w1=`expr $w %% 8`\n");
			fprintf(shellFile, "	h1=`expr $h %% 8`\n");
			fprintf(shellFile, "	o=0\n");
			fprintf(shellFile, "	if [ \"$w1\" != $o ]\n");
			fprintf(shellFile, "	then \n");
			fprintf(shellFile, "		w=`expr 8 + $w / 8 \\* 8`\n");
			fprintf(shellFile, "	fi\n");
			fprintf(shellFile, "	if [ \"$h1\" != $o ]\n");
			fprintf(shellFile, "	then\n");
			fprintf(shellFile, "		h=`expr 8 + $h / 8 \\* 8`\n");
			fprintf(shellFile, "	fi\n");
			fprintf(shellFile, "	echo \"$w $h\"\n");
			fprintf(shellFile, "	pixel=${w}x${h}\n");
			fprintf(shellFile, "	echo \"$pixel\"\n");
			fprintf(shellFile, "	ffmpeg -f rawvideo -pix_fmt yuv420p -s:v REPLACExREPLACE -r 30 -i COHP42_REPLACExREPLACE_30Hz_8b_420.yuv "
				"-s ${pixel} COHP42_${pixel}_30Hz_8b_420.yuv \n");
			fprintf(shellFile, "done\n");
			fclose(shellFile);
			break;
		case VideoCommon::EAC:
			w = sqrt(m_height * m_width / 6);
			width = (w % 8) ? (8 + w / 8 * 8) : w;
			height = width;
			fprintf(file, "#======== File I/O =====================\n");
			fprintf(file, "OutputFile                    : C:\\VRTest\\sequence_cvt\\%s\\EAC.yuv\n", m_description.c_str());
			fprintf(file, "#RefFile                       : reference_file_name\n");
			fprintf(file, "#======== Unit definition ================\n");
			fprintf(file, "FaceSizeAlignment             : 1           # face size alignment;\n");
			fprintf(file, "\n");
			fprintf(file, "#=========== Misc. ============\n");
			fprintf(file, "InternalBitDepth              : 8          # codec operating bit-depth\n");
			fprintf(file, "\n");
			fprintf(file, "#============ 360 video settings ======================\n");
			fprintf(file, "InputGeometryType                 : 0                                   # 0: equirectangular; 1: cubemap; 2: equalarea; this should be in the cfg of per sequence.\n");
			fprintf(file, "SourceFPStructure                 : 1 1   0 0                           # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
			fprintf(file, "                                                                        # rotation degrees[0, 90, 180, 270] is anti-clockwise;\n");
			fprintf(file, "CodingGeometryType                : 12\n");
			fprintf(file, "CodingFPStructure                 : 2 3   4 0 0 0 5 0   3 180 1 270 2 0  # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
			fprintf(file, "                                                                        # rotation degrees[0, 90, 180] is anti-clockwise;\n");
			fprintf(file, "SVideoRotation                    : 0 0 0                               # rotation along X, Y, Z;                 \n");
			fprintf(file, "CodingFaceWidth                   : %d                                   # 0: automatic calculation;\n", width);
			fprintf(file, "CodingFaceHeight                  : %d                                   # 0: automatic calculation;\n", height);
			fprintf(file, "#ViewPortSettings                  : 80.0 80.0  -90.0  0.0               # view port settings: horizontal FOV [0,360], vertical FOV [0, 180], yaw [-180, 180], pitch [-90, 90]\n");
			fprintf(file, "SphFile                           : sphere_655362.txt\n");
			fprintf(file, "\n");
			fprintf(file, "### DO NOT ADD ANYTHING BELOW THIS LINE ###\n");
			fprintf(file, "### DO NOT DELETE THE EMPTY LINE BELOW ###\n");
			fprintf(file, "\n");
			fprintf(file, "\n");

			eacShellDIr = shellDir + "\\EAC.sh";
			shellFile = fopen(eacShellDIr.c_str(), "w");
			fprintf(shellFile, "#!/bin/bash\n");
			fprintf(shellFile, "for((i=1;i<10;++i))\n");
			fprintf(shellFile, "do\n");
			fprintf(shellFile, "	w=`expr %d \\* $i / 10`\n", width * 3);
			fprintf(shellFile, "	h=`expr %d \\* $i / 10`\n", height * 2);
			fprintf(shellFile, "	w1=`expr $w %% 8`\n");
			fprintf(shellFile, "	h1=`expr $h %% 8`\n");
			fprintf(shellFile, "	o=0\n");
			fprintf(shellFile, "	if [ \"$w1\" != $o ]\n");
			fprintf(shellFile, "	then \n");
			fprintf(shellFile, "		w=`expr 8 + $w / 8 \\* 8`\n");
			fprintf(shellFile, "	fi\n");
			fprintf(shellFile, "	if [ \"$h1\" != $o ]\n");
			fprintf(shellFile, "	then\n");
			fprintf(shellFile, "		h=`expr 8 + $h / 8 \\* 8`\n");
			fprintf(shellFile, "	fi\n");
			fprintf(shellFile, "	echo \"$w $h\"\n");
			fprintf(shellFile, "	pixel=${w}x${h}\n");
			fprintf(shellFile, "	echo \"$pixel\"\n");
			fprintf(shellFile, "	ffmpeg -f rawvideo -pix_fmt yuv420p -s:v %dx%d -r 30 -i EAC_%dx%d_30Hz_8b_420.yuv "
				"-s ${pixel} EAC_${pixel}_30Hz_8b_420.yuv \n", width * 3, height * 2, width * 3, height * 2);
			fprintf(shellFile, "done\n");
			fclose(shellFile);
			break;
		case VideoCommon::ECP:
			w = sqrt(m_height * m_width / 6);
			width = (w % 8) ? (8 + w / 8 * 8) : w;
			height = width;
			fprintf(file, "#======== File I/O =====================\n");
			fprintf(file, "OutputFile                    : C:\\VRTest\\sequence_cvt\\%s\\ECP.yuv\n", m_description.c_str());
			fprintf(file, "#RefFile                       : reference_file_name\n");
			fprintf(file, "#======== Unit definition ================\n");
			fprintf(file, "FaceSizeAlignment             : 1           # face size alignment;\n");
			fprintf(file, "\n");
			fprintf(file, "#=========== Misc. ============\n");
			fprintf(file, "InternalBitDepth              : 8          # codec operating bit-depth\n");
			fprintf(file, "\n");
			fprintf(file, "#============ 360 video settings ======================\n");
			fprintf(file, "InputGeometryType                 : 0                                   # 0: equirectangular; 1: cubemap; 2: equalarea; this should be in the cfg of per sequence.\n");
			fprintf(file, "SourceFPStructure                 : 1 1   0 0                           # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
			fprintf(file, "                                                                        # rotation degrees[0, 90, 180, 270] is anti-clockwise;\n");
			fprintf(file, "CodingGeometryType                : 11\n");
			fprintf(file, "CodingFPStructure                 : 2 3   2 0 3 0 4 0 1 90 5 270 0 90  # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
			fprintf(file, "                                                                        # rotation degrees[0, 90, 180] is anti-clockwise;\n");
			fprintf(file, "SVideoRotation                    : 0 0 0                               # rotation along X, Y, Z;                 \n");
			fprintf(file, "CodingFaceWidth                   : %d                                   # 0: automatic calculation;\n", width);
			fprintf(file, "CodingFaceHeight                  : %d                                   # 0: automatic calculation;\n", height);
			fprintf(file, "#ViewPortSettings                  : 80.0 80.0  -90.0  0.0               # view port settings: horizontal FOV [0,360], vertical FOV [0, 180], yaw [-180, 180], pitch [-90, 90]\n");
			fprintf(file, "SphFile                           : sphere_655362.txt\n");
			fprintf(file, "\n");
			fprintf(file, "### DO NOT ADD ANYTHING BELOW THIS LINE ###\n");
			fprintf(file, "### DO NOT DELETE THE EMPTY LINE BELOW ###\n");
			fprintf(file, "\n");
			fprintf(file, "\n");

			ecpShellDir = shellDir + "\\ECP.sh";
			shellFile = fopen(ecpShellDir.c_str(), "w");
			fprintf(shellFile, "#!/bin/bash\n");
			fprintf(shellFile, "for((i=1;i<10;++i))\n");
			fprintf(shellFile, "do\n");
			fprintf(shellFile, "	w=`expr %d \\* $i / 10`\n", width * 3);
			fprintf(shellFile, "	h=`expr %d \\* $i / 10`\n", height * 2);
			fprintf(shellFile, "	w1=`expr $w %% 8`\n");
			fprintf(shellFile, "	h1=`expr $h %% 8`\n");
			fprintf(shellFile, "	o=0\n");
			fprintf(shellFile, "	if [ \"$w1\" != $o ]\n");
			fprintf(shellFile, "	then \n");
			fprintf(shellFile, "		w=`expr 8 + $w / 8 \\* 8`\n");
			fprintf(shellFile, "	fi\n");
			fprintf(shellFile, "	if [ \"$h1\" != $o ]\n");
			fprintf(shellFile, "	then\n");
			fprintf(shellFile, "		h=`expr 8 + $h / 8 \\* 8`\n");
			fprintf(shellFile, "	fi\n");
			fprintf(shellFile, "	echo \"$w $h\"\n");
			fprintf(shellFile, "	pixel=${w}x${h}\n");
			fprintf(shellFile, "	echo \"$pixel\"\n");
			fprintf(shellFile, "	ffmpeg -f rawvideo -pix_fmt yuv420p -s:v %dx%d -r 30 -i ECP_%dx%d_30Hz_8b_420.yuv "
				"-s ${pixel} ECP_${pixel}_30Hz_8b_420.yuv \n", width * 3, height * 2, width * 3, height * 2);
			fprintf(shellFile, "done\n");
			fclose(shellFile);
			break;
		case VideoCommon::our:
			fprintf(file, "#======== File I/O =====================\n");
			fprintf(file, "OutputFile                    : C:\\VRTest\\sequence_cvt\\%s\\our.yuv\n", m_description.c_str());
			fprintf(file, "#RefFile                       : reference_file_name\n");
			fprintf(file, "\n");
			fprintf(file, "#======== Unit definition ================\n");
			fprintf(file, "FaceSizeAlignment             : 1           # face size alignment;\n");
			fprintf(file, "\n");
			fprintf(file, "#=========== Misc. ============\n");
			fprintf(file, "InternalBitDepth              : 8          # codec operating bit-depth\n");
			fprintf(file, "\n");
			fprintf(file, "#============ 360 video settings ======================\n");
			fprintf(file, "InputGeometryType                 : 0                                   # 0: equirectangular; 1: cubemap; 2: equalarea; this should be in the cfg of per sequence.\n");
			fprintf(file, "SourceFPStructure                 : 1 1   0 0                           # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
			fprintf(file, "                                                                        # rotation degrees[0, 90, 180, 270] is anti-clockwise;\n");
			fprintf(file, "CodingGeometryType                : 13\n");
			fprintf(file, "CodingFPStructure                 : 1 1   0 0                           # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
			fprintf(file, "                                                                        # rotation degrees[0, 90, 180] is anti-clockwise;\n");
			fprintf(file, "SVideoRotation                    : 0 0 0                               # rotation along X, Y, Z;                 \n");
			fprintf(file, "CodingFaceWidth                   : %d                                   # 0: automatic calculation;\n", m_width);
			fprintf(file, "CodingFaceHeight                  : %d                                   # 0: automatic calculation;\n", m_height);
			fprintf(file, "\n");
			fprintf(file, "SphFile                           : sphere_655362.txt\n");
			fprintf(file, "\n");
			fprintf(file, "\n");
			fprintf(file, "### DO NOT ADD ANYTHING BELOW THIS LINE ###\n");
			fprintf(file, "### DO NOT DELETE THE EMPTY LINE BELOW ###\n");
			fprintf(file, "\n");
			fprintf(file, "\n");

			ourShellDir = shellDir + "\\OUR.sh";
			shellFile = fopen(ourShellDir.c_str(), "w");
			fprintf(shellFile, "#!/bin/bash\n");
			fprintf(shellFile, "for((i=1;i<10;++i))\n");
			fprintf(shellFile, "do\n");
			fprintf(shellFile, "	w=`expr %d \\* $i / 10`\n", m_width);
			fprintf(shellFile, "	h=`expr %d \\* $i / 10`\n", m_height);
			fprintf(shellFile, "	w1=`expr $w %% 8`\n");
			fprintf(shellFile, "	h1=`expr $h %% 8`\n");
			fprintf(shellFile, "	o=0\n");
			fprintf(shellFile, "	if [ \"$w1\" != $o ]\n");
			fprintf(shellFile, "	then \n");
			fprintf(shellFile, "		w=`expr 8 + $w / 8 \\* 8`\n");
			fprintf(shellFile, "	fi\n");
			fprintf(shellFile, "	if [ \"$h1\" != $o ]\n");
			fprintf(shellFile, "	then\n");
			fprintf(shellFile, "		h=`expr 8 + $h / 8 \\* 8`\n");
			fprintf(shellFile, "	fi\n");
			fprintf(shellFile, "	echo \"$w $h\"\n");
			fprintf(shellFile, "	pixel=${w}x${h}\n");
			fprintf(shellFile, "	echo \"$pixel\"\n");
			fprintf(shellFile, "	ffmpeg -f rawvideo -pix_fmt yuv420p -s:v %dx%d -r 30 -i our_%dx%d_30Hz_8b_420.yuv "
				"-s ${pixel} our_${pixel}_30Hz_8b_420.yuv \n", m_width, m_height, m_width, m_height);
			fprintf(shellFile, "done\n");
			fclose(shellFile);
			break;
		case VideoCommon::RSP:
			w = sqrt(m_height * m_width / 6);
			width = (w % 8) ? (8 + w / 8 * 8) : w;
			height = width;
			fprintf(file, "#======== File I/O =====================\n");
			fprintf(file, "OutputFile                    : C:\\VRTest\\sequence_cvt\\%s\\RSP.yuv\n", m_description.c_str());
			fprintf(file, "#RefFile                       : reference_file_name\n");
			fprintf(file, "#======== Unit definition ================\n");
			fprintf(file, "FaceSizeAlignment             : 1           # face size alignment;\n");
			fprintf(file, "\n");
			fprintf(file, "#=========== Misc. ============\n");
			fprintf(file, "InternalBitDepth              : 8          # codec operating bit-depth\n");
			fprintf(file, "\n");
			fprintf(file, "#============ 360 video settings ======================\n");
			fprintf(file, "InputGeometryType                 : 0                                   # 0: equirectangular; 1: cubemap; 2: equalarea; this should be in the cfg of per sequence.\n");
			fprintf(file, "SourceFPStructure                 : 1 1   0 0                           # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
			fprintf(file, "                                                                        # rotation degrees[0, 90, 180, 270] is anti-clockwise;\n");
			fprintf(file, "CodingGeometryType                : 10\n");
			fprintf(file, "CodingFPStructure                 : 2 3   4 0 0 0 5 0   3 0 1 0 2 0  # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
			fprintf(file, "                                                                        # rotation degrees[0, 90, 180] is anti-clockwise;\n");
			fprintf(file, "SVideoRotation                    : 0 0 0                               # rotation along X, Y, Z;                 \n");
			fprintf(file, "CodingFaceWidth                   : %d                                   # 0: automatic calculation;\n", width);
			fprintf(file, "CodingFaceHeight                  : %d                                   # 0: automatic calculation;\n", height);
			fprintf(file, "#ViewPortSettings                  : 80.0 80.0  -90.0  0.0               # view port settings: horizontal FOV [0,360], vertical FOV [0, 180], yaw [-180, 180], pitch [-90, 90]\n");
			fprintf(file, "SphFile                           : sphere_655362.txt\n");
			fprintf(file, "\n");
			fprintf(file, "### DO NOT ADD ANYTHING BELOW THIS LINE ###\n");
			fprintf(file, "### DO NOT DELETE THE EMPTY LINE BELOW ###\n");
			fprintf(file, "\n");
			fprintf(file, "\n");
			break;
		case VideoCommon::TSP:
			h =  sqrt(m_height * m_width / 2);
			width = (h % 8) ? (8 + h / 8 * 8) : h;
			height = width;
			fprintf(file, "#======== File I/O =====================\n");
			fprintf(file, "OutputFile                    : C:\\VRTest\\sequence_cvt\\%s\\TSP.yuv\n", m_description.c_str());
			fprintf(file, "#RefFile                       : reference_file_name\n");
			fprintf(file, "#======== Unit definition ================\n");
			fprintf(file, "FaceSizeAlignment             : 1           # face size alignment;\n");
			fprintf(file, "\n");
			fprintf(file, "#=========== Misc. ============\n");
			fprintf(file, "InternalBitDepth              : 8          # codec operating bit-depth\n");
			fprintf(file, "\n");
			fprintf(file, "#============ 360 video settings ======================\n");
			fprintf(file, "InputGeometryType                 : 0                                   # 0: equirectangular; 1: cubemap; 2: equalarea; this should be in the cfg of per sequence.\n");
			fprintf(file, "SourceFPStructure                 : 1 1   0 0                           # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
			fprintf(file, "                                                                        # rotation degrees[0, 90, 180, 270] is anti-clockwise;\n");
			fprintf(file, "CodingGeometryType                : 7\n");
			fprintf(file, "CodingFPStructure                 : 1 2   0 0 1 0                       # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
			fprintf(file, "                                                                        # rotation degrees[0, 90, 180] is anti-clockwise;\n");
			fprintf(file, "SVideoRotation                    : 0 0 0                               # rotation along X, Y, Z;                 \n");
			fprintf(file, "CodingFaceWidth                   : %d                                   # 0: automatic calculation;\n", width);
			fprintf(file, "CodingFaceHeight                  : %d                                   # 0: automatic calculation;\n", height);
			fprintf(file, "#ViewPortSettings                  : 80.0 80.0  -90.0  0.0               # view port settings: horizontal FOV [0,360], vertical FOV [0, 180], yaw [-180, 180], pitch [-90, 90]\n");
			fprintf(file, "#SphFile                           : sphere_655362.txt\n");
			fprintf(file, "\n");
			fprintf(file, "### DO NOT ADD ANYTHING BELOW THIS LINE ###\n");
			fprintf(file, "### DO NOT DELETE THE EMPTY LINE BELOW ###\n");
			fprintf(file, "\n");
			fprintf(file, "\n");

			tspShellDir = shellDir + "\\TSP.sh";
			shellFile = fopen(tspShellDir.c_str(), "w");
			fprintf(shellFile, "#!/bin/bash\n");
			fprintf(shellFile, "for((i=1;i<10;++i))\n");
			fprintf(shellFile, "do\n");
			fprintf(shellFile, "	w=`expr %d \\* $i / 10`\n", width * 2);
			fprintf(shellFile, "	h=`expr %d \\* $i / 10`\n", height);
			fprintf(shellFile, "	w1=`expr $w %% 8`\n");
			fprintf(shellFile, "	h1=`expr $h %% 8`\n");
			fprintf(shellFile, "	o=0\n");
			fprintf(shellFile, "	if [ \"$w1\" != $o ]\n");
			fprintf(shellFile, "	then \n");
			fprintf(shellFile, "		w=`expr 8 + $w / 8 \\* 8`\n");
			fprintf(shellFile, "	fi\n");
			fprintf(shellFile, "	if [ \"$h1\" != $o ]\n");
			fprintf(shellFile, "	then\n");
			fprintf(shellFile, "		h=`expr 8 + $h / 8 \\* 8`\n");
			fprintf(shellFile, "	fi\n");
			fprintf(shellFile, "	echo \"$w $h\"\n");
			fprintf(shellFile, "	pixel=${w}x${h}\n");
			fprintf(shellFile, "	echo \"$pixel\"\n");
			fprintf(shellFile, "	ffmpeg -f rawvideo -pix_fmt yuv420p -s:v %dx%d -r 30 -i TSP_%dx%d_30Hz_8b_420.yuv "
				"-s ${pixel} TSP_${pixel}_30Hz_8b_420.yuv \n", width * 2, height, width * 2, height);
			fprintf(shellFile, "done\n");
			fclose(shellFile);
			break;
		}		
		fclose(file);
	}
}

void CvtConfigGenerator::testGenerate(char* inputVideoName, int width, int height, int frameSize) {
	std::string dest[9] = {"ACP", "CISP", "CMP32", "COHP42", "EAC", "ECP", "our", "RSP", "TSP"};
	for (int i = 0; i < 9; ++i) {
		std::string outputName = "360test_test_sequence.cfg";
		std::string outputDir = "C:/VRTest/ERP_" + dest[i];
		if (!boost::filesystem::exists(outputDir)) {
			boost::filesystem::create_directories(outputDir);
		}
		outputDir = outputDir + "/" + outputName;
#pragma warning (disable : 4996)
		FILE *file = fopen(outputDir.c_str(), "w");
		fprintf(file, "#======== File I/O ===============\n");
		fprintf(file, "InputFile                     : C:\\VRTest\\sequence\\%s\n", inputVideoName);
		fprintf(file, "InputBitDepth                 : 8           # Input bitdepth\n");
		fprintf(file, "InputChromaFormat             : 420         # Ratio of luminance to chrominance samples\n");
		fprintf(file, "FrameRate                     : 30          # Frame Rate per second\n");
		fprintf(file, "FrameSkip                     : 0           # Number of frames to be skipped in input\n");
		fprintf(file, "SourceWidth                   : %d         # Input  frame width\n", width);
		fprintf(file, "SourceHeight                  : %d          # Input  frame height\n", height);
		fprintf(file, "FramesToBeEncoded             : %d         # Number of frames to be \n", frameSize);
		fprintf(file, "\n");
		fprintf(file, "#Level                         : 5.2\n");
		fprintf(file, "\n");
		fclose(file);
	}
}

void CvtConfigGenerator::batGenerate() {
	std::string dest[9] = { "ACP", "CISP", "CMP32", "COHP42", "EAC", "ECP", "our", "RSP", "TSP" };
	for (int i = 0; i < 9; ++i) {
		std::string outputDir = "C:/VRTest/ERP_" + dest[i];
		outputDir = outputDir + "/" + dest[i] + "_" + m_resolution + ".bat";
#pragma warning (disable : 4996)
		FILE *file = fopen(outputDir.c_str(), "w");
		fprintf(file, "C:\\hm-360lib\\HM-16.16\\bin\\vc2015\\x64\\Debug\\Test\\convert\\TApp360Convert.exe -c C:\\VRTest\\ERP_%s\\360convert_ERP_%s_test.cfg -c C:\\VRTest\\ERP_%s\\360test_test_sequence.cfg", dest[i].c_str(), dest[i].c_str(), dest[i].c_str());
		fclose(file);
	}
}

void CvtConfigGenerator::runBatch() {
	std::string dest[9] = { "ACP", "CISP", "CMP32", "COHP42", "EAC", "ECP", "our", "RSP", "TSP" };
	for (int i = 0; i < 9; ++i) {
		std::string outputDir = "C://VRTest//ERP_" + dest[i];
		outputDir = outputDir + "//" + dest[i] + "_" + m_resolution + ".bat";
		system(outputDir.c_str());
	}
}

void CvtConfigGenerator::getInfo()
{
	videoCommon.initialCommon();
	int head = m_inputVideoName.find("_") + 1;
	int tail = m_inputVideoName.find("_", head + 1);//TODO.
	m_resolution = m_inputVideoName.substr(head, tail - head);
	int block = m_inputVideoName.find("x");
	m_width = std::atoi(m_inputVideoName.substr(head, block).c_str());
	m_height = std::atoi(m_inputVideoName.substr(block + 1, tail - block).c_str());
	m_description = m_inputVideoName.substr(0, head - 1);
}

CvtConfigGenerator::~CvtConfigGenerator()
{
}

void CvtConfigGenerator::shellGenerate() {
}


