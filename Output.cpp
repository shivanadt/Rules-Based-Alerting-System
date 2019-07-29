#include <Output.h>
#include<iostream>
#include<io.h>
#include<fstream>
#include<string>
#include<thread>
#include<Windows.h>
#include<chrono>
#include<time.h>
#include <random>
#include<sstream>
#include< document.h>
#include<prettywriter.h>
#include <Source.h>
#include <mutex>
#include <Input.h>
#include <Source.h>

using namespace std;
using namespace OutputClass;
using namespace rapidjson;
using namespace InputClass;
using namespace DefaultValues;

extern std::mutex mtx;
extern std::string str;
extern std::string tempstr;

namespace OutputClass
{

	int COutput::monitoringSystem(rapidjson::Document& document, bool& retflag)
	{
		cout << "Monitoring is in process, you will get the alert once the range is deviated" << endl;
		retflag = true;
		// Log file Implentation
		ofstream logfile;
		logfile.open("logfile.txt", ios_base::app);
		//
	//	if (str.empty()) return false;
		while (true)
		{

			this_thread::sleep_for(std::chrono::milliseconds(10000));
			char buffer[255];
			int i = 0;
			while (str.empty());
			if (!str.empty())
			{
				mtx.lock();
				i = 0;
				while (str[i] != NULL)
				{
					buffer[i] = str[i];
					i++;
				}
				tempstr = str;
				str.clear();
				mtx.unlock();

			}
			document.Parse(buffer, i);
			assert(document.IsObject());
			return true;
			Value::ConstMemberIterator itr = document.MemberBegin();
			string PatientID = itr->value.GetString();
			itr++;
			while (itr != document.MemberEnd())
			{
				double tempPulseRate, tempTemperature, tempSpo2;
				string x = itr->name.GetString();
				string currTimeAndDate = CInput::timeAndDate();
				if (x == "SPO2")
				{
					tempSpo2 = itr->value.GetDouble();
					bool flag = spo2Check(tempSpo2);
					if (flag)
					{
						//tempSpo2 = itr->value.GetDouble();
						logfile << "Patient ID: " << PatientID << "  " << "SPO2:  " << tempSpo2 << "  TimeandDate:  " << currTimeAndDate << endl;
						break;
					}
				}

				else if (x == "Pulse_rate")
				{
					tempPulseRate = itr->value.GetDouble();
					bool flag = pulserateCheck(tempPulseRate);
					if (flag)
					{
						//tempPulseRate = itr->value.GetDouble();
						logfile << "Patient ID:  " << PatientID << "  " << "Pulse Rate:  " << tempPulseRate << "  TimeandDate:  " << currTimeAndDate << endl;
						break;
					}
				}
				else if (x == "Temperature")
				{
					tempTemperature = itr->value.GetDouble();
					bool flag = temperatureCheck(tempTemperature);

					if (flag)
					{
						//tempTemperature = itr->value.GetDouble();
						logfile << "Patient ID: " << PatientID << "  " << "Temperature:  " << tempTemperature << "  TimeandDate:  " << currTimeAndDate << endl;
						break;
					}
				}
				itr++;
			}
		}
		
		retflag = false;
		return {};

	}


	bool COutput::temperatureCheck(double tempTemperature)
	{
		bool flag = true;
		constParameters ConstValues;
		//double tempTemperature = itr->value.GetDouble();
		if (tempTemperature > ConstValues.temperatureMax)
		{
			cout << tempstr << ": " << "\033[1;31mCritical\033[0m\n" << endl;
			Beep(523, 500);
			cout << "-----------------------------------------------------------------------------------------------" << endl;
			flag = false;
		}
		return flag;
	}

	bool COutput::pulserateCheck(double tempPulseRate)
	{
		bool flag = true;
		constParameters ConstValues;
		//double tempPulseRate = itr->value.GetDouble();
		if (tempPulseRate < ConstValues.pulserateMin || tempPulseRate > ConstValues.pulserateMax)
		{
			cout << tempstr << ": " << "\033[1;31mCritical\033[0m\n" << endl;
			Beep(523, 500);
			flag = false;
		}
		return flag;
	}

	bool COutput::spo2Check(double tempSpo2)
	{
		bool flag = true;
		constParameters ConstValues;
		//double tempSpo2 = itr->value.GetDouble();
		if (tempSpo2 < ConstValues.spo2Min)
		{
			cout << tempstr << ": " << "\033[1;31mCritical\033[0m\n" << endl;
			Beep(523, 500);
			cout << "-----------------------------------------------------------------------------------------------" << endl;
			flag = false;
		}
		return flag;
	}


	//bool COutput::temperatureCheck(double tempTemperature)
	//{
	//	bool flag = 0;
	//	constParameters ConstValues;
	//	//double tempTemperature = itr->value.GetDouble();
	//	if (tempTemperature > ConstValues.temperatureMax)
	//	{
	//		cout << tempstr << ": " << "\033[1;31mCritical\033[0m\n" << endl;
	//		Beep(523, 500);
	//		cout << "-----------------------------------------------------------------------------------------------" << endl;
	//		flag = 1;
	//	}
	//	return flag;
	//}

	//bool COutput::pulserateCheck(Value::ConstMemberIterator itr)
	//{
	//	bool flag = 0;
	//	constParameters ConstValues;
	//	double tempPulseRate = itr->value.GetDouble();
	//	if (tempPulseRate < ConstValues.pulserateMin || tempPulseRate > ConstValues.pulserateMax)
	//	{
	//		cout << tempstr << ": " << "\033[1;31mCritical\033[0m\n" << endl;
	//		Beep(523, 500);
	//		flag = 1;
	//	}
	//	return flag;
	//}
	//
	//bool COutput::spo2Check(Value::ConstMemberIterator itr)
	//{
	//	bool flag = 0;
	//	constParameters ConstValues;
	//	double tempSpo2 = itr->value.GetDouble();
	//	if (tempSpo2 < ConstValues.spo2Min || tempSpo2 > ConstValues.spo2Max)
	//	{
	//		cout << tempstr << ": " << "\033[1;31mCritical\033[0m\n" << endl;
	//		Beep(523, 500);
	//		cout << "-----------------------------------------------------------------------------------------------" << endl;
	//		flag = 1;
	//	}
	//	return flag;
	//}

}