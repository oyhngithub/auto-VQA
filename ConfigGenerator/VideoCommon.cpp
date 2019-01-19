#include"VideoCommon.h"

VideoCommon::VideoCommon() {};

void VideoCommon::initialCommon() {
	str2geo = { {"ERP", ERP}, {"CMP32", CMP32}, {"EAC", EAC}, {"COHP42", COHP42}, {"CISP", CISP}, {"ECP", ECP}
	,{"RSP", RSP}, {"TSP", TSP}, {"ACP", ACP}, {"our", our} };
}
