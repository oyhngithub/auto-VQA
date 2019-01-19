#pragma once
#include "VideoCommon.h"
class CvtConfigGenerator
{
protected:
	std::string m_inputVideoName;
	std::string m_testName;
	std::string m_cvtName;
	std::string m_resolution;
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
};

