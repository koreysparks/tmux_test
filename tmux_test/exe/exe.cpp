
#pragma once
#include "log.hpp"

#include <stdio.h>
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

void Sleep(int nMilliSeconds)
{
#ifdef WIN32

	Sleep(nMilliSeconds);
#else

	usleep(1000* nMilliSeconds);

#endif

}


struct TestData
{
	char charData0[1000];
	char charData1[1000];
	char charData2[1000];
	char charData3[1000];
	char charData4[1000];
	char charData5[1000];
	char charData6[1000];
	char charData7[1000];
};


int main(const int argc, const char* argv[])
{
	
	int index = atoi(argv[1]);
	int dataCount = 1000 * 10;

	TestData* p = (TestData*)malloc(1000 * 8   * dataCount);
	CLog log(argv[1], false, false);
	if (NULL == p)
	{
		log.log("no malloc, can not exe");
		return 0;
	}

	
	log.log("start exe");
	for(size_t i = 0; i < dataCount; ++i)
	{
		for (size_t j = 0; j < 1000; ++j)
		{
			p->charData0[j] = index;
			p->charData1[j] = index;
			p->charData2[j] = index;
			p->charData3[j] = index;
			p->charData4[j] = index;
			p->charData5[j] = index;
			p->charData6[j] = index;
			p->charData7[j] = index;

		}
		++p;
	}

	log.log("stop exe");
	//free(p);




	
	return 0;
}









