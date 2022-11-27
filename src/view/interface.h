#ifndef SRC_VIEW_INTERFACE_H_
#define SRC_VIEW_INTERFACE_H_

#include <memory>
#include "../controller/controller.h"
#include <string.h>

class Interface {
  public:
     Interface(const std::string file_path);
     ~Interface();

     void Run();

    private:
      Controller* controller_;
};  // class Interface
#endif  // SRC_VIEW_INTERFACE_H_