#include "level_2.h"

level_2::level_2(QObject *parent) : QObject(parent)
{

}

level_2::array const level_2::arrdata = {{
                                            {2 , 2 , 2 , 2 , 2 , 2 , 0 , 0 , 0 },
                                            {2 , 1 , 1 , 1 , 1 , 2 , 2 , 0 , 0 },
                                            {2 , 3 , 4 , 4 , 3 , 1 , 2 , 2 , 0 },
                                            {2 , 1 , 3 , 4 , 4 , 3 , 1 , 2 , 2 },
                                            {2 , 2 , 1 , 3 , 4 , 4 , 3 , 1 , 2 },
                                            {0 , 2 , 2 , 1 , 3 , 4 , 4 , 3 , 2 },
                                            {0 , 0 , 2 , 2 , 1 , 5 , 1 , 1 , 2 },
                                            {0 , 0 , 0 , 2 , 2 , 2 , 2 , 2 , 2 },
                                            {0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 }
                                         }};
/*
 * air : 0
 * ground : 1
 * wall : 2
 * target : 3
 * box : 4
 * player : 5
 */
