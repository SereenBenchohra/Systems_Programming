
#ifndef INC_357_PROCESSHANDLE_H
#define INC_357_PROCESSHANDLE_H
#include <stdlib.h>

int spawn(void );
void download_all(Down_Info **download_list, int array_len);
void max_exceeded(Down_Info **download_list, int array_len, int maxDown);


#endif //INC_357_PROCESSHANDLE_H
