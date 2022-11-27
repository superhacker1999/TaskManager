#include "interface.h"

Interface::Interface(const std::string file_path) {
  controller_ = new Controller(file_path);
}

Interface::~Interface() {
  delete controller_;
}

void Interface::Run() {
  std::string command;
  while (true) {
    getline(std::cin, command);
    controller_->Execute(command);
  }
}

int main(int argc, char** argv) {
  (void)argc;
  Interface iface(argv[1]);
  iface.Run();  
  return 0;
}
