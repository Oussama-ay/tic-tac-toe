IMAGE_NAME = emscripten-tictactoe
WASM_DIR = wasm
ENGINE_DIR = engine

.PHONY: all build-image build-wasm clean

all: build-wasm

build-image:
	docker build -t $(IMAGE_NAME) .

build-wasm: build-image
	mkdir -p $(WASM_DIR)
	docker run --rm -v $(shell pwd):/project $(IMAGE_NAME) \
		emcc $(ENGINE_DIR)/engine.cpp -o $(WASM_DIR)/engine.js \
		-s EXPORTED_FUNCTIONS='["_get_best_move"]' \
		-s EXPORTED_RUNTIME_METHODS='["ccall","cwrap"]' \
		-s SINGLE_FILE=1 \
		-O3

clean:
	rm -rf $(WASM_DIR)/engine.js
