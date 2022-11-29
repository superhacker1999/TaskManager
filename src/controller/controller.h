#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "../model/taskmanager/taskmanager.h"

class Controller {
  public:
    Controller(const std::string& file_path);
    ~Controller();
    int Execute(const std::string& command);
    void SetOutputStr(std::string** str);

  private:
    TaskManager* task_mngr_;

};  // class Controller
#endif  // SRC_CONTROLLER_CONTROLLER_H_