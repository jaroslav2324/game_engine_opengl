
g++ -g src/main.cpp \
 src/maths/Vector2D.cpp \
 src/maths/Point2D.cpp \
 src/maths/Matrix2x2.cpp \
 src/maths/Segment2D.cpp \
 src/maths/mathsCircle.cpp \
 src/maths/mathsRect.cpp \
 src/triangulation/structures.cpp \
 src/triangulation/triangulation.cpp \
 src/rendering/Renderer.cpp \
 src/objects/Circle.cpp \
 src/objects/Rect.cpp \
 src/objects/CollidableObject.cpp \
 src/objects/RigidBody.cpp \
 src/objects/ObjectManager.cpp \
 src/objects/Softbody.cpp \
 src/objects/SoftbodyCircle.cpp \
 src/objects/SoftbodyCell.cpp \
 src/objects/SoftbodyRect.cpp \
 src/utils/pointsGeneration.cpp \
 src/utils/Color.cpp \
 src/physics/AABB.cpp \
 src/physics/PhysicsParameters.cpp \
 src/physics/CollisionShape.cpp \
 src/physics/CircleCollisionShape.cpp \
 src/physics/PhysicsManager.cpp \
 src/physics/RectCollisionShape.cpp \
 src/physics/ColisionManager.cpp \
 src/scenes/Scenes.cpp \
 src/scenes/PingPong.cpp \
 src/scenes/SoftbodyScene.cpp \
 src/softbody/SoftbodyPoint.cpp \
 src/softbody/SoftbodySpring.cpp \
 -o collisionEngine -lglut -lGLU -lGL
