letsbuildthis:
	python waf configure
	python waf build

clean:
	python waf clean

tests:
	build/virtraft --servers 3 -i 15000 -d 20 --seed 1 -q
	build/virtraft --servers 5 -i 15000 -d 20 -m 20 --seed 2 -q
	python tests/test_fuzzer.py
.PHONY : tests
