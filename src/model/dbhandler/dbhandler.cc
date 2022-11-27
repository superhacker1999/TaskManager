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

const std::string DBHandler::AddTask(const std::string& name,
                            const std::string& description,
                            const std::string& date,
                            const std::string& category) {
  std::string query = "insert into tasks\
    (name, description, date, category, status)\
    values('"+ name + "','" + description + "','" +
    date + "','" + category + "',0);";
  return Execute_(query, "New task added successfully");
}

const std::string DBHandler::MakeItDone(const std::string& name) {
  std::string query = "update tasks\
   set status=done\
   where name='" + name + "';";
  std::string succes_msg = "Task " + name + " is done!";
  return Execute_(query, succes_msg);
}

//todo
// add check if this name exists
const std::string DBHandler::UpdateTask(const std::string& prev_name,
                                    const std::string& name,
                                    const std::string& description,
                                    const std::string& date,
                                    const std::string& category) {
  std::string query = "update tasks set name='"
    + name + "', description='"
    + description + "', date='"
    + date + "', category='"
    + category + "' where name='"
    + prev_name + "';";
  std::string success_msg = "Task " + prev_name + " successfully updated!";
  return Execute_(query, success_msg);
}

const std::string DBHandler::DeleteTask(const std::string& name) {
  std::string query = "delete from tasks\
    where name='" + name + "';";
  std::string success_msg = "Task " + name + " deleted successfully";
  return Execute_(query, success_msg);
}

const std::string DBHandler::ViewTasks(const std::string& condition) {
  std::string query = condition;
  std::string success_msg = "Success!\n";
  return Execute_(query, success_msg);
}

int main() {
  DBHandler manager("/Users/padmemur/Desktop/MERTEH/todo.db");
  std::cout << manager.ViewTasks("select * from tasks;");
  return 0;
}