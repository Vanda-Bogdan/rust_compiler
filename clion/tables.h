#pragma once
#include "stdlib.h"
#include <stdbool.h>


enum constant {
    Utf8 = 1
};

struct table_item{

    int ID;
    struct table_item * next;
};


