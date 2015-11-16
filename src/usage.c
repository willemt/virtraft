
#line 1 "src/usage.rl"
#include <stdio.h>
#include <string.h>

#define BUFLEN 1024
#define BUFSIZE 2048

typedef struct
{
    /* commands */
    

    /* flags */
    int debug;
    int help;
    int nodes;
    int version;

    /* options */
    char* client_rate;
    char* drop_rate;
    char* seed;

    /* arguments */
    char* NODES;

} options_t;

struct params
{
    options_t* opt;
    char buffer[BUFLEN + 1];
    int buflen;
    int cs;
};


#line 70 "src/usage.rl"



#line 44 "src/usage.c"
static const char _params_actions[] = {
	0, 1, 0, 1, 3, 1, 4, 1, 
	5, 1, 6, 2, 1, 7, 2, 1, 
	8, 2, 1, 9, 2, 1, 10, 2, 
	2, 0
};

static const char _params_key_offsets[] = {
	0, 0, 1, 5, 8, 9, 10, 11, 
	12, 13, 14, 15, 16, 17, 18, 19, 
	24, 27, 28, 29, 30, 31, 32, 33, 
	34, 35, 36, 37, 38, 39, 40, 42, 
	43, 44, 45, 46, 47, 48, 49, 50, 
	51, 52, 53, 54, 55, 56, 57, 58, 
	59, 60, 61, 62, 63, 64, 65, 66, 
	67, 68, 69, 69
};

static const char _params_trans_keys[] = {
	45, 45, 104, 110, 118, 104, 110, 118, 
	101, 108, 112, 0, 111, 100, 101, 115, 
	0, 0, 0, 45, 99, 100, 103, 115, 
	99, 100, 115, 108, 105, 101, 110, 116, 
	95, 114, 97, 116, 101, 0, 0, 0, 
	101, 114, 98, 117, 103, 0, 111, 112, 
	95, 114, 97, 116, 101, 0, 0, 0, 
	101, 101, 100, 0, 0, 0, 101, 114, 
	115, 105, 111, 110, 0, 45, 0
};

static const char _params_single_lengths[] = {
	0, 1, 4, 3, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 5, 
	3, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 2, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 0, 1
};

static const char _params_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0
};

static const unsigned char _params_index_offsets[] = {
	0, 0, 2, 7, 11, 13, 15, 17, 
	19, 21, 23, 25, 27, 29, 31, 33, 
	39, 43, 45, 47, 49, 51, 53, 55, 
	57, 59, 61, 63, 65, 67, 69, 72, 
	74, 76, 78, 80, 82, 84, 86, 88, 
	90, 92, 94, 96, 98, 100, 102, 104, 
	106, 108, 110, 112, 114, 116, 118, 120, 
	122, 124, 126, 127
};

static const char _params_trans_targs[] = {
	2, 0, 3, 7, 12, 57, 0, 4, 
	8, 51, 0, 5, 0, 6, 0, 7, 
	0, 58, 0, 9, 0, 10, 0, 11, 
	0, 12, 0, 13, 0, 0, 14, 59, 
	14, 16, 27, 42, 34, 48, 0, 17, 
	30, 45, 0, 18, 0, 19, 0, 20, 
	0, 21, 0, 22, 0, 23, 0, 24, 
	0, 25, 0, 26, 0, 27, 0, 28, 
	0, 0, 29, 59, 29, 31, 35, 0, 
	32, 0, 33, 0, 34, 0, 59, 0, 
	36, 0, 37, 0, 38, 0, 39, 0, 
	40, 0, 41, 0, 42, 0, 43, 0, 
	0, 44, 59, 44, 46, 0, 47, 0, 
	48, 0, 49, 0, 0, 50, 59, 50, 
	52, 0, 53, 0, 54, 0, 55, 0, 
	56, 0, 57, 0, 58, 0, 0, 15, 
	0, 0
};

static const char _params_trans_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 5, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 7, 0, 0, 23, 20, 
	1, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 23, 11, 1, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 3, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 23, 14, 1, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 23, 17, 1, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 9, 0, 0, 0, 
	0, 0
};

static const int params_start = 1;
static const int params_first_final = 58;
static const int params_error = 0;

