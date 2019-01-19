#pragma once

#include<map>
class VideoCommon {
private:

public:
	enum GeometryType
	{
		ERP = 0,
		CMP32,
		EAC,
		COHP42,
		CISP,
		ECP,
		RSP,
		TSP,
		ACP,
		our,
	};
	 std::map<std::string, GeometryType> str2geo;

	VideoCommon();
	void initialCommon();
};

