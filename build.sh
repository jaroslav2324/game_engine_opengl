
g++ -g src/main.cpp \
 src/triangulation/structures.cpp \
 src/triangulation/triangulation.cpp \
  src/rendering/Renderer.cpp \
 src/objects/circle.cpp \
 src/utils/randomGeneration.cpp \
  src/utils/Color.cpp \
 -o collisionEngine -lglut -lGLU -lGL
