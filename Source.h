#pragma once
#include<mutex>
#include<string>

namespace DefaultValues
{
	class constParameters
	{
	public:
		const double spo2Min = 70;
		const double pulserateMax = 220;
		const double pulserateMin = 40;
		const double temperatureMax = 103.5;
	};

}
 

int monitoringSystem(rapidjson::Document& document, bool& retflag);
