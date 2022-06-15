.PHONY: clean docs format

clean:
	@git clean -fdXi

docs:
	@doxygen doxygen/Doxyfile

format:
	@find src test -name *.h -o -name *.c -o -name *.cpp ! -name fixtures.c | xargs clang-format -i