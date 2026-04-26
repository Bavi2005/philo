This is my Philo, 

first of all, what is philo?:
Overview: It's a project by 42 schools for us to learn about thread mutexes and also processors.

ok, now the concept of it;

---------------------------------------------------------------------------------------
ere are the key things you need to know to succeed in this assignment:
• One or more philosophers sit at a round table.
There is a large bowl of spaghetti in the middle of the table.
• The philosophers take turns eating, thinking, and sleeping.
While they are eating, they are not thinking nor sleeping;
while thinking, they are not eating nor sleeping;
and, of course, while sleeping, they are not eating nor thinking.
• There are also forks on the table. There are as many forks as philosophers.
• Since eating spaghetti with just one fork is impractical, a philosopher must pick up
both the fork to their right and the fork to their left before eating.
• When a philosopher has finished eating, they put their forks back on the table and
start sleeping. Once awake, they start thinking again. The simulation stops when
a philosopher dies of starvation.
• Every philosopher needs to eat and should never starve.
• Philosophers do not communicate with each other.
• Philosophers do not know if another philosopher is about to die.
• Needless to say, philosophers should avoid dying!
---------------------------------------------------------------------------------------

This is what the subject gave us, but simply saying
1. There is x number of philo andthe  same x number of forks
2. To eat philo must pick up 2 forks or else no eat!!
3. Then, while the philo eats, the other philo must either sleep or think, but if the philo does not get food for so long or exceeds the time we gave, he dies.
4. What we gotta do is to make sure they don't die and utilize our threads to let the philo live until we kill them eventually after they finish eating the required amount.

   Think of it as a hitman game, ur the hitman but the boss gave u a task the same one like i explained u gotta make sure they all eat before they die and they give you the task to make sure theey eat properly as your boss told you how much and how fast each of them must eat la so ur the hitman now u decide how ur gonna do.....
   But it's just a way to grasp the idea la

   Now coming back to the project.


Let's make some fun with the subject.pdf

-------------------------------------------------------------------------------
• Your program(s) must take the following arguments:
number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]
◦ number_of_philosophers: The number of philosophers, and also the number
of forks.
◦ time_to_die (in milliseconds): If a philosopher has not started eating within
time_to_die milliseconds since the start of their last meal or the start of the
simulation, they die.
◦ time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
◦ time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
◦ number_of_times_each_philosopher_must_eat (optional argument): If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.
--------------------------------------------------------------------------------

Now what they are saying is that the way to use it, actually, I'm gonna put this on the top, but still let me explain to u here too
./philo <num of philo> <time to die> <time to eat> <time to sleep> <num of time to do so>

How this works
You just read above la it's so obvious, dh next part

________________________________________________________________________________
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
Replace timestamp_in_ms with the current timestamp in milliseconds
and X with the philosopher number
---------------------------------------------------------------------------------

The output should be like this. 

__________________________________________________________________________________
1303 6 is eating
1310 8 is thinking
1310 8 has taken a fork
1310 9 is sleeping
1310 10 is thinking
1310 10 has taken a fork
1310 10 has taken a fork
1310 10 is eating
1310 8 has taken a fork
1310 8 is eating
1403 4 is sleeping
1403 2 is sleeping
1403 6 is sleeping
1410 10 is sleeping
1410 8 is sleeping
1410 All philo have eaten enough
___________________________________________________________________________________

Macam tu.......

So how ur gonna do it will be down here, but we gotta know how to do it too.

Things we gotta learn before doing which was given in the subject itself


1. memset
2. usleep
3. gettimeofday
4. pthread_create
5. pthread_detach
6. pthread_join
7. pthread_mutex_init
8. pthread_mutex_destroy
9. pthread_mutex_lock
10. pthread_mutex_unlock

Learn them and I'll update my readme day by day after this guys, so this is my overview for today. In the upcoming days, I'll try to understand it all and update here and to my git repo on 42 intra profile too, so wish me luckkk
