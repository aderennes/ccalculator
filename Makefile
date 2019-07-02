clean:
	if [ -d "build" ]; then rm -r build/; fi

build: clean
	mkdir build/ && gcc *.c -o build/ccalculator

run: build
	./build/ccalculator
