#pragma once
#include<string>
using namespace std;
namespace InputClass
{
	class Input
	{
	public:
		static double randSPO2();
		static double randPulseRate();
		static double randTemperature();
		static string TimeAndDate();
		static void InputGenerator();
	};
}


