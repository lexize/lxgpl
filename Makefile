FREETYPE_FLAGS = -I/usr/include/freetype2 -lfreetype
LUA_FLAGS = -I/usr/local/include -l:liblua.a
THIRDPARTY_FLAGS = -Ithirdparty
CFLAGS ?= -Wall -Wno-unused-parameter -Wno-incompatible-pointer-types -Wextra -Isrc/ ${FREETYPE_FLAGS} ${LUA_FLAGS} ${THIRDPARTY_FLAGS} -lm -ggdb -fPIC

CC ?= gcc

AR ?= ar

build/canvas.o: src/canvas.c src/canvas.h
	${CC} ${CFLAGS} -o build/canvas.o -c src/canvas.c

build/drawing_context.o: src/drawing_context.c src/drawing_context.h
	${CC} ${CFLAGS} -o build/drawing_context.o -c src/drawing_context.c

build/font.o: src/font.c src/font.h
	${CC} ${CFLAGS} -o build/font.o -c src/font.c

build/gui.o: src/gui.c src/gui.h
	${CC} ${CFLAGS} -o build/gui.o -c src/gui.c

build/hashmap.o: src/hashmap.c src/hashmap.h
	${CC} ${CFLAGS} -o build/hashmap.o -c src/hashmap.c

build/shapes.o: src/shapes.c src/shapes.h
	${CC} ${CFLAGS} -o build/shapes.o -c src/shapes.c

build/string_builder.o: src/string_builder.c src/string_builder.h
	${CC} ${CFLAGS} -o build/string_builder.o -c src/string_builder.c

build/string_hashmap.o: src/string_hashmap.c src/string_hashmap.h
	${CC} ${CFLAGS} -o build/string_hashmap.o -c src/string_hashmap.c

build/colors.o: src/colors.c src/colors.h
	${CC} ${CFLAGS} -o build/colors.o -c src/colors.c

build/math_utils.o: src/math_utils.c src/math_utils.h
	${CC} ${CFLAGS} -o build/math_utils.o -c src/math_utils.c

build/vectors.o: src/vectors.c src/vectors.h
	${CC} ${CFLAGS} -o build/vectors.o -c src/vectors.c

build/curves.o: src/curves.c src/curves.h
	${CC} ${CFLAGS} -o build/curves.o -c src/curves.c

build/matrices.o: src/matrices.c src/matrices.h
	${CC} ${CFLAGS} -o build/matrices.o -c src/matrices.c

build/cgltf.o: src/cgltf.c
	${CC} ${CFLAGS} -o build/cgltf.o -c src/cgltf.c

build/widgets_panel.o: src/widgets/panel.c src/widgets/panel.h
	${CC} ${CFLAGS} -o build/widgets_panel.o -c src/widgets/panel.c

build/widgets_label.o: src/widgets/label.c src/widgets/label.h
	${CC} ${CFLAGS} -o build/widgets_label.o -c src/widgets/label.c

CORELIB = build/canvas.o build/drawing_context.o build/font.o build/gui.o build/hashmap.o build/shapes.o build/string_builder.o build/string_hashmap.o build/colors.o build/math_utils.o build/vectors.o build/curves.o build/matrices.o
WIDGETS = build/widgets_panel.o build/widgets_label.o

libs/liblxgui.so: $(CORELIB) $(WIDGETS)
	mkdir -p libs
	${CC} -fPIC -shared -o libs/liblxgui.so $(CORELIB) $(WIDGETS)                                                                           

libs/liblxgui.a: $(CORELIB) $(WIDGETS)
	mkdir -p libs
	${AR} rcs libs/liblxgui.a $(CORELIB) $(WIDGETS)

build/examples_test.o: examples/test.c
	${CC} ${CFLAGS} -o build/examples_test.o -c examples/test.c

build/sdl_test.o: examples/sdl.c
	${CC} ${CFLAGS} -o build/sdl_test.o -c examples/sdl.c

build/test: libs/liblxgui.a build/examples_test.o
	${CC} ${CFLAGS} -O build/examples_test.o -L${PWD}/libs -l:liblxgui.a -o build/test
build/sdl_test: libs/liblxgui.a build/sdl_test.o
	${CC} ${CFLAGS} -lSDL3 -O build/sdl_test.o -L${PWD}/libs -l:liblxgui.a -o build/sdl_test
