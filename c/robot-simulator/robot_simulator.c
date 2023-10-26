#include "robot_simulator.h"

robot_status_t robot_create(robot_direction_t direction, int x, int y)
{
    return (robot_status_t) {direction, (robot_position_t){x, y}};
}


void robot_move(robot_status_t *robot, const char *commands)
{
    if (!robot || !commands)
        return;

    for (int i = 0; commands[i] != 0; i++){
        switch (commands[i]){
            case 'L':
                robot->direction = (DIRECTION_MAX + robot->direction - 1) % DIRECTION_MAX;
                break;
            case 'R':
                robot->direction = (robot->direction + 1) % DIRECTION_MAX;
                break;
            case 'A':
                switch (robot->direction){
                    case DIRECTION_NORTH:
                        robot->position.y++;
                        break;
                    case DIRECTION_EAST:
                        robot->position.x++;
                        break;
                    case DIRECTION_SOUTH:
                        robot->position.y--;
                        break;
                    case DIRECTION_WEST:
                        robot->position.x--;
                        break;
                    default:
                        continue;
                }
                break;
            default:
                continue;
        }
    }
}