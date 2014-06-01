#include "../include/spaghetti.h"

int usage()
{
  std::cerr << "Usage: ./rm <root> <file>"
            << std::endl;
  return 1;
}

int main(int argc, char *argv[])
{
  if (argc != 3)
    return usage();

  Spaghetti::FileSystem fs(argv[1]);
  return fs._rm(argv[2]);
}



