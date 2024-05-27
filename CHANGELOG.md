## v0.4.2 (2024-05-27)

### Fix

- using glad as a normal source file

## v0.4.1 (2024-05-27)

### Refactor

- separated draw function into draw and draw prepearations

## v0.4.0 (2024-05-24)

### Feat

- **window**: improved power of Window class
- turned Drawable more meaningful

### Refactor

- removed unused methods

## v0.3.0 (2024-05-23)

### Feat

- **camera**: now is possible to configure zNear and zFar

## v0.2.2 (2024-04-12)

### Fix

- sphere model
- define GLM_ENABLE_EXPERIMENTAL in newer versions of GLM

### Refactor

- **window**: removed CTRL button
- using Object3D without pointer
- removed unused include
- **Entity**: stores shared_ptr instead of a copy of the object
- **shaders**: reduced redundancy and using better practices

## v0.2.1 (2023-11-15)

### Refactor

- **scene**: using smart pointers to store the objects
- **fragment-shader**: simulating a light from a sphere

## v0.2.0 (2023-11-10)

### Feat

- **scene**: add copy move and assign constructors
- **window**: add copy move and assign operator
- **entity**: add copy move and assign operator
- **object3d**: add copy move and assign operator
- **model**: add copy move and assign operator
- **gmesh**: add copy move and assign operator
- **camera**: add copy move and assign operator
- **ebo**: add copy move and assign operator
- **shader**: add copy move and assign operator
- **mesh**: add copy move and assign operator
- **texture**: add copy move and assign operator
- **vbo**: add copy move and assign operator
- **vao**: add copy and move constructor
- implemented scene
- add bind_shader at drawable things
- **model**: add constructor for simple mesh model
- more steps in scene
- **shader**: added default constructor
- **scene**: add files
- add file idrawable.hpp

### Fix

- **object3d**: pos -> model_mat
- **vao**: add operator assign
- **entity**: add_object function

### Refactor

- move constructors and assign operators
- using current_scene in window
- **model.cpp**: removed warnings
- **utils**: declaring under namespace
- **scene**: move to public
- **entity**: using new model matrix in object3d
- **object3d**: model matrix
- **model**: moved to public some attributes
- **gmesh**: moved to public some attributes
- storing shader in gmesh
- **entity**: using just Object3D
- **object3d**: assemble object2d into object3d
- removed object and object2d
- **object.hpp**: now Object inherit from Drawable
- **idrawable**: renamed file
- renamed to Drawable
- using idrawable
- improved semantics of the code

## v0.1.0 (2023-10-20)

### Feat

- **object3d**: added static method to create Object3D from file
- **engine.hpp**: added new headers
- **object.hpp**: Entity is now a friend class
- **object3d**: added object3d
- **object**: added abstract class Object
- added one more abstraction level in mesh
- added m26 model
- **window**: added set_color using Color
- **model**: allow user to choose a default color for model
- **sphere.obj**: added sphere 3D object

### Fix

- **entity**: assert expr
- **object3d**: error when callign constructor Object3D()
- using GMesh instead of Mesh now
- **window.cpp**: minor error
- deleted docs
- using glFlush instead of SwapBuffers
- indices, now it's possible to use culling
- hand model removed and renamed indoali
- **def_fragment_shader.glsl**: fixed alpha attrib of temp_frag_color when doing specular light
- specular light bug when not loading specular map from material
- **engine.hpp**: added missing headers
- **object2d.cpp**: drawing simple mesh without disabling GL_CULL_FACE
- **def_fragment_shader.glsl**: lighting when the mesh isn't textured
- code style for namespace

### Refactor

- removed some warnings
- **object2d**: matrix is now obrigatory
- **window**: using delta t as default in Window::process_input
- **entity**: added polymorphism with Object class
- **model**: minor change in constructor and moved some member to protected
- using initializer lists
- **object2d**: now object2d inherit from Mesh
- **vao.cpp**: changed method param name
- fixed fps to 60
- removed unused header
- fixed mistyping
- **window.cpp**: removing the 60 fps "limit"
- **camera**: using delta V as one of the parameters for calculate the movement
- changed some things in floor scale
- using projection and view uniforms instead of the whole camera
- processing camera matrix inside shader
- removed warning
- removed glDisable(GL_CULL_FACE) when rendering simple meshes
- removed and added some headers
- using other file to do assimp things
- **main.cpp**: small changes
- **window**: Removed main_loop because it was not being used
- **mesh.hpp**: turn some members to private
- **main.cpp**: using inheritance and implemented main_loop as it was in window.cpp
- **window**: removed the code from main_loop
