# OpenGL Museum Project

A project by Wes and Zach Harris while in 3D Graphics and Design class at New Mexico Tech.

## Assignments

### 2/2/2018: Setup Environment

Task 1: Set up the OpenGL environment using glad. Run script to draw a red triangle into a black window.

![alt text](https://github.com/pixarninja/opengl_museum/blob/master/setup_environment/screenshots/Solid.png)

Task 2: Uncomment line 123 to draw in wireframe polygons.

![alt text](https://github.com/pixarninja/opengl_museum/blob/master/setup_environment/screenshots/Wireframe2.png)

### Museum Plan

1. The theme for our museum will be "Rick And Morty".
2. The museum will have 5 rooms consisting of the family's house.
3. We would like to incorporate parts of the show into the museum building. Perhaps some of the floors and walls could represent Rick's garage, and others could represent the living room, etc. We could either get those textures from screenshotting the show itself, or by replicating them with PhotoShop.
4. We plan for the museum to have a ceiling, however for one or two rooms it might be appropriate to remove the ceiling or create one that is not a regular ceiling shape.
5. We would like to at least use a model of Rick's space ship as a sculpture. Other sculptures could include Rick's portal gun or other props from the show. We will model their spaceship in blender and use texture painting to make it realistic.
6. For our paintings we would like to use the pictures from Rick and Morty's house, such as Snuffles and family photos. We were also thinking of making "cardboard" cutouts of the Sanchez family and using those as "paintings" as well.

### 2/14/2018: First cut of museum

Task 1: Create the initial outline for the museum. Show how the rooms will be laid out.

![first_cut](https://github.com/pixarninja/opengl_museum/blob/master/Blender_Files/first_cut.png)

### 3/5/2018: Second cut of the museum

Task 1: Add models to existing museum.

![second_cut](https://github.com/pixarninja/opengl_museum/blob/master/Blender_Files/second_cut.png)

### 3/7/2018: Final Object Loader

Task 1: Create an object loader that imports an object into OpenGL. The object rotates on any of the X, Y, or Z axes, controlled by mouseclicks.

![object_loader](https://github.com/pixarninja/opengl_museum/blob/master/setup_environment/screenshots/ObjectLoader.png)

Task 2: Import a more complicated file. We chose to upload the obj file of our basic museum, and a model of a pikachu. We cycle through the files using the space bar.

![object_loader_museum](https://github.com/pixarninja/opengl_museum/blob/master/setup_environment/screenshots/ObjectLoaderMuseum.png)

![object_loader_pikachu](https://github.com/pixarninja/opengl_museum/blob/master/setup_environment/screenshots/ObjectLoaderPikachu.png)

### 3/28/2018: Integrate Class Structure

Task 1: Implement a driver using the classes provided to us. This is now complete, and a sample rendering of an object loaded in with the new driver is produced below.

![driver](https://github.com/pixarninja/opengl_museum/blob/master/setup_environment/screenshots/Driver.png)

### 4/4/2018: Integrate Textures

Task 1: Add textures to the objects imported into OpenGL. We haven't perfected this yet, however we've managed to at least get the textures imported. Our next task is to ensure that the texture coordinates are being read correctly so that when we map textures on our museum, the UV coordinates match with how they are read in.

![awkward_rock](https://github.com/pixarninja/opengl_museum/blob/master/setup_environment/screenshots/AwkwardRock.jpg)

### 5/4/2018

We have pushed our final code and created submission folders. The project (mysteriously) does not display textures correctly. We theorize that it has to do with how the objects are being exported. We will try to look at this later, however we can't correct it before the final project deadline.

### Running The Project

If you would like to run the project, load the setup_environment project folder into CLion and run it from the IDE. The camera is working and can be operated using the following keys:

- "a", move the camera left (in the -X direction)
- "d", move the camera right (in the +X direction)
- "s", move the camera down (in the -Y direction)
- "w", move the camera up (in the +Y direction)
- "m", move the camera backwards (in the -Z direction)
- "n", move the camera forward (in the +Z direction)
- "left arrow", rotate the camera left (about the Y axis counter-clockwise)
- "right arrow", rotate the camera right (about the Y axis clockwise)
- "down arrow", rotate the camera down (about the X axis counter-clockwise)
- "up arrow", rotate the camera up (about the X axis clockwise)
- ",", rotate the camera clockwise (about the Z axis)
- ".", rotate the camera counter-clockwise (about the Z axis)

Below are screenshots of the final blender model, completely texture mapped with baked lighting.

![final_1](https://github.com/pixarninja/opengl_museum/blob/master/setup_environment/screenshots/final_1.png)

![final_2](https://github.com/pixarninja/opengl_museum/blob/master/setup_environment/screenshots/final_2.png)

![final_3](https://github.com/pixarninja/opengl_museum/blob/master/setup_environment/screenshots/final_3.png)

![final_4](https://github.com/pixarninja/opengl_museum/blob/master/setup_environment/screenshots/final_4.png)

![final_5](https://github.com/pixarninja/opengl_museum/blob/master/setup_environment/screenshots/final_5.png)

![final_6](https://github.com/pixarninja/opengl_museum/blob/master/setup_environment/screenshots/final_6.png)

![final_7](https://github.com/pixarninja/opengl_museum/blob/master/setup_environment/screenshots/final_7.png)

### Future Work

We would like to correct the mistakes that still persist, possibly by creating lighting in opengl instead of relying on baked textures. We would also like to make it more of a "game" by adding limitations to where the user can move. These may or may not be completed in the future.
