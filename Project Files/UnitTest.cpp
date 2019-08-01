#include "pch.h"
#include <CppUnitTest.h>
#include "Debug/..//..//Test/Output.h"
#include <mutex>
#include<queue>
#include<string>
using namespace std;


extern std::mutex mtx;
extern queue<string> q;
extern std::string tempstr;



using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OutputClass;
using namespace std;

namespace UnitTest1
{
	TEST_CLASS(Test_output)
	{
		TEST_METHOD(temperatureCheck_InAboveRange)
		{
			//output::temperatureCheck(10.1);
			//output::pulserateCheck(100);
			//output::spo2Check(80);
			Assert::AreEqual(Output::temperatureCheck(190), false);
		}

		TEST_METHOD(temperatureCheck_WithInRange)
		{
			//output::temperatureCheck(10.1);
			//output::pulserateCheck(100);
			//output::spo2Check(80);
			Assert::AreEqual(Output::temperatureCheck(100), true);
		}

		TEST_METHOD(pulserateCheck_WithInRange)
		{
			Assert::AreEqual(Output::pulserateCheck(80), true);
			/*output::temperatureCheck(10.1);
			output::pulserateCheck(100);
			output::spo2Check(80);*/
		}

		TEST_METHOD(pulserateCheck_InAboveOrBelowRange)
		{
			Assert::AreEqual(Output::pulserateCheck(0), false);
			/*output::temperatureCheck(10.1);
			output::pulserateCheck(100);
			output::spo2Check(80);*/
		}

		TEST_METHOD(spo2Check_WithInRange)
		{
			Assert::AreEqual(Output::spo2Check(100), true);
			/*output::temperatureCheck(10.1);
			output::pulserateCheck(100);
			output::spo2Check(80);*/
		}

		TEST_METHOD(spo2Check_InAboveOrBelowRange)
		{
			Assert::AreEqual(Output::spo2Check(35), false);
			/*output::temperatureCheck(10.1);
			output::pulserateCheck(100);
			output::spo2Check(80);*/
		}

		TEST_METHOD(monitoringsystem_InputValidOrInvalid)
		{
			Document document;
			string str = " { \"Patient ID\" : \"WP1234\", \"SPO2\" : 70 , \"Pulse_rate\" : 80, \"Temperature\": 102} ";
			q.push(str);
			Assert::AreEqual((bool)Output::MonitoringSystem(), true);
			/*output::temperatureCheck(10.1);
			output::pulserateCheck(100);
			output::spo2Check(80);*/
		}
	};
}
