#include"schedulingAlgs.h"


//remove blanks in readyQ
void removeBlanks(struct process q[], int count)
{
	for(int i = 0; i < count; i++)
	{
		if (q[i].arrvltime == 0 && q[i].brsttime == 0)			
		{				
			q[count] = q[i];
			q[i] = q[i + 1];
			resetProcess(readyQ, (i + 1));
		}
	}
}

//printing function
void print(char *alg, int count)
{
	//holding totals
	int totwait = 0, totrspns = 0, totTA = 0;
	//holding averages
	double avewait, averspns, aveTA;
	//loop through everything 
	for(int i = 0; i < count; i++)
	{
		totwait += readyQ[i].waittime;
		totrspns += readyQ[i].rspnstime;
		totTA += readyQ[i].TAtime;
	}
	//calculating the averages
	avewait = totwait/(double)count;
	averspns = totrspns/(double)count;
	aveTA = totTA/(double)count;
	//print it out
	
	printf("%s\nAvg.Resp.: %.2f, Avg.T.A.: %.2f, Avg. Wait: %.2f\n", alg, averspns, aveTA, avewait); 
}//end print

//reset the readyQ
void reset(struct process *q, int count)
{
	for(int i = 0; i < count; i++)
	{
		q[i].done = false;
		q[i].rspnstime = -1;
		q[i].waittime = 0;
		q[i].TAtime = 0;
		q[i].arrvltime = 0;
		q[i].brsttime = 0;
		q[i].rmngtime = 0;
		q[i].interupt = 0;
	}
}//end reset()

//reset a particular process
void resetProcess(struct process *q, int index)
{
	q[index].arrvltime = 0;
	q[index].brsttime = 0;
	q[index].rmngtime = 0;
	q[index].rspnstime = -1;
	q[index].waittime = 0;
	q[index].interupt = 0;
	q[index].TAtime = 0;
	q[index].runstart = 0;
	q[index].runend = 0;
	q[index].timedone = 0;
	q[index].running = false;
	q[index].done = false;
	q[index].interupt = false;	
	q[index].active = false; 
}


//First come first serve
void FCFS(int *arrvl, int *brst, int count)
{
	//reset to make sure readyQ ready to use
	reset(readyQ, count);
	//variable for job being done
//	int currentjob = 0;
	//a clock variable
	int clock = 0;
	//first we need to take the incoming data and add 
	//each process to the readyQ
	//for FCFS this really isn't super necessary 
	//but it keeps us from messing with the original data
	for(int i = 0; i < count; i++)
	{
		readyQ[i].arrvltime = arrvl[i];
		readyQ[i].brsttime = brst[i];
	}
	//loop through all the processes
	for(int i = 0; i < count; i++)
	{
		if(clock < readyQ[i].arrvltime)
		{
			clock = readyQ[i].arrvltime;
		}
		//now calulate and add the stats in the q
		readyQ[i].waittime = clock - readyQ[i].arrvltime;
		//in FCFS response time is the same as arrival time
		readyQ[i].rspnstime = clock - readyQ[i].arrvltime;
		//add the time it took for the process to finish
		clock += readyQ[i].brsttime;

		//calc the turnaround time
		readyQ[i].TAtime = clock - readyQ[i].arrvltime;
		//identify that this process is done
		readyQ[i].done = true;
	}
	//print out the stats
	print("First Come, First Served", count);
	//then clear out the readyQ to be used again
	reset(readyQ, count);
}//end FCFS






