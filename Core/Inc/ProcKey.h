#ifndef _PROC_KEY_H_
#define _PROC_KEY_H_


#include "key.h"

typedef enum {
    MODE_SCREEN = 0,
    MODE_MOTOR,
    MODE_SENSOR,
    MODE_AUDIO,
    MODE_MAX
} TestMode;

void OnKey1Event(KeyEvent event);
void OnKey2Event(KeyEvent event);
void OnKey3Event(KeyEvent event);


#endif
