#include "taskmanager.h"

TaskManager::TaskManager(const std::string& file_path) : dbhandler_(new DBHandler(file_path)) {
  functions_ = {
    {kERROR, nullptr} , {kEXIT, nullptr},
    {kADD, &DBHandler::AddTask}, {kDONE, &DBHandler::MakeItDone},
    {kUPDATE, &DBHandler::UpdateTask}, {kDELETE, &DBHandler::DeleteTask},
    {kSELECT, &DBHandler::SelectTasks}
  };
}

TaskManager::~TaskManager() {
  delete dbhandler_;
}

void TaskManager::Execute(const std::string& command) {
  auto result = parser_.ParseCommand(command);
  if (result.first == kEXIT) {
    throw EXIT_SUCCESS;
  } else if (result.first == kERROR) {
    throw std::runtime_error("Invalid command.");
  } else {
    try {
      output_str_ = (dbhandler_->*functions_[result.first])(result.second);
    } catch (std::exception& err) {
      throw std::runtime_error("Incorrect input data.");
    }
  }
}

void TaskManager::SetOutputStr(std::string** str) {
  *str = &output_str_;
}