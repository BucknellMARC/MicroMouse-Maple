#ifndef ROBOT_CPP
#define ROBOT_CPP

#include <stdlib.h>
#include <stdio.h>

#include "define.h"
#include "Robot.h"
#include "MazeAlgorithm.h"

// default initializer
Robot* robot_create(int xPos, int yPos, MazeMap *mm)
{
	Robot* robot = (Robot*)calloc(1, sizeof(Robot));

	// assign the initial position to the robot
	robot->xPos = xPos;
	robot->yPos = yPos;

	robot->direction = EAST;

	// zero out the maze array
	MazeArrayPtr php = robot->posHistory;
	for (int row = 0; row < MAZE_HEIGHT; row++) {
		for (int col = 0; col < MAZE_WIDTH; col++) {
			php[row][col] = 0;
		}
	}

	robot->mazeMap = mm;

	return robot;
}

void robot_run(Robot* robot) {
	Rotation rotation = malgo_explore_suggest(
		robot->xPos, robot->yPos, robot->direction, robot->mazeMap, robot->posHistory
		);

	robot_turn_r(robot, rotation);
	printf("%i\n", rotation);

	// only drive forward if there is no wall
	BOOL wallForward = mazemap_does_wall_exist(robot->mazeMap, robot->xPos, robot->yPos, robot->direction);
	if (!wallForward) {
		robot_drive_forward(robot);
	}
}

void robot_run_flood_fill(Robot* robot) {
	printf("--Robot::runFloodFill()--\n");

	Rotation dToGo = malgo_floodfill_suggest(robot->xPos, robot->yPos, robot->mazeMap, robot->ffMap);

	printf("direction to go: %d\n", (int)dToGo);

	// turn that direction
	robot_turn_d(robot, dToGo);
	
	// and drive forward
	robot_drive_forward(robot);
}

BOOL robot_look(Robot* robot, Rotation rotation) {
	// get the direction
	Direction direction = mazemap_rotation_to_direction(robot->direction, rotation);

	return !mazemap_does_wall_exist(robot->mazeMap, robot->xPos, robot->yPos, direction);
}

void robot_turn_d(Robot* robot, Direction direction) {
	robot->direction = direction;
}

void robot_turn_r(Robot* robot, Rotation rotation) {
	// set the new direction
	//printf("Original direction: %d\n", (int)robot->direction);

	robot->direction = mazemap_rotation_to_direction(robot->direction, rotation);

	//printf("New Direction: %d\n\n", (int)robot->direction);
}

BOOL robot_drive_forward(Robot* robot) {
	Direction direction = robot->direction;

	printf("X: %d\tY:%d\n", robot->xPos, robot->yPos);
	printf("Forwards: %d\nLeft: %d\nRight: %d\n", robot_look(robot, FORWARDS), robot_look(robot, LEFT), robot_look(robot, RIGHT));

	switch (direction) {
	case NORTH:
		robot->yPos++;
		break;

	case EAST:
		robot->xPos++;
		break;

	case SOUTH:
		robot->yPos--;
		break;

	case WEST:
		robot->xPos--;
		break;

	default:
		printf("Error: Robot is in an unexpected state!\n");
	}

	// increment the history counter for that position
	//robot->posHistory[robot->yPos][robot->xPos]++;

	return TRUE;
}

void robot_destroy(Robot* robot) {
	free(robot);
}

#endif

