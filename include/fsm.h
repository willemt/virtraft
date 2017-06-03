#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <stdlib.h>

typedef void* fsm_t;

typedef struct {
    int *cells;
    int size;
} fsm_simple_t;

typedef struct {
    int type;

    /* cell affected by command */
    int cell;

    /* value that affects command */
    int value;
} fsm_simple_cmd_t;

typedef fsm_simple_t fsm_kvstore_t;
typedef fsm_simple_cmd_t fsm_kvstore_cmd_t;

fsm_simple_t* fsm_simple_new(int size);

void fsm_simple_push(fsm_simple_t* me, fsm_simple_cmd_t* cmd);

void fsm_simple_rand_cmd(fsm_simple_t* me, fsm_simple_cmd_t* cmd);

fsm_kvstore_t* fsm_kvstore_new(int size);

void fsm_kvstore_push(fsm_kvstore_t* me, fsm_kvstore_cmd_t* cmd);

void fsm_kvstore_rand_cmd(fsm_kvstore_t* me, fsm_kvstore_cmd_t* cmd);

#endif /* STATE_MACHINE_H */
