#include <iostream>
#include "err_handling.h"

int error(std::string msg, int err_code) {
  if (err_code == 0) {
    std::cerr << "Unexpected argument. error() should never take 0 as a code" << std::endl;
  }
  std::cerr << msg << std::endl;
  return err_code;
}
