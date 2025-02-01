#ifndef ERR_HANDLING_H
#define ERR_HANDLING_H

#include <string>

// Function to print an error message and exit with custom, non-zero error code
int error(std::string msg, int err_code);

#endif  // ERR_HANDLING_H
