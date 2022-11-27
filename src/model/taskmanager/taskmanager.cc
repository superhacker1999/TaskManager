#include "taskmanager.h"

TaskManager::TaskManager(const std::string& file_path) : dbhandler_(new DBHandler(file_path)) {
  UpdateMap_();
}

TaskManager::~TaskManager() {
  delete dbhandler_;
}

void TaskManager::Execute(const std::string& command) {
  auto result = parser_.ParseCommand(command);
  if (result.first == kEXIT) {
    // instructions to exit
  } else if (result.first == kERROR) {
    // sending error to view class
  } else {
    // std::cout << "vec size = " << result.second.size() << std::endl;
    data_ = result.second;
    UpdateMap_();
    functions_[result.first](data_);
  }
}

void TaskManager::UpdateMap_() {
  functions_ = {
    {kERROR, nullptr}, {kEXIT, nullptr},
    {kADD, std::bind(&DBHandler::AddTask, dbhandler_, data_)},
    {kDONE, std::bind(&DBHandler::MakeItDone, dbhandler_, data_)},
    {kUPDATE, std::bind(&DBHandler::UpdateTask, dbhandler_, data_)},
    {kDELETE, std::bind(&DBHandler::DeleteTask, dbhandler_, data_)},
    {kSELECT, std::bind(&DBHandler::SelectTasks, dbhandler_, data_)}
  };
}