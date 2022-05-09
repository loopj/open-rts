EXAMPLES = $(wildcard examples/**/**/*.c)

.PHONY: clean test $(EXAMPLES)

clean:
	@rm -rf .pio .vscode docs

# Run unit tests in native environment
test:
	@pio test -e native

# Build and upload an example, must provide ENV
$(EXAMPLES):
	PLATFORMIO_SRC_DIR=$(dir $@) pio run -e ${ENV} -t upload && PLATFORMIO_SRC_DIR=$(dir $@) pio run -e ${ENV} -t monitor