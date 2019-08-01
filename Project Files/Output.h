#pragma once
#include<document.h>
#include<prettywriter.h>

using namespace rapidjson;

namespace OutputClass
{
	class Output
	{
	public:
		static bool temperatureCheck(double);
		static bool pulserateCheck(double);
		static bool spo2Check(double);
		static bool MonitoringSystem();
		static rapidjson::Document bufferParsor();
	};
}


