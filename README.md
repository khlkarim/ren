this is a 3d graphics library based on a opengl backend
if visualizes 3d models animations simulations
you give it 3d data and it visualizes it
1. visualizing a 3d scene
is it a framework? like raylib? meaning how would you use this? how would you interface with a 3d renderer


a 3d model inspector

you have a scene
the scene has one camera and other objects in it
you view the scene from the prepective from the camera
you are able to load 3d objects and dynamicly move them in the scene

classes:
    Camera
        position
        lookAtDirection
    Object
        Primitive
            Triangle 
            Rectangle
        Composite (loaded)

            loaded:
                - vertices
                - texture

            dynamic: 
                - vertex shader 
                - fragment shader
                - position 
                - orientation

create a scene
in the scene (scene initialization):
    create a camera
    add objects
on each frame:
    manipulate the objects in the scene (including the camera)
    render the scene

the rendering logic is in the scene class
it parses the data structure that represent the scene and visualizes it

take inspiration of unity
use high composition

each  entity has a unique identifier just in case
how unique is that identifier?
it would be used to reference that entity? lightweight reference

i should add a namespace (ren::)
read rotation as euler angles 
store them as quaterions