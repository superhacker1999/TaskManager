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
    try {
      controller_->Execute(command);
    } catch (int exc) {
        std::cout << "Exit signal\n";
        break;
    } catch (std::runtime_error& exc) {
        std::cout << exc.what() << std::endl;
    }
  }
}

int main(int argc, char** argv) {
  (void)argc;
  Interface iface(argv[1]);
  iface.Run();  
  return 0;
}
