#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "fsm.h"

enum {
    FSM_CMD_OP,
    FSM_CMD_OP_INVERSE,
    FSM_CMD_OP_NUM,
};

/* A function that maps between f: X -> X can be used to create a
 * non-commutative function. */
int mapping[] = {
    5,
    3,
    1,
    4,
    2,
};

fsm_simple_t* fsm_simple_new(int size)
{
    fsm_simple_t* me = calloc(1, sizeof(fsm_simple_t));
    me->size = size;
    me->cells = calloc(me->size, sizeof(int));
    return me;
}

void fsm_simple_push(fsm_simple_t* me, fsm_simple_cmd_t* cmd)
{
    switch (cmd->type) {
        case FSM_CMD_OP:
            me->cells[cmd->cell] += mapping[cmd->value];
            break;
        case FSM_CMD_OP_INVERSE:
            me->cells[cmd->cell] -= mapping[cmd->value];
            break;
    }
}

void fsm_simple_rand_cmd(fsm_simple_t* me, fsm_simple_cmd_t* cmd)
{
    cmd->type = random() % FSM_CMD_OP_NUM;
    cmd->value = random() % (sizeof(mapping) / sizeof(*mapping));
    cmd->cell = random() % me->size;
}

int fsm_simple_cmp(fsm_simple_t* me, fsm_simple_t* other)
{
    if (me->size != other->size)
        return me->size - other->size;
    return memcmp(me->cells, other->cells, sizeof(int) * me->size);
}
