/*
 *   if.h
 *  Created on: 2018
 *      Author: zhaoxi
 */
#ifndef IF_H_
#define IF_H_
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define LIKELY(x) __builtin_expect(!!(x), 1)
#define UNLIKELY(x) __builtin_expect(!!(x), 0)
#endif
