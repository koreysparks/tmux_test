
#pragma once
#include "log.hpp"
#include "thread.hpp"


#include <fstream>
#include <sstream>
#include <iostream>
#include <string.h>
#include <ctime>
#include <map>
#include <assert.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include<unistd.h>

#include<sys/wait.h>

using namespace std;

using namespace pp;

CLog				g_log("test", false, false);


void Sleep(int nMilliSeconds)
{
#ifdef WIN32

	Sleep(nMilliSeconds);
#else

	usleep(1000* nMilliSeconds);

#endif

}


void* runBK(void* lParam)
{
	long* p = (long*)(lParam);
	char index[10];
	memset(index, 0, 10);
	sprintf(index, "%ld", *p);
	system("cd bk " );
	system(("mkdir -p  " + string(index)).c_str());
	system(("cd " + string(index)).c_str());
	system(("./exe " + string(index)).c_str());

	return NULL;

}

void* runRS(void* lParam)
{
	long* p = (long*)(lParam);
	char index[10];
	memset(index, 0, 10);
	sprintf(index, "%ld", *p);
	system("cd rs " );
	system(("mkdir -p  " + string(index)).c_str());
	system(("cd " + string(index)).c_str());
	system(("./exe " + string(index)).c_str());

	return NULL;
}

void* testTmux(void* lParam)
{
	long* p = (long*)(lParam);
	char index[10];
	memset(index, 0, 10);
	sprintf(index, "%ld", *p);

	printf ("start without tmux window %s", index );
	string in = "" ;
	CThread threadBK, threadRS;
	threadBK.init(runBK, lParam);
	threadRS.init(runRS, lParam);
	Sleep(1000 * 10);
	printf ("end without tmux window %s", index ) ;

	return NULL;
}



int main()
{
	long threadCount = 1000 ;
	CThread thread[1000];

	for (long index = 0; index < threadCount; ++index)
	{
		g_log.log("start test tmux thread %d", index);
		thread[index].init(testTmux, (void*)(&index));
		Sleep(1000);
		g_log.log("end test tmux thread %d", index);
	}


	
	return 0;
}









