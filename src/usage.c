
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
    int no_random_period;
    int nodes;
    int tsv;
    int version;

    /* options */
    char* client_rate;
    char* drop_rate;
    char* dupe_rate;
    char* iterations;
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


#line 82 "src/usage.rl"



#line 48 "src/usage.c"
static const char _params_actions[] = {
	0, 1, 0, 1, 3, 1, 4, 1, 
	5, 1, 6, 1, 7, 1, 8, 2, 
	1, 9, 2, 1, 10, 2, 1, 11, 
	2, 1, 12, 2, 1, 13, 2, 1, 
	14, 2, 2, 0
};

static const char _params_key_offsets[] = {
	0, 0, 1, 5, 8, 9, 10, 11, 
	12, 13, 14, 15, 16, 17, 18, 19, 
	27, 33, 34, 35, 36, 37, 38, 39, 
	40, 41, 42, 43, 44, 45, 46, 49, 
	50, 51, 52, 53, 54, 55, 56, 57, 
	58, 59, 60, 61, 62, 63, 64, 65, 
	66, 67, 68, 69, 70, 71, 72, 73, 
	74, 75, 76, 77, 78, 79, 80, 81, 
	82, 83, 84, 85, 86, 87, 88, 89, 
	90, 91, 92, 93, 94, 95, 96, 97, 
	98, 99, 100, 101, 102, 103, 104, 105, 
	106, 107, 108, 109, 110, 111, 112, 113, 
	114, 115, 116, 117, 117
};

static const char _params_trans_keys[] = {
	45, 45, 104, 110, 118, 104, 110, 118, 
	101, 108, 112, 0, 111, 100, 101, 115, 
	0, 0, 0, 45, 68, 99, 100, 103, 
	105, 112, 115, 99, 100, 105, 110, 115, 
	116, 108, 105, 101, 110, 116, 95, 114, 
	97, 116, 101, 0, 0, 0, 101, 114, 
	117, 98, 117, 103, 0, 111, 112, 95, 
	114, 97, 116, 101, 0, 0, 0, 112, 
	101, 95, 114, 97, 116, 101, 0, 0, 
	0, 116, 101, 114, 97, 116, 105, 111, 
	110, 115, 0, 0, 0, 111, 95, 114, 
	97, 110, 100, 111, 109, 95, 112, 101, 
	114, 105, 111, 100, 0, 101, 101, 100, 
	0, 0, 0, 115, 118, 0, 101, 114, 
	115, 105, 111, 110, 0, 45, 0
};

static const char _params_single_lengths[] = {
	0, 1, 4, 3, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 8, 
	6, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 3, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 0, 1
};

static const char _params_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0
};

static const short _params_index_offsets[] = {
	0, 0, 2, 7, 11, 13, 15, 17, 
	19, 21, 23, 25, 27, 29, 31, 33, 
	42, 49, 51, 53, 55, 57, 59, 61, 
	63, 65, 67, 69, 71, 73, 75, 79, 
	81, 83, 85, 87, 89, 91, 93, 95, 
	97, 99, 101, 103, 105, 107, 109, 111, 
	113, 115, 117, 119, 121, 123, 125, 127, 
	129, 131, 133, 135, 137, 139, 141, 143, 
	145, 147, 149, 151, 153, 155, 157, 159, 
	161, 163, 165, 167, 169, 171, 173, 175, 
	177, 179, 181, 183, 185, 187, 189, 191, 
	193, 195, 197, 199, 201, 203, 205, 207, 
	209, 211, 213, 215, 216
};

static const char _params_trans_targs[] = {
	2, 0, 3, 7, 12, 98, 0, 4, 
	8, 92, 0, 5, 0, 6, 0, 7, 
	0, 99, 0, 9, 0, 10, 0, 11, 
	0, 12, 0, 13, 0, 0, 14, 100, 
	14, 16, 52, 27, 42, 34, 64, 82, 
	86, 0, 17, 30, 55, 67, 83, 89, 
	0, 18, 0, 19, 0, 20, 0, 21, 
	0, 22, 0, 23, 0, 24, 0, 25, 
	0, 26, 0, 27, 0, 28, 0, 0, 
	29, 100, 29, 31, 35, 45, 0, 32, 
	0, 33, 0, 34, 0, 100, 0, 36, 
	0, 37, 0, 38, 0, 39, 0, 40, 
	0, 41, 0, 42, 0, 43, 0, 0, 
	44, 100, 44, 46, 0, 47, 0, 48, 
	0, 49, 0, 50, 0, 51, 0, 52, 
	0, 53, 0, 0, 54, 100, 54, 56, 
	0, 57, 0, 58, 0, 59, 0, 60, 
	0, 61, 0, 62, 0, 63, 0, 64, 
	0, 65, 0, 0, 66, 100, 66, 68, 
	0, 69, 0, 70, 0, 71, 0, 72, 
	0, 73, 0, 74, 0, 75, 0, 76, 
	0, 77, 0, 78, 0, 79, 0, 80, 
	0, 81, 0, 82, 0, 100, 0, 84, 
	0, 85, 0, 86, 0, 87, 0, 0, 
	88, 100, 88, 90, 0, 91, 0, 100, 
	0, 93, 0, 94, 0, 95, 0, 96, 
	0, 97, 0, 98, 0, 99, 0, 0, 
	15, 0, 0
};

