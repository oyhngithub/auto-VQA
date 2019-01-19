#include "CvtConfigGenerator.h"
#include "string"
#include "boost/filesystem.hpp"

CvtConfigGenerator::CvtConfigGenerator()
{
}

CvtConfigGenerator::CvtConfigGenerator(char* inputVideoName)
{
	videoCommon.initialCommon();
	m_inputVideoName = inputVideoName;
	int head = m_inputVideoName.find("_") + 1;
	int tail = m_inputVideoName.find("_", head + 1);//TODO.
	m_resolution = m_inputVideoName.substr(head, tail - head);
	int block = m_inputVideoName.find("x");
	m_width = std::atoi(m_inputVideoName.substr(head, block).c_str());
	m_height = std::atoi(m_inputVideoName.substr(block + 1, tail - block).c_str());

	testGenerate(inputVideoName, m_width, m_height, 1);
	convertGenerate();
	batGenerate();
	runBatch();
}

void CvtConfigGenerator::convertGenerate(int width, int height) {

}

void CvtConfigGenerator::convertGenerate() {
	std::string dest[9] = { "ACP", "CISP", "CMP32", "COHP42", "EAC", "ECP", "our", "RSP", "TSP" };

	for (int i = 0; i < 9; ++i) {
		m_cvtName = "360convert_ERP_" + dest[i] + "_test.cfg";
		std::string fileName = "360convert_ERP_" + dest[i] + "_test.cfg";
		std::string outputDir = "C:/VRTest/ERP_" + dest[i] + "/" + fileName;
#pragma warning (disable : 4996)
		FILE* file = fopen(outputDir.c_str(), "w");
		switch (videoCommon.str2geo[dest[i]])
		{
		case VideoCommon::ACP:
			fprintf(file, "#======== File I/O =====================\n");
			fprintf(file, "OutputFile                    : C:\\VRTest\\sequence_cvt\\ACP.yuv\n");
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
			fprintf(file, "CodingFaceWidth                   : 0                                   # 0: automatic calculation;\n");
			fprintf(file, "CodingFaceHeight                  : 0                                   # 0: automatic calculation;\n");
			fprintf(file, "#ViewPortSettings                  : 80.0 80.0  -90.0  0.0               # view port settings: horizontal FOV [0,360], vertical FOV [0, 180], yaw [-180, 180], pitch [-90, 90]\n");
			fprintf(file, "SphFile                           : sphere_655362.txt\n");
			fprintf(file, "\n");
			fprintf(file, "### DO NOT ADD ANYTHING BELOW THIS LINE ###\n");
			fprintf(file, "### DO NOT DELETE THE EMPTY LINE BELOW ###\n");
			fprintf(file, "\n");
			fprintf(file, "\n");
			break;
		case VideoCommon::CISP:
			fprintf(file, "#======== File I/O =====================\n");
			fprintf(file, "OutputFile                    : C:\\VRTest\\sequence_cvt\\CISP.yuv\n");
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
			fprintf(file, "CodingFaceWidth                   : 0                                   # 0: automatic calculation;\n");
			fprintf(file, "CodingFaceHeight                  : 0                                   # 0: automatic calculation;\n");
			fprintf(file, "\n");
			fprintf(file, "### DO NOT ADD ANYTHING BELOW THIS LINE ###\n");
			fprintf(file, "### DO NOT DELETE THE EMPTY LINE BELOW ###\n");
			fprintf(file, "\n");
			fprintf(file, "\n");
			break;
		case VideoCommon::CMP32:
			fprintf(file, "#======== File I/O =====================\n");
			fprintf(file, "OutputFile                    : C:\\VRTest\\sequence_cvt\\CMP32.yuv\n");
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
			fprintf(file, "CodingFaceWidth                   : 0                                   # 0: automatic calculation;\n");
			fprintf(file, "CodingFaceHeight                  : 0                                   # 0: automatic calculation;\n");
			fprintf(file, "#ViewPortSettings                  : 80.0 80.0  -90.0  0.0               # view port settings: horizontal FOV [0,360], vertical FOV [0, 180], yaw [-180, 180], pitch [-90, 90]\n");
			fprintf(file, "SphFile                           : sphere_655362.txt\n");
			fprintf(file, "\n");
			fprintf(file, "### DO NOT ADD ANYTHING BELOW THIS LINE ###\n");
			fprintf(file, "### DO NOT DELETE THE EMPTY LINE BELOW ###\n");
			fprintf(file, "\n");
			fprintf(file, "\n");
			break;
		case VideoCommon::COHP42:
			fprintf(file, "#======== File I/O =====================\n");
			fprintf(file, "OutputFile                    : C:\\VRTest\\sequence_cvt\\COHP42.yuv\n");
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
			fprintf(file, "CodingFaceWidth                   : 0                                   # 0: automatic calculation;\n");
			fprintf(file, "CodingFaceHeight                  : 0  \n");
			fprintf(file, "\n");
			fprintf(file, "### DO NOT ADD ANYTHING BELOW THIS LINE ###\n");
			fprintf(file, "### DO NOT DELETE THE EMPTY LINE BELOW ###\n");
			fprintf(file, "\n");
			fprintf(file, "\n");
			break;
		case VideoCommon::EAC:
			fprintf(file, "#======== File I/O =====================\n");
			fprintf(file, "OutputFile                    : C:\\VRTest\\sequence_cvt\\EAC.yuv\n");
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
			fprintf(file, "CodingFaceWidth                   : 0                                   # 0: automatic calculation;\n");
			fprintf(file, "CodingFaceHeight                  : 0                                   # 0: automatic calculation;\n");
			fprintf(file, "#ViewPortSettings                  : 80.0 80.0  -90.0  0.0               # view port settings: horizontal FOV [0,360], vertical FOV [0, 180], yaw [-180, 180], pitch [-90, 90]\n");
			fprintf(file, "SphFile                           : sphere_655362.txt\n");
			fprintf(file, "\n");
			fprintf(file, "### DO NOT ADD ANYTHING BELOW THIS LINE ###\n");
			fprintf(file, "### DO NOT DELETE THE EMPTY LINE BELOW ###\n");
			fprintf(file, "\n");
			fprintf(file, "\n");
			break;
		case VideoCommon::ECP:
			fprintf(file, "#======== File I/O =====================\n");
			fprintf(file, "OutputFile                    : C:\\VRTest\\sequence_cvt\\ECP.yuv\n");
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
			fprintf(file, "CodingFaceWidth                   : 0                                   # 0: automatic calculation;\n");
			fprintf(file, "CodingFaceHeight                  : 0                                   # 0: automatic calculation;\n");
			fprintf(file, "#ViewPortSettings                  : 80.0 80.0  -90.0  0.0               # view port settings: horizontal FOV [0,360], vertical FOV [0, 180], yaw [-180, 180], pitch [-90, 90]\n");
			fprintf(file, "SphFile                           : sphere_655362.txt\n");
			fprintf(file, "\n");
			fprintf(file, "### DO NOT ADD ANYTHING BELOW THIS LINE ###\n");
			fprintf(file, "### DO NOT DELETE THE EMPTY LINE BELOW ###\n");
			fprintf(file, "\n");
			fprintf(file, "\n");
			break;
		case VideoCommon::our:
			fprintf(file, "#======== File I/O =====================\n");
			fprintf(file, "OutputFile                    : C:\\VRTest\\sequence_cvt\\our.yuv\n");
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
			fprintf(file, "CodingFaceWidth                   : 0                                   # 0: automatic calculation;\n");
			fprintf(file, "CodingFaceHeight                  : 0                                   # 0: automatic calculation;\n");
			fprintf(file, "\n");
			fprintf(file, "SphFile                           : sphere_655362.txt\n");
			fprintf(file, "\n");
			fprintf(file, "\n");
			fprintf(file, "### DO NOT ADD ANYTHING BELOW THIS LINE ###\n");
			fprintf(file, "### DO NOT DELETE THE EMPTY LINE BELOW ###\n");
			fprintf(file, "\n");
			fprintf(file, "\n");
			break;
		case VideoCommon::RSP:
			fprintf(file, "#======== File I/O =====================\n");
			fprintf(file, "OutputFile                    : C:\\VRTest\\sequence_cvt\\RSP.yuv\n");
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
			fprintf(file, "CodingFaceWidth                   : 0                                   # 0: automatic calculation;\n");
			fprintf(file, "CodingFaceHeight                  : 0                                   # 0: automatic calculation;\n");
			fprintf(file, "#ViewPortSettings                  : 80.0 80.0  -90.0  0.0               # view port settings: horizontal FOV [0,360], vertical FOV [0, 180], yaw [-180, 180], pitch [-90, 90]\n");
			fprintf(file, "SphFile                           : sphere_655362.txt\n");
			fprintf(file, "\n");
			fprintf(file, "### DO NOT ADD ANYTHING BELOW THIS LINE ###\n");
			fprintf(file, "### DO NOT DELETE THE EMPTY LINE BELOW ###\n");
			fprintf(file, "\n");
			fprintf(file, "\n");
			break;
		case VideoCommon::TSP:
			fprintf(file, "#======== File I/O =====================\n");
			fprintf(file, "OutputFile                    : C:\\VRTest\\sequence_cvt\\TSP.yuv\n");
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
			fprintf(file, "CodingFaceWidth                   : 0                                   # 0: automatic calculation;\n");
			fprintf(file, "CodingFaceHeight                  : 0                                   # 0: automatic calculation;\n");
			fprintf(file, "#ViewPortSettings                  : 80.0 80.0  -90.0  0.0               # view port settings: horizontal FOV [0,360], vertical FOV [0, 180], yaw [-180, 180], pitch [-90, 90]\n");
			fprintf(file, "#SphFile                           : sphere_655362.txt\n");
			fprintf(file, "\n");
			fprintf(file, "### DO NOT ADD ANYTHING BELOW THIS LINE ###\n");
			fprintf(file, "### DO NOT DELETE THE EMPTY LINE BELOW ###\n");
			fprintf(file, "\n");
			fprintf(file, "\n");
			break;
		}		
	}
}

void CvtConfigGenerator::testGenerate(char* inputVideoName, int width, int height, int frameSize) {
	std::string dest[9] = {"ACP", "CISP", "CMP32", "COHP42", "EAC", "ECP", "our", "RSP", "TSP"};
	for (int i = 0; i < 9; ++i) {
		m_cvtName = dest[i] + "_" +  m_resolution;
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
	}
}

void CvtConfigGenerator::batGenerate() {
	std::string dest[9] = { "ACP", "CISP", "CMP32", "COHP42", "EAC", "ECP", "our", "RSP", "TSP" };
	for (int i = 0; i < 9; ++i) {
		std::string outputDir = "C:/VRTest/ERP_" + dest[i];
		outputDir = outputDir + "/" + dest[i] + "_" + m_resolution + ".bat";
#pragma warning (disable : 4996)
		FILE *file = fopen(outputDir.c_str(), "w");
		fprintf(file, "C:\\hm-360lib\\HM-16.16\\bin\\vc2015\\x64\\Debug\\Test\\convert\\TApp360Convert.exe -c 360convert_ERP_%s_test.cfg -c 360test_test_sequence.cfg\npause", dest[i].c_str());
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

CvtConfigGenerator::~CvtConfigGenerator()
{
}


