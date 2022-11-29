#include "taskmanager.h"

TaskManager::TaskManager(const std::string& file_path)
  : dbhandler_(new DBHandler(file_path)), 
    functions_({
      {kERROR, nullptr} , {kEXIT, nullptr},
      {kADD, &DBHandler::AddTask}, {kDONE, &DBHandler::MakeItDone},
      {kUPDATE, &DBHandler::UpdateTask}, {kDELETE, &DBHandler::DeleteTask},
      {kSELECT, &DBHandler::SelectTasks}
    }) { ; }

TaskManager::~TaskManager() {
  delete dbhandler_;
}

int TaskManager::Execute(const std::string& command) {
  auto result = parser_.ParseCommand(command);
  if (result.first != kEXIT && result.first != kERROR && result.first != kPREUPDATE) {
    try {
      output_str_ = (dbhandler_->*functions_[result.first])(result.second);
    } catch (std::exception& err) {
      std::cout << "incorrindata\n";
      throw std::invalid_argument("Incorrect input data.");
    }
  }
  return result.first;
}

void TaskManager::SetOutputStr(std::string** str) {
  *str = &output_str_;
}