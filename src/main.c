/**
 * Copyright (c) 2015, Willem-Hendrik Thiart
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "raft.h"
#include "linked_list_queue.h"

#include "usage.c"

#define VERSION "0.1.0"
#define PERIOD_MSEC 500
#define RAFT_BUFLEN 512
#define len(x) (sizeof((x)) / sizeof((x)[0]))

/** Message types used for peer to peer traffic
 * These values are used to identify message types during deserialization */
typedef enum
{
    MSG_REQUESTVOTE,
    MSG_REQUESTVOTE_RESPONSE,
    MSG_APPENDENTRIES,
    MSG_APPENDENTRIES_RESPONSE,
} peer_message_type_e;

typedef struct
{
    int type;
    int len;
    void* data;
    raft_node_t* sender;
} msg_t;

typedef struct peer_connection_s peer_connection_t;

struct peer_connection_s
{
    raft_node_t* node;
    peer_connection_t* next;
};

typedef struct
{
    /* the server's node ID */
    int node_id;

    raft_server_t* raft;

    /* Link list of peer connections */
    peer_connection_t* conns;

    void* inbox;
} node_t;

typedef struct
{
    node_t* nodes;
    int n_nodes;
    int n_entries;
    node_t* leader;
} system_t;

system_t sys;

options_t opts;

static void __int_handler(int dummy)
{
    int i;

    for (i = 0; i < sys.n_nodes; i++)
    {
        raft_server_t* r = sys.nodes[i].raft;

        printf("node: %d %lx\n", i, (unsigned long)r);
        printf("state: %s\n",
               raft_get_state(r) == RAFT_STATE_LEADER ? "leader" :
               raft_get_state(r) == RAFT_STATE_CANDIDATE ? "candidate" :
               "follower");
        printf("current_idx: %d\n", raft_get_current_idx(r));
        printf("last_log_term: %d\n", raft_get_last_log_term(r));
        printf("current_term: %d\n", raft_get_current_term(r));
        printf("commit_idx: %d\n", raft_get_commit_idx(r));
        printf("last_applied_idx: %d\n", raft_get_last_applied_idx(r));
        printf("log_count: %d\n", raft_get_log_count(r));
        printf("\n");
    }
}

/** Raft callback for applying an entry to the finite state machine */
static int __raft_applylog(
    raft_server_t* raft,
    void *udata,
    const unsigned char *data,
    const int len
    )
{
    /* State Machine Safety */

    int i;

    int last_applied_idx = raft_get_last_applied_idx(raft);
    raft_entry_t* ety = raft_get_entry_from_idx(raft, last_applied_idx);

    assert(last_applied_idx <= raft_get_current_idx(raft));

    for (i = 0; i < sys.n_nodes; i++)
    {
        raft_server_t* other = sys.nodes[i].raft;

        if (other == raft)
            continue;

        raft_entry_t* other_ety = raft_get_entry_from_idx(other, last_applied_idx);
        if (other_ety && last_applied_idx <= raft_get_commit_idx(other))
        {
            if (ety->term != other_ety->term || ety->id != other_ety->id)
            {
                printf("node applied bad ety idx:%d (ie. t: %d vs %d) %lx %lx id: %d vs %d\n",
                       last_applied_idx,
                       ety->term,
                       other_ety ? other_ety->term : -999,
                       (unsigned long)raft,
                       (unsigned long)other,
                       ety->id,
                       other_ety ? other_ety->id : -999);
                __int_handler(0);
                abort();
            }
        }
    }

    return 0;
}

// TODO
/** Raft callback for saving term field to disk.
 * This only returns when change has been made to disk. */
static int __raft_persist_term(
    raft_server_t* raft,
    void *udata,
    const int current_term
    )
{
    return 0;
}

// TODO
/** Raft callback for saving voted_for field to disk.
 * This only returns when change has been made to disk. */
static int __raft_persist_vote(
    raft_server_t* raft,
    void *udata,
    const int voted_for
    )
{
    return 0;
}

/** Raft callback for displaying debugging information */
void __raft_log(raft_server_t* raft, raft_node_t* node, void *udata,
                const char *buf)
{
    system_t* sys = udata;
    if (node)
        printf("> %lx, %lx %s\n",
               (unsigned long)raft,
               (unsigned long)sys->nodes[raft_node_get_id(node)].raft,
               buf);
    else
        printf("> %lx               %s\n", (unsigned long)raft, buf);
}

// TODO
/** Raft callback for appending an item to the log */
static int __raft_logentry_offer(
    raft_server_t* raft,
    void *udata,
    raft_entry_t *ety,
    int ety_idx
    )
{
    return 0;
}

// TODO
/** Raft callback for removing the first entry from the log
 * @note this is provided to support log compaction in the future */
