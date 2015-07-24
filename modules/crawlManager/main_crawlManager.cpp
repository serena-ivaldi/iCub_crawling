
// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/* 
 * Copyright (C) 2015 Serena Ivaldi (INRIA)
 * email:   serena.ivaldi@inria.fr
 *
 *
 * Copyright (C) 2008 Sarah Degallier Ludovic Righetti BIRG EPFL Lausanne
 * RobotCub Consortium, European Commission FP6 Project IST-004370
 * email:   sarah.degallier@robotcub.org ludovic.righetti@a3.epfl.ch
 * website: www.robotcub.org
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
 */

/**
 * @ingroup icub_crawling
 *
 * \defgroup icub_crawlManager crawlManager
 *
 * This module is part of the application \ref icub_crawlingDemo "crawlingDemo".
 * It is an updated version based on the crawling demo performed at the end of the Robotcub project.
 *
 *\section intro_sec Description 
 *
 * This module send the appropriate parameters for the dynamical systems generating the trajectories (\ref icub_crawlGenerator "crawlGenerator") according to the chosen behavior. It sends the parameters at timing corresponding to the beat of each of the part.If you want to  use the whole drumming application, please refer to \ref icub_crawlingDemo "crawlingDemo". 
 *
 *\section lib_sec Libraries
 *
 *No external libraries
 *
 *
 *\section parameters_sec Parameters
 *
 * Parameters are read by default from the config file managerConfig.ini 
 *
 *
 *\section tested_os_sec Tested OS
 *
 * This module is under development.
 *
 *\section example_sec Example Instantiation of the Module
 *
 * ./crawlManager
 *
 **/



#include <iostream>
#include <yarp/os/all.h>
#include "CrawlManagerModule.h"

using namespace std;
using namespace yarp::os;


int main(int argc, char *argv[])
{

	ResourceFinder rf;
    rf.setVerbose(true);
    rf.setDefaultContext("crawling");
    //SI: was before -> but now context has changed
    //rf.setDefaultContext("crawlingApplication/conf");
	
    rf.setDefaultConfigFile("crawling_managerConfig.ini");
    //SI: was before located -> ICUB_ROOT\contrib\src\crawlingTest\app\conf\managerConfig.ini
    
    rf.configure(argc, argv);
    
    if (rf.check("help"))
    {
        cout << "Options:" << endl << endl;
        cout << "\t--robot      robot: the robot name. default: iCub" << endl;
        
        return 0;
    }
	
    Network yarp;
    
    if (!yarp.checkNetwork())
    {
        yError("Sorry YARP network does not seem to be available, is the yarp server available?\n");
        return 1;
    }
    
    //create and run the Crawl generator module
    CrawlManagerModule mod;
    return mod.runModule(rf);

}