static const char _params_trans_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 5, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 9, 0, 0, 33, 30, 
	1, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	33, 15, 1, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 3, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	33, 18, 1, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 33, 21, 1, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 33, 24, 1, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 7, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	33, 27, 1, 0, 0, 0, 0, 11, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 13, 0, 0, 
	0, 0, 0
};

static const int params_start = 1;
static const int params_first_final = 99;
static const int params_error = 0;

static const int params_en_main = 1;


#line 85 "src/usage.rl"

static void params_init(struct params *fsm, options_t* opt)
{
    memset(opt, 0, sizeof(options_t));

    fsm->opt = opt;
    fsm->buflen = 0;
    fsm->opt->client_rate = strdup("100");
    fsm->opt->drop_rate = strdup("0");
    fsm->opt->dupe_rate = strdup("0");
    fsm->opt->iterations = strdup("-1");
    fsm->opt->seed = strdup("0");

    
#line 223 "src/usage.c"
	{
	 fsm->cs = params_start;
	}

#line 99 "src/usage.rl"
}

static void params_execute(struct params *fsm, const char *data, int len)
{
    const char *p = data;
    const char *pe = data + len;

    
#line 237 "src/usage.c"
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
#line 44 "src/usage.rl"
	{
        if (fsm->buflen < BUFLEN)
            fsm->buffer[fsm->buflen++] = (*p);
    }
	break;
	case 1:
#line 49 "src/usage.rl"
	{
        if (fsm->buflen < BUFLEN)
            fsm->buffer[fsm->buflen++] = 0;
    }
	break;
	case 2:
#line 54 "src/usage.rl"
	{ fsm->buflen = 0; }
	break;
	case 3:
#line 57 "src/usage.rl"
	{ fsm->opt->debug = 1; }
	break;
	case 4:
#line 58 "src/usage.rl"
	{ fsm->opt->help = 1; }
	break;
	case 5:
#line 59 "src/usage.rl"
	{ fsm->opt->no_random_period = 1; }
	break;
	case 6:
#line 60 "src/usage.rl"
	{ fsm->opt->nodes = 1; }
	break;
	case 7:
#line 61 "src/usage.rl"
	{ fsm->opt->tsv = 1; }
	break;
	case 8:
#line 62 "src/usage.rl"
	{ fsm->opt->version = 1; }
	break;
	case 9:
#line 63 "src/usage.rl"
	{ fsm->opt->client_rate = strdup(fsm->buffer); }
	break;
	case 10:
#line 64 "src/usage.rl"
	{ fsm->opt->drop_rate = strdup(fsm->buffer); }
	break;
	case 11:
#line 65 "src/usage.rl"
	{ fsm->opt->dupe_rate = strdup(fsm->buffer); }
	break;
	case 12:
#line 66 "src/usage.rl"
	{ fsm->opt->iterations = strdup(fsm->buffer); }
	break;
	case 13:
#line 67 "src/usage.rl"
	{ fsm->opt->seed = strdup(fsm->buffer); }
	break;
	case 14:
#line 68 "src/usage.rl"
	{ fsm->opt->NODES = strdup(fsm->buffer); }
	break;
#line 376 "src/usage.c"
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

#line 107 "src/usage.rl"
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
    fprintf(stdout, "  virtraft --nodes NODES [-d RATE | -D RATE | -c RATE | -s SEED | -i ITERS | -p | --tsv | --debug]\n");
    fprintf(stdout, "  virtraft --version\n");
    fprintf(stdout, "  virtraft --help\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "Options:\n");
    fprintf(stdout, "  -n --nodes              Number of nodes\n");
    fprintf(stdout, "  -d --drop_rate RATE     Message drop rate 0-100 [default: 0]\n");
    fprintf(stdout, "  -D --dupe_rate RATE     Message duplication rate 0-100 [default: 0]\n");
    fprintf(stdout, "  -c --client_rate RATE   Rate entries are received from the client 0-100 [default: 100]\n");
    fprintf(stdout, "  -p --no_random_period   Don't use a random period\n");
    fprintf(stdout, "  -s --seed SEED          The simulation's seed [default: 0]\n");
    fprintf(stdout, "  -i --iterations ITERS   Number of iterations before the simulation ends [default: -1]\n");
    fprintf(stdout, "  --tsv                   Output node status tab separated values at exit\n");
    fprintf(stdout, "  -g --debug              Show debug logs\n");
    fprintf(stdout, "  -v --version            Display version.\n");
    fprintf(stdout, "  -h --help               Prints a short usage summary.\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "Examples:\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "  Output a node status table:\n");
    fprintf(stdout, "    build/virtraft --nodes 3 --iterations 1000 --tsv | column -t\n");
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

