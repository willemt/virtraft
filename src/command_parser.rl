#include <stdio.h>
#include <string.h>
#include <unistd.h>

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
        __poll_messages(&sys);
    }

    action periodic {
        raft_periodic(sys.servers[fc - '0'].raft, 500);
        __ensure_election_safety(&sys);
        __poll_messages(&sys);
    }

    action receive_msg_from_inbox {
        __push_entry(fsm->sys);
        __server_poll_messages(&sys.servers[fc - '0'], &sys);
    }

    action drop_msg_from_inbox {
        __push_entry(fsm->sys);
        __server_drop_messages(&sys.servers[fc - '0'], &sys);
    }

    action partition {
        int node_id1 = *(fpc) - '0';

        assert(0 <= node_id1 && node_id1 < sys.n_servers);

        server_t* sv = &sys.servers[node_id1];
        sv->partitioned = !sv->partitioned;
    }

    action togglmem {
        int node_id1 = *(fpc) - '0';

        assert(0 <= node_id1 && node_id1 < sys.n_servers);

        server_t* node = &sys.servers[node_id1];

        __toggle_membership(node);

        __poll_messages(&sys);
    }

    unreserved  = alnum | "-" | "." | "_" | "~" | "=";


    main := (
        ("perid" digit @periodic) |
        ("recv" digit @receive_msg_from_inbox) |
        ("drop" digit @drop_msg_from_inbox) |
        ("entry" @recv_entry) |
        ("togglmem" digit @togglmem) |
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
    int ran = 0;
    struct path_parse pp;
    __init(&pp, sys, result);

    char buf[1];

    int fd = fcntl(0, F_DUPFD, 0);

    /* set to non-blocking so we can exit when there isn't anything on stdin */
    fcntl(fd, F_SETFL, O_NONBLOCK);

    while (0 < read(fd, buf, 1))
    {
        // printf("reading: %c\n", *buf);
        ran = 1;
        if (*buf == '\0')
            break;
        __execute(&pp, buf, 1);
    }

    __finish(&pp);

    /* we have to set to blocking to allow writing to sdout to work */
    fcntl(fd, F_SETFL, 0);

    return ran;
}
