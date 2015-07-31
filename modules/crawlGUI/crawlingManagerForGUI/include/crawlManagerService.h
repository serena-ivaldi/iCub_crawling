// This is an automatically-generated file.
// It could get re-generated if the ALLOW_IDL_GENERATION flag is on.

#ifndef YARP_THRIFT_GENERATOR_crawlManagerService
#define YARP_THRIFT_GENERATOR_crawlManagerService

#include <yarp/os/Wire.h>
#include <yarp/os/idl/WireTypes.h>

class crawlManagerService;


class crawlManagerService : public yarp::os::Wire {
public:
  crawlManagerService();
  virtual bool start();
  virtual bool stop();
  virtual bool is_running();
  virtual bool startCrawling();
  virtual bool stopCrawling();
  virtual bool goToInitPose();
  virtual bool faster();
  virtual bool slower();
  virtual bool turnRight();
  virtual bool turnLeft();
  virtual bool toggleVerbosity();
  virtual bool checkConnections();
  virtual bool read(yarp::os::ConnectionReader& connection);
  virtual std::vector<std::string> help(const std::string& functionName="--all");
};

#endif

