EXAMPLES = $(wildcard examples/**/**/*.c) $(wildcard examples/**/**/*.cpp) $(wildcard examples/**/**/*.ino)

.PHONY: clean docs format test $(EXAMPLES)

clean:
	@rm -rf .pio .vscode docs
	@find -name "sdkconfig.*" | xargs rm -f

docs:
	@doxygen doxygen/Doxyfile

format:
	@find src test -name *.h -o -name *.c -o -name *.cpp ! -name fixtures.c | xargs clang-format -i

# Run unit tests in native environment
test:
	@pio test -e native

# Build and upload an example, must provide ENV
$(EXAMPLES):
	PLATFORMIO_SRC_DIR=$(dir $@) pio run -e ${ENV} -t upload && PLATFORMIO_SRC_DIR=$(dir $@) pio run -e ${ENV} -t monitor