#include "config.hpp"
#include "sortingMachine.hpp"
class Main {
private:
  SortingMachine<int> sorter = SortingMachine<int>();

public:
  int main(int argc, char *argv[]) {
    if (argc == 2) {
      Config::setConfigFile(argv[1]);
    }

    return 0;
  };
};
