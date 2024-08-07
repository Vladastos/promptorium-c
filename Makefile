
all: run

run: build
	./builddir/promptorium

build:
	cd builddir && meson compile && cd ..

format:
	clang-format -i src/main.c

clean:
	rm -rf builddir

install:
	cd builddir && meson install && cd ..
