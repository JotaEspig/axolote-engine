* Improve project structure organization: e.g. create another namespace for drawable things and make a semantic separation between math representation and drawables
* Allow programmer to have more freedom and be more responsible for VBOs and VAOs. Axolote Engine should be a facilitator for OpenGL.
    - Vertex should be customizable;
    - Entity, Model, Object3D, etc... classes should give the possibility to have VAOs, VBOs binded by the programmer. For example, passing VAO as constructor arg
