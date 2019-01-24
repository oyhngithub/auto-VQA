#pragma once
#include "VideoCommon.h"
class CvtConfigGenerator
{
private:
	std::string m_inputVideoName;
	std::string m_testName;
	std::string m_cvtFileName;
	std::string m_resolution;
	std::string m_description;
	int m_width;
	int m_height;
	int m_frameSize;
	
public:
	CvtConfigGenerator(char* inputVideoName);
	CvtConfigGenerator();
	void testGenerate(char* inputVideoName, int width, int height, int frameSize);
	void convertGenerate(int width, int height);
	void convertGenerate();
	~CvtConfigGenerator();
	VideoCommon videoCommon;
	void batGenerate();
	void runBatch();
	void getInfo();
	void shellGenerate();
};

