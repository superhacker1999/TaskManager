#include "interface.h"

Interface::Interface(const std::string file_path)
  : taskmngr_(std::make_unique<DBHandler>(file_path)) {
  ;
}

Interface::~Interface() {
  ;
}

void Interface::Run() {
  std::string command;
  while (true) {
    getline(std::cin, command);
    if (Parser_(command))
      break;
  }
}

int main(int argc, char** argv) {
  Interface iface(argv[1]);
  iface.Run();
}
