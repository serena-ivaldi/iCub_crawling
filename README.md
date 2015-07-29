# iCub_crawling

This is the repo for new code for the iCub crawling. The code is under development :)

## Overview of the modules

CrawlManager:

- it is the main manager module, used for high-level interface and control of the limb controllers (generators)
- input port /check_port/ gets the speed and the status from the generators
- output port /parts_port sends the parameters to each part (amplitude, stance, swing etc.)
- reads parameters from a configuration file `crawling_managerConfig.ini` which is currently in `icub_crawling/app/contexts/crawling/`
- when launched, it is expecting the generators (x6, one for each limb) to be already running and connected to the robot. if they are not running, it gives a warning but the module starts

CrawlGenerator:

- lower level module generating the motion patterns, using parameters given by the CrawlManager module
- this class is instanciated once for each robot part :
    - the two arms
    - the two legs
    - the head
    - the torso
    each instance needs a parameter file describing the limb to be controlled
- through connexions to other instances of this class, it couples the motion of the body parts_port
- the actual velocity control of  the actuators is delegated to the velocityControl module to which it sends the desired velocities
- one instance of CrawlGenerator needs a corresponding one of velocityControl


## Compiling and installation

For the three modules:

~~~shell
cd iCub_crawling/modules/crawlManager
mkdir build
cd build
ccmake ..
make
~~~

To make sure the configuration file `crawling_managerConfig.ini` is read correctly by the module, add these lines to your `.bashrc` (if you are on Linux) or `.bash_profile` (if you are on OSX).

~~~
export crawling_app=PATH_WHERE_YOU_PUT_THE_CRAWLING_PROJECT/iCub_crawling/app/
export YARP_DATA_DIRS=$YARP_DATA_DIRS:$crawling_app
~~~

Then, the crawlGenerator module can be compiled using the came process :

~~~shell
cd iCub_crawling/modules/crawlGenerator
mkdir build
cd build
ccmake ..
make
~~~

To allow the programs to be executed without the need to explicitly type theyr path, one has also to update the `PATH` environment variable as follows. `pathToTheRepository` has to be changed to the real path to this code source.

~~~shell
export crawling_root=/pathToTheRepository/iCub_crawling
export PATH=$PATH:$crawling_root/modules/crawlGenerator/build:$crawling_root/modules/crawlManager/build
export PATH=$PATH:$crawling_root/app/contexts/crawling
~~~

It is possible not to do this, but then yarpmanager won't be able to find the crawlGenerator modules.


## How to use it

For now, the ports the crawlGenerator connects to are hard-coded in the source. Thus, it would only work with iCub_SIM out of the box but one could change the port names in `generatorThread.cpp` to use the Gazebo simulator or the actual robot. Also the application description file `crawling.xml` should be adapted.

How to use it on iCub:

1. start the yarp server with `yarpserver`
2. start the gazebo simulator and insert the iCub into the world
3. move to the `app` folder
4. launch the yarp manager with the application description for the crawlGenerator module
    ~~~
    yarpmanager --application yarpmananger/crawling-gazebo.xml
    ~~~
    One only needs to open the Crawling applicaion (couble-click on it) and launch it by pressing the green button with a play-like shape.
5. launch crawlManager (from `modules/crawlManager/build`)

The terminal is used to choose the appropriate action to do:

1. init pos
2. crawl straight
3. faster
4. slower
5. turn right
6. turn left
9. stop (also closes the manager module)