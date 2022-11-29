#ifndef SRC_MODEL_TASKMANAGER_TASKMANAGER_H_
#define SRC_MODEL_TASKMANAGER_TASKMANAGER_H_

#include <map>
#include "../parser/parser.h"
#include "../dbhandler/dbhandler.h"
#include <exception>

class TaskManager {
  public:
    TaskManager(const std::string& file_path);
    ~TaskManager();
    int Execute(const std::string& command);
    using DBHandlerFunc = const std::string (DBHandler::*) (Parser::str_vec_);
    void SetOutputStr(std::string** str);

  private:
    DBHandler* dbhandler_;
    Parser parser_;
    std::map< int, DBHandlerFunc > functions_;
    std::string output_str_;
    
};  // class TaskManager

#endif  // SRC_MODEL_TASKMANAGER_TASKMANAGER_H_