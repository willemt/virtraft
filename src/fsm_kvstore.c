#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "fsm.h"

enum {
    FSM_CMD_OP_SET,
    FSM_CMD_OP_GET,
    FSM_CMD_OP_NUM,
};

fsm_kvstore_t* fsm_kvstore_new(int size)
{
    fsm_kvstore_t* me = calloc(1, sizeof(fsm_kvstore_t));
    me->size = size;
    me->cells = calloc(me->size, sizeof(int));
    return me;
}

void fsm_kvstore_push(fsm_kvstore_t* me, fsm_kvstore_cmd_t* cmd)
{
    switch (cmd->type) {
        case FSM_CMD_OP_SET:
            me->cells[cmd->cell] = cmd->value;
            break;
        case FSM_CMD_OP_GET:
            // TODO
            break;
    }
}

void fsm_kvstore_rand_cmd(fsm_kvstore_t* me, fsm_kvstore_cmd_t* cmd)
{
    cmd->type = random() % FSM_CMD_OP_NUM;
    cmd->value = random() % 255;
    cmd->cell = random() % me->size;
}

int fsm_kvstore_cmp(fsm_kvstore_t* me, fsm_kvstore_t* other)
{
    if (me->size != other->size)
        return me->size - other->size;
    return memcmp(me->cells, other->cells, sizeof(int) * me->size);
}

/* void fsm_kvstore_snapshot(fsm_kvstore_t* me, char** out, int *len) */
/* { */
/*     *len = sizeof(int) * me->size */
/*     *out = malloc(*len); */
/*     memcpy(*out, me->cells, *len); */
/* } */
