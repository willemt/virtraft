import unittest
from subprocess import Popen, PIPE


app_exe = 'build/virtraft'

commands = [
    'entry',
    'entry',
    'entry',
    'entry',
    'entry',
    'perid0',
    'perid1',
    'perid2',
    'perid3',
    'perid4',
    'part0',
    'part1',
    'part2',
    'part3',
    'part4',
]


from hypothesis import given
from hypothesis.strategies import lists, sampled_from


class CoreTestCase(unittest.TestCase):
    @given(lists(sampled_from(commands), min_size=2, max_size=20))
    def test_join(self, data):
        # assume(not any(map(lambda (a, b): a == b, zip(data, data[1:]))))
        args = [app_exe, '--nodes', '5']
        args.extend(['--seed', '3'])
        args.extend(['--no_random_period'])
        # args.extend(['--client_rate', '0'])
        # args.extend(['--drop_rate', '50'])
        # args.extend(['--dupe_rate', '50'])
        p = Popen(args, stdin=PIPE, stdout=PIPE)
        p.communicate(input=''.join(data))
        assert p.returncode == 0


if __name__ == '__main__':
    unittest.main()
