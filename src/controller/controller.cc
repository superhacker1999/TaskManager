#include "controller.h"

Controller::Controller() {
  task_mngr_ = std::make_unique<TaskManager>(smth);
}

Controller::~Controller() {
  ;
}

