/*
input: video name frame size
output: generate different types of cfg files and bat according to the projection type in video name 

input format: 
			description
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

	ConfigGenerator configGenerator(argv[1]);
	configGenerator.nameReader(argv[2]);
	//configGenerator.generator();
	//TestRunner testRunner(configGenerator.m_bashName);
	configGenerator.generateFeatures();
	configGenerator.generateFbBatch();
	configGenerator.runFbBatch();
}