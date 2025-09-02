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

how do i implement composition? pointers or stack allocated classes? => unique pointers
stack allocated classes have to be initialized
and live and die simultainously with the class!

you cant change the camera in the scene
int instanceID = scene.instantiate(prefab)

EntityInstance entity = scene.get(instanceID)

entities are what is in the scene object, any outside asset in not an entity
entities are instances of prefabs

there are two worlds:
    offline:
        outside any scene
        utils 
        assets
        static files
    online:
        in a scene
        visual and audioal instances of static assets

an entity is anything that is part of a scene
an static asset is anything that can be instantiated as entity

it is not like the scene cant access disk

why would i load a whole entity

what are the different assets that can be loaded into a 3d scene?
    3D models:
        meshes
        textures 
        shaders
    audio files

Entity component system:
    the scene is composed of entities
    each entity has an id managed by the scene
    you can retrieve the entity by its id
    you can add components to an entity
    and these components add functionality to an entity (extend its interface: entity.component.functionality())

would i ever need to manipulate an entity offline (maybe add a functionality that mimics that: component.disable)
maybe each asset corresponds to a component and each component correponds to a functionality

asset -> component -> functionlity
prefab -> entity

there is no concept of a "model", it is just meshes textures materials and shaders
each corresponds to a seperate asset
and each is added seperately to an entity

component = entity.addComponent<ComponentType>()

how do i store the components in the entity (linearly?)
an entity is generic, it does not know its component
you can ask it for a component of a type

entity.getComponent<ComponentType>()

you prepare components
they dont care about the entities they are inserted in 

you add a copy of a component to an entity
now that entity has that functionality and you can use it *through the entity*

some components should exist twice, some may

entities CANT be manipulated outside of a scene
they can be extracted to prefabs through

Component formal = AssetManager.loadComponent<>();

Entity entity = scene.newEntity();
entity.addComponent<>(formal);

Component effective = entity.getComponent<>();
effective.mutate();

scene.render:
    if entity.hasComponent<Render | Mesh>():
        Component rendereble = entity.getComponent<Renderable>();
        renderable.render();

there are 3 major components of the system:
    the asset manager:
        transforms static physical assets to entity components
    the components:
        each one represents a functionality
        if an entity has a component of a type => the entity *implements* that functionality
    the input system:
        the input system is a seperate thing 
        independent of anything
        it wraps arround glfw callbacks
        it is not that complex: keyboard keys and mouse clicks
        the user then can hook to those callbacks to implement interactivity however they want
        this component can also be used by other core components to implement default behavior (Camera, anything else?)
    the core:
        window management 
        scene management => entity management
        it receives components prepared by an outside system
        adds them to entities and uses the functionality

i always need glfw to be initialized (assert?)

not everything is a component:  
    a component is a high level characteristic of an entity
    you dont add an audio asset to an entity
    you dont add a shader to an entity
    you dont add a texture to an entity

    => an entity can and is encouraged to have complex components rather than many components

what are the different components an entity can have?
    Transform: world space position
    Mesh: mesh data (vertex attributes) (geometry)
    Renderer: mesh rendering data (textures maps and materials) (applied to geometry)
    Collider: collition detection / mesh boundry


entities are ID encapsulates in a scene (map<entity.id, vector<component>>)
entity.has/add/remove-component
components are structs that hold relevant state
systems are static class that mutate components

the user creates a scene
the user creates a component

using the scene, the user creates an entity
the user adds the component the entity

when the user wants to change something about the entity
he calls a system method on that component

how do i contruct components?
    how do i contruct a mesh or a renderer

    some components, you just instantiate
    other components are tied to resources, maybe use RAII (multiple contructors)

Systems:
    you dont use the systems
    you set the state in the components, that state fully describes the behavior you want
    then the systems iterate over all the entity and get applied on them, they are like workers

CreateEntity
set
set
set
Render

InputSystem inputSystem;
inputSystem.on("W", () => {
    scene.getcomponent();
    alter
});

implement a mesh and a mesh renderer component
add dimentional parameters to primitive meshes

in the wilde you dont incounter single meshes, but rather full models aka prefabs
i dont know what information the meshrenderer holds
    the mesh contains vertex information 
    the meshrenderer contains rendering information
    does a mesh renderer have a mesh or a mesh has a meshrenderer

entity = gameobject
the parent child relationships exist between entities/gameobjects

entity <-> mesh <-> meshrenderer

i need to implement the concept of prefabs
they are a snapshot of an entity
they are loaded using the assetloader
they can be instantiated to a scene

input system

why am i opting to return references to things
    dont return references to local variables

if the program should fail, just let it fail
when should the program fail:
    illegal access (valid access required)
add assert statements instead
remove entity and remove component

prefabs x textures and materials

prefabs are entities 
they are generated by loader and instantiated into scenes

prefabs can consist of multiple entities -> parent child relationships
strict hierarchy
you once add parent entities to a scene
and child the others

0. remove entity
0. remove component (what if i have a reference to them)
1. implement a parent child relationship (alter other code sections)
    demonstrate this by implementing a planetery system
2. load prefabs as parent entities

why dont i straight up instanciate entities?
and i wouldn't need prefabs at all

<!-- scene.instantiate(entity) -->
entity.hierarchyComponent.addchild/setParent
renderingSystem.render(scene)

1. move id management to Entity class (should make you able to work with entities outside the scene) (id should be customizable) done
3. add a hierarchy component (rendering depends on the hierarchy)
2. move rendering logic to RenderingSystem class (rendering a scene is a per Entity thing) 
    this is honestly unecessary, it works already

even the scene has a hierarchy
and you just render hierarchies to a camera

the hierarchy component just contains a collection of entities
you can register a child, but you need to give it a unique id in its hierarchy level to access it later
you construct an entity and you register copies of it as children with different ids
then you add the root entities to the scene

each entity might have a hierarchy component
the scene also has a hierarchy

remove use of unique ptr when unnecessary
    you only need pointers when polymorphism
        i need unique pointers when working with components
        i dont think i need them with entities, or scene camera, or shader
    use stack based objects

scene   
    camera 
    hierarchy 
        unordered_map of entities
            entity (copy constructor)
                pointers to components (polymorphism)
                    MeshRenderer
                        shader
                    Hierarchy
                        entities

a material encapsulates a shader, uniforms and textures

i need a mesh factory

improve error handling (bubble up)
fixed systems usage (its currently akward)

input cant happen in multiple windows 
the lowest level of input is a window you cant go beyond that

there are 2 types of events 
    keyboard
    mouse

use textures and skyboxes

inputsystem.mouse.rightbutton.is_pressed
inputsystem.keyboard.key_a.pressed
                          .released

a physcis engine defines the position of entities as a function of time
entities has physics properties
entities can interact and have relationships (joints and constraints)

// TODO: 
    testing correctness
        normals
        debug textures
    add a timer utility

simple and scalable
integrating imgui, sdl, trying to implement cool graphics stuff
polish physics
get 5 ideas to present