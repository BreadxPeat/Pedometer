# Pedometer
Arduino UNO based Pedometer, with functioning data structures and algorithms

This is a high school project, based on arduino uno and data structures and algorithms. Here we have used - 
1. Accelerometer
2. Arduino UNO 

We have defined a threshold to verify if a step has been taken, in this case it has been set to 1.4.
To calculate the total distance travelled by the accelerometer we have used three-dimensional geometry i.e 
{(x2-x1)**2 + (y2-y1)**2 + (z2-z1)**2}**0.5
We then divide the total distance with threshold to get total no.of steps.


We then created a function - file() to print and save the no.of steps in an sd card.