static const int params_en_main = 1;


#line 73 "src/usage.rl"

static void params_init(struct params *fsm, options_t* opt)
{
    memset(opt, 0, sizeof(options_t));

    fsm->opt = opt;
    fsm->buflen = 0;
    fsm->opt->client_rate = strdup("100");
    fsm->opt->drop_rate = strdup("0");
    fsm->opt->seed = strdup("0");

    
#line 168 "src/usage.c"
	{
	 fsm->cs = params_start;
	}

#line 85 "src/usage.rl"
}

static void params_execute(struct params *fsm, const char *data, int len)
{
    const char *p = data;
    const char *pe = data + len;

    
#line 182 "src/usage.c"
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
	_keys = _params_trans_keys + _params_key_offsets[ fsm->cs];
	_trans = _params_index_offsets[ fsm->cs];

	_klen = _params_single_lengths[ fsm->cs];
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

	_klen = _params_range_lengths[ fsm->cs];
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
	 fsm->cs = _params_trans_targs[_trans];

	if ( _params_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _params_actions + _params_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
#line 40 "src/usage.rl"
	{
        if (fsm->buflen < BUFLEN)
            fsm->buffer[fsm->buflen++] = (*p);
    }
	break;
	case 1:
#line 45 "src/usage.rl"
	{
        if (fsm->buflen < BUFLEN)
            fsm->buffer[fsm->buflen++] = 0;
    }
	break;
	case 2:
#line 50 "src/usage.rl"
	{ fsm->buflen = 0; }
	break;
	case 3:
#line 53 "src/usage.rl"
	{ fsm->opt->debug = 1; }
	break;
	case 4:
#line 54 "src/usage.rl"
	{ fsm->opt->help = 1; }
	break;
	case 5:
#line 55 "src/usage.rl"
	{ fsm->opt->nodes = 1; }
	break;
	case 6:
#line 56 "src/usage.rl"
	{ fsm->opt->version = 1; }
	break;
	case 7:
#line 57 "src/usage.rl"
	{ fsm->opt->client_rate = strdup(fsm->buffer); }
	break;
	case 8:
#line 58 "src/usage.rl"
	{ fsm->opt->drop_rate = strdup(fsm->buffer); }
	break;
	case 9:
#line 59 "src/usage.rl"
	{ fsm->opt->seed = strdup(fsm->buffer); }
	break;
	case 10:
#line 60 "src/usage.rl"
	{ fsm->opt->NODES = strdup(fsm->buffer); }
	break;
#line 305 "src/usage.c"
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

#line 93 "src/usage.rl"
}

static int params_finish(struct params *fsm)
{
    if (fsm->cs == params_error)
        return -1;
    if (fsm->cs >= params_first_final)
        return 1;
    return 0;
}

static void show_usage()
{
    fprintf(stdout, "virtraft - test raft\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "Usage:\n");
    fprintf(stdout, "  virtraft --nodes NODES [--drop_rate RATE | --client_rate RATE | --seed SEED | --debug]\n");
    fprintf(stdout, "  virtraft --version\n");
    fprintf(stdout, "  virtraft --help\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "Options:\n");
    fprintf(stdout, "  -n --nodes              Number of nodes\n");
    fprintf(stdout, "  -d --drop_rate RATE     Message drop rate 0-100 [default: 0]\n");
    fprintf(stdout, "  -c --client_rate RATE   Rate entries are received from the client 0-100 [default: 100]\n");
    fprintf(stdout, "  -s --seed SEED          The simulation's seed [default: 0]\n");
    fprintf(stdout, "  -g --debug              Show debug logs\n");
    fprintf(stdout, "  -v --version            Display version.\n");
    fprintf(stdout, "  -h --help               Prints a short usage summary.\n");
    fprintf(stdout, "\n");
}

static int parse_options(int argc, char **argv, options_t* options)
{
    int a;
    struct params params;

    params_init(&params, options);
    for (a = 1; a < argc; a++ )
        params_execute(&params, argv[a], strlen(argv[a]) + 1);
    if (params_finish(&params) != 1)
    {
        fprintf(stderr, "Error processing arguments\n");
        show_usage();
        return -1;
    }

    return 0;
}

