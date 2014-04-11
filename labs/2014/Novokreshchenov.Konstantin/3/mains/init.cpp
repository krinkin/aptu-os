#include "Const.h"
#include "command.h"
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        print_error(ERROR_FEW_ARGS);
        return ERROR_FEW_ARGS;
    }
    std::string root = argv[1];

    size_t result = init_fileSystem(root);
    if (result != SUCCESS) {
        print_error(result);
        return result;
    }
    return SUCCESS;
}
