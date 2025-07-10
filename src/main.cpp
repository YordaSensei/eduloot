#include <iostream>
#include "Teacher.h"

int main(int argc, char *argv[])
{
    Teacher teacher("Zoey", 100.0);
    teacher.getInfo();
    teacher.makePurchase();
    return 0;
}