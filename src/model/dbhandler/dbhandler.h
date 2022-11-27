#ifndef SRC_MODEL_DBHANDLER_H_
#define SRC_MODEL_DBHANDLER_H_

#include <sqlite3.h>
#include <memory>
#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>
#include <vector>

class DBHandler {
  public:
    DBHandler(const std::string& db_file_path);
    ~DBHandler();
    // name, description, date, category - 4
    const std::string AddTask(std::vector<const std::string&> values);
    // name - 1
    const std::string MakeItDone(std::vector<const std::string&> values);
    // prev_name, name, description, date, category - 5
    const std::string UpdateTask(std::vector<const std::string&> values);
    // name - 1
    const std::string DeleteTask(std::vector<const std::string&> values);
    // condition - 1
    const std::string SelectTasks(std::vector<const std::string&> values);

  private:
    sqlite3* db_;

    static int exec(void* NotUsed, int argc, char** argv, char** azColName);
    const std::string Execute_(const std::string& query, const std::string& on_success);

};  // class DBHandler
#endif  // SRC_MODEL_DBHANDLER_H_

