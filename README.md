*************************
**_PROD_BY_GLEBANISTER_**
*************************

To install:

	-Linux:
		-Run doall.sh
	-Windows:
		-Sorry, but no


To change settings:

	-Go to the include/Environment.h
	-Change anything you want
	-"bash build.sh" to apply changes


To change background:

	-Create image corresponding to the window resolution settings
	-Set up background path


To run:

	-"bahs run.sh" or "./main" 

To explore:

	-Short click to create light ball
	-Long click to create heavy ball
	-Very long click to very heavy ball


Settings:

	TOP_NAME[8] = "GRAVITY" - window name
	BACKGROUND_PATH[21] = "../textures/back.png" - background path
	SCREEN_WIDTH = 1024; - screen width
	SCREEN_HEIGHT = 768; - screen height
	GAME_DELAY = 15; - pause between frames
	RADIUS = 10; - object radius
	GREEN = 20; - green component
	INC_DELTA = 1; - mass increasing speed
	PIXELS_IN_UNIT = 100; - useless
	MIN_MASS = 1; - minimall weight
	MAX_MASS = 300; - maximal wieght
	GR_CONST = 20.0; - gravitational constant
	COLLISION_CONTROL = 1000.0; - try it, dunno how to explain
	STAY_INSIDE = false; - balls staying inside
	BOUNCES_OFF_THE_WALLS = true balls bouncing off the walls
