#ifndef SRC_MODEL_DBHANDLER_H_
#define SRC_MODEL_DBHANDLER_H_

#include <sqlite3.h>
#include <memory>
#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>

class DBHandler {
  public:
    DBHandler(const std::string& db_file_path);
    ~DBHandler();
    const std::string AddTask(const std::string& name,
                        const std::string& description,
                        const std::string& date,
                        const std::string& category);
    const std::string MakeItDone(const std::string& name);
    const std::string UpdateTask(const std::string& prev_name,
                              const std::string& name,
                              const std::string& description,
                              const std::string& date,
                              const std::string& category);
    const std::string DeleteTask(const std::string& name);
    const std::string ViewTasks(const std::string& condition);

  private:
    sqlite3* db_;

    static int exec(void* NotUsed, int argc, char** argv, char** azColName);
    const std::string Execute_(const std::string& query, const std::string& on_success);

};  // class DBHandler
#endif  // SRC_MODEL_DBHANDLER_H_

