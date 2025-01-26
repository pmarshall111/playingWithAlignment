.PHONY: build
build:
	rm -rf build && mkdir build && cd build && cmake .. && make

.PHONY: run_speed
run_speed:
	./build/speedTest.tsk