#pragma once

#include<map>
#include<iostream>


class VideoCommon {
private:

public:
	enum GeometryType
	{
		ACP = 0,
		CISP,
		CMP32,
		COHP42,
		EAC,
		ECP,
		ERP,
		our,
	};
	const static int m_projType = 8;
	const static int m_resoType = 5;
	std::map<std::string, GeometryType> str2geo;
	const int faceSize[m_projType][m_resoType][2] = {
	{{1088,1088},  {960 ,960},   {832 ,832},   {704 ,704},   {384 ,384}},
	{{920, 796},   {776, 672},   {680, 588},   {536, 464},   {328, 284}},
	{{1088,1088},  {960 ,960},   {832 ,832},   {704 ,704},   {384 ,384}},
	{{816, 708},   {1232, 1068}, {1584, 1372}, {1824, 1580}, {2064, 1788}},
	{{1088,1088},  {960 ,960},   {832 ,832},   {704 ,704},   {384 ,384}},
	{{1088,1088},  {960 ,960},   {832 ,832},   {704 ,704},   {384 ,384}},
	{{3840, 1920}, {2880, 1440}, {2560, 1280}, {2160, 1080} ,{1440, 720}},
	{{3840, 1920}, {2880, 1440}, {2560, 1280}, {2160, 1080} ,{1440, 720}}
	};
	VideoCommon();
	void initialCommon();
};

