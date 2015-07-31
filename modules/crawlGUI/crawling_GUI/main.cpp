#include "mainwindow.h"
#include <QApplication>

#include <yarp/os/all.h>
#include <iostream>

using namespace std;
using namespace yarp::os;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    yarp::os::ResourceFinder rf;
    rf.setVerbose(true);
    rf.setDefaultContext("crawling");               //overridden by --context parameter
    rf.setDefaultConfigFile("crawlmanagergui.ini");  //overridden by --from parameter
    rf.configure(argc,argv);


    Network yarp;

    if (!yarp.checkNetwork())
    {
        yError("Sorry YARP network does not seem to be available, is the yarp server available?\n");
        return 1;
    }

    //create and run the GUI
    MainWindow w;
    w.show();

    return a.exec();
}
