#include "level_1.h"

level_1::level_1(QObject *parent) : QObject(parent)
{

}

level_1::array const level_1::arrdata = {{
                                            {0 , 2 , 2 , 2 , 2 , 0 , 0 , 0 , 0 },
                                            {0 , 2 , 1 , 1 , 2 , 2 , 2 , 2 , 2 },
                                            {0 , 2 , 4 , 1 , 1 , 1 , 4 , 1 , 2 },
                                            {0 , 2 , 1 , 3 , 2 , 3 , 1 , 1 , 2 },
                                            {2 , 2 , 1 , 2 , 2 , 2 , 1 , 2 , 2 },
                                            {2 , 1 , 4 , 3 , 2 , 3 , 1 , 2 , 0 },
                                            {2 , 1 , 5 , 1 , 1 , 1 , 4 , 2 , 0 },
                                            {2 , 2 , 2 , 2 , 2 , 1 , 1 , 2 , 0 },
                                            {0 , 0 , 0 , 0 , 2 , 2 , 2 , 2 , 0 }
                                         }};
/*
 * air : 0
 * ground : 1
 * wall : 2
 * target : 3
 * box : 4
 * player : 5
 */
