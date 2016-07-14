all: bin/compile.sh
	bin/compile.sh

clean: build/
	rm -rf build/
