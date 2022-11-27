#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_


#include "../model/taskmanager/taskmanager.h"

class Controller {
  public:
    Controller(const std::string& file_path);
    ~Controller();
    void Execute(const std::string& command);
    // привязать string_view из iface к string в taskmngr;
    // method to call parser of smth

  private:
    TaskManager* task_mngr_;

};  // class Controller
#endif  // SRC_CONTROLLER_CONTROLLER_H_