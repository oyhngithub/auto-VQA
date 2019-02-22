#include "ConfigGenerator.h"
#include "VideoCom.h"
#include "boost/filesystem.hpp"

ConfigGenerator::ConfigGenerator() {}
ConfigGenerator::ConfigGenerator(char* argv)
	:m_videoName(argv)
{
	videoCom.initialCom();
}


void ConfigGenerator::nameReader(char* frameNumber) {
	getFrameNumber(frameNumber);
	//getInfo();
}

void ConfigGenerator::getFrameNumber(const char* frameNumber) {
	m_frameNumber = std::atoi(std::string(frameNumber).c_str());
}

void ConfigGenerator::generator() {
	testGenerator();
	encoderGenerator();
	randomaccessGenerator();
	bashGenerator();
	//runBatch();
}
/*
void ConfigGenerator::getInfo() {
	//get format
	int index = m_videoName.find("_");
	m_projectionType = m_videoName.substr(0, index);

	//get resolution
	int head = m_videoName.find("_") + 1;
	int tail = m_videoName.find("_", head + 1);//TODO.
	m_resolution = m_videoName.substr(head, tail - head);
	int block = m_videoName.find("x");
	m_width = std::atoi(m_videoName.substr(head, block).c_str());
	m_height = std::atoi(m_videoName.substr(block + 1, tail - block).c_str());
	
	//
}*/

void ConfigGenerator::testGenerator() {
	for (int i = 0; i < 8; ++i) {
		std::string outputDir = "C:/VRTest/sequence_cvt/" + m_videoName + "_" + videoCom.dest[i] + "/encodeCfg";
		for (int j = 0; j < 5; ++j) {
			int w = videoCom.sourceSize[videoCom.str2geo[videoCom.dest[i]]][j][0];
			int h = videoCom.sourceSize[videoCom.str2geo[videoCom.dest[i]]][j][1];
			
			std::string cfgName = videoCom.dest[i] + "_" + std::to_string(w) + "x" + std::to_string(h) + "_360test.cfg";
			std::string outputDir = "C:/VRTest/sequence_cvt/" + m_videoName + "_" + videoCom.dest[i] + "/encodeCfg";
			if (!boost::filesystem::exists(outputDir)) {
				boost::filesystem::create_directories(outputDir);
			}
#pragma warning (disable : 4996)
			std::string outputFile = outputDir + "/" + cfgName;
			FILE* format_resolution_360test = fopen(outputFile.c_str(), "w+");
			fprintf(format_resolution_360test, "#======== File I/O ===============\n");
			fprintf(format_resolution_360test, "InputFile                     : C:\\VRTest\\sequence_cvt\\%s_%s\\%s_%dx%d_30Hz_8b_420.yuv\n", m_videoName.c_str(), videoCom.dest[i].c_str(), videoCom.dest[i].c_str(), w, h);
			fprintf(format_resolution_360test, "InputBitDepth                 : 8           # Input bitdepth\n");
			fprintf(format_resolution_360test, "InputChromaFormat             : 420         # Ratio of luminance to chrominance samples\n");
			fprintf(format_resolution_360test, "FrameRate                     : 30          # Frame Rate per second\n");
			fprintf(format_resolution_360test, "FrameSkip                     : 0           # Number of frames to be skipped in input\n");
			fprintf(format_resolution_360test, "SourceWidth                   : %d        # Input  frame width\n", w);
			fprintf(format_resolution_360test, "SourceHeight                  : %d        # Input  frame height\n", h);
			fprintf(format_resolution_360test, "FramesToBeEncoded             : %d         # Number of frames to be coded\n", m_frameNumber);
			fprintf(format_resolution_360test, "\n");
			fprintf(format_resolution_360test, "Level                         : 5.2\n");
			fclose(format_resolution_360test);

		}
	}
}

