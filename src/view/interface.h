#ifndef SRC_VIEW_INTERFACE_H_
#define SRC_VIEW_INTERFACE_H_

#include <memory>
#include "../model/taskmanager.h"
#include <string.h>

class Interface {
  public:
     Interface(const std::string file_path);
     ~Interface();

     void Run();

    private:
      std::unique_ptr<Controller> controller;
};  // class Interface
#endif  // SRC_VIEW_INTERFACE_H_