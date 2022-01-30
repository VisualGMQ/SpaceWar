GLFW_DEP = -L./libs/glfw/ -lglfw
GLAD_DEP = -I./libs/glad/include
STB_IMAGE_DEP = -I./libs/stb_image
SRC = $(wildcard ./*.cpp) glad.o # ./libs/stb_image/stbi_image.cpp
CPP_FLAGS = -std=c++17

game.out: ${SRC}
	$(CXX) $^ ${GLFW_DEP} -o $@ ${GLAD_DEP} ${CPP_FLAGS} #${STB_IMAGE_DEP}

glad.o: ./libs/glad/src/gl.c
	$(CC) $^ -c -o $@ ${GLAD_DEP}

.PHONY:clean pack
clean:
	-rm -rf output
	-rm *.o

pack:
	-rm -rf output
	-mkdir output
	-mv game.out output/
	-cp libs/glfw/libglfw.3.dylib output/
