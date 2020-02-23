#include <Arduino.h>

#include "SimpleTimer.h"

#include "parameters.h"
#include "goalList.h"
#include "robotstate.h"
#include "collisions.h"
#include "goal.h"

SimpleTimer timer;

extern RobotState robotState;
extern Collisions collisions;
extern GoalList goalList;

void fillGoals() {
    // TODO add goal dynamically with ros or custom serial / CAN protocol
    // or fetch all goals from xml / json / whatever
    goalList.addGoal(Goto(1000, 0));
    goalList.addGoal(Rot(3.14));
    goalList.addGoal(Goto(0, 1000));
    goalList.addGoal(Goto(0, 0, 500));
    goalList.addGoal(Rot(0));
}

void asservLoop() {
    robotState.update();
    collisions.update();
    goalList.processCurrentGoal();
}

void setup() {
    fillGoals();
    timer.setInterval(TIMER_MS, asservLoop);
}

void loop() {
    timer.run();
}