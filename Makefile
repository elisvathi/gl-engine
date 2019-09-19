BUILD_DIR = build
BIN_DIR = $(BUILD_DIR)/bin

gpu-tracer: build-project run

build-project:
	@cd $(BUILD_DIR) && cmake --build .

clean:
	rm -rf build

reinstall: clean install

install:
	mkdir build && cd build && conan install .. && cmake .. && cmake --build .

run:
	@cd $(BIN_DIR) && ./GEngine
