.PHONY: format

format:
	@find src test -name *.h -o -name *.c -o -name *.cpp ! -name fixtures.c | xargs clang-format -i