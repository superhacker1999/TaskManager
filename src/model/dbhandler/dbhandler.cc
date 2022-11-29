#include "dbhandler.h"

DBHandler::DBHandler(const std::string& db_file_path) {
  if (sqlite3_open(db_file_path.c_str(), &db_)) {
    std::cout << "Couldn't open db : " << sqlite3_errmsg(db_) << std::endl;
    exit(EXIT_FAILURE);
  }
}

DBHandler::~DBHandler() {
  sqlite3_close(db_);
}

int DBHandler::exec(void* data, int argc, char** argv, char** azColName) {
  std::string select_data;
  (void)azColName;
  (void)data;
  char** str_data = (char**)data;
  for (int i = 1; i < argc; ++i) {
    select_data.append(argv[i]);
    select_data.append(" | ");
  }
  select_data.push_back('\n');

  size_t len = strlen(*str_data) + select_data.size();
  *str_data = (char*)realloc(*str_data, len);

  strcat(*str_data, (char*)select_data.c_str());
  return 0;
}

const std::string DBHandler::Execute_(const std::string& query, const std::string& on_success) {
  char *zerMsg = 0;
  char* message = (char*)calloc(10, sizeof(char));
  std::string output_str;
  std::string header = "\nNAME  |  DESCRIPTION  |  DATE  |  CATEGORY  |  STATUS\n\n";
  if (sqlite3_exec(db_, query.c_str(), exec, &message, &zerMsg) != SQLITE_OK) {
    printf("SQL error: %s\n", zerMsg);
    sqlite3_free(zerMsg);
    output_str = message;
  } else {
    if (strlen(message) > 0)
      output_str = header + message;
    else
      output_str = on_success;
  }
  free(message);
  return output_str;
}

const std::string DBHandler::AddTask(std::vector<std::string> values) {
  std::string query = "insert into tasks\
    (name, description, date, category, status)\
    values('"+ values.at(0) + "','" + values.at(1) + "','" +
    values.at(2) + "','" + values.at(3) + "',0);";
  return Execute_(query, "New task \""+ values.at(0) +"\" added successfully!\n");
}

const std::string DBHandler::MakeItDone(std::vector<std::string> values) {
  std::string query = "update tasks\
   set status=1\
   where name='" + values.at(0) + "';";
  std::string succes_msg = "Task " + values.at(0) + " is done!\n";
  return Execute_(query, succes_msg);
}

const std::string DBHandler::UpdateTask(std::vector<std::string> values) {
  if (IsTaskExist_(values.at(0))) {
    std::string query = "update tasks set name='"
      + values.at(1) + "', description='"
      + values.at(2) + "', date='"
      + values.at(3) + "', category='"
      + values.at(4) + "' where name='"
      + values.at(0) + "';";
    std::string success_msg = "Task " + values.at(0) + " successfully updated!\n";
    return Execute_(query, success_msg);  
  } else {
    return "There is no task with such name\n";
  }
}

const std::string DBHandler::DeleteTask(std::vector<std::string> values) {
  std::string query = "delete from tasks\
    where name='" + values.at(0) + "';";
  std::string success_msg = "Task " + values.at(0) + " deleted successfully\n";
  return Execute_(query, success_msg);
}

const std::string DBHandler::SelectTasks(std::vector<std::string> values) {
  std::string query = values.at(0);
  size_t pos = query.find('*');
  query.insert(pos + 1, " from tasks");
  query.push_back(';');
  std::string success_msg = "No matches found.\n";
  return Execute_(query, success_msg);
}

bool DBHandler::IsTaskExist_(std::string name) {
  std::string query = "select * where name='" + name + "'";
  if (SelectTasks({query}) == "No matches found.\n")
    return false;
  else
    return true;
}