//shortJ
void SJF2(int *arrvl, int *brst, int count)
{
	reset(readyQ, count);
	int numdone = 0, index = -1, clock = 0;
	//putting everything in readyQ
	//but we will treat things only if the clock is correct
	//then we can scan the readyQ for processes based on
	//the job size
	for(int i = 0; i < count; i++)
	{
		readyQ[i].arrvltime = arrvl[i];
		readyQ[i].brsttime = brst[i]; 
	}
	//while there are still processes to run
	//keep looping
	while(numdone < count)
	{
		//if a process has arrived after this point in time
		//update the clock
		if(readyQ[numdone].arrvltime > clock)
		{
			clock = readyQ[numdone].arrvltime;

		}
		//loop through the Q looking for processes
		//that have come in during the running of the last process
		for(int i = 0; readyQ[i].arrvltime <= clock && i < count; i++)
		{
			//if we don't already know which is the smallest
			if(index == -1)
			{
				//and the process has not been run already
				//then we should assign it as the next to be run
				//but it has to have arrived within the time we are at currently
				if(!readyQ[i].done)
				{
					index = i;
				}
			}
			//if we already have assigned one as the smallest but haven't looked 
			//at everything here then compare the burst times and record the index 
			//of this process because it is smaller than the last one assigned
			else if(!readyQ[i].done && readyQ[i].brsttime < readyQ[index].brsttime)
			{
				index = i;
			}
		}
		//at this point we have found the smallest process
		//which has arrived within the time we are currently 
		//it is the smallest job so run it completely
		//because were are non-preemptive
		//update the clock and all the process attributes
		readyQ[index].done = true;
		readyQ[index].waittime = clock - readyQ[index].arrvltime;
		readyQ[index].rspnstime = clock - readyQ[index].arrvltime;
		clock += readyQ[index].brsttime;
		readyQ[index].TAtime = clock - readyQ[index].arrvltime;

		//we have now completed one process so
		//update how many have been done
		//and return the index for the smallest back to 
		//basically a null value
		numdone++;
		index = -1;
	}//end while loop

	//test printing loop
//	for (int i = 0; i < count; i++)
//	{
//		printf("arrvl; %d, brst: %d\n", readyQ[i].arrvltime, readyQ[i].brsttime);
//	}
	print("Shortest Job First", count);
	//reset readyQ
	reset(readyQ, count);
}//end shortJ



//Shortest time remaining first
void SRTF(int *arrvl, int *brst, int count)
{
	//clear out readyQ
	reset(readyQ, count);
	
	int time = 0;
	int smallest = 0, numdone = 0;
	//just a variable to help me make sense of the way the time is working
	double end; 
	//i am adding everything to the readyQ but then treating it
	//like things aren't in there unless the time meets their arrival time
	for (int i = 0; i < count; i++)
	{
		readyQ[i].arrvltime = arrvl[i];
		readyQ[i].brsttime = brst[i];
		readyQ[i].rmngtime = brst[i];
	}
	//at this point rmngtime needs some nonimportant number
	//it's techically = full brsttime
	readyQ[99].rmngtime = 99999;

	//because in this algorithm we need to check for the next shortest
	//remaining process and new ones coming in we will loop based on time. 
	//each iteration is basically one unit of time. 
	//so this loops through all the processes until maxed out
	//i used a for loop because it's easier to increment the time
	//and also check for the numdone to count
	for(time = 0; numdone != count; time++)
	{
		//set the smallest to the last item in the list
		//used to search through everything to find the smallest one
		smallest = 99;
		//loop through all to find the smallest remaining time 
		for(int i = 0; i < count; i++)
		{
			if(readyQ[i].arrvltime <= time && readyQ[i].rmngtime < readyQ[smallest].rmngtime && readyQ[i].rmngtime > 0)
			{
				//index of the smallest remaining time process
				//at this point in time
				smallest = i; 
			}
		}
		//so if brsttime and response time are the same
		//meaning this process has not yet been run
		//we need to record it's first time being run - it's arrival time
		if(readyQ[smallest].brsttime == readyQ[smallest].rmngtime)
		{
			readyQ[smallest].rspnstime = time - readyQ[smallest].arrvltime;
		}
		//this is the process at readyq[smallest] getting run for 
		//one unit of time. 
		readyQ[smallest].rmngtime--;
		
		//if the process is completely done then record all the stats
		if(readyQ[smallest].rmngtime == 0)
		{
			numdone++;
			end = time + 1;
			readyQ[smallest].timedone = end;
			readyQ[smallest].waittime = end - readyQ[smallest].arrvltime - readyQ[smallest].brsttime; 
			readyQ[smallest].TAtime = end - readyQ[smallest].arrvltime;
		}

	}//end main for loop

	//print handles all the averging and formatting	
	print("Shortest Remaining Time First", count);
	//reset the readyQ for other algs
	reset(readyQ, count);
}//end STR




