// This is an automatically-generated file.
// It could get re-generated if the ALLOW_IDL_GENERATION flag is on.

#include <crawlManagerService.h>
#include <yarp/os/idl/WireTypes.h>



class crawlManagerService_start : public yarp::os::Portable {
public:
  bool _return;
  void init();
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class crawlManagerService_stop : public yarp::os::Portable {
public:
  bool _return;
  void init();
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class crawlManagerService_is_running : public yarp::os::Portable {
public:
  bool _return;
  void init();
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class crawlManagerService_startCrawling : public yarp::os::Portable {
public:
  bool _return;
  void init();
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class crawlManagerService_stopCrawling : public yarp::os::Portable {
public:
  bool _return;
  void init();
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class crawlManagerService_goToInitPose : public yarp::os::Portable {
public:
  bool _return;
  void init();
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class crawlManagerService_faster : public yarp::os::Portable {
public:
  bool _return;
  void init();
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class crawlManagerService_slower : public yarp::os::Portable {
public:
  bool _return;
  void init();
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class crawlManagerService_turnRight : public yarp::os::Portable {
public:
  bool _return;
  void init();
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class crawlManagerService_turnLeft : public yarp::os::Portable {
public:
  bool _return;
  void init();
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class crawlManagerService_toggleVerbosity : public yarp::os::Portable {
public:
  bool _return;
  void init();
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class crawlManagerService_checkConnections : public yarp::os::Portable {
public:
  bool _return;
  void init();
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

bool crawlManagerService_start::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(1)) return false;
  if (!writer.writeTag("start",1,1)) return false;
  return true;
}

bool crawlManagerService_start::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readBool(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void crawlManagerService_start::init() {
  _return = false;
}

bool crawlManagerService_stop::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(1)) return false;
  if (!writer.writeTag("stop",1,1)) return false;
  return true;
}

bool crawlManagerService_stop::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readBool(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void crawlManagerService_stop::init() {
  _return = false;
}

bool crawlManagerService_is_running::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(2)) return false;
  if (!writer.writeTag("is_running",1,2)) return false;
  return true;
}

bool crawlManagerService_is_running::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readBool(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void crawlManagerService_is_running::init() {
  _return = false;
}

bool crawlManagerService_startCrawling::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(1)) return false;
  if (!writer.writeTag("startCrawling",1,1)) return false;
  return true;
}

bool crawlManagerService_startCrawling::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readBool(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void crawlManagerService_startCrawling::init() {
  _return = false;
}

bool crawlManagerService_stopCrawling::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(1)) return false;
  if (!writer.writeTag("stopCrawling",1,1)) return false;
  return true;
}

bool crawlManagerService_stopCrawling::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readBool(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void crawlManagerService_stopCrawling::init() {
  _return = false;
}

bool crawlManagerService_goToInitPose::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(1)) return false;
  if (!writer.writeTag("goToInitPose",1,1)) return false;
  return true;
}

bool crawlManagerService_goToInitPose::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readBool(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void crawlManagerService_goToInitPose::init() {
  _return = false;
}

bool crawlManagerService_faster::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(1)) return false;
  if (!writer.writeTag("faster",1,1)) return false;
  return true;
}

bool crawlManagerService_faster::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readBool(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void crawlManagerService_faster::init() {
  _return = false;
}

bool crawlManagerService_slower::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(1)) return false;
  if (!writer.writeTag("slower",1,1)) return false;
  return true;
}

bool crawlManagerService_slower::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readBool(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void crawlManagerService_slower::init() {
  _return = false;
}

bool crawlManagerService_turnRight::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(1)) return false;
  if (!writer.writeTag("turnRight",1,1)) return false;
  return true;
}

bool crawlManagerService_turnRight::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readBool(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void crawlManagerService_turnRight::init() {
  _return = false;
}

bool crawlManagerService_turnLeft::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(1)) return false;
  if (!writer.writeTag("turnLeft",1,1)) return false;
  return true;
}

bool crawlManagerService_turnLeft::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readBool(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void crawlManagerService_turnLeft::init() {
  _return = false;
}

bool crawlManagerService_toggleVerbosity::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(1)) return false;
  if (!writer.writeTag("toggleVerbosity",1,1)) return false;
  return true;
}

bool crawlManagerService_toggleVerbosity::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readBool(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void crawlManagerService_toggleVerbosity::init() {
  _return = false;
}

bool crawlManagerService_checkConnections::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(1)) return false;
  if (!writer.writeTag("checkConnections",1,1)) return false;
  return true;
}

