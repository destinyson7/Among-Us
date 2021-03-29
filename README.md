# Computer Graphics
## Assignment 0

### Running the Code

- Unzip the code and add the required libraries given in the CMakeLists.txt.

- Make a separate directory named libraries outside the source directory and put glad and glfw inside it. Put glm in the includes (usr/includes) folder.

- Run the following commands
  	```
	mkdir build
	cd build
	cmake ..
    make
    ./assignment-0
	```

- You will be given three options for the shape you want to see. Press any one of the three keys.
After that window opens, then you can press the other keys mentioned above to move the camera and object.

### Modelling

The three dodecahedrons I chose are:
1. Decagonal Prism
2. Undecagonal Pyramid
3. Hexagonal Dipyramid

I calculated the coordinates of the vertices using python and stored them in a text file from which I take input in the code.

### Animating

1. Six keys to move the camera along the three different axes. The camera always face the object.
    - W - Up
    - S - Down
    - A - Left
    - D - Right
    - E - Front
    - R - Backward

2. Six keys to move the object along the three different axes.
    - I - Up
    - K - Down
    - J - Left
    - L - Right
    - O - Front
    - P - Backward

3. Three different keys to move to three different pre-decided positions/orientations of the camera. After each ’teleportation’, camera should face the object.
    - F - Moves camera to (0, 0, 3)
    - G - Moves camera to (0, 0, -3)
    - H - Moves camera to (3, 0, 3)

4. Key to make the object spin about any one axis.
    - Z - Spins object about [1, 0, 0] local axis
    - X - Spins object about [0, 1, 0] local axis
    - C - Spins object about [0, 0, 1] local axis

5. Key to make the the camera spin about the object.
    - B - First recenters the object to origin, and then the camera rotates around the object.

6. esc - Exits the window.


**Note**: The bonus part is stored in the bonus folder. Follow the exact same steps for the bonus directory and you will get a texture on the Decagonal Prism :).

### Assignment by:
- Tanish Lad
- Roll Number: 2018114005
