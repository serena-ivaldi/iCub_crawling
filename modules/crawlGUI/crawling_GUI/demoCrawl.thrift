service crawlManagerService {
  bool start();
  bool stop();
  bool is_running();
  bool startCrawling();
  bool stopCrawling();
  bool goToInitPose();
  bool faster();
  bool slower();
  bool turnRight();
  bool turnLeft();
  bool toggleVerbosity();
  bool checkConnections();
}

