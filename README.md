# iCub_crawling

This is the repo for new code for the iCub crawling. The code is under development :)



## Porting the old modules

### Overview of the modules

CrawlManager:

- it is the main manager module, used for high-level interface and control of the limb controllers (generators)
- input port /check_port/ gets the speed and the status from the generators
- output port /parts_port sends the parameters to each part (amplitude, stance, swing etc.)
- reads parameters from a configuration file `crawling_managerConfig.ini` which is currently in `icub_crawling/app/contexts/crawling/`
- when launched, it is expecting the generators (x6, one for each limb) to be already running and connected to the robot. if they are not running, it gives a warning but the module starts


### How to use it

How to use it on iCub:

1. launch wholeBodyTorqueObserver
2. launch gravityComp
3. launch crawlGenerator (x6) .. one for each limb! (RA, LA, RL, LL, TO, HE)
4. launch crawlManager

The terminal is used to choose the appropriate action to do:

1. init pos
2. crawl straight
3. faster
4. slower
5. turn right
6. turn left
9. stop (also closes the manager module)


### Installation

Crawl Manager can be installed using CMake

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



