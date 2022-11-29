#include "interface.h"

Interface::Interface(const std::string file_path) {
  controller_ = new Controller(file_path);
  controller_->SetOutputStr(&output_str_);
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
      if (exc == EXIT_SUCCESS) {
        std::cout << "Exit signal\n";
        break;
      } else {
        GetUpdateInfo(command);
        controller_->Execute(command);
      }
    } catch (std::runtime_error& exc) {
        std::cout << exc.what() << std::endl;
    }
    std::cout << *output_str_;
  }
}

void Interface::GetUpdateInfo(std::string& command) {
  std::string buffer;
  std::cout << "New name = ";
  getline(std::cin, buffer);
  command += " " + buffer;
  std::cout << "New description = ";
  getline(std::cin, buffer);
  command += " " + buffer;
  std::cout << "New date = ";
  getline(std::cin, buffer);
  command += " " + buffer;
  std::cout << "New category = ";
  getline(std::cin, buffer);
  command += " " + buffer;
}

int main(int argc, char** argv) {
  if (argc == 2) {
    Interface iface(argv[1]);
    iface.Run();  
  }
  return 0;
}
