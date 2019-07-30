#pragma once
#include<document.h>
#include<prettywriter.h>

using namespace rapidjson;

namespace OutputClass
{
	class COutput
	{
	public:
		static bool temperatureCheck(double tempTemperature);
		static bool pulserateCheck(double tempPulseRate);
		static bool spo2Check(double tempSpo2);
		static int monitoringSystem(rapidjson::Document&, bool&);
	};
}


