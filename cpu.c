#include <stdio.h>
#include <stdlib.h>
#include "oslabs.h"


int checkNull(struct PCB process);
struct PCB createPCB(int pid, int arrivalTime, int totalBurst, int execStart, int execEnd, int remainBurst, int pri);


int main() {
	struct PCB p1 = createPCB(1,1,4,1,5,4,8);
	struct PCB p2 = createPCB(2,2,3,0,0,3,6);
	struct PCB p3 = createPCB(0,0,0,0,0,0,0);

	//Case 1
	struct PCB readyQueue[10];
	int *ptr = 0;

	struct PCB runningPCB = handle_process_arrival_pp(readyQueue, ptr, p2, p1, 5);
	

    return 0;
}

int checkNull(struct PCB process)
{
	if (process.process_id == 0 && 
		process.arrival_timestamp == 0 && 
		process.total_bursttime == 0 &&
		process.execution_starttime == 0 && 
		process.execution_endtime == 0 && 
		process.remaining_bursttime == 0 &&
		process.process_priority == 0) {

		return 1;
	}
	else {
		return 0;
	}
}

struct PCB createPCB(int pid, int arrivalTime, int totalBurst, int execStart, int execEnd, int remainBurst, int pri)
{
	struct PCB newPCB;
	newPCB.process_id = pid;
	newPCB.arrival_timestamp = arrivalTime;
	newPCB.total_bursttime = totalBurst;
	newPCB.execution_starttime = execStart;
	newPCB.execution_endtime = execEnd;
	newPCB.remaining_bursttime = remainBurst;
	newPCB.process_priority = pri;

	return newPCB;
}

struct PCB handle_process_arrival_pp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp)
{
	struct PCB newPCB = new_process;
	struct PCB oldPCB = current_process;
    int count = queue_cnt;

	/* If no process is running, run this! 
	   Modify PCB of new process:
	   		1. Execution start time = current timestamp
	   		2. Execution end time = timestamp + total burst time
	   		3. Remaining burst time set to total burst time
	*/

	if (checkNull(current_process) == 1){
		newPCB.execution_starttime = timestamp;
		newPCB.execution_endtime = timestamp + new_process.total_bursttime;
		newPCB.remaining_bursttime = new_process.total_bursttime;
		return newPCB;
	}

    if (new_process.process_priority >= current_process.process_priority) {
        newPCB.execution_starttime = 0;
        newPCB.execution_endtime = 0;
        ready_queue[count] = newPCB;
        return oldPCB;
    }

    else if (new_process.process_priority < current_process.process_priority) {
        newPCB.execution_starttime = timestamp;
        newPCB.execution_endtime = timestamp + new_process.total_bursttime;
        newPCB.remaining_bursttime = new_process.total_bursttime;

        oldPCB.execution_endtime = 0;
        oldPCB.remaining_bursttime = oldPCB.total_bursttime - (timestamp - oldPCB.execution_starttime);
        ready_queue[count] = oldPCB;

        return newPCB;
    }
}