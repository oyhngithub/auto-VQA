#pragma once
#include "VideoCommon.h"
#include "iostream"

class CvtConfigGenerator
{
private:
	std::string m_inputVideoName;
	std::string m_testName;
	std::string m_cvtFileName;
	std::string m_resolution;
	std::string m_description;
	std::string m_baseDir;
	int m_frameCnt;
	int m_width;
	int m_height;
	int m_frameSize;
	
public:
	CvtConfigGenerator(char* baseDir, char* inputVideoName, int frameCnt);
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

