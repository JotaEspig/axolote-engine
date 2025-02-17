## v0.9.1 (2025-02-17)

### Fix

- windows installer vcpkg_path not expanding
- error found on windows
- showing error when failed to load texture
- polygon mode using post-processing

### Refactor

- using cached shaders in scene

## v0.9.0 (2024-12-20)

### Feat

- added Instancing class to render instanced objects
- added another way to create a Shader class
- allowing user to use post-processing effects using SceneRenderer class
- added camera renderers
- **scene**: add methods to remove drawables and lights
- added gamma correction to the scene
- add method to maximize window

### Fix

- updating camera when resizing window

### Refactor

- **Instancing**: using Object3D to allow lights handling
- showing more debug info in get_file_contents
- removed method in Window class because of inconsistency in its use
- renamed method in Shader class
- CameraRenderer and Scene using SceneContext intermediary class for communication
- camera matrices are now private
- pre-calculating camera matrix
- calculating camera matrix in cpu
- stopped using alias

## v0.8.0 (2024-10-19)

### Feat

- added get ray from mouse input
- added get ray from mouse input
- added get_end() method to Line, changed 'a' to 'start'
- **framebuffer**: working resizing everything else
- **window**: added getter for glfw window pointer
- **light**: added intensity to Directional Light

### Fix

- ambient color
- defining M_PIf in windows
- defining M_PIf in windows
- utils/line now using thickness correctly
- for windows
- scene now updates grid's position
- using set_window_size
- mirror now using correct aspect ratio for projection
- cmake assimp include dir
- bug in texture when unit was not set manually
- **gmesh**: now gmesh considers an untyped texture as diffuse
- **texture**: generating texture in the default constructor
- small error on windows

### Refactor

- **shaders**: removed useless clamp
- scene doesnt stores the shaders anymore
- get_shader -> get_shaders
- debug destroyed gl object after destroying it
- change constructor parameters to use string instead of const char*

## v0.7.1 (2024-08-19)

### Fix

- **window**: opengl version to 3.3

## v0.7.0 (2024-08-18)

### Feat

- added option to disable lights per object
- **line**: added normals into line
- **grid**: implemented grid into the scene
- **grid**: implemented fading
- using interface to define a opengl object
- add debug print function
- opengl objects are now destroyed
- implemented sorted way to draw objects
- **lights**: added smooth edges for spot light
- **lights**: implemented simple spot light
- **lights**: implemented directional light

### Fix

- grid draw order
- texture opacity discard

### Refactor

- renamed Vertex.position to just pos
- **grid**: configurable fading
- using doubles instead of floats in update methods
- changed small things in debug
- **lights**: separated ambient light and ambient light intensity
- saving normal matrix in Object3D class
- **shaders**: renamed all variables, uniforms, functions, etc related to axolote engine

## v0.6.5 (2024-06-17)

### Fix

- now gl methods dont call unbind

## v0.6.4 (2024-06-11)

### Fix

- missing model.hpp

## v0.6.3 (2024-06-11)

### Fix

- installation script...

## v0.6.2 (2024-06-11)

### Fix

- installation script...

## v0.6.1 (2024-06-11)

### Fix

- installation script

## v0.6.0 (2024-06-11)

### Feat

- add some wrapper methods for OpenGL functions
- **window**: add wrapper methods to glfw functions

### Fix

- **window**: changed Key to camera go upwards
- **window**: keys_pressed map access methods

## v0.5.0 (2024-05-27)

### Feat

- added method attrib_divisor
- updated glad

## v0.4.4 (2024-05-27)

### Fix

- VBO constructor using template now

## v0.4.3 (2024-05-27)

### Fix

- cmake file

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
