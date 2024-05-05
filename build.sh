
g++ -g src/main.cpp \
 src/maths/Vector2D.cpp \
 src/maths/Point2D.cpp \
 src/maths/Matrix2x2.cpp \
 src/triangulation/structures.cpp \
 src/triangulation/triangulation.cpp \
  src/rendering/Renderer.cpp \
 src/objects/Circle.cpp \
 src/objects/Rect.cpp \
  src/objects/CollidableObject.cpp \
  src/objects/RigidBody.cpp \
  src/objects/ObjectManager.cpp \
  src/utils/randomGeneration.cpp \
  src/utils/Color.cpp \
  src/physics/PhysicsParameters.cpp \
  src/physics/CollisionShape.cpp \
  src/physics/CircleCollisionShape.cpp \
  src/physics/PhysicsManager.cpp \
  src/physics/RectCollisionShape.cpp \
  src/physics/ColisionManager.cpp \
 -o collisionEngine -lglut -lGLU -lGL
