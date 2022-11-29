#include "controller.h"

Controller::Controller(const std::string& file_path) {
  task_mngr_ = new TaskManager(file_path);
}

Controller::~Controller() {
  delete task_mngr_;
}

void Controller::Execute(const std::string& command) {
  try {
    task_mngr_->Execute(command);  
  } catch (int exc) {
    throw exc;
  } catch (std::runtime_error& exc) {
    throw exc;
  }
}