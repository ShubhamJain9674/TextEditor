.PHONY: debug release test run clean

DEBUG_DIR := build/debug
RELEASE_DIR := build/release

debug:
	cmake -S . -B $(DEBUG_DIR) \
		-DCMAKE_BUILD_TYPE=Debug \
		-DTEXTEDITOR_BUILD_TESTS=ON
	cmake --build $(DEBUG_DIR)

release:
	cmake -S . -B $(RELEASE_DIR) \
		-DCMAKE_BUILD_TYPE=Release \
		-DTEXTEDITOR_BUILD_TESTS=OFF
	cmake --build $(RELEASE_DIR)

test:
	cmake --build $(DEBUG_DIR)
	./$(DEBUG_DIR)/tests/EditorTests

run:
	cmake --build $(DEBUG_DIR)
	./$(DEBUG_DIR)/TextEditor

clean:
	rm -rf build