static int __raft_logentry_poll(
    raft_server_t* raft,
    void *udata,
    raft_entry_t *entry,
    int ety_idx
    )
{
    return 0;
}

// TODO
/** Raft callback for deleting the most recent entry from the log.
 * This happens when an invalid leader finds a valid leader and has to delete
 * superseded log entries. */
static int __raft_logentry_pop(
    raft_server_t* raft,
    void *udata,
    raft_entry_t *entry,
    int ety_idx
    )
{
    return 0;
}

static int __append_msg(
    system_t* sys,
    void* data,
    int type,
    int len,
    raft_node_t* node,
    raft_server_t* raft
    )
{
    int node_id = raft_node_get_id(node);

    /* drop rate */
    if (random() % 100 < atoi(opts.drop_rate))
        return 0;

    node_t* n = &sys->nodes[node_id];

    msg_t* m = malloc(sizeof(msg_t));
    m->type = type;
    m->len = len;
    m->sender = raft_get_node(n->raft, raft_get_nodeid(raft));
    m->data = malloc(len);
    memcpy(m->data, data, len);

    /* give to peer */
    /* peer_connection_t* peer = raft_node_get_udata(node); */
    llqueue_offer(n->inbox, m);

    return 1;
}

int __raft_send_requestvote(raft_server_t* raft,
                            void* udata,
                            raft_node_t* node,
                            msg_requestvote_t* msg)
{
    return __append_msg(udata, msg, MSG_REQUESTVOTE, sizeof(*msg), node, raft);
}

int sender_requestvote_response(raft_server_t* raft,
                                void* udata,
                                raft_node_t* node,
                                msg_requestvote_response_t* msg)
{
    return __append_msg(udata, msg, MSG_REQUESTVOTE_RESPONSE, sizeof(*msg),
                        node, raft);
}

int __raft_send_appendentries(raft_server_t* raft,
                              void* udata,
                              raft_node_t* node,
                              msg_appendentries_t* msg)
{
    msg_entry_t* entries = calloc(1, sizeof(msg_entry_t) * msg->n_entries);
    memcpy(entries, msg->entries, sizeof(msg_entry_t) * msg->n_entries);
    msg->entries = entries;
    return __append_msg(udata, msg, MSG_APPENDENTRIES, sizeof(*msg), node,
                        raft);
}

int sender_appendentries_response(raft_server_t* raft,
                                  void* udata,
                                  raft_node_t* node,
                                  msg_appendentries_response_t* msg)
{
    return __append_msg(udata, msg, MSG_APPENDENTRIES_RESPONSE,
                        sizeof(*msg), node, raft);
}

raft_cbs_t raft_funcs = {
    .send_requestvote            = __raft_send_requestvote,
    .send_appendentries          = __raft_send_appendentries,
    .applylog                    = __raft_applylog,
    .persist_vote                = __raft_persist_vote,
    .persist_term                = __raft_persist_term,
    .log_offer                   = __raft_logentry_offer,
    .log_poll                    = __raft_logentry_poll,
    .log_pop                     = __raft_logentry_pop,
    .log                         = __raft_log,
};

static void __create_node(node_t* sv, int id, system_t* sys)
{
    sv->raft = raft_new();
    raft_set_callbacks(sv->raft, &raft_funcs, sys);
    raft_set_election_timeout(sv->raft, 500);
    sv->inbox = llqueue_new();

    int i;

    for (i = 0; i < atoi(opts.NODES); i++)
    {
        peer_connection_t* p = calloc(1, sizeof(*p));

        p->next = sv->conns;
        sv->conns = p;

        int is_myself = id == i;

        p->node = raft_add_node(sv->raft, p, i, is_myself);
    }
}

static void __server_poll_messages(node_t* me, system_t* sys)
{
    msg_t* m;

    /* if (random() < 0.5) */
    /*     return; */

    while ((m = llqueue_poll(me->inbox)))
    {
        switch (m->type)
        {
        case MSG_APPENDENTRIES:
        {
            msg_appendentries_response_t response;
            raft_recv_appendentries(me->raft, m->sender, m->data, &response);
            __append_msg(sys, &response, MSG_APPENDENTRIES_RESPONSE,
                         sizeof(response), m->sender, me->raft);
        }
        break;
        case MSG_APPENDENTRIES_RESPONSE:
            raft_recv_appendentries_response(me->raft, m->sender, m->data);
            break;
        case MSG_REQUESTVOTE:
        {
            msg_requestvote_response_t response;
            raft_recv_requestvote(me->raft, m->sender, m->data, &response);
            __append_msg(sys, &response, MSG_REQUESTVOTE_RESPONSE,
                         sizeof(response), m->sender, me->raft);
        }
        break;
        case MSG_REQUESTVOTE_RESPONSE:
            raft_recv_requestvote_response(me->raft, m->sender, m->data);
            break;
        }
    }
}

