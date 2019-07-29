#include<iostream>
//#include<io.h>
#include<fstream>
#include<string>
#include<thread>
//#include<Windows.h>
#include<chrono>
//#include<time.h>
#include <random>
#include<sstream>
#include< document.h>
#include<prettywriter.h>
#include <Source.h>
#include <mutex>
#include <Input.h>
#include <Output.h>
#include <Source.h>



using namespace std;
using namespace rapidjson;
using namespace InputClass;
using namespace OutputClass;

std::mutex mtx;
std::string str = "";
std::string tempstr = "";

int main()
{
	thread t_start(CInput::InputGenerator);
	Document document;
	bool retflag;
	int retval = COutput::monitoringSystem(document, retflag);
	//int retval = output::monitoringSystem(document, retflag);
	if (retflag) return retval;
}




