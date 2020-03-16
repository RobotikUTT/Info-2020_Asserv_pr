#include "goalList.h"

#include "control.h"

GoalList goalList;

extern Control control;

void GoalList::resetGoals() {
    currentGoalIndex = 0;
    lastGoalIndex = 0;
    goals[currentGoalIndex] = Goal();
}

void GoalList::processCurrentGoal() {
    if (goals[currentGoalIndex].isReached() && currentGoalIndex != lastGoalIndex) {
        currentGoalIndex = (currentGoalIndex + 1) % MAX_SIMULTANEOUS_GOALS;
        control.resetPIDs();
    }
    goals[currentGoalIndex].process();
}

void GoalList::addGoal(Goal goal) {
    lastGoalIndex = (lastGoalIndex + 1) % MAX_SIMULTANEOUS_GOALS;
    goals[lastGoalIndex] = goal;
}