/** Election Safety
 * At most one leader can be elected in a given term. */
static void __ensure_election_safety(system_t* sys)
{
    int i;

    for (i = 0; i < sys->n_nodes; i++)
    {
        raft_server_t* r = sys->nodes[i].raft;

        if (!raft_is_leader(r))
            continue;

        int j;
        for (j = i + 1; j < sys->n_nodes; j++)
        {
            raft_server_t* r2 = sys->nodes[j].raft;
            if (raft_is_leader(r2) &&
                raft_get_current_term(r) == raft_get_current_term(r2))
            {
                printf("election safety invalidated %lx %lx\n",
                       (unsigned long)r,
                       (unsigned long)r2);
                __int_handler(0);
                abort();
            }
        }
    }
}

// TODO:
/* Log Matching
 * If two logs contain an entry with the same index and term, then the
 * logs are identical in all entries up through the given index. */
static void __ensure_log_matching(system_t* sys)
{

}

void strrnd(char* s, size_t len)
{
    int i;
    for (i = 0; i < len; i++)
        s[i] = 'a' + random() % 64;
}

static void __push_entry(system_t* sys)
{
    int i;

    for (i = 0; i < sys->n_nodes; i++)
    {
        raft_server_t* r = sys->nodes[i].raft;
        if (raft_is_leader(r))
        {
            /* printf("adding %lx\n", (unsigned long)r); */
            raft_entry_t* ety = calloc(1, sizeof(*ety));
            ety->id = sys->n_entries++;
            ety->data.buf = malloc(16);
            ety->data.len = 16;
            strrnd(ety->data.buf, 16);
            msg_entry_response_t response;
            raft_recv_entry(r, ety, &response);
        }
    }
}

/** Leader Completeness
 * If a log entry is committed in a given term, then that entry will be present
 * in the logs of the leaders for all higher-numbered terms. §3.6 */
static void __ensure_leader_completeness(system_t* sys)
{
    int i;

    for (i = 0; i < sys->n_nodes; i++)
    {
        raft_server_t* r = sys->nodes[i].raft;

        int j;
        int comi = raft_get_commit_idx(r);

        /* we need to confirm that at least half of the nodes have this */
        int have = 1;

        if (comi == 0)
            continue;

        raft_entry_t* ety = raft_get_entry_from_idx(r, comi);

        for (j=0; j < sys->n_nodes; j++)
        {
            raft_server_t* r2 = sys->nodes[j].raft;

            if (r == r2)
                continue;

            /* all the other nodes should not conflict with this */

            raft_entry_t* oety = raft_get_entry_from_idx(r2, comi);

            if (!oety)
                continue;

            if (!(oety->term != ety->term || oety->id != ety->id))
            {
                have += 1;
            }
        }

        /* a majority don't have it */
        if (!(sys->n_nodes / 2 < have))
        {
            printf("leaders completeness failed: %lx commit_idx: %d t: %d id: %d\n",
                   (unsigned long)r,
                   raft_get_commit_idx(r),
                   ety->term,
                   ety->id
                   );
            __int_handler(0);
            abort();
        }
    }
}

int main(int argc, char **argv)
{
    int e, i;

    e = parse_options(argc, argv, &opts);
    if (-1 == e)
        exit(-1);
    else if (opts.help)
    {
        show_usage();
        exit(0);
    }
    else if (opts.version)
    {
        fprintf(stdout, "%s\n", VERSION);
        exit(0);
    }

    if (!opts.debug)
        raft_funcs.log = NULL;

    signal(SIGPIPE, SIG_IGN);
    signal(SIGINT, __int_handler);

    srand(atoi(opts.seed));

    sys.n_nodes = atoi(opts.NODES);
    sys.nodes = calloc(sys.n_nodes, sizeof(*sys.nodes));

    printf("Starting with %d nodes\n", sys.n_nodes);

    /* create server for every node */
    for (i = 0; i < sys.n_nodes; i++)
        __create_node(&sys.nodes[i], i, &sys);

    int client_rate = atoi(opts.client_rate);

    while (1)
    {
        if (opts.debug)
            printf("\n");

        if (random() % 100 < client_rate)
            __push_entry(&sys);

        for (i = 0; i < sys.n_nodes; i++)
            /* if (random() % 100 < 90) */
                __server_poll_messages(&sys.nodes[i], &sys);

        for (i = 0; i < sys.n_nodes; i++)
            raft_periodic(sys.nodes[i].raft, random() % 200);

        __ensure_election_safety(&sys);
        __ensure_log_matching(&sys);
        __ensure_leader_completeness(&sys);
        /* sleep(1); */
    }
}
