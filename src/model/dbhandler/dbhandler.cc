#include "dbhandler.h"

DBHandler::DBHandler(const std::string& db_file_path) {
  if (sqlite3_open(db_file_path.c_str(), &db_)) {
    std::cout << "Couldn't open db : " << sqlite3_errmsg(db_) << std::endl;
    exit(EXIT_FAILURE);
  } else {
    std::cout << "DB opened successfully\n"; 
  }
}

DBHandler::~DBHandler() {
  sqlite3_close(db_);
}

int DBHandler::exec(void* data, int argc, char** argv, char** azColName) {
  std::string select_data;
  char** str_data = (char**)data;
  for (int i = 1; i < argc; ++i) {
    select_data.append(argv[i]);
    select_data.push_back('|');
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
  if (sqlite3_exec(db_, query.c_str(), exec, &message, &zerMsg) != SQLITE_OK) {
    sprintf(message, "SQL error: %s\n", zerMsg);
    sqlite3_free(zerMsg);
    output_str = message;
  } else {
    output_str = message;
    std::cout << on_success;
  }
  free(message);
  return output_str;
}

const std::string DBHandler::AddTask(std::vector<const std::string&> values) {
  std::string query = "insert into tasks\
    (name, description, date, category, status)\
    values('"+ values.at(0) + "','" + values.at(1) + "','" +
    values.at(2) + "','" + values.at(3) + "',0);";
  return Execute_(query, "New task added successfully");
}

const std::string DBHandler::MakeItDone(std::vector<const std::string&> values) {
  std::string query = "update tasks\
   set status=done\
   where name='" + values.at(0) + "';";
  std::string succes_msg = "Task " + values.at(0) + " is done!";
  return Execute_(query, succes_msg);
}

//todo
// add check if this name exists
const std::string DBHandler::UpdateTask(std::vector<const std::string&> values) {
  std::string query = "update tasks set name='"
    + values.at(0) + "', description='"
    + values.at(1) + "', date='"
    + values.at(2) + "', category='"
    + values.at(3) + "' where name='"
    + values.at(4) + "';";
  std::string success_msg = "Task " + values.at(0) + " successfully updated!";
  return Execute_(query, success_msg);
}

const std::string DBHandler::DeleteTask(std::vector<const std::string&> values) {
  std::string query = "delete from tasks\
    where name='" + values.at(0) + "';";
  std::string success_msg = "Task " + values.at(0) + " deleted successfully";
  return Execute_(query, success_msg);
}

const std::string DBHandler::SelectTasks(std::vector<const std::string&> values) {
  std::string query = values.at(0);
  std::string success_msg = "Success!\n";
  return Execute_(query, success_msg);
}

int main() {
  DBHandler manager("/Users/padmemur/Desktop/MERTEH/todo.db");
  // std::cout << manager.ViewTasks(std::vector<const std::string>{"select * from tasks;"});
  return 0;
}