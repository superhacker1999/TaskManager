#include "parser.h"

int Parser::ParseCommand(const std::string& command) {
  int parsed_command = kERROR;
  std::string command_line(command, 0, 6);
  if (command_line.find("exit") != std::string::npos) {
    parsed_command = kEXIT;
  } else if (command_line.find("add") != std::string::npos) {
    parsed_command = kADD;
    PrepareCommand()
  } else if (command_line.find("done") != std::string::npos) {
    parsed_command = kDONE;
  } else if (command_line.find("update") != std::string::npos) {
    parsed_command = kUPDATE;
  } else if (command_line.find("delete") != std::string::npos) {
    parsed_command = kDELETE;
  } else if (command_line.find("select") != std::string::npos) {
    parsed_command = kSELECT;
  } else {
    // parsed_command = kERROR;
  }
  return parsed_command;
}
