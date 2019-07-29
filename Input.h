#pragma once
#include<string>
using namespace std;
namespace InputClass
{
	class CInput
	{
	public:
		static double randSPO2();
		static double randPulseRate();
		static double randTemperature();
		static string timeAndDate();
		static void InputGenerator();
	};
}


