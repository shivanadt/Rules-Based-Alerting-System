#include "pch.h"
#include <CppUnitTest.h>
#include <Output.h>
#include <mutex>

extern std::mutex mtx;
extern std::string str;
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
			Assert::AreEqual(COutput::temperatureCheck(190),false);
		}

		TEST_METHOD(temperatureCheck_WithInRange)
		{
			//output::temperatureCheck(10.1);
			//output::pulserateCheck(100);
			//output::spo2Check(80);
			Assert::AreEqual(COutput::temperatureCheck(100), true);
		}

		TEST_METHOD(pulserateCheck_WithInRange)
		{
			Assert::AreEqual(COutput::pulserateCheck(80), true);
			/*output::temperatureCheck(10.1);
			output::pulserateCheck(100);
			output::spo2Check(80);*/
		}

		TEST_METHOD(pulserateCheck_InAboveOrBelowRange)
		{
			Assert::AreEqual(COutput::pulserateCheck(0), false);
			/*output::temperatureCheck(10.1);
			output::pulserateCheck(100);
			output::spo2Check(80);*/
		}

		TEST_METHOD(spo2Check_WithInRange)
		{
			Assert::AreEqual(COutput::spo2Check(100), true);
			/*output::temperatureCheck(10.1);
			output::pulserateCheck(100);
			output::spo2Check(80);*/
		}

		TEST_METHOD(spo2Check_InAboveOrBelowRange)
		{
			Assert::AreEqual(COutput::spo2Check(35), false);
			/*output::temperatureCheck(10.1);
			output::pulserateCheck(100);
			output::spo2Check(80);*/
		}

		TEST_METHOD(monitoringsystem_InputValidOrInvalid)
		{
			Document document;
			str = " { \"Patient ID\" : \"WP1234\", \"SPO2\" : 70 , \"Pulse_rate\" : 80, \"Temperature\": 102} ";
			//str = "";
			bool retflag = false;
			Assert::AreEqual((bool)COutput::monitoringSystem(document,retflag), true);
			/*output::temperatureCheck(10.1);
			output::pulserateCheck(100);
			output::spo2Check(80);*/
		}
	};
}
