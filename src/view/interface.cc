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
  int status = -1;
  while (true) {
    getline(std::cin, command);
    try {
      status = controller_->Execute(command);
    } catch (std::invalid_argument& exc) {
      std::cout << exc.what() << std::endl;
      continue;
    }
    if (status == kEXIT) {
      break;
    } else if (status == kERROR) {
      std::cout << "Invalid command\n";
    } else if (status == kPREUPDATE) {
      GetUpdateInfo(command);
      controller_->Execute(command);
    } else {
      std::cout << *output_str_;
    }
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
