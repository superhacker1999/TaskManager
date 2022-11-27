#include "parser.h"

std::pair<int, Parser::str_vec_> Parser::ParseCommand(const std::string& command) {
  std::pair<int, str_vec_> result;
  std::string command_line(command, 0, 6);
  if (command_line.find("exit") != std::string::npos) {
    result.first = kEXIT;
  } else if (command_line.find("add") != std::string::npos) {
    result.first = kADD;
    result.second = PrepareCommand_(command);
  } else if (command_line.find("done") != std::string::npos) {
    result.first = kDONE;
    result.second = PrepareCommand_(command);
  } else if (command_line.find("update") != std::string::npos) {
    result.first = kUPDATE;
    result.second = PrepareCommand_(command);
  } else if (command_line.find("delete") != std::string::npos) {
    result.first = kDELETE;
    result.second = PrepareCommand_(command);
  } else if (command_line.find("select") != std::string::npos) {
    result.first = kSELECT;
    result.second = PrepareCommand_(command);
  } else {
    // error command
    result.first = kERROR;
  }
  return result;
}

Parser::str_vec_ Parser::PrepareCommand_(const std::string& command) {
  size_t start, end = 0;
  char delim = (command.find('\'') != std::string::npos) ? '\'' : ' ';
  str_vec_ result;
  while ((start = command.find_first_not_of(delim, end)) != std::string::npos) {
    end = command.find(delim, start);
    result.push_back(command.substr(start, end - start));
  }
  // remove command word from vector, we dont need it
  result.erase(result.begin());
  std::cout << "result.size() = " << result.size() << std::endl;
  return result;
}