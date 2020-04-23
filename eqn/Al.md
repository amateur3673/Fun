# Algorithm for solving a system of linear equations.
This is a problem i finished in second year, because this is a simple method for solving equation, it won't give you high accuracy for all cases. But most of the case i test, the result is acceptable.  
Before diving deep into the algorithm, let's me introduce the file structure. The file structure contains 3 files:
- ``eqn.c``: the source file: contains all hand-made function for solve the system of linear equations.
- ``eqn``: the executive file, is compiled from ``eqn.c``.
- ``input.txt``: the input file, you provide the input equation for the program here, each line of the input is an equation, the last number in each line is the result of the equation. For example, if you want the algorithm solves the equations:
$x_1+5x_2+4x_3+3x_4=7$  
$x_1-2x_2+6x_3-5x_4=8$  
$x_1+3x_3=-12$  
You should write in the input file like this:  
1 5 4 3 7  
1 -2 6 -5 8  
1 0 3 0 -12

When i wrote this code, i had just few knowledge about data structure, so the code is not optimized for speed. It's just OK with the result.  
## 1.Problem
This is the problem when i was studying linear algebra in university. When i worked on this project for the first time, i code for the equation in the case the number of variables equals to the number of equations. I realized that i could expand my method with echelon matrix.

An echelon matrix is such a matrix that the number of "first-zeros" in each line increases. Here, what i mean by "first-zeros" are the zero numbers in each line, there no other number between any first zero numbers. For example if your line is: 0 0 0 1 0 2, then the first three zeros are "first-zeros", the fifth zero is not "first-zero".

The thing needed to be done first is to form the echelon matrix. In the source code, ``countzero`` function is used to count the "first-zeros" in eachline, and ``sortmat`` function is used for sorting the "first-zero" in each line in order not to decrease.

Function ``cheo`` to form the echelon matrix. For each step, we sort the line in order not to decrease "first-zeros", and perform a substract from "currentline" with all lines below to get all below lines get higher "first-zeros". For example if your lines are:

0 1 1 1 5 currentline  
0 1 2 3 5  
0 2 1 4 5  

then after substract we get:

0 1 1 1 5  
0 0 -1 -2 0  
0 0 1 -2 5

You'll see after performing substraction, all the line below the "currentline" get higher "first-zero". The "cheo" algorithm is described as below:

Start from zero line.  
While not iterate the final line:
- Perform sorting "first-zeros".
- Perform substraction. 
- Go to next line.  

## 2. Rank and solving problem.

After we form a echelon matrix, we get rid of the lines with all zero. We found the rank of matrix by ``rank`` function. After removing the redundant lines, we got the matrix with the number of lines equals to the rank of matrix. 

After that, we check if the equation is solvable, if the last line after we remove lines has full zero before the last number and the last number in that line is non-zero, then the equation is non-solvable. For example, if your last line is:  

0 0 0 0 0 9 

then the equation cannot be solvable. We stop the algorithm here.

## 3. Solvable equation.

If your equation is solvable, your algorithm will run into this step. In this step, we define a new terminology: "free column".  
Since each variable is represented by a column, if your equation has multiple solution, then a variable can be interpreted as the linear sum of other variables. If you get the result like this after ``cheo``:

1 2 4 5 7 8 9 6  
0 0 1 3 4 6 8 10  
0 0 0 0 0 2 5 3

the equivalent equations of above expression:

$x_0+2x_1+4x_2+5x_3+7x_4+8x_5+9x_6=6$  
$x_2+3x_3+4x_4+6x_5+8x_6=10$  
$2x_5+5x_6=3$

We can express our solution like this: 

$x_5=3-5x_6$  
$x_2=10-8x_6-6x_5-4x_4-3x_3$, since $x_5=3-5x_6$, then $x_2$ can be expressed as a linear combination of $x_3,x_4,x_6$.

$x_0=6-9x_6-8x_5-7x_4-5x_3-4x_2-2x_1$, since $x_5$ can be expressed of $x_6$ and $x_2$ can be expressed by $x_3,x_4,x_6$, so $x_0$ can be expressed as $x_1,x_3,x_4,x_6$. 

We call $x_1,x_3,x_4,x_6$ are "free column". When we find the solution, we find the expression of "non-free column" of "free-column". As you can see in the example above, "free-column" lays at the position between the first non zero in a line and first non-zero in the next line. The number of "non-free column" equals to the rank of matrix.  

``find_index`` is responsible for finding the "free-column".  
**Express the solution:**    
If your solution is:  
$x_0=2x_2+3x_3-1$  
$x_1=3x_2-5x_3+2$  
$x_2=x_2$  
$x_3=x_3$  

then we can write:  
$(x_0,x_1,x_2,x_3)=x_2(2,3,1,0)+x_3(3,-5,0,1)+(-1,2,0,0)$ or  
$(x_0,x_1,x_2,x_3)=t_1(2,3,1,0)+t_2(3,-5,0,1)+(-1,2,0,0)$ with $(t_1,t_2)\in R$. My algorithm will return a matrix like this:

2 3 1 0  
3 -5 0 1  
-1 2 0 0 

Algorithms will return a matrix of shape (number of "free column"+1,number of variables). The term (-1,2,0,0) represents for the "free vector". It always lays on the last line of the result matrix. To archive the result matrix, we need to perform 2 steps:  
- Step 1: Calculate the "free vector".
- Step 2: Calculate the rest of the result matrix.

**Calculate the "free vector":**  

If our result is $(x_0,x_1,x_2,x_3)=x_2(2,3,1,0)+x_3(3,-5,0,1)+(-1,2,0,0)$. This is true for all the value of $x_2,x_3$. To obtain the "free vector", we set the value of all "free column" equals to zero.

**Calculate the rest of the result matrix:**  
If we want to calculate the coefficents of each "free column", we set the value of other "free column" equals to zero. Ignore the "free vector" we have already calculated, we move the column of corresponding coefficent to the right, and change the sign of that column.

We have ``simplify1`` function to freeze the "free column" for calculate the "free vector", and ``simplify2`` function for calculate the "free-column" coefficent. Notice when we apply ``simplify1`` and ``simplify2``, our equations have the number of variables equal to the number of equation, so can can solve it numerically.

To numerically solve the equation, we apply ``solve`` function. In this function, we apply the recursion method to solve the equations from bottom to up. We write the result corresponds to the position in the result matrix.  
________
**Summary:** 

That's all about the equation method i introduce in this repository. Simple, isn't it ?
