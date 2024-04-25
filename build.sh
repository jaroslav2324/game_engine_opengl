
g++ -g src/main.cpp \
 src/triangulation/structures.cpp \
 src/triangulation/triangulation.cpp \
  src/rendering/Renderer.cpp \
 src/objects/Circle.cpp \
  src/objects/RigidBody.cpp \
 src/utils/randomGeneration.cpp \
  src/utils/Color.cpp \
  src/physics/CollisionShape.cpp \
  src/physics/CircleCollisionShape.cpp \
  src/physics/ColisionManager.cpp \
 -o collisionEngine -lglut -lGLU -lGL
