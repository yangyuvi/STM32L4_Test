#ifndef _PROC_KEY_H_
#define _PROC_KEY_H_


#include "key.h"

typedef enum {
    MODE_MOTOR = 0,
    MODE_SCREEN,
    MODE_AUDIO,
    MODE_SENSOR,
    MODE_MAX
} TestMode;

void OnKey1Event(KeyEvent event);
void OnKey2Event(KeyEvent event);
void OnKey3Event(KeyEvent event);


#endif
