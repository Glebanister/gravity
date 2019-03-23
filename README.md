=======================
*_PROD_BY_GLEBANISTER_*
=======================

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

	-"bash run.sh" or "./main" 

To explore:

	-Press 'P' to start
	-Press 'P' to pause
	-Press 'D' to disable interactoin
	-Left mouse button to positive weight
	-Riht mouse button to negative weight
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
	RED = 255; - red component
	GREEN = 255; - green component
	BLUE = 255; - blue compunent
	INC_DELTA = 2; - mass increasing speed
	PIXELS_IN_UNIT = 100; - useless
	MIN_MASS = 1; - minimall weight
	MAX_MASS = 300; - maximal wieght
	GR_CONST = 20.0; - gravitational constant
	COLLISION_CONTROL = 1000.0; - try it, dunno how to explain
	SPEED_COEFFICENT = 1; - start speed coeficent
	STAY_INSIDE = false; - balls staying inside
	BOUNCES_OFF_THE_WALLS = true balls bouncing off the walls
	PAUSE_INTERACTION = true; start state of interaction
    PAUSE_GAME = true; start state of game (paused/unpaused)
