#include "error_handle.h"

/**
 * \brief Prints an error then ends the program
 *
 * \param error The error to print out
 */
void die(std::string error) {
    printf("\x1B[91m%s\n\x1B[0m", error.c_str());
    system("pause");
    exit(-1);
}
