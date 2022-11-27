#include "controller.h"

Controller::Controller(const std::string& file_path) {
  task_mngr_ = new TaskManager(file_path);
}

Controller::~Controller() {
  delete task_mngr_;
}

void Controller::Execute(const std::string& command) {
  task_mngr_->Execute(command);
}

