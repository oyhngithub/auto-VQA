#pragma once

#include<map>
#include<iostream>


class VideoCom {
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
	static std::map<std::string, GeometryType> str2geo;
	const static int m_projType = 8;
	const static int m_resoType = 5;
	static int sourceSize[m_projType][m_resoType][2];
	static int faceSize[m_projType][m_resoType][2];
	static int groundTruthSize[m_projType][2];
	VideoCom();
	void initialCom();
	static std::string dest[m_projType];
};

