/**
 * \file goalList.h
 * \brief Class which holds a fifo of goals. @see goal.h
 * \author Paul Constant <constantpaul@hotmail.fr>
 * \date 2020/02/23
**/

#ifndef GOALLIST_H
#define GOALLIST_H

#include <stdint.h>

#include "goal.h"
#include "control.h"

class GoalList {
public:
    GoalList() { 
        resetGoals(); 
    }
    
    /**
     * \brief Processes the current goal. If it is reached, processes the next one.
    **/
    void processCurrentGoal();
    void addGoal(Goal goal);
    void resetGoals();

private:
    Goal goals[MAX_SIMULTANEOUS_GOALS];

    int16_t currentGoalIndex = 0;
    int16_t lastGoalIndex = 0;
};
#endif // GOALLIST_H