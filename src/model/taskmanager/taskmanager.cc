#include "taskmanager.h"

TaskManager::TaskManager() : dbhandler_(DBHandler("../todo.db")){
  functions_ = {
    {kERROR, nullptr}, {kEXIT, nullptr},
    {kADD, std::bind(&DBHandler::AddTask, &dbhandler_, data_)},
    {kDONE, std::bind(&DBHandler::MakeItDone, &dbhandler_, data_)},
    {kUPDATE, std::bind(&DBHandler::UpdateTask, &dbhandler_, data_)},
    {kDELETE, std::bind(&DBHandler::DeleteTask, &dbhandler_, data_)},
    {kSELECT, std::bind(&DBHandler::SelectTasks, &dbhandler_, data_)}
  };
  // example 1
  // functions_[kUPDATE](data_);

  // example 2
  // functions_.find(kUPDATE)->second(data_);
}
