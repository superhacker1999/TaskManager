#ifndef SRC_MODEL_TASKMANAGER_TASKMANAGER_H_
#define SRC_MODEL_TASKMANAGER_TASKMANAGER_H_

#include <map>
#include "../parser/parser.h"
#include "../dbhandler/dbhandler.h"
#include <exception>

// taskmanager has a map of ecncoding command
// and pointers to the functions of DBHandler
// in case something need to execute, just add new data to data_ vector
// and run a method using functions_.find([command_encoding])();

class TaskManager {
  public:
    TaskManager(const std::string& file_path);
    ~TaskManager();
    void Execute(const std::string& command);
    using DBHandlerFunc = const std::string (DBHandler::*) (Parser::str_vec_);
    void SetOutputStr(std::string** str);

  private:
    DBHandler* dbhandler_;
    Parser parser_;
    std::map< int, DBHandlerFunc > functions_;
    std::string output_str_;

    void UpdateMap_();
    
};  // class TaskManager

#endif  // SRC_MODEL_TASKMANAGER_TASKMANAGER_H_