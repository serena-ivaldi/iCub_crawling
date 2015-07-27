/** @file CrawlGeneratorModule.h Header file the CrawlGeneratorModule class.
*
* Version information : 1.0
*
* Date 04/05/2009
*
*/
/*
* Copyright (C) 2009 Sarah Degallier, EPFL
* RobotCub Consortium, European Commission FP6 Project IST-004370
* email: sarah.degallier@epfl.ch
* website: www.robotcub.org
* Copyright (C) 2015 Dorian Goepp, Inria, Larsen team
*
* Permission is granted to copy, distribute, and/or modify this program
* under the terms of the GNU General Public License, version 2
* or any later version published by the Free Software Foundation.
*
* A copy of the license can be found at
* http://www.robotcub.org/icub/license/gpl.txt
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
* See the GNU General Public License for more details.
*/

#ifndef CrawlGeneratorModule__H
#define CrawlGeneratorModule__H

#include <yarp/os/all.h>
#include <yarp/dev/Drivers.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/dev/ControlBoardInterfaces.h>
#include <yarp/os/RateThread.h>
#include <yarp/os/RFModule.h>

#include <stdio.h>
#include <iostream>
#include <string>
#include "Cpgs.h"
#include "CrawlInvKin.h"
#include "CrawlGeneratorThread.h"

using namespace yarp::os;
using namespace yarp::dev;
using namespace std;

#define LIMIT_TOL 2.0 //conservative limit tolerance in degrees
#define MAX_FREQUENCY 1.5 //in Hz
#define MAX_TURN_ANGLE 0.52 //in radians

#define VELOCITY_INDEX_OFFSET 1000

#define LEFT 1
#define RIGHT 2

#define ARM 1
#define LEG 2

/**
* The main crawling generator module.
* This class is responsible for recovering the necessary parameters to properly
* setup and run the periodic thread theThread, where the actual movement generation is done.
* @see GeneratorThread
*/
class CrawlGeneratorModule : public yarp::os::RFModule
{
private:
    GeneratorThread *theThread; /**< Periodic generator thread */
    std::string partName; /**< Name of the controlled part */

public:
    /**
    * Constructor of the GeneratorThread class.
    * Does nothing.
    */
    CrawlGeneratorModule();

    /**
    * Destructor of the GeneratorThread class.
    * Does nothing.
    */
    ~CrawlGeneratorModule();

    /**
    * Stops the module.
    * Stops and deletes the running loop thread theThread.
    * @return true.
    * @see GeneratorThread
    */
    virtual bool close();

    /**
    * Opens the module.
    * Recovers the part name and period for the loop thread theThread. Creates, initialise and start theThread.
    * @param s a searchable object containing all the parameters of the controlled part.
    * @return true if the theThread has been initialised properly, false otherwise.
    * @see GeneratorThread
    */
	bool configure(yarp::os::ResourceFinder &rf);

   // virtual bool open(yarp::os::Searchable &s);

    /**
    * Returns the period between two successive updates of the module.
    * Overrides the Module::getPeriod() function and returns the period between two successive calls to updateModule() by runModule().
    * @return the value of the period.
    * @see updateModule()
    */
    virtual double getPeriod();

    /**
    * Periodic update module method.
    * Does nothing.
    * @return true.
    */
    virtual bool updateModule();
};


#endif //CrawlGeneratorModule__H


