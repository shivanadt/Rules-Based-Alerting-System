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
#include "Input.h"
#include "Output.h"
#include "Source.h"
#include<queue>



using namespace std;
using namespace rapidjson;
using namespace InputClass;
using namespace OutputClass;

std::mutex mtx;
queue<string> q;

int main()
{
	
	thread t2(Input::InputGenerator);
	thread t1(Output::MonitoringSystem);
	t1.join();
	t2.join();
}




