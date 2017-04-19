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
    def test_core(self, data):
        # assume(not any(map(lambda (a, b): a == b, zip(data, data[1:]))))
        args = [app_exe, '--servers', '5']
        args.extend(['--seed', '3'])
        args.extend(['--no_random_period'])
        args.extend(['--quiet'])
        # args.extend(['--client_rate', '0'])
        # args.extend(['--drop_rate', '50'])
        # args.extend(['--dupe_rate', '50'])
        p = Popen(args, stdin=PIPE, stdout=PIPE)
        p.communicate(input=''.join(data))
        assert p.returncode == 0

    @given(lists(sampled_from([
        'togglmem0',
        'togglmem1',
        'togglmem2',
        'togglmem3',
        'togglmem4',
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
        ]), min_size=2, max_size=20))
    def test_with_membership_changes(self, data):
        args = [app_exe, '--servers', '5']
        args.extend(['--seed', '3'])
        args.extend(['--no_random_period'])
        args.extend(['--quiet'])
        p = Popen(args, stdin=PIPE, stdout=PIPE)
        p.communicate(input=''.join(data))
        assert p.returncode == 0


class RegressionTestCase(unittest.TestCase):
    def _run(self, data, servers=5, seed='3'):
        args = [app_exe, '--servers', str(servers)]
        if seed:
            args.extend(['--seed', seed])
        args.extend(['--no_random_period'])
        args.extend(['--quiet'])
        p = Popen(args, stdin=PIPE, stdout=PIPE)
        p.communicate(input=''.join(data))
        print(p.returncode)
        assert p.returncode == 0

    def test_no_seed(self):
        self._run(['entry'], seed=None)

    def test_toggle_membership(self):
        self._run(['togglmem0', 'togglmem3'], servers=5)


if __name__ == '__main__':
    unittest.main()
