Problem 1.
	Single Thread: main = 2.808869 
	Multi Thread: main = 2.922184, thread1 = 2.922054, thread2 = 2.283989

Problem 2.
	No. This is because the threads are run concurrently, not consecutively. The main thread will run in
	(roughly) the same amount of time as the longest thread.

Problem 3.
	Single threaded has the faster execution time FOR THIS EXAMPLE. My guess at the reason for this is
	that the multithreaded version has heavier boilerplate. However, this is essentially a one time cost.
	Generally the multithreaded version should be faster for longer problems, as the disadvantages
	of a few extra lines of code will eventually be outpaced by the ability to divide the execution time
	amongst 2 or more threads.

Problem 4.
	Because it is not certain which thread will return first.
