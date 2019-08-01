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
#include<queue>
#include "Source.h"
#include <mutex>
#include "Input.h"
#include "Source.h"
using namespace std;

using namespace std;
using namespace InputClass;


extern std::mutex mtx;
extern queue<string> q;


void Input::InputGenerator()
{
	double SPO2;
	double Pulse_rate;
	double Temperature;
	int i = 0;
	while (true)
	{
		mtx.lock();
		string str;
		stringstream temp_str(str);
		SPO2 = Input::randSPO2();
		Pulse_rate = Input::randPulseRate();
		Temperature = Input::randTemperature();
		temp_str << "{" << "\"Patient ID\"" << " : " << "\"WP1234\"" << " , " << "\"SPO2\"" << ": " << SPO2 << ", \"Pulse_rate\"" << ": " << Pulse_rate << ", \"Temperature\"" << " :" << Temperature << "}";
		i++;
		
		q.push(temp_str.str());
		cout <<"Inside InputGenerator "<< q.front() << endl;
		mtx.unlock();
		this_thread::sleep_for(std::chrono::milliseconds(10000));


	}
}


string Input::TimeAndDate()
{
	char str[26];
	time_t result = time(0);
	ctime_s(str, sizeof(str), &result);
	string temp_string;
	int i = 0;
	while (i < 26)
	{
		temp_string.push_back(str[i]);
		i++;
	}

	return temp_string;
}

double Input::randSPO2()
{
	double lower_bound = 50;
	double upper_bound = 105;
	uniform_real_distribution<double> unif(lower_bound, upper_bound);
	static default_random_engine re;
	double a_random_double = unif(re);
	return a_random_double;
}

double Input::randTemperature()
{
	double lower_bound = 95;
	double upper_bound = 105;
	uniform_real_distribution<double> unif(lower_bound, upper_bound);
	static default_random_engine re;
	double a_random_double = unif(re);
	return a_random_double;
}

double Input::randPulseRate()
{
	double lower_bound = 20;
	double upper_bound = 250;
	uniform_real_distribution<double> unif(lower_bound, upper_bound);
	static default_random_engine re;
	double a_random_double = unif(re);
	return a_random_double;
}

