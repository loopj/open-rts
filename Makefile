.PHONY: clean docs format

clean:
	@rm -rf .vscode docs
	@find -type d -name build -o -name "sdkconfig*" | xargs rm -rf

docs:
	@doxygen doxygen/Doxyfile

format:
	@find src test -name *.h -o -name *.c -o -name *.cpp ! -name fixtures.c | xargs clang-format -i