1. 	Two characters are printed to the screen

2. 	The executing program stalled after printing the B, and does not complete. This is because the semaphore is initialized to a value of 2 and is then decremented twice, down to 0, by threads A and B.
	When thread C is created, the semaphore is decremented a third time. However, this causes the semaphore to become negative. Because the semaphore is not posted anywhere in the code, it will
	wait infinitely at this point and will not print "C" to the screen or hit the return statement.

Code Extraction:

	sem_post(&sem);
