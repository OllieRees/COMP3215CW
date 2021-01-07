#include "EDF.h"

/* DESCR: Assigns priority to a task based on EDF: priority is based on how close the task's deadline is
 * PARAM: the task which is having its priority assigned
 * PARAM: time is the current time that the function is called
 * RETURN: the priority of the task
 */
uint8_t assignPriority_EDF(Task * task, int time) {
    return time - (time % task -> period);
}