bool crawlManagerService_checkConnections::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readBool(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void crawlManagerService_checkConnections::init() {
  _return = false;
}

crawlManagerService::crawlManagerService() {
  yarp().setOwner(*this);
}
bool crawlManagerService::start() {
  bool _return = false;
  crawlManagerService_start helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","bool crawlManagerService::start()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
bool crawlManagerService::stop() {
  bool _return = false;
  crawlManagerService_stop helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","bool crawlManagerService::stop()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
bool crawlManagerService::is_running() {
  bool _return = false;
  crawlManagerService_is_running helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","bool crawlManagerService::is_running()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
bool crawlManagerService::startCrawling() {
  bool _return = false;
  crawlManagerService_startCrawling helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","bool crawlManagerService::startCrawling()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
bool crawlManagerService::stopCrawling() {
  bool _return = false;
  crawlManagerService_stopCrawling helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","bool crawlManagerService::stopCrawling()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
bool crawlManagerService::goToInitPose() {
  bool _return = false;
  crawlManagerService_goToInitPose helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","bool crawlManagerService::goToInitPose()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
bool crawlManagerService::faster() {
  bool _return = false;
  crawlManagerService_faster helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","bool crawlManagerService::faster()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
bool crawlManagerService::slower() {
  bool _return = false;
  crawlManagerService_slower helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","bool crawlManagerService::slower()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
bool crawlManagerService::turnRight() {
  bool _return = false;
  crawlManagerService_turnRight helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","bool crawlManagerService::turnRight()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
bool crawlManagerService::turnLeft() {
  bool _return = false;
  crawlManagerService_turnLeft helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","bool crawlManagerService::turnLeft()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
bool crawlManagerService::toggleVerbosity() {
  bool _return = false;
  crawlManagerService_toggleVerbosity helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","bool crawlManagerService::toggleVerbosity()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
bool crawlManagerService::checkConnections() {
  bool _return = false;
  crawlManagerService_checkConnections helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","bool crawlManagerService::checkConnections()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}

bool crawlManagerService::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  reader.expectAccept();
  if (!reader.readListHeader()) { reader.fail(); return false; }
  yarp::os::ConstString tag = reader.readTag();
  bool direct = (tag=="__direct__");
  if (direct) tag = reader.readTag();
  while (!reader.isError()) {
    // TODO: use quick lookup, this is just a test
    if (tag == "start") {
      bool _return;
      _return = start();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeBool(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "stop") {
      bool _return;
      _return = stop();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeBool(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "is_running") {
      bool _return;
      _return = is_running();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeBool(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "startCrawling") {
      bool _return;
      _return = startCrawling();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeBool(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "stopCrawling") {
      bool _return;
      _return = stopCrawling();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeBool(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "goToInitPose") {
      bool _return;
      _return = goToInitPose();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeBool(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "faster") {
      bool _return;
      _return = faster();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeBool(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "slower") {
      bool _return;
      _return = slower();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeBool(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "turnRight") {
      bool _return;
      _return = turnRight();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeBool(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "turnLeft") {
      bool _return;
      _return = turnLeft();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeBool(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "toggleVerbosity") {
      bool _return;
      _return = toggleVerbosity();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeBool(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "checkConnections") {
      bool _return;
      _return = checkConnections();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeBool(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "help") {
      std::string functionName;
      if (!reader.readString(functionName)) {
        functionName = "--all";
      }
      std::vector<std::string> _return=help(functionName);
      yarp::os::idl::WireWriter writer(reader);
        if (!writer.isNull()) {
          if (!writer.writeListHeader(2)) return false;
          if (!writer.writeTag("many",1, 0)) return false;
          if (!writer.writeListBegin(BOTTLE_TAG_INT, static_cast<uint32_t>(_return.size()))) return false;
          std::vector<std::string> ::iterator _iterHelp;
          for (_iterHelp = _return.begin(); _iterHelp != _return.end(); ++_iterHelp)
          {
            if (!writer.writeString(*_iterHelp)) return false;
           }
          if (!writer.writeListEnd()) return false;
        }
      reader.accept();
      return true;
    }
    if (reader.noMore()) { reader.fail(); return false; }
    yarp::os::ConstString next_tag = reader.readTag();
    if (next_tag=="") break;
    tag = tag + "_" + next_tag;
  }
  return false;
}

std::vector<std::string> crawlManagerService::help(const std::string& functionName) {
  bool showAll=(functionName=="--all");
  std::vector<std::string> helpString;
  if(showAll) {
    helpString.push_back("*** Available commands:");
    helpString.push_back("start");
    helpString.push_back("stop");
    helpString.push_back("is_running");
    helpString.push_back("startCrawling");
    helpString.push_back("stopCrawling");
    helpString.push_back("goToInitPose");
    helpString.push_back("faster");
    helpString.push_back("slower");
    helpString.push_back("turnRight");
    helpString.push_back("turnLeft");
    helpString.push_back("toggleVerbosity");
    helpString.push_back("checkConnections");
    helpString.push_back("help");
  }
  else {
    if (functionName=="start") {
      helpString.push_back("bool start() ");
    }
    if (functionName=="stop") {
      helpString.push_back("bool stop() ");
    }
    if (functionName=="is_running") {
      helpString.push_back("bool is_running() ");
    }
    if (functionName=="startCrawling") {
      helpString.push_back("bool startCrawling() ");
    }
    if (functionName=="stopCrawling") {
      helpString.push_back("bool stopCrawling() ");
    }
    if (functionName=="goToInitPose") {
      helpString.push_back("bool goToInitPose() ");
    }
    if (functionName=="faster") {
      helpString.push_back("bool faster() ");
    }
    if (functionName=="slower") {
      helpString.push_back("bool slower() ");
    }
    if (functionName=="turnRight") {
      helpString.push_back("bool turnRight() ");
    }
    if (functionName=="turnLeft") {
      helpString.push_back("bool turnLeft() ");
    }
    if (functionName=="toggleVerbosity") {
      helpString.push_back("bool toggleVerbosity() ");
    }
    if (functionName=="checkConnections") {
      helpString.push_back("bool checkConnections() ");
    }
    if (functionName=="help") {
      helpString.push_back("std::vector<std::string> help(const std::string& functionName=\"--all\")");
      helpString.push_back("Return list of available commands, or help message for a specific function");
      helpString.push_back("@param functionName name of command for which to get a detailed description. If none or '--all' is provided, print list of available commands");
      helpString.push_back("@return list of strings (one string per line)");
    }
  }
  if ( helpString.empty()) helpString.push_back("Command not found");
  return helpString;
}


