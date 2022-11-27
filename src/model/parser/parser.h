#ifndef SRC_PARSER_PARSER_H_
#define SRC_PARSER_PARSER_H_

#include <string>
#include <vector>
#include <utility>

enum commands {
  kERROR,
  kADD,
  kDONE,
  kUPDATE,
  kDELETE,
  kSELECT,
  kEXIT
};

class Parser {
  public:
    Parser() {;}
    ~Parser() {;}
    int ParseCommand(const std::string& command);
    std::vector<std::string> PrepareCommand(const std::string& command);

};  // class Parser
#endif  // SRC_PARSER_PARSER_H_