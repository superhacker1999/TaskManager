#include "controller.h"

Controller::Controller(const std::string& file_path)
    : task_mngr_(new TaskManager(file_path)) {
  ;
}

Controller::~Controller() { delete task_mngr_; }

int Controller::Execute(const std::string& command) {
  int result;
  try {
    result = task_mngr_->Execute(command);
  } catch (std::runtime_error& exc) {
    throw exc;
  }
  return result;
}

void Controller::SetOutputStr(std::string** str) {
  task_mngr_->SetOutputStr(str);
}