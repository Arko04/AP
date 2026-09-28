#include <iostream>
#include "Manager.hpp"
#include "Const.hpp"

using namespace std;

int main()
{
    Manager manager(DATA_DIR);
    manager.get_input();
    return 0;
}
