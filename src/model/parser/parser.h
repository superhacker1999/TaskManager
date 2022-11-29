#ifndef SRC_PARSER_PARSER_H_
#define SRC_PARSER_PARSER_H_

#include <string>
#include <vector>
#include <utility>
#include <functional>
#include <map>
#include "../dbhandler/dbhandler.h"

enum commands {
  kERROR,
  kEXIT,
  kADD,
  kDONE,
  kUPDATE,
  kDELETE,
  kSELECT,
  kPREUPDATE
};

class Parser {
  public:
    Parser();
    ~Parser() {;}
    using str_vec_ = std::vector<std::string>;
    using func_ = std::function<const std::string(str_vec_)>;
    std::pair<int, str_vec_> ParseCommand(const std::string& command);
    
  private:
    str_vec_ PrepareCommand_(const std::string& command);
    int GetFunc(const std::string& command_line);

    std::vector<std::string> commands_;
    std::map<std::string, int> funcs_;

};  // class Parser
#endif  // SRC_PARSER_PARSER_H_