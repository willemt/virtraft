
#line 1 "src/command_parser.rl"
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


#line 62 "src/command_parser.rl"



#line 25 "src/command_parser.c"
static const char _path_parse_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4
};

static const char _path_parse_key_offsets[] = {
	0, 0, 1, 2, 3, 5, 6, 7, 
	8, 9, 11, 12, 13, 15, 16, 17, 
	18, 20, 21, 22, 23, 25
};

static const char _path_parse_trans_keys[] = {
	114, 111, 112, 48, 57, 110, 116, 114, 
	121, 97, 101, 114, 116, 48, 57, 114, 
	105, 100, 48, 57, 101, 99, 118, 48, 
	57, 100, 101, 112, 114, 0
};

static const char _path_parse_single_lengths[] = {
	0, 1, 1, 1, 0, 1, 1, 1, 
	1, 2, 1, 1, 0, 1, 1, 1, 
	0, 1, 1, 1, 0, 4
};

static const char _path_parse_range_lengths[] = {
	0, 0, 0, 0, 1, 0, 0, 0, 
	0, 0, 0, 0, 1, 0, 0, 0, 
	1, 0, 0, 0, 1, 0
};

static const char _path_parse_index_offsets[] = {
	0, 0, 2, 4, 6, 8, 10, 12, 
	14, 16, 19, 21, 23, 25, 27, 29, 
	31, 33, 35, 37, 39, 41
};

static const char _path_parse_trans_targs[] = {
	2, 0, 3, 0, 4, 0, 21, 0, 
	6, 0, 7, 0, 8, 0, 21, 0, 
	10, 13, 0, 11, 0, 12, 0, 21, 
	0, 14, 0, 15, 0, 16, 0, 21, 
	0, 18, 0, 19, 0, 20, 0, 21, 
	0, 1, 5, 9, 17, 0, 0
};

static const char _path_parse_trans_actions[] = {
	0, 0, 0, 0, 0, 0, 7, 0, 
	0, 0, 0, 0, 0, 0, 1, 0, 
	0, 0, 0, 0, 0, 0, 0, 9, 
	0, 0, 0, 0, 0, 0, 0, 3, 
	0, 0, 0, 0, 0, 0, 0, 5, 
	0, 0, 0, 0, 0, 0, 0
};

static const int path_parse_start = 21;
static const int path_parse_first_final = 21;
static const int path_parse_error = 0;

static const int path_parse_en_main = 21;


#line 65 "src/command_parser.rl"

static void __init(struct path_parse *fsm, system_t* sys, parse_result_t* result)
{
    fsm->sys = sys;
    fsm->r = result;
    fsm->node_id = 0;
    
#line 95 "src/command_parser.c"
	{
	 fsm->cs = path_parse_start;
	}

#line 72 "src/command_parser.rl"
}

static void __execute(struct path_parse *fsm, const char *data, size_t len)
{
    const char *p = data;
    const char *pe = data + len;
    //const char *eof = data + len;
    
#line 109 "src/command_parser.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( p == pe )
		goto _test_eof;
	if (  fsm->cs == 0 )
		goto _out;
_resume:
	_keys = _path_parse_trans_keys + _path_parse_key_offsets[ fsm->cs];
	_trans = _path_parse_index_offsets[ fsm->cs];

	_klen = _path_parse_single_lengths[ fsm->cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _path_parse_range_lengths[ fsm->cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	 fsm->cs = _path_parse_trans_targs[_trans];

	if ( _path_parse_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _path_parse_actions + _path_parse_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
#line 24 "src/command_parser.rl"
	{
        __periodic(&sys);
    }
	break;
	case 1:
#line 28 "src/command_parser.rl"
	{
        raft_periodic(sys.servers[(*p) - '0'].raft, 500);
        __ensure_election_safety(&sys);
        __ensure_log_matching(&sys);
        __ensure_leader_completeness(&sys);
    }
	break;
	case 2:
#line 35 "src/command_parser.rl"
	{
        __push_entry(fsm->sys);
        __server_poll_messages(&sys.servers[(*p) - '0'], &sys);
    }
	break;
	case 3:
#line 40 "src/command_parser.rl"
	{
        __push_entry(fsm->sys);
        __server_drop_messages(&sys.servers[(*p) - '0'], &sys);
    }
	break;
	case 4:
#line 45 "src/command_parser.rl"
	{
        int node_id1 = *(p) - '0';
        server_t* sv = &sys.servers[node_id1];
        sv->partitioned = !sv->partitioned;
    }
	break;
#line 219 "src/command_parser.c"
		}
	}

_again:
	if (  fsm->cs == 0 )
		goto _out;
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

#line 80 "src/command_parser.rl"
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

    while (0 < read(0, buf, 1))
    {
        // printf("reading: %c\n", *buf);
        ran = 1;
        if (*buf == '\0')
            break;
        __execute(&pp, buf, 1);
    }

    __finish(&pp);

    return ran;
}
