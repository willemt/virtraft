#include <stdio.h>
#include <string.h>

typedef struct
{
    int old;
} parse_result_t;

struct path_parse
{
    int node_id;
    system_t* sys;
    parse_result_t* r;
    int cs;
};

%%{
    machine path_parse;
    access fsm->;

    action key_start { fsm->r->key.s = (char*)fpc; }
    action key_end { fsm->r->key.len = (size_t)(fpc - fsm->r->key.s); }

    action recv_entry {
        __periodic(&sys);
    }

    action periodic {
        raft_periodic(sys.nodes[fc - '0'].raft, 500);
        __ensure_election_safety(&sys);
        __ensure_log_matching(&sys);
        __ensure_leader_completeness(&sys);
    }

    action receive_msg_from_inbox {
        __push_entry(fsm->sys);
        __server_poll_messages(&sys.nodes[fc - '0'], &sys);
    }

    action drop_msg_from_inbox {
        __push_entry(fsm->sys);
        __server_drop_messages(&sys.nodes[fc - '0'], &sys);
    }

    action partition {
        int node_id1 = *(fpc) - '0';
        node_t* node = &sys.nodes[node_id1];
        node->partitioned = !node->partitioned;
    }

    unreserved  = alnum | "-" | "." | "_" | "~" | "=";


    main := (
        ("perid" digit @periodic) |
        ("recv" digit @receive_msg_from_inbox) |
        ("drop" digit @drop_msg_from_inbox) |
        ("entry" @recv_entry) |
        ("part" digit @partition)
        ) *;

}%%

%% write data;

static void __init(struct path_parse *fsm, system_t* sys, parse_result_t* result)
{
    fsm->sys = sys;
    fsm->r = result;
    fsm->node_id = 0;
    %% write init;
}

static void __execute(struct path_parse *fsm, const char *data, size_t len)
{
    const char *p = data;
    const char *pe = data + len;
    //const char *eof = data + len;
    %% write exec;
}

static int __finish(struct path_parse *fsm)
{
    if (fsm->cs == path_parse_error)
        return -1;
    if (fsm->cs >= path_parse_first_final)
        return 1;
    return 0;
}

int parse_commands(system_t *sys, parse_result_t *result)
{
    struct path_parse pp;
    __init(&pp, sys, result);

    #define BUFSIZE 1

    char buf[BUFSIZE];

    while (0 < read(0, buf, 1))
    {
        // printf("reading: %c\n", *buf);
        if (*buf == '\0')
            break;
        __execute(&pp, buf, BUFSIZE);
    }

    if (__finish(&pp) != 1)
        return -1;

    return 0;
}