//Round Robin version 3
void RR3(int *arrvl, int *brst, int count)
{
	int numdone = 0, index = 0, inready = 0;
	int time = 0;
	bool interuptChecked = false;
	//make sure the readyQ is cleared out to use
	reset(readyQ, count);
	
	//main loop I decided to use a dowhile
	do
	{
		//if time is less than next arrival check for something in the readyQ to run
		if (time < arrvl[inready])
		{
			bool checkReady = false;
			for (int i = 0; i <= inready; i++)
			{
				if (readyQ[i].active == true)
				{
					checkReady = true;
					break;	
				}	
			}
			//if nothing is there then jump time forward
			if (checkReady == false)
			{
				time = arrvl[inready];	
			}	
		}
		//if this was already checked when a process stopped running
		//but has remaining time left we don't want to re-add something 
		if (interuptChecked == false)
		{
			while (arrvl[inready] <= time && inready < count)
			{
				readyQ[inready].arrvltime = arrvl[inready];
				readyQ[inready].brsttime = brst[inready];
				readyQ[inready].rmngtime = brst[inready];
				readyQ[inready].active = true;
				inready++;	
			}	
		}
		interuptChecked = false;

		//-----------------------------------------------------------then run this process-------------------------------------------------		
		readyQ[index].running = true;
		//record the time at which this process is starting to run
		readyQ[index].runstart = time;
		
		//if this process has never been run
		//then it's brsttime and rmngtime will
		//be the same
		//so at this point in time it's the first 
		//time it's been run
		if (readyQ[index].brsttime == readyQ[index].rmngtime)
		{
			//set it's response time
			readyQ[index].rspnstime = time - readyQ[index].arrvltime;
		}
	
		//we are running a particular process					
		//for one quantum (100) 
		//decrement it's rmngtime
		if (readyQ[index].rmngtime > QUANTUM)
		{		
			//decrement the rmngtime
			readyQ[index].rmngtime -= QUANTUM;
			//update when the process has stopped running
			readyQ[index].runend = readyQ[index].runstart + QUANTUM;
			//we have to update time to reflect this
			time += QUANTUM;
			//set tht this prpocess was interupted
			readyQ[index].interupt = true;
			//we have updated time so we are no 
			//longer running the process
			readyQ[index].running = false;
			if (time >= arrvl[inready])
			{
				interuptChecked = true;
				while (arrvl[inready] <= time && inready < count)
				{
					readyQ[inready].arrvltime = arrvl[inready];
					readyQ[inready].brsttime = brst[inready];
					readyQ[inready].rmngtime = brst[inready];
					readyQ[inready].active = true;
					inready++;	
				}	
			}
			//after updateing the readyQ we need to shuffle the readyQ	
			//if processes were added then the last one run will be placed 
			//at the end of the line then shifted down because index stays the same
			//if nothing was added then we will still shuffle but the process
			//will end up back in it's original spot to be run again
			readyQ[inready] = readyQ[index];
			resetProcess(readyQ, index);
			removeBlanks(readyQ, (inready + 1));			
		}//process has remaining time leftover

		else if (readyQ[index].rmngtime <= QUANTUM)
		{
			//update the clock
			time += readyQ[index].rmngtime;
			//record when the process is done running 
			//in this case this is also the completion time
			readyQ[index].runend = readyQ[index].runstart + readyQ[index].rmngtime;
			readyQ[index].timedone = readyQ[index].runend;
			//update Turnaround time
			readyQ[index].TAtime = readyQ[index].timedone - readyQ[index].arrvltime;
			//update waiting time for this process
			readyQ[index].waittime = readyQ[index].TAtime - readyQ[index].brsttime;
			//update the rmngtime which is now zero
			readyQ[index].rmngtime = 0;
			//it's no longer running 
			//and it's also done so set the done marker
			readyQ[index].running = false;
			readyQ[index].done = true;
			//if interupt was ever set return it to false
			readyQ[index].interupt = false;
			readyQ[index].active = false;
			numdone++;
			index++;
		}//process is completely done
		//-------------------------------------------------------end running process--------------------------------------------		
	} while (numdone < count);//end main for loop

	//Print all the data from the readyQ
	print("Round Robin with Time Quantum of 100", count);
	
	//reset the readyQ if we need it again
	reset(readyQ, count);
}//end RR 3
