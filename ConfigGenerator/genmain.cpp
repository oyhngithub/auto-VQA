/*
input: video name frame size
output: generate different types of cfg files and bat according to the projection type in video name 

input format: 
			G1AbandonedKingdom_7680x3840_fps30_82_yuv420.yuv 1
output format: 
			dir:C:\VRTest\sequence_cvt\description\format\
			sphere_655362.txt
			DynamicViewports.cfg
			encoder_360_format.cfg
			format_widthxheight_360test.cfg
			format_widthxheight_encoder_randomaccess_main.cfg
			format_widthxheight_test.bat
*/
#include "ConfigGenerator.h"
#include "cstdio"
#include "assert.h"
#include "TestRunner.h"


int main(int argc, char* argv[]) {
	
	if (argc != 3) {
		printf("Please input file name, frame number before start!(like: Format_WidthxHeight_***.yuv 18)\n");
		return 0;
	}
	std::string fullName = argv[1];
	int head = fullName.find("_") + 1;
	std::string desc = fullName.substr(0, head - 1);


	ConfigGenerator configGenerator(fullName, desc.c_str());
	configGenerator.nameReader(argv[2]);
	configGenerator.generator();//Generate file for Encoder
	//TestRunner testRunner(configGenerator.m_bashName);
	//configGenerator.generateFeatures();
	//configGenerator.generateFbBatch();
	//configGenerator.runFbBatch();
	//configGenerator.generateFFmpegCfg();
}