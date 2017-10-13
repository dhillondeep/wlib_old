/**!
 * @author Deep Dhillon
 * @date October 12, 2017
 * @file tasker.ino
 *
 * @section Description
 * wlib Scheduler demonstration. It allows for multiple tasks to execute in parallel.
 * Behind the screen it switches tasks to give each task same amount of time. This class
 * is under wlp namespace so it will only work if you are using wlp namespace
 *
 * @section Circuit
 * None
 */

#include <Wlib.h>
#include <core/tasks/Tasker.h>

using namespace wlp;

void setup2();
void loop2();
void loop3();

void setup(){
    Serial.begin(9600);

    // creates a task that will have setup run one time and loop run multiple times
    Tasker::start(setup2, loop2);
    // creates a task that will be run multiple times and stack size is provided (optional)
    Tasker::startLoop(loop3, 128);
}

void loop(){
    Serial.println("Original Loop");
    Tasker::yield();
}

void setup2(){
    Serial.println("I am starting setup 2");
}

void loop2(){
    Serial.println("Loop 2");
    Tasker::yield(); // yield for another tasks (delay will do the same job as well)
}

void loop3(){
    // get the size of stack if needed
    Serial.println("Loop 3 Stack Size: " + String(Tasker::stack()));
    Tasker::yield();
}
