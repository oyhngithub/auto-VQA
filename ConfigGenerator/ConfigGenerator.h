#pragma once

#include <string>
#include "VideoCom.h"

class ConfigGenerator {
protected:
	std::string m_videoName;
	std::string m_resolution;
	std::string m_projectionType;

	std::string m_encoder_360_format;
	std::string m_format_resolution_360test;
	std::string m_format_resolution_randomaccess_main;
	int m_frameNumber;
	int m_width;
	int m_height;
public:
	std::string m_bashName;
	ConfigGenerator();
	ConfigGenerator(char* argv);
	virtual ~ConfigGenerator() {};
	void getFrameNumber(const char* frameNumber);
	void nameReader(char* frameNumber);
	void generator();
	void getResolution();
	void getFormat();
	void encoderGenerator();
	void testGenerator();
	void randomaccessGenerator();
	void bashGenerator();
	void getInfo();
	VideoCom videoCom;
	void runBatch();
	void generateFbBatch();
	void runFbBatch();
	void generateFeatures();
	void generateFFmpegCfg();
};

