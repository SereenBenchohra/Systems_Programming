#include <stdint.h>

#ifndef NICOFUNCTS_H
#define NICOFUNCTS_H

uint32_t extract_special_int(char *where, int len);

int insert_special_int(char *where, size_t size, int32_t val);

#endif
