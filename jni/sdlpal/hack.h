#pragma once
#include "common.h"

#ifdef __cplusplus
extern "C"
{
#endif

// ´©Ç½
void setFlyMode(BOOL isFly);
BOOL isFlyMode();

void setNoEnemy(BOOL isTrans);
BOOL isNoEnemy();

// Éý¼¶
void uplevel();

// show me the money
void addMoney();

#ifdef __cplusplus
}
#endif