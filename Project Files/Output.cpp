#include "Output.h"
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
#include "Source.h"
#include <mutex>
#include<queue>
#include "Input.h"
#include "Source.h"

using namespace std;
using namespace OutputClass;
using namespace rapidjson;
using namespace InputClass;
using namespace DefaultValues;

extern std::mutex mtx;
extern queue<string > q;

string tempstr;

bool Output::MonitoringSystem()
{

	// Log file Implentation
	ofstream logfile;
	logfile.open("logfile.txt", ios_base::app);
	//
	Document document;
	while (true)
	{
		char buffer[255];
		int i = 0;
		try
		{
			while (q.empty());
			if (!q.empty())
			{
				string str = q.front();
				q.pop();
				mtx.lock();
				i = 0;
				while (str[i] != NULL)
				{
					buffer[i] = str[i];
					i++;
				}
				tempstr = str;
				cout << "Inside monitoring system " << tempstr << endl;
				str.clear();
				mtx.unlock();
			}

		} 
		catch (...)
		{
			cout << "Exception while creating buffer" << endl;
		}
		try
		{
			document.Parse(buffer, i);
			assert(document.IsObject());
		}
		catch (...)
		{
			cout << "The input string is not in JSON format" << endl;
		}
		
		Value::ConstMemberIterator itr = document.MemberBegin();
		string PatientID = itr->value.GetString();
		itr++;
		try
		{
			while (itr != document.MemberEnd())
			{
				double tempPulseRate, tempTemperature, tempSpo2;
				string x = itr->name.GetString();
				string currTimeAndDate = Input::TimeAndDate();
				if (x == "SPO2")
				{
					double temp = itr->value.GetDouble();
					bool flag = spo2Check(temp);
					if (flag)
					{
						tempSpo2 = itr->value.GetDouble();
						logfile << "Patient ID: " << PatientID << "  " << "SPO2:  " << tempSpo2 << "  TimeandDate:  " << currTimeAndDate << endl;
						break;
					}
				}

				else if (x == "Pulse_rate")
				{
					double temp = itr->value.GetDouble();
					bool flag = pulserateCheck(temp);
					if (flag)
					{
						tempPulseRate = itr->value.GetDouble();
						logfile << "Patient ID:  " << PatientID << "  " << "Pulse Rate:  " << tempPulseRate << "  TimeandDate:  " << currTimeAndDate << endl;
						break;
					}
				}
				else if (x == "Temperature")
				{
					double temp = itr->value.GetDouble();
					bool flag = temperatureCheck(itr->value.GetDouble());

					if (flag)
					{
						tempTemperature = itr->value.GetDouble();
						logfile << "Patient ID: " << PatientID << "  " << "Temperature:  " << tempTemperature << "  TimeandDate:  " << currTimeAndDate << endl;
						break;
					}
				}
				itr++;
			}
		}
			catch (...)
			{
				cout << "Errow while printing" << endl;
			}
		
		this_thread::sleep_for(std::chrono::milliseconds(10000));
	}
	return true;
}

bool Output::temperatureCheck(double tempTemperature)
{
	bool flag = 0;
	ConstParameters ConstValues;
	if (tempTemperature > ConstValues.temperatureMax)
	{
		cout << tempstr << ": " << "\033[1;31mCritical\033[0m\n" << endl;
		Beep(523, 500);
		cout << "-----------------------------------------------------------------------------------------------" << endl;
		flag = 1;
	}
	return flag;
}

bool Output::pulserateCheck(double tempPulseRate)
{
	bool flag = 0;
	ConstParameters ConstValues;
	if (tempPulseRate < ConstValues.pulserateMin || tempPulseRate > ConstValues.pulserateMax)
	{
		cout << tempstr << ": " << "\033[1;31mCritical\033[0m\n" << endl;
		Beep(523, 500);
		flag = 1;
	}
	return flag;
}

bool Output::spo2Check(double tempSpo2)
{
	bool flag = 0;
	ConstParameters ConstValues;
	if (tempSpo2 < ConstValues.spo2Min || tempSpo2 > ConstValues.spo2Max)
	{
		cout << tempstr << ": " << "\033[1;31mCritical\033[0m\n" << endl;
		Beep(523, 500);
		cout << "-----------------------------------------------------------------------------------------------" << endl;
		flag = 1;
	}
	return flag;
}

