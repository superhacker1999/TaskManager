#include "parser.h"

Parser::Parser()
    : commands_({"exit", "add", "done", "update", "delete", "select"}) {
  for (int i = kEXIT; i <= kSELECT; ++i)
    funcs_.insert(std::make_pair(commands_.at(i - 1), i));
}

std::pair<int, Parser::str_vec_> Parser::ParseCommand(
    const std::string& command) {
  std::pair<int, str_vec_> result;
  std::string command_line(command, 0, 6);
  result.first = GetFunc(command_line);
  if (result.first == kUPDATE &&
      std::count(command.begin(), command.end(), ' ') < 2)
    result.first = kPREUPDATE;
  else if (result.first >= kADD && result.first <= kDELETE) {
    result.second = PrepareCommand_(command);
  } else if (result.first == kSELECT) {
    result.second = std::vector<std::string>{command};
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
  result.erase(result.begin());
  return result;
}

int Parser::GetFunc(const std::string& command_line) {
  int res = kERROR;
  for (auto it : funcs_)
    if (command_line.find(it.first) != std::string::npos) res = it.second;
  return res;
}