void ConfigGenerator::encoderGenerator() {
	for (int i = 0; i < 8; ++i) {
		std::string outputDir = "C:/VRTest/sequence_cvt/" + m_videoName + "_" + videoCom.dest[i] + "/encodeCfg";
		std::string postfix = "_encoder_360.cfg";

		for (int j = 0; j < 5; ++j) {
			VideoCom videoCom;
			int w = videoCom.faceSize[i][j][0];
			int h = videoCom.faceSize[i][j][1];
			int source_w = videoCom.sourceSize[i][j][0];
			int source_h = videoCom.sourceSize[i][j][1];
			std::string cfgDir = outputDir + "/" + videoCom.dest[i] + "_" + std::to_string(source_w) + "x" + std::to_string(source_h) + postfix;

			//std::string fullName = prefix + m_projectionType + postfix;
#pragma warning (disable : 4996)
			FILE* encoder_360_format = fopen(cfgDir.c_str(), "w");
			int test = videoCom.str2geo[videoCom.dest[i]];
			switch (videoCom.str2geo[videoCom.dest[i]]) {
			case VideoCom::ERP:
				fprintf(encoder_360_format, "#============ 360 video settings ======================\n");
				fprintf(encoder_360_format, "SphereVideo                       : 1                                    # 1: 360 video; 0: traditional video;\n");
				fprintf(encoder_360_format, "InputGeometryType                 : 0                                    # 0: equirectangular; 1: cubemap; 2: equalarea; this should be in the cfg of per sequence.\n");
				fprintf(encoder_360_format, "SourceFPStructure                 : 1 1   0 0                            # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
				fprintf(encoder_360_format, "                                                                         # rotation degrees[0, 90, 180, 270] is anti-clockwise;\n");
				fprintf(encoder_360_format, "CodingGeometryType                : 0\n");
				fprintf(encoder_360_format, "CodingFPStructure                 : 1 1   0 0                            # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
				fprintf(encoder_360_format, "                                                                         # rotation degrees[0, 90, 180] is anti-clockwise;\n");
				fprintf(encoder_360_format, "SVideoRotation                    : 0 0 0                                # rotation along X, Y, Z;                 \n");
				//TODO. maybe deal with the CodingFaceWidth and CodingFaceHeight later.
				fprintf(encoder_360_format, "CodingFaceWidth                   : %d									  # 0: automatic calculation; 4096 for 8K; 3328 for 4K;\n", w);
				fprintf(encoder_360_format, "CodingFaceHeight                  : %d                                    # 0: automatic calculation; 2048 for 8K; 1664 for 4K;\n", h);
				fprintf(encoder_360_format, "InterpolationMethodY              : 5                                    # interpolation method for luma, 0: default setting(bicubic); 1:NN, 2: bilinear, 3: bicubic, 4: lanczos2, 5: lanczos3\n");
				fprintf(encoder_360_format, "InterpolationMethodC              : 4                                    # interpolation method for chroma, 0: default setting(bicubic); 1:NN, 2: bilinear, 3: bicubic, 4: lanczos2, 5: lanczos3\n");
				fprintf(encoder_360_format, "InternalChromaFormat              : 420                                  # internal chroma format for the conversion process;\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "#============ 360 video metrics reported by encoder ======================\n");
				fprintf(encoder_360_format, "SPSNR_NN                          : 1                                    # enable end-to-end S-PSNR-NN calculation;\n");
				fprintf(encoder_360_format, "SPSNR_I                           : 0                                    # enable end-to-end S-PSNR-I calculation;\n");
				fprintf(encoder_360_format, "CPP_PSNR                          : 0                                    # enable end-to-end CPP-PSNR calculation;\n");
				fprintf(encoder_360_format, "E2EWSPSNR                         : 1                                    # enable end-to-end WS-PSNR calculation;\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "CODEC_SPSNR_NN                    : 1                                    # enable codec S-PSNR-NN calculation;\n");
				fprintf(encoder_360_format, "WSPSNR                            : 1                                    # enable codec WS-PSNR calculation;\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "CF_SPSNR_NN                       : 1                                    # enable cross-format S-PSNR-NN calculation;\n");
				fprintf(encoder_360_format, "CF_SPSNR_I                        : 0                                    # enable cross-format S-PSNR-I calculation;\n");
				fprintf(encoder_360_format, "CF_CPP_PSNR                       : 1                                    # enable cross-format CPP-PSNR calculation;    \n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "SphFile                           : ../cfg-360Lib/360Lib/sphere_655362.txt\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "ViewPortPSNREnable                : 0\n");
				fprintf(encoder_360_format, "ViewPortList                      : 2  75.0 75.0 0.0 0.0  75.0 75.0 -90.0 0.0      # num_of_viewports  hFOV_0 vFOV_0 yaw_0 pitch_0 hFOV_1 vFOV_1 yaw_1 pitch_1 ...\n");
				fprintf(encoder_360_format, "ViewPortWidth                     : 1816                                           # 1816 for 8K; 856 for 4K;\n");
				fprintf(encoder_360_format, "ViewPortHeight                    : 1816                                           # 1816 for 8K; 856 for 4K;  \n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "DynamicViewPortPSNREnable         : 0\n");
				fprintf(encoder_360_format, "DynamicViewPortList               : 2  75.0 75.0  0 -45.0 -15.0  299 45.0 15.0     75.0 75.0  0 -135.0 -15.0  299 -45.0 15.0   # num_of_dynamic_viewports  hFOV_0 vFOV_0 startPOC_0 startYaw_0 startPitch_0  endPOC_0 ednYaw_0 endPitch_0     hFOV_1 vFOV_1 startPOC_1 startYaw_1 startPitch_1  endPOC_1 ednYaw_1 endPitch_1 ...\n");
				fprintf(encoder_360_format, "DynamicViewPortWidth              : 1816                                           # 1816 for 8K; 856 for 4K;\n");
				fprintf(encoder_360_format, "DynamicViewPortHeight             : 1816                                           # 1816 for 8K; 856 for 4K;\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "### DO NOT ADD ANYTHING BELOW THIS LINE ###\n");
				fprintf(encoder_360_format, "### DO NOT DELETE THE EMPTY LINE BELOW ###\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "\n");
				break;
			case VideoCom::our:
				fprintf(encoder_360_format, "#============ 360 video settings ======================\n");
				fprintf(encoder_360_format, "SphereVideo                       : 1                                    # 1: 360 video; 0: traditional video;\n");
				fprintf(encoder_360_format, "InputGeometryType                 : 13                                    # 0: equirectangular; 1: cubemap; 2: equalarea; this should be in the cfg of per sequence.\n");
				fprintf(encoder_360_format, "SourceFPStructure                 : 1 1   0 0                            # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
				fprintf(encoder_360_format, "                                                                         # rotation degrees[0, 90, 180, 270] is anti-clockwise;\n");
				fprintf(encoder_360_format, "CodingGeometryType                : 13\n");
				fprintf(encoder_360_format, "CodingFPStructure                 : 1 1   0 0                            # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
				fprintf(encoder_360_format, "                                                                         # rotation degrees[0, 90, 180] is anti-clockwise;\n");
				fprintf(encoder_360_format, "SVideoRotation                    : 0 0 0                                # rotation along X, Y, Z;                 \n");
				//TODO. maybe deal with the CodingFaceWidth and CodingFaceHeight later.
				fprintf(encoder_360_format, "CodingFaceWidth                   : %d									  # 0: automatic calculation; 4096 for 8K; 3328 for 4K;\n", w);
				fprintf(encoder_360_format, "CodingFaceHeight                  : %d                                    # 0: automatic calculation; 2048 for 8K; 1664 for 4K;\n", h);
				fprintf(encoder_360_format, "InterpolationMethodY              : 5                                    # interpolation method for luma, 0: default setting(bicubic); 1:NN, 2: bilinear, 3: bicubic, 4: lanczos2, 5: lanczos3\n");
				fprintf(encoder_360_format, "InterpolationMethodC              : 4                                    # interpolation method for chroma, 0: default setting(bicubic); 1:NN, 2: bilinear, 3: bicubic, 4: lanczos2, 5: lanczos3\n");
				fprintf(encoder_360_format, "InternalChromaFormat              : 420                                  # internal chroma format for the conversion process;\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "#============ 360 video metrics reported by encoder ======================\n");
				fprintf(encoder_360_format, "SPSNR_NN                          : 1                                    # enable end-to-end S-PSNR-NN calculation;\n");
				fprintf(encoder_360_format, "SPSNR_I                           : 0                                    # enable end-to-end S-PSNR-I calculation;\n");
				fprintf(encoder_360_format, "CPP_PSNR                          : 0                                    # enable end-to-end CPP-PSNR calculation;\n");
				fprintf(encoder_360_format, "E2EWSPSNR                         : 1                                    # enable end-to-end WS-PSNR calculation;\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "CODEC_SPSNR_NN                    : 1                                    # enable codec S-PSNR-NN calculation;\n");
				fprintf(encoder_360_format, "WSPSNR                            : 0                                    # enable codec WS-PSNR calculation;\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "CF_SPSNR_NN                       : 1                                    # enable cross-format S-PSNR-NN calculation;\n");
				fprintf(encoder_360_format, "CF_SPSNR_I                        : 0                                    # enable cross-format S-PSNR-I calculation;\n");
				fprintf(encoder_360_format, "CF_CPP_PSNR                       : 1                                    # enable cross-format CPP-PSNR calculation;    \n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "SphFile                           : ../cfg-360Lib/360Lib/sphere_655362.txt\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "ViewPortPSNREnable                : 0\n");
				fprintf(encoder_360_format, "ViewPortList                      : 2  75.0 75.0 0.0 0.0  75.0 75.0 -90.0 0.0      # num_of_viewports  hFOV_0 vFOV_0 yaw_0 pitch_0 hFOV_1 vFOV_1 yaw_1 pitch_1 ...\n");
				fprintf(encoder_360_format, "ViewPortWidth                     : 1816                                           # 1816 for 8K; 856 for 4K;\n");
				fprintf(encoder_360_format, "ViewPortHeight                    : 1816                                           # 1816 for 8K; 856 for 4K;  \n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "DynamicViewPortPSNREnable         : 0\n");
				fprintf(encoder_360_format, "DynamicViewPortList               : 2  75.0 75.0  0 -45.0 -15.0  299 45.0 15.0     75.0 75.0  0 -135.0 -15.0  299 -45.0 15.0   # num_of_dynamic_viewports  hFOV_0 vFOV_0 startPOC_0 startYaw_0 startPitch_0  endPOC_0 ednYaw_0 endPitch_0     hFOV_1 vFOV_1 startPOC_1 startYaw_1 startPitch_1  endPOC_1 ednYaw_1 endPitch_1 ...\n");
				fprintf(encoder_360_format, "DynamicViewPortWidth              : 1816                                           # 1816 for 8K; 856 for 4K;\n");
				fprintf(encoder_360_format, "DynamicViewPortHeight             : 1816                                           # 1816 for 8K; 856 for 4K;\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "### DO NOT ADD ANYTHING BELOW THIS LINE ###\n");
				fprintf(encoder_360_format, "### DO NOT DELETE THE EMPTY LINE BELOW ###\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "\n");
				break;
			case VideoCom::ACP:
				fprintf(encoder_360_format, "#============ 360 video settings ======================\n");
				fprintf(encoder_360_format, "SphereVideo                       : 1                                    # 1: 360 video; 0: traditional video;\n");
				fprintf(encoder_360_format, "InputGeometryType                 : 9                                    # 0: equirectangular; 1: cubemap; 2: equalarea; this should be in the cfg of per sequence.\n");
				fprintf(encoder_360_format, "SourceFPStructure                 : 2 3   4 0 0 0 5 0   3 180 1 270 2 0  # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
				fprintf(encoder_360_format, "                                                                         # rotation degrees[0, 90, 180, 270] is anti-clockwise;\n");
				fprintf(encoder_360_format, "CodingGeometryType                : 9\n");
				fprintf(encoder_360_format, "CodingFPStructure                 : 2 3   4 0 0 0 5 0   3 180 1 270 2 0  # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
				fprintf(encoder_360_format, "                                                                         # rotation degrees[0, 90, 180] is anti-clockwise;\n");
				fprintf(encoder_360_format, "SVideoRotation                    : 0 0 0                                # rotation along X, Y, Z;                 \n");
				fprintf(encoder_360_format, "CodingFaceWidth                   : %d                                 # 0: automatic calculation; 1184 for 8K; 960 for 4K;\n", w);
				fprintf(encoder_360_format, "CodingFaceHeight                  : %d                                 # 0: automatic calculation; 1184 for 8K; 960 for 4K;\n", h);
				fprintf(encoder_360_format, "InterpolationMethodY              : 5                                    # interpolation method for luma, 0: default setting(bicubic); 1:NN, 2: bilinear, 3: bicubic, 4: lanczos2, 5: lanczos3\n");
				fprintf(encoder_360_format, "InterpolationMethodC              : 4                                    # interpolation method for chroma, 0: default setting(bicubic); 1:NN, 2: bilinear, 3: bicubic, 4: lanczos2, 5: lanczos3\n");
				fprintf(encoder_360_format, "InternalChromaFormat              : 420                                  # internal chroma format for the conversion process;\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "#============ 360 video metrics reported by encoder ======================\n");
				fprintf(encoder_360_format, "SPSNR_NN                          : 1                                    # enable end-to-end S-PSNR-NN calculation;\n");
				fprintf(encoder_360_format, "SPSNR_I                           : 0                                    # enable end-to-end S-PSNR-I calculation;\n");
				fprintf(encoder_360_format, "CPP_PSNR                          : 0                                    # enable end-to-end CPP-PSNR calculation;\n");
				fprintf(encoder_360_format, "E2EWSPSNR                         : 1                                    # enable end-to-end WS-PSNR calculation;\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "CODEC_SPSNR_NN                    : 1                                    # enable codec S-PSNR-NN calculation;\n");
				fprintf(encoder_360_format, "WSPSNR                            : 1                                    # enable codec WS-PSNR calculation;\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "CF_SPSNR_NN                       : 1                                    # enable cross-format S-PSNR-NN calculation;\n");
				fprintf(encoder_360_format, "CF_SPSNR_I                        : 0                                    # enable cross-format S-PSNR-I calculation;\n");
				fprintf(encoder_360_format, "CF_CPP_PSNR                       : 1                                    # enable cross-format CPP-PSNR calculation;    \n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "SphFile                           : ../cfg-360Lib/360Lib/sphere_655362.txt\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "ViewPortPSNREnable                : 0\n");
				fprintf(encoder_360_format, "ViewPortList                      : 2  75.0 75.0 0.0 0.0  75.0 75.0 -90.0 0.0      # num_of_viewports  hFOV_0 vFOV_0 yaw_0 pitch_0 hFOV_1 vFOV_1 yaw_1 pitch_1 ...\n");
				fprintf(encoder_360_format, "ViewPortWidth                     : 1816                                           # 1816 for 8K; 856 for 4K;\n");
				fprintf(encoder_360_format, "ViewPortHeight                    : 1816                                           # 1816 for 8K; 856 for 4K;  \n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "DynamicViewPortPSNREnable         : 0\n");
				fprintf(encoder_360_format, "DynamicViewPortList               : 2  75.0 75.0  0 -45.0 -15.0  299 45.0 15.0     75.0 75.0  0 -135.0 -15.0  299 -45.0 15.0   # num_of_dynamic_viewports  hFOV_0 vFOV_0 startPOC_0 startYaw_0 startPitch_0  endPOC_0 ednYaw_0 endPitch_0     hFOV_1 vFOV_1 startPOC_1 startYaw_1 startPitch_1  endPOC_1 ednYaw_1 endPitch_1 ...\n");
				fprintf(encoder_360_format, "DynamicViewPortWidth              : 1816                                           # 1816 for 8K; 856 for 4K;\n");
				fprintf(encoder_360_format, "DynamicViewPortHeight             : 1816                                           # 1816 for 8K; 856 for 4K;\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "### DO NOT ADD ANYTHING BELOW THIS LINE ###\n");
				fprintf(encoder_360_format, "### DO NOT DELETE THE EMPTY LINE BELOW ###\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "\n");
				break;
			case VideoCom::CISP:
				fprintf(encoder_360_format, "#============ 360 video settings ======================\n");
				fprintf(encoder_360_format, "SphereVideo                       : 1                                    # 1: 360 video; 0: traditional video;\n");
				fprintf(encoder_360_format, "InputGeometryType                 : 5                                    # 0: equirectangular; 1: cubemap; 2: equalarea; this should be in the cfg of per sequence.\n");
				fprintf(encoder_360_format, "SourceFPStructure                 : 4 5   0 180 2 180 4 0 6 180 8 0   1 180 3 180 5 180 7 180 9 180    11 0 13 0 15 0 17 0 19 0   10 180 12 0 14 180 16 0 18 0      # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
				fprintf(encoder_360_format, "                                                                         # rotation degrees[0, 90, 180, 270] is anti-clockwise;\n");
				fprintf(encoder_360_format, "                                                                        # rotation degrees[0, 90, 180, 270] is anti-clockwise;\n");
				fprintf(encoder_360_format, "CodingGeometryType                : 5\n");
				fprintf(encoder_360_format, "CodingFPStructure                 : 4 5   0 180 2 180 4 0 6 180 8 0   1 180 3 180 5 180 7 180 9 180    11 0 13 0 15 0 17 0 19 0   10 180 12 0 14 180 16 0 18 0      # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
				fprintf(encoder_360_format, "                                                                        # rotation degrees[0, 90, 180] is anti-clockwise;\n");
				fprintf(encoder_360_format, "CodingCompactFPStructure          : 1\n");
				fprintf(encoder_360_format, "SVideoRotation                    : 0 0 0                                # rotation along X, Y, Z;                 \n");
				fprintf(encoder_360_format, "CodingFaceWidth                   : %d                                  # 0: automatic calculation; 952 for 8K; 776 for 4K;\n", w);
				fprintf(encoder_360_format, "CodingFaceHeight                  : %d                                  # 0: automatic calculation; 824 for 8K; 672 for 4K;\n", h);
				fprintf(encoder_360_format, "InterpolationMethodY              : 5                                    # interpolation method for luma, 0: default setting(bicubic); 1:NN, 2: bilinear, 3: bicubic, 4: lanczos2, 5: lanczos3\n");
				fprintf(encoder_360_format, "InterpolationMethodC              : 4                                    # interpolation method for chroma, 0: default setting(bicubic); 1:NN, 2: bilinear, 3: bicubic, 4: lanczos2, 5: lanczos3\n");
				fprintf(encoder_360_format, "InternalChromaFormat              : 420                                  # internal chroma format for the conversion process;\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "#============ 360 video metrics reported by encoder ======================\n");
				fprintf(encoder_360_format, "SPSNR_NN                          : 1                                    # enable end-to-end S-PSNR-NN calculation;\n");
				fprintf(encoder_360_format, "SPSNR_I                           : 0                                    # enable end-to-end S-PSNR-I calculation;\n");
				fprintf(encoder_360_format, "CPP_PSNR                          : 0                                    # enable end-to-end CPP-PSNR calculation;\n");
				fprintf(encoder_360_format, "E2EWSPSNR                         : 1                                    # enable end-to-end WS-PSNR calculation;\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "CODEC_SPSNR_NN                    : 1                                    # enable codec S-PSNR-NN calculation;\n");
				fprintf(encoder_360_format, "WSPSNR                            : 1                                    # enable codec WS-PSNR calculation;\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "CF_SPSNR_NN                       : 1                                    # enable cross-format S-PSNR-NN calculation;\n");
				fprintf(encoder_360_format, "CF_SPSNR_I                        : 0                                    # enable cross-format S-PSNR-I calculation;\n");
				fprintf(encoder_360_format, "CF_CPP_PSNR                       : 1                                    # enable cross-format CPP-PSNR calculation;    \n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "SphFile                           : ../cfg-360Lib/360Lib/sphere_655362.txt\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "ViewPortPSNREnable                : 0\n");
				fprintf(encoder_360_format, "ViewPortList                      : 2  75.0 75.0 0.0 0.0  75.0 75.0 -90.0 0.0      # num_of_viewports  hFOV_0 vFOV_0 yaw_0 pitch_0 hFOV_1 vFOV_1 yaw_1 pitch_1 ...\n");
				fprintf(encoder_360_format, "ViewPortWidth                     : 1816                                           # 1816 for 8K; 856 for 4K;\n");
				fprintf(encoder_360_format, "ViewPortHeight                    : 1816                                           # 1816 for 8K; 856 for 4K;  \n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "DynamicViewPortPSNREnable         : 0\n");
				fprintf(encoder_360_format, "DynamicViewPortList               : 2  75.0 75.0  0 -45.0 -15.0  299 45.0 15.0     75.0 75.0  0 -135.0 -15.0  299 -45.0 15.0   # num_of_dynamic_viewports  hFOV_0 vFOV_0 startPOC_0 startYaw_0 startPitch_0  endPOC_0 ednYaw_0 endPitch_0     hFOV_1 vFOV_1 startPOC_1 startYaw_1 startPitch_1  endPOC_1 ednYaw_1 endPitch_1 ...\n");
				fprintf(encoder_360_format, "DynamicViewPortWidth              : 1816                                           # 1816 for 8K; 856 for 4K;\n");
				fprintf(encoder_360_format, "DynamicViewPortHeight             : 1816                                           # 1816 for 8K; 856 for 4K;\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "### DO NOT ADD ANYTHING BELOW THIS LINE ###\n");
				fprintf(encoder_360_format, "### DO NOT DELETE THE EMPTY LINE BELOW ###\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "\n");
				break;
			case VideoCom::CMP32:
				fprintf(encoder_360_format, "#============ 360 video settings ======================\n");
				fprintf(encoder_360_format, "SphereVideo                       : 1                                    # 1: 360 video; 0: traditional video;\n");
				fprintf(encoder_360_format, "InputGeometryType                 : 1                                    # 0: equirectangular; 1: cubemap; 2: equalarea; this should be in the cfg of per sequence.\n");
				fprintf(encoder_360_format, "SourceFPStructure                 : 2 3   4 0 0 0 5 0   3 180 1 270 2 0  # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
				fprintf(encoder_360_format, "                                                                         # rotation degrees[0, 90, 180, 270] is anti-clockwise;\n");
				fprintf(encoder_360_format, "CodingGeometryType                : 1\n");
				fprintf(encoder_360_format, "CodingFPStructure                 : 2 3   4 0 0 0 5 0   3 180 1 270 2 0  # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
				fprintf(encoder_360_format, "                                                                         # rotation degrees[0, 90, 180] is anti-clockwise;\n");
				fprintf(encoder_360_format, "SVideoRotation                    : 0 0 0                                # rotation along X, Y, Z;                 \n");
				fprintf(encoder_360_format, "CodingFaceWidth                   : %d                                 # 0: automatic calculation; 1184 for 8K; 960 for 4K;\n", w);
				fprintf(encoder_360_format, "CodingFaceHeight                  : %d                                 # 0: automatic calculation; 1184 for 8K; 960 for 4K;\n", h);
				fprintf(encoder_360_format, "InterpolationMethodY              : 5                                    # interpolation method for luma, 0: default setting(bicubic); 1:NN, 2: bilinear, 3: bicubic, 4: lanczos2, 5: lanczos3\n");
				fprintf(encoder_360_format, "InterpolationMethodC              : 4                                    # interpolation method for chroma, 0: default setting(bicubic); 1:NN, 2: bilinear, 3: bicubic, 4: lanczos2, 5: lanczos3\n");
				fprintf(encoder_360_format, "InternalChromaFormat              : 420                                  # internal chroma format for the conversion process;\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "#============ 360 video metrics reported by encoder ======================\n");
				fprintf(encoder_360_format, "SPSNR_NN                          : 1                                    # enable end-to-end S-PSNR-NN calculation;\n");
				fprintf(encoder_360_format, "SPSNR_I                           : 0                                    # enable end-to-end S-PSNR-I calculation;\n");
				fprintf(encoder_360_format, "CPP_PSNR                          : 0                                    # enable end-to-end CPP-PSNR calculation;\n");
				fprintf(encoder_360_format, "E2EWSPSNR                         : 1                                    # enable end-to-end WS-PSNR calculation;\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "CODEC_SPSNR_NN                    : 1                                    # enable codec S-PSNR-NN calculation;\n");
				fprintf(encoder_360_format, "WSPSNR                            : 1                                    # enable codec WS-PSNR calculation;\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "CF_SPSNR_NN                       : 1                                    # enable cross-format S-PSNR-NN calculation;\n");
				fprintf(encoder_360_format, "CF_SPSNR_I                        : 0                                    # enable cross-format S-PSNR-I calculation;\n");
				fprintf(encoder_360_format, "CF_CPP_PSNR                       : 1                                    # enable cross-format CPP-PSNR calculation;    \n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "SphFile                           : ../cfg-360Lib/360Lib/sphere_655362.txt\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "ViewPortPSNREnable                : 0\n");
				fprintf(encoder_360_format, "ViewPortList                      : 2  75.0 75.0 0.0 0.0  75.0 75.0 -90.0 0.0      # num_of_viewports  hFOV_0 vFOV_0 yaw_0 pitch_0 hFOV_1 vFOV_1 yaw_1 pitch_1 ...\n");
				fprintf(encoder_360_format, "ViewPortWidth                     : 1816                                           # 1816 for 8K; 856 for 4K;\n");
				fprintf(encoder_360_format, "ViewPortHeight                    : 1816                                           # 1816 for 8K; 856 for 4K;  \n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "DynamicViewPortPSNREnable         : 0\n");
				fprintf(encoder_360_format, "DynamicViewPortList               : 2  75.0 75.0  0 -45.0 -15.0  299 45.0 15.0     75.0 75.0  0 -135.0 -15.0  299 -45.0 15.0   # num_of_dynamic_viewports  hFOV_0 vFOV_0 startPOC_0 startYaw_0 startPitch_0  endPOC_0 ednYaw_0 endPitch_0     hFOV_1 vFOV_1 startPOC_1 startYaw_1 startPitch_1  endPOC_1 ednYaw_1 endPitch_1 ...\n");
				fprintf(encoder_360_format, "DynamicViewPortWidth              : 1816                                           # 1816 for 8K; 856 for 4K;\n");
				fprintf(encoder_360_format, "DynamicViewPortHeight             : 1816                                           # 1816 for 8K; 856 for 4K;\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "### DO NOT ADD ANYTHING BELOW THIS LINE ###\n");
				fprintf(encoder_360_format, "### DO NOT DELETE THE EMPTY LINE BELOW ###\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "\n");
				break;
			case VideoCom::COHP42:
				fprintf(encoder_360_format, "#============ 360 video settings ======================\n");
				fprintf(encoder_360_format, "SphereVideo                       : 1                                    # 1: 360 video; 0: traditional video;\n");
				fprintf(encoder_360_format, "InputGeometryType                 : 3                                    # 0: equirectangular; 1: cubemap; 2: equalarea; this should be in the cfg of per sequence\n");
				fprintf(encoder_360_format, "SourceFPStructure                 : 4 2   2 270  3 90  6 90  7 270  0 270  1 90  4 90  5 270      # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
				fprintf(encoder_360_format, "                                                                         # rotation degrees[0, 90, 180, 270] is anti-clockwise;\n");
				fprintf(encoder_360_format, "                                                                        # rotation degrees[0, 90, 180, 270] is anti-clockwise;\n");
				fprintf(encoder_360_format, "CodingGeometryType                : 3\n");
				fprintf(encoder_360_format, "CodingFPStructure                 : 4 2   2 270  3 90  6 90  7 270  0 270  1 90  4 90  5 270      # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
				fprintf(encoder_360_format, "                                                                        # rotation degrees[0, 90, 180] is anti-clockwise;\n");
				fprintf(encoder_360_format, "CodingCompactFPStructure          : 1                                    # 0: uncompact OHP; 1: OHP with frame packing option 1; 2: OHP with frame packing option 2;\n");
				fprintf(encoder_360_format, "SVideoRotation                    : 0 0 0                                # rotation along X, Y, Z;                 \n");
				fprintf(encoder_360_format, "CodingFaceWidth                   : %d                                 # 0: automatic calculation; 1552 for 8K; 1256 for 4K;\n", w);
				fprintf(encoder_360_format, "CodingFaceHeight                  : %d                                 # 0: automatic calculation; 1344 for 8K; 1088 for 4K;\n", h);
				fprintf(encoder_360_format, "InterpolationMethodY              : 5                                    # interpolation method for luma, 0: default setting(bicubic); 1:NN, 2: bilinear, 3: bicubic, 4: lanczos2, 5: lanczos3\n");
				fprintf(encoder_360_format, "InterpolationMethodC              : 4                                    # interpolation method for chroma, 0: default setting(bicubic); 1:NN, 2: bilinear, 3: bicubic, 4: lanczos2, 5: lanczos3\n");
				fprintf(encoder_360_format, "InternalChromaFormat              : 420                                  # internal chroma format for the conversion process;\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "#============ 360 video metrics reported by encoder ======================\n");
				fprintf(encoder_360_format, "SPSNR_NN                          : 1                                    # enable end-to-end S-PSNR-NN calculation;\n");
				fprintf(encoder_360_format, "SPSNR_I                           : 0                                    # enable end-to-end S-PSNR-I calculation;\n");
				fprintf(encoder_360_format, "CPP_PSNR                          : 0                                    # enable end-to-end CPP-PSNR calculation;\n");
				fprintf(encoder_360_format, "E2EWSPSNR                         : 1                                    # enable end-to-end WS-PSNR calculation;\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "CODEC_SPSNR_NN                    : 1                                    # enable codec S-PSNR-NN calculation;\n");
				fprintf(encoder_360_format, "WSPSNR                            : 1                                    # enable codec WS-PSNR calculation;\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "CF_SPSNR_NN                       : 1                                    # enable cross-format S-PSNR-NN calculation;\n");
				fprintf(encoder_360_format, "CF_SPSNR_I                        : 0                                    # enable cross-format S-PSNR-I calculation;\n");
				fprintf(encoder_360_format, "CF_CPP_PSNR                       : 1                                    # enable cross-format CPP-PSNR calculation;    \n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "SphFile                           : ../cfg-360Lib/360Lib/sphere_655362.txt\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "ViewPortPSNREnable                : 0\n");
				fprintf(encoder_360_format, "ViewPortList                      : 2  75.0 75.0 0.0 0.0  75.0 75.0 -90.0 0.0      # num_of_viewports  hFOV_0 vFOV_0 yaw_0 pitch_0 hFOV_1 vFOV_1 yaw_1 pitch_1 ...\n");
				fprintf(encoder_360_format, "ViewPortWidth                     : 1816                                           # 1816 for 8K; 856 for 4K;\n");
				fprintf(encoder_360_format, "ViewPortHeight                    : 1816                                           # 1816 for 8K; 856 for 4K;  \n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "DynamicViewPortPSNREnable         : 0\n");
				fprintf(encoder_360_format, "DynamicViewPortList               : 2  75.0 75.0  0 -45.0 -15.0  299 45.0 15.0     75.0 75.0  0 -135.0 -15.0  299 -45.0 15.0   # num_of_dynamic_viewports  hFOV_0 vFOV_0 startPOC_0 startYaw_0 startPitch_0  endPOC_0 ednYaw_0 endPitch_0     hFOV_1 vFOV_1 startPOC_1 startYaw_1 startPitch_1  endPOC_1 ednYaw_1 endPitch_1 ...\n");
				fprintf(encoder_360_format, "DynamicViewPortWidth              : 1816                                           # 1816 for 8K; 856 for 4K;\n");
				fprintf(encoder_360_format, "DynamicViewPortHeight             : 1816                                           # 1816 for 8K; 856 for 4K;\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "### DO NOT ADD ANYTHING BELOW THIS LINE ###\n");
				fprintf(encoder_360_format, "### DO NOT DELETE THE EMPTY LINE BELOW ###\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "\n");
				break;
			case VideoCom::EAC:
				fprintf(encoder_360_format, "#============ 360 video settings ======================\n");
				fprintf(encoder_360_format, "SphereVideo                       : 1                                    # 1: 360 video; 0: traditional video;\n");
				fprintf(encoder_360_format, "InputGeometryType                 : 12                                   # 0: equirectangular; 1: cubemap; 2: equalarea; this should be in the cfg of per sequence.\n");
				fprintf(encoder_360_format, "SourceFPStructure                 : 2 3   4 0 0 0 5 0   3 180 1 270 2 0  # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
				fprintf(encoder_360_format, "                                                                         # rotation degrees[0, 90, 180, 270] is anti-clockwise;\n");
				fprintf(encoder_360_format, "CodingGeometryType                : 12\n");
				fprintf(encoder_360_format, "CodingFPStructure                 : 2 3   4 0 0 0 5 0   3 180 1 270 2 0  # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
				fprintf(encoder_360_format, "                                                                         # rotation degrees[0, 90, 180] is anti-clockwise;\n");
				fprintf(encoder_360_format, "SVideoRotation                    : 0 0 0                                # rotation along X, Y, Z;                 \n");
				fprintf(encoder_360_format, "CodingFaceWidth                   : %d                                 # 0: automatic calculation; 1184 for 8K; 960 for 4K;\n", w);
				fprintf(encoder_360_format, "CodingFaceHeight                  : %d                                 # 0: automatic calculation; 1184 for 8K; 960 for 4K;\n", h);
				fprintf(encoder_360_format, "InterpolationMethodY              : 5                                    # interpolation method for luma, 0: default setting(bicubic); 1:NN, 2: bilinear, 3: bicubic, 4: lanczos2, 5: lanczos3\n");
				fprintf(encoder_360_format, "InterpolationMethodC              : 4                                    # interpolation method for chroma, 0: default setting(bicubic); 1:NN, 2: bilinear, 3: bicubic, 4: lanczos2, 5: lanczos3\n");
				fprintf(encoder_360_format, "InternalChromaFormat              : 420                                  # internal chroma format for the conversion process;\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "#============ 360 video metrics reported by encoder ======================\n");
				fprintf(encoder_360_format, "SPSNR_NN                          : 1                                    # enable end-to-end S-PSNR-NN calculation;\n");
				fprintf(encoder_360_format, "SPSNR_I                           : 0                                    # enable end-to-end S-PSNR-I calculation;\n");
				fprintf(encoder_360_format, "CPP_PSNR                          : 0                                    # enable end-to-end CPP-PSNR calculation;\n");
				fprintf(encoder_360_format, "E2EWSPSNR                         : 1                                    # enable end-to-end WS-PSNR calculation;\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "CODEC_SPSNR_NN                    : 1                                    # enable codec S-PSNR-NN calculation;\n");
				fprintf(encoder_360_format, "WSPSNR                            : 1                                    # enable codec WS-PSNR calculation;\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "CF_SPSNR_NN                       : 1                                    # enable cross-format S-PSNR-NN calculation;\n");
				fprintf(encoder_360_format, "CF_SPSNR_I                        : 0                                    # enable cross-format S-PSNR-I calculation;\n");
				fprintf(encoder_360_format, "CF_CPP_PSNR                       : 1                                    # enable cross-format CPP-PSNR calculation;   \n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "SphFile                           : ../cfg-360Lib/360Lib/sphere_655362.txt\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "ViewPortPSNREnable                : 0\n");
				fprintf(encoder_360_format, "ViewPortList                      : 2  75.0 75.0 0.0 0.0  75.0 75.0 -90.0 0.0      # num_of_viewports  hFOV_0 vFOV_0 yaw_0 pitch_0 hFOV_1 vFOV_1 yaw_1 pitch_1 ...\n");
				fprintf(encoder_360_format, "ViewPortWidth                     : 1816                                           # 1816 for 8K; 856 for 4K;\n");
				fprintf(encoder_360_format, "ViewPortHeight                    : 1816                                           # 1816 for 8K; 856 for 4K;  \n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "DynamicViewPortPSNREnable         : 0\n");
				fprintf(encoder_360_format, "DynamicViewPortList               : 2  75.0 75.0  0 -45.0 -15.0  299 45.0 15.0     75.0 75.0  0 -135.0 -15.0  299 -45.0 15.0   # num_of_dynamic_viewports  hFOV_0 vFOV_0 startPOC_0 startYaw_0 startPitch_0  endPOC_0 ednYaw_0 endPitch_0     hFOV_1 vFOV_1 startPOC_1 startYaw_1 startPitch_1  endPOC_1 ednYaw_1 endPitch_1 ...\n");
				fprintf(encoder_360_format, "DynamicViewPortWidth              : 1816                                           # 1816 for 8K; 856 for 4K;\n");
				fprintf(encoder_360_format, "DynamicViewPortHeight             : 1816                                           # 1816 for 8K; 856 for 4K;\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "### DO NOT ADD ANYTHING BELOW THIS LINE ###\n");
				fprintf(encoder_360_format, "### DO NOT DELETE THE EMPTY LINE BELOW ###\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "\n");
				break;
			case VideoCom::ECP:
				fprintf(encoder_360_format, "#============ 360 video settings ======================\n");
				fprintf(encoder_360_format, "SphereVideo                       : 1                                    # 1: 360 video; 0: traditional video;\n");
				fprintf(encoder_360_format, "InputGeometryType                 : 11                                    # 0: equirectangular; 1: cubemap; 2: equalarea; this should be in the cfg of per sequence.\n");
				fprintf(encoder_360_format, "SourceFPStructure                 : 2 3   2 0 3 0 4 0 1 90 5 270 0 90    # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
				fprintf(encoder_360_format, "                                                                         # rotation degrees[0, 90, 180, 270] is anti-clockwise;\n");
				fprintf(encoder_360_format, "CodingGeometryType                : 11\n");
				fprintf(encoder_360_format, "CodingFPStructure                 : 2 3   2 0 3 0 4 0 1 90 5 270 0 90    # frame packing order: numRows numCols Row0Idx0 ROT Row0Idx1 ROT ... Row1...\n");
				fprintf(encoder_360_format, "                                                                         # rotation degrees[0, 90, 180] is anti-clockwise;\n");
				fprintf(encoder_360_format, "SVideoRotation                    : 0 0 0                                # rotation along X, Y, Z;                 \n");
				fprintf(encoder_360_format, "CodingFaceWidth                   : %d                                 # 0: automatic calculation; 1184 for 8K; 960 for 4K;\n", w);
				fprintf(encoder_360_format, "CodingFaceHeight                  : %d                                 # 0: automatic calculation; 1184 for 8K; 960 for 4K;\n", h);
				fprintf(encoder_360_format, "InterpolationMethodY              : 5                                    # interpolation method for luma, 0: default setting(bicubic); 1:NN, 2: bilinear, 3: bicubic, 4: lanczos2, 5: lanczos3\n");
				fprintf(encoder_360_format, "InterpolationMethodC              : 4                                    # interpolation method for chroma, 0: default setting(bicubic); 1:NN, 2: bilinear, 3: bicubic, 4: lanczos2, 5: lanczos3\n");
				fprintf(encoder_360_format, "InternalChromaFormat              : 420                                  # internal chroma format for the conversion process;\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "#============ 360 video metrics reported by encoder ======================\n");
				fprintf(encoder_360_format, "SPSNR_NN                          : 1                                    # enable end-to-end S-PSNR-NN calculation;\n");
				fprintf(encoder_360_format, "SPSNR_I                           : 0                                    # enable end-to-end S-PSNR-I calculation;\n");
				fprintf(encoder_360_format, "CPP_PSNR                          : 0                                    # enable end-to-end CPP-PSNR calculation;\n");
				fprintf(encoder_360_format, "E2EWSPSNR                         : 1                                    # enable end-to-end WS-PSNR calculation;\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "CODEC_SPSNR_NN                    : 1                                    # enable codec S-PSNR-NN calculation;\n");
				fprintf(encoder_360_format, "WSPSNR                            : 1                                    # enable codec WS-PSNR calculation;\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "CF_SPSNR_NN                       : 1                                    # enable cross-format S-PSNR-NN calculation;\n");
				fprintf(encoder_360_format, "CF_SPSNR_I                        : 0                                    # enable cross-format S-PSNR-I calculation;\n");
				fprintf(encoder_360_format, "CF_CPP_PSNR                       : 1                                    # enable cross-format CPP-PSNR calculation;    \n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "SphFile                           : ../cfg-360Lib/360Lib/sphere_655362.txt\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "ViewPortPSNREnable                : 0\n");
				fprintf(encoder_360_format, "ViewPortList                      : 2  75.0 75.0 0.0 0.0  75.0 75.0 -90.0 0.0      # num_of_viewports  hFOV_0 vFOV_0 yaw_0 pitch_0 hFOV_1 vFOV_1 yaw_1 pitch_1 ...\n");
				fprintf(encoder_360_format, "ViewPortWidth                     : 1816                                           # 1816 for 8K; 856 for 4K;\n");
				fprintf(encoder_360_format, "ViewPortHeight                    : 1816                                           # 1816 for 8K; 856 for 4K;  \n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "DynamicViewPortPSNREnable         : 0\n");
				fprintf(encoder_360_format, "DynamicViewPortList               : 2  75.0 75.0  0 -45.0 -15.0  299 45.0 15.0     75.0 75.0  0 -135.0 -15.0  299 -45.0 15.0   # num_of_dynamic_viewports  hFOV_0 vFOV_0 startPOC_0 startYaw_0 startPitch_0  endPOC_0 ednYaw_0 endPitch_0     hFOV_1 vFOV_1 startPOC_1 startYaw_1 startPitch_1  endPOC_1 ednYaw_1 endPitch_1 ...\n");
				fprintf(encoder_360_format, "DynamicViewPortWidth              : 1816                                           # 1816 for 8K; 856 for 4K;\n");
				fprintf(encoder_360_format, "DynamicViewPortHeight             : 1816                                           # 1816 for 8K; 856 for 4K;\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "### DO NOT ADD ANYTHING BELOW THIS LINE ###\n");
				fprintf(encoder_360_format, "### DO NOT DELETE THE EMPTY LINE BELOW ###\n");
				fprintf(encoder_360_format, "\n");
				fprintf(encoder_360_format, "\n");
				break;
			}
			fclose(encoder_360_format);
		}
	}
}

void ConfigGenerator::randomaccessGenerator() {
	for (int i = 0; i < 8; ++i) {
		std::string outputDir = "C:/VRTest/sequence_cvt/" + m_videoName + "_" + videoCom.dest[i] + "/encodeCfg";
		std::string postfix = "_encoder_randomaccess_main.cfg";
		for (int j = 0; j < 5; ++j) {
			int w = videoCom.sourceSize[i][j][0];
			int h = videoCom.sourceSize[i][j][1];
			std::string cfgFile = outputDir + "/" + videoCom.dest[i] + "_" + std::to_string(w) + "x" + std::to_string(h) + postfix;
			std::string recDir = "C:/VRTest/sequence_cvt/" + m_videoName + "_" + videoCom.dest[i] + "/rec";
			std::string binDir = "C:/VRTest/sequence_cvt/" + m_videoName + "_" + videoCom.dest[i] + "/bin";
			if (!boost::filesystem::exists(recDir)) {
				boost::filesystem::create_directories(recDir);
			}
			if (!boost::filesystem::exists(binDir)) {
				boost::filesystem::create_directories(binDir);
			}
#pragma warning (disable : 4996)
			FILE* randomaccess = fopen(cfgFile.c_str(), "w");
			fprintf(randomaccess, "#======== File I/O =====================\n");
			fprintf(randomaccess, "BitstreamFile                 : C:\\VRTest\\sequence_cvt\\%s_%s\\bin\\str_%dx%d.bin\n", m_videoName.c_str(), videoCom.dest[i].c_str(), w, h);
			fprintf(randomaccess, "ReconFile                     : C:\\VRTest\\sequence_cvt\\%s_%s\\rec\\rec_%dx%d.yuv\n", m_videoName.c_str(), videoCom.dest[i].c_str(), w, h);
			fprintf(randomaccess, "\n");
			fprintf(randomaccess, "#======== Profile ================\n");
			fprintf(randomaccess, "Profile                       : main\n");
			fprintf(randomaccess, "\n");
			fprintf(randomaccess, "#======== Unit definition ================\n");
			fprintf(randomaccess, "MaxCUWidth                    : 64          # Maximum coding unit width in pixel\n");
			fprintf(randomaccess, "MaxCUHeight                   : 64          # Maximum coding unit height in pixel\n");
			fprintf(randomaccess, "MaxPartitionDepth             : 4           # Maximum coding unit depth\n");
			fprintf(randomaccess, "QuadtreeTULog2MaxSize         : 5           # Log2 of maximum transform size for\n");
			fprintf(randomaccess, "                                            # quadtree-based TU coding (2...6)\n");
			fprintf(randomaccess, "QuadtreeTULog2MinSize         : 2           # Log2 of minimum transform size for\n");
			fprintf(randomaccess, "                                            # quadtree-based TU coding (2...6)\n");
			fprintf(randomaccess, "QuadtreeTUMaxDepthInter       : 3\n");
			fprintf(randomaccess, "QuadtreeTUMaxDepthIntra       : 3\n");
			fprintf(randomaccess, "\n");
			fprintf(randomaccess, "#======== Coding Structure =============\n");
			fprintf(randomaccess, "IntraPeriod                   : 32          # Period of I-Frame ( -1 = only first)\n");
			fprintf(randomaccess, "DecodingRefreshType           : 1           # Random Accesss 0:none, 1:CRA, 2:IDR, 3:Recovery Point SEI\n");
			fprintf(randomaccess, "GOPSize                       : 16           # GOP Size (number of B slice = GOPSize-1)\n");
			fprintf(randomaccess, "ReWriteParamSetsFlag          : 1           # Write parameter sets with every IRAP\n");
			fprintf(randomaccess, "\n");
			fprintf(randomaccess, "IntraQPOffset                 : -3\n");
			fprintf(randomaccess, "LambdaFromQpEnable            : 1           # see JCTVC-X0038 for suitable parameters for IntraQPOffset, QPoffset, QPOffsetModelOff, QPOffsetModelScale when enabled\n");
			fprintf(randomaccess, "#        Type POC QPoffset QPOffsetModelOff QPOffsetModelScale CbQPoffset CrQPoffset QPfactor tcOffsetDiv2 betaOffsetDiv2 temporal_id #ref_pics_active #ref_pics reference pictures     predict deltaRPS #ref_idcs reference idcs\n");
			fprintf(randomaccess, "Frame1:  B   16   1        0.0                      0.0            0          0          1.0      0            0              0           2                3         -16 -24 -32            0  \n");
			fprintf(randomaccess, "Frame2:  B    8   1       -4.8848                   0.2061         0          0          1.0      0            0              1           2                3         -8  -16   8            1       8        4         1 1 0 1    \n");
			fprintf(randomaccess, "Frame3:  B    4   4       -5.7476                   0.2286         0          0          1.0      0            0              2           2                4         -4  -12   4  12        1       4        4         1 1 1 1 \n");
			fprintf(randomaccess, "Frame4:  B    2   5       -5.90                     0.2333         0          0          1.0      0            0              3           2                5         -2  -10   2   6  14    1       2        5         1 1 1 1 1 \n");
			fprintf(randomaccess, "Frame5:  B    1   6       -7.1444                   0.3            0          0          1.0      0            0              4           2                5         -1    1  3    7  15    1       1        6         1 0 1 1 1 1  \n");
			fprintf(randomaccess, "Frame6:  B    3   6       -7.1444                   0.3            0          0          1.0      0            0              4           2                5         -1   -3   1   5  13    1      -2        6         1 1 1 1 1 0 \n");
			fprintf(randomaccess, "Frame7:  B    6   5       -5.90                     0.2333         0          0          1.0      0            0              3           2                4         -2   -6   2  10        1      -3        6         0 1 1 1 1 0 \n");
			fprintf(randomaccess, "Frame8:  B    5   6       -7.1444                   0.3            0          0          1.0      0            0              4           2                5         -1   -5   1   3  11    1       1        5         1 1 1 1 1  \n");
			fprintf(randomaccess, "Frame9:  B    7   6       -7.1444                   0.3            0          0          1.0      0            0              4           2                5         -1   -3  -7   1   9    1      -2        6         1 1 1 1 1 0 \n");
			fprintf(randomaccess, "Frame10: B   12   4       -5.7476                   0.2286         0          0          1.0      0            0              2           2                3         -4  -12   4            1      -5        6         0 0 1 1 1 0 \n");
			fprintf(randomaccess, "Frame11: B   10   5       -5.90                     0.2333         0          0          1.0      0            0              3           2                4         -2  -10   2   6        1       2        4         1 1 1 1 \n");
			fprintf(randomaccess, "Frame12: B    9   6       -7.1444                   0.3            0          0          1.0      0            0              4           2                5         -1   -9   1   3   7    1       1        5         1 1 1 1 1 \n");
			fprintf(randomaccess, "Frame13: B   11   6       -7.1444                   0.3            0          0          1.0      0            0              4           2                5         -1   -3 -11   1   5    1      -2        6         1 1 1 1 1 0 \n");
			fprintf(randomaccess, "Frame14: B   14   5       -5.90                     0.2333         0          0          1.0      0            0              3           2                4         -2   -6 -14   2        1      -3        6         0 1 1 1 1 0 \n");
			fprintf(randomaccess, "Frame15: B   13   6       -7.1444                   0.3            0          0          1.0      0            0              4           2                5         -1   -5 -13   1   3    1       1        5         1 1 1 1 1 \n");
			fprintf(randomaccess, "Frame16: B   15   6       -7.1444                   0.3            0          0          1.0      0            0              4           2                5         -1   -3 -7  -15   1    1      -2        6         1 1 1 1 1 0 \n");
			fprintf(randomaccess, "\n");
			fprintf(randomaccess, "#=========== Motion Search =============\n");
			fprintf(randomaccess, "FastSearch                    : 1           # 0:Full search  1:TZ search\n");
			fprintf(randomaccess, "SearchRange                   : 384         # (0: Search range is a Full frame)\n");
			fprintf(randomaccess, "ASR                           : 1           # Adaptive motion search range\n");
			fprintf(randomaccess, "MinSearchWindow               : 96          # Minimum motion search window size for the adaptive window ME\n");
			fprintf(randomaccess, "BipredSearchRange             : 4           # Search range for bi-prediction refinement\n");
			fprintf(randomaccess, "HadamardME                    : 1           # Use of hadamard measure for fractional ME\n");
			fprintf(randomaccess, "FEN                           : 1           # Fast encoder decision\n");
			fprintf(randomaccess, "FDM                           : 1           # Fast Decision for Merge RD cost\n");
			fprintf(randomaccess, "\n");
			fprintf(randomaccess, "#======== Quantization =============\n");
			fprintf(randomaccess, "QP                            : 32          # Quantization parameter(0-51)\n");
			fprintf(randomaccess, "MaxDeltaQP                    : 0           # CU-based multi-QP optimization\n");
			fprintf(randomaccess, "MaxCuDQPDepth                 : 0           # Max depth of a minimum CuDQP for sub-LCU-level delta QP\n");
			fprintf(randomaccess, "DeltaQpRD                     : 0           # Slice-based multi-QP optimization\n");
			fprintf(randomaccess, "RDOQ                          : 1           # RDOQ\n");
			fprintf(randomaccess, "RDOQTS                        : 1           # RDOQ for transform skip\n");
			fprintf(randomaccess, "SliceChromaQPOffsetPeriodicity: 0           # Used in conjunction with Slice Cb/Cr QpOffsetIntraOrPeriodic. Use 0 (default) to disable periodic nature.\n");
			fprintf(randomaccess, "SliceCbQpOffsetIntraOrPeriodic: 0           # Chroma Cb QP Offset at slice level for I slice or for periodic inter slices as defined by SliceChromaQPOffsetPeriodicity. Replaces offset in the GOP table.\n");
			fprintf(randomaccess, "SliceCrQpOffsetIntraOrPeriodic: 0           # Chroma Cr QP Offset at slice level for I slice or for periodic inter slices as defined by SliceChromaQPOffsetPeriodicity. Replaces offset in the GOP table.\n");
			fprintf(randomaccess, "\n");
			fprintf(randomaccess, "#=========== Deblock Filter ============\n");
			fprintf(randomaccess, "LoopFilterOffsetInPPS         : 1           # Dbl params: 0=varying params in SliceHeader, param = base_param + GOP_offset_param; 1 (default) =constant params in PPS, param = base_param)\n");
			fprintf(randomaccess, "LoopFilterDisable             : 0           # Disable deblocking filter (0=Filter, 1=No Filter)\n");
			fprintf(randomaccess, "LoopFilterBetaOffset_div2     : 0           # base_param: -6 ~ 6\n");
			fprintf(randomaccess, "LoopFilterTcOffset_div2       : 0           # base_param: -6 ~ 6\n");
			fprintf(randomaccess, "DeblockingFilterMetric        : 0           # blockiness metric (automatically configures deblocking parameters in bitstream). Applies slice-level loop filter offsets (LoopFilterOffsetInPPS and LoopFilterDisable must be 0)\n");
			fprintf(randomaccess, "\n");
			fprintf(randomaccess, "#=========== Misc. ============\n");
			fprintf(randomaccess, "InternalBitDepth              : 8           # codec operating bit-depth\n");
			fprintf(randomaccess, "\n");
			fprintf(randomaccess, "#=========== Coding Tools =================\n");
			fprintf(randomaccess, "SAO                           : 1           # Sample adaptive offset  (0: OFF, 1: ON)\n");
			fprintf(randomaccess, "AMP                           : 1           # Asymmetric motion partitions (0: OFF, 1: ON)\n");
			fprintf(randomaccess, "TransformSkip                 : 1           # Transform skipping (0: OFF, 1: ON)\n");
			fprintf(randomaccess, "TransformSkipFast             : 1           # Fast Transform skipping (0: OFF, 1: ON)\n");
			fprintf(randomaccess, "SAOLcuBoundary                : 0           # SAOLcuBoundary using non-deblocked pixels (0: OFF, 1: ON)\n");
			fprintf(randomaccess, "\n");
			fprintf(randomaccess, "#============ Slices ================\n");
			fprintf(randomaccess, "SliceMode                : 0                # 0: Disable all slice options.\n");
			fprintf(randomaccess, "                                            # 1: Enforce maximum number of LCU in an slice,\n");
			fprintf(randomaccess, "                                            # 2: Enforce maximum number of bytes in an 'slice'\n");
			fprintf(randomaccess, "                                            # 3: Enforce maximum number of tiles in a slice\n");
			fprintf(randomaccess, "SliceArgument            : 1500             # Argument for 'SliceMode'.\n");
			fprintf(randomaccess, "                                            # If SliceMode==1 it represents max. SliceGranularity-sized blocks per slice.\n");
			fprintf(randomaccess, "                                            # If SliceMode==2 it represents max. bytes per slice.\n");
			fprintf(randomaccess, "                                            # If SliceMode==3 it represents max. tiles per slice.\n");
			fprintf(randomaccess, "\n");
			fprintf(randomaccess, "LFCrossSliceBoundaryFlag : 1                # In-loop filtering, including ALF and DB, is across or not across slice boundary.\n");
			fprintf(randomaccess, "                                            # 0:not across, 1: across\n");
			fprintf(randomaccess, "\n");
			fprintf(randomaccess, "#============ PCM ================\n");
			fprintf(randomaccess, "PCMEnabledFlag                      : 0                # 0: No PCM mode\n");
			fprintf(randomaccess, "PCMLog2MaxSize                      : 5                # Log2 of maximum PCM block size.\n");
			fprintf(randomaccess, "PCMLog2MinSize                      : 3                # Log2 of minimum PCM block size.\n");
			fprintf(randomaccess, "PCMInputBitDepthFlag                : 1                # 0: PCM bit-depth is internal bit-depth. 1: PCM bit-depth is input bit-depth.\n");
			fprintf(randomaccess, "PCMFilterDisableFlag                : 0                # 0: Enable loop filtering on I_PCM samples. 1: Disable loop filtering on I_PCM samples.\n");
			fprintf(randomaccess, "\n");
			fprintf(randomaccess, "#============ Tiles ================\n");
			fprintf(randomaccess, "TileUniformSpacing                  : 0                # 0: the column boundaries are indicated by TileColumnWidth array, the row boundaries are indicated by TileRowHeight array\n");
			fprintf(randomaccess, "                                                       # 1: the column and row boundaries are distributed uniformly\n");
			fprintf(randomaccess, "NumTileColumnsMinus1                : 0                # Number of tile columns in a picture minus 1\n");
			fprintf(randomaccess, "TileColumnWidthArray                : 2 3              # Array containing tile column width values in units of CTU (from left to right in picture)\n");
			fprintf(randomaccess, "NumTileRowsMinus1                   : 0                # Number of tile rows in a picture minus 1\n");
			fprintf(randomaccess, "TileRowHeightArray                  : 2                # Array containing tile row height values in units of CTU (from top to bottom in picture)\n");
			fprintf(randomaccess, "\n");
			fprintf(randomaccess, "LFCrossTileBoundaryFlag             : 1                # In-loop filtering is across or not across tile boundary.\n");
			fprintf(randomaccess, "                                                       # 0:not across, 1: across \n");
			fprintf(randomaccess, "\n");
			fprintf(randomaccess, "#============ WaveFront ================\n");
			fprintf(randomaccess, "WaveFrontSynchro                    : 0                # 0:  No WaveFront synchronisation (WaveFrontSubstreams must be 1 in this case).\n");
			fprintf(randomaccess, "                                                       # >0: WaveFront synchronises with the LCU above and to the right by this many LCUs.\n");
			fprintf(randomaccess, "\n");
			fprintf(randomaccess, "#=========== Quantization Matrix =================\n");
			fprintf(randomaccess, "ScalingList                   : 0                      # ScalingList 0 : off, 1 : default, 2 : file read\n");
			fprintf(randomaccess, "ScalingListFile               : scaling_list.txt       # Scaling List file name. If file is not exist, use Default Matrix.\n");
			fprintf(randomaccess, "\n");
			fprintf(randomaccess, "#============ Lossless ================\n");
			fprintf(randomaccess, "TransquantBypassEnableFlag : 0                         # Value of PPS flag.\n");
			fprintf(randomaccess, "CUTransquantBypassFlagForce: 0                         # Force transquant bypass mode, when transquant_bypass_enable_flag is enabled\n");
			fprintf(randomaccess, "\n");
			fprintf(randomaccess, "#============ Rate Control ======================\n");
			fprintf(randomaccess, "RateControl                         : 0                # Rate control: enable rate control\n");
			fprintf(randomaccess, "TargetBitrate                       : 1000000          # Rate control: target bitrate, in bps\n");
			fprintf(randomaccess, "KeepHierarchicalBit                 : 2                # Rate control: 0: equal bit allocation; 1: fixed ratio bit allocation; 2: adaptive ratio bit allocation\n");
			fprintf(randomaccess, "LCULevelRateControl                 : 1                # Rate control: 1: LCU level RC; 0: picture level RC\n");
			fprintf(randomaccess, "RCLCUSeparateModel                  : 1                # Rate control: use LCU level separate R-lambda model\n");
			fprintf(randomaccess, "InitialQP                           : 0                # Rate control: initial QP\n");
			fprintf(randomaccess, "RCForceIntraQP                      : 0                # Rate control: force intra QP to be equal to initial QP\n");
			fprintf(randomaccess, "\n");
			fprintf(randomaccess, "### DO NOT ADD ANYTHING BELOW THIS LINE ###\n");
			fprintf(randomaccess, "### DO NOT DELETE THE EMPTY LINE BELOW ###\n");
			fclose(randomaccess);
		}
	}
}

void ConfigGenerator::bashGenerator() {


	for (int i = 0; i < 8; ++i) {
		std::string outputDir = "C:\\VRTest\\sequence_cvt\\" + m_videoName + "_" + videoCom.dest[i] + "\\encodeCfg";
		std::string resultDir = "C:/VRTest/sequence_cvt/" + m_videoName + "_" + videoCom.dest[i] + "/output";
		if (!boost::filesystem::exists(resultDir)) {
			boost::filesystem::create_directories(resultDir);
		}
		for (int j = 0; j < 5; ++j) {
			VideoCom common;
			int w = common.sourceSize[videoCom.str2geo[videoCom.dest[i]]][j][0];
			int h = common.sourceSize[videoCom.str2geo[videoCom.dest[i]]][j][1];
			std::string cfgName = outputDir + "\\" + videoCom.dest[i] + "_" + std::to_string(w) + "x" + std::to_string(h) + ".bat";
			std::string cfg_pause = outputDir + "\\" + videoCom.dest[i] + "_" + std::to_string(w) + "x" + std::to_string(h) + "_pause.bat";
#pragma warning (disable : 4996)
			FILE* batch = fopen(cfgName.c_str(), "w");

			const char* dest = videoCom.dest[i].c_str();
			fprintf(batch, "C:\\VRTest\\bin\\TAppEncoder.exe -c %s\\%s_%dx%d_encoder_randomaccess_main.cfg -c %s\\%s_%dx%d_encoder_360.cfg -c %s\\%s_%dx%d_360test.cfg -c C:\\VRTest\\common_cfg\\DynamicViewports.cfg --SphFile=C:\\VRTest\\common_cfg\\sphere_655362.txt >C:\\VRTest\\sequence_cvt\\%s_%s\\output\\%s_%dx%d_output.txt\n"
				, outputDir.c_str(), dest, w, h, outputDir.c_str(), dest, w, h, outputDir.c_str(), dest, w, h, m_videoName.c_str(), dest, dest, w, h);
			fclose(batch);
			//with pause
			batch = fopen(cfg_pause.c_str(), "w");
			fprintf(batch, "C:\\VRTest\\bin\\TAppEncoder.exe -c %s\\%s_%dx%d_encoder_randomaccess_main.cfg -c %s\\%s_%dx%d_encoder_360.cfg -c %s\\%s_%dx%d_360test.cfg -c C:\\VRTest\\common_cfg\\DynamicViewports.cfg --SphFile=C:\\VRTest\\common_cfg\\sphere_655362.txt >C:\\VRTest\\sequence_cvt\\%s_%s\\output\\%s_%dx%d_output.txt\n"
				, outputDir.c_str(), dest, w, h, outputDir.c_str(), dest, w, h, outputDir.c_str(), dest, w, h, m_videoName.c_str(), dest, dest, w, h);
			fprintf(batch, "pause");
			fclose(batch);
		}
	}
}
void ConfigGenerator::runBatch() {
	for (int i = 0; i < 8; ++i) {
		std::string batDir = "C:/VRTest/sequence_cvt/" + m_videoName + "_" + videoCom.dest[i] + "/encodeCfg";
		for (int j = 0; j < 5; ++j) {
			VideoCom common;
			int w = common.sourceSize[videoCom.str2geo[videoCom.dest[i]]][j][0];
			int h = common.sourceSize[videoCom.str2geo[videoCom.dest[i]]][j][1];
			std::string cfgName = batDir + "/" + videoCom.dest[i] + "_" + std::to_string(w) + "x" + std::to_string(h) + ".bat";
			system(cfgName.c_str());
		}
	}
}

