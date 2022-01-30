GLFW_DEP = -L./libs/glfw/ -lglfw
GLAD_DEP = -I./libs/glad/include
STB_IMAGE_DEP = -I./libs/stb_image
SRC = $(wildcard ./*.cpp) ./libs/glad/src/gl.c ./libs/stb_image/stbi_image.cpp
CPP_FLAGS = -std=c++17

game.out: $(SRC)
	$(CXX) $^ ${GLFW_DEP} -o $@ ${GLAD_DEP} ${STB_IMAGE_DEP} ${CPP_FLAGS}

.PHONY:clean pack
clean:
	-rm *.o
	-rm *.out
pack:
	-rm -r output
	-mkdir output
	-mv game.out output/
	-cp libs/glfw/libglfw.3.dylib output/
