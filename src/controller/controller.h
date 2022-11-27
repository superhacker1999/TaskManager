#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include <memory>
#include

class Controller {
  public:
    Controller();
    ~Controller();
    void Execute(const std::string& command);
    // привязать string_view из iface к string в taskmngr;
    // method to call parser of smth

  private:
    std::unique_ptr<TaskManager> task_mngr_;

};  // class Controller
#endif  // SRC_CONTROLLER_CONTROLLER_H_