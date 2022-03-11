
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

CLog				g_log("test_tmux", false, false);

void Sleep(int nMilliSeconds)
{
#ifdef WIN32

	Sleep(nMilliSeconds);
#else

	usleep(1000* nMilliSeconds);

#endif

}


void* testTmux(void* lParam)
{
	long* p = (long*)(lParam);
	char index[4];
	memset(index, 0, 4);
	sprintf(index, "%ld", *p);

	printf ("start tmux window %s\n", index );
	system(("./start_primary.sh " + string(index)).c_str());
	
	Sleep(60000);
	
	printf ("end tmux window %s\n", index ) ;

	return NULL;
}



int main()
{
	long threadCount = 50 * 1000 ;
	CThread thread[threadCount];

	for (long index = 0; index < threadCount; ++index)
	{
		g_log.log("start test tmux thread %d", index);
		thread[index].init(testTmux, (void*)(&index));
		Sleep(10);
		g_log.log("end test tmux thread %d", index);
	}


	
	return 0;
}









