
#include "CrawlGeneratorModule.h"

#include <yarp/os/Os.h>
#include <stdio.h>
#include <string>

#define DEBUG 0

#define SGN(a) (a<0 ? -1 : 1)
#define ABS(a) (a<0 ? -a : a)

//#include <ppEventDebugger.h>

CrawlGeneratorModule::CrawlGeneratorModule()
{
}

CrawlGeneratorModule::~CrawlGeneratorModule()
{
}

double CrawlGeneratorModule::getPeriod()

{

	//    printf("Crawl Generator Module is running\n");

	return 1.0;

}



bool CrawlGeneratorModule::updateModule()
{
	return true;

}


bool CrawlGeneratorModule::close()
{
	theThread->stop();
	delete theThread;
	fprintf(stderr, "%s module closed\n", partName.c_str());
	return true;
}


bool CrawlGeneratorModule::configure(yarp::os::ResourceFinder &rf)
{
	Property options(rf.toString().c_str());
	int period = 25; // in ms

	if(options.check("period"))
	{
		period = options.find("period").asInt();
	}

	if(options.check("part"))
	{
		partName=options.find("part").asString().c_str();
		printf("module taking care of part %s\n",partName.c_str());
	}


	theThread = new GeneratorThread(period);
	if(!theThread->init(rf))
	{
		printf("Failed to initialize the thread\n");
		fflush(stdout);
		return false;
	}

	theThread->start();

	return true;

}

