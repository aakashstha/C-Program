# This task is based on Numerical Methods and Concurrency.
## Content 
1. Task-1: Linear Regression
2. Task-2: Calculating Pi using Leibniz formula and multithreading
3. Task-3: Finding prime numbers from multiple text files using multithreading
4. Task-4: Gaussian Blur with multithreading   

## To complete this task the knowledge of Mathematics, C-Programming and Concurrency is used.
<br>

1. This project consist of 4 task which is written in C-programming language.
2. To run this task you need to have gcc c compiler install in your machine.
3. If you are running on macOS then installing X-Code makes it lot easier and you will get pre install gcc compiler.
4. After installing gcc compiler and downloading this project. Navigate to this file using Terminal or Command Prompt. After that visit which task you want to run from down below.
5. In my case I had used Visual Studio Code (VS-Code in short) and its integrated Terminal to run all my tasks.
<hr>

## For running this project.
1. For Task-1
    * From the CLI type = gcc task1.c -o xyz1
    * ./xyz1
2. For Task-2
    * From the CLI type = gcc task2.c -o xyz2 -pthread
    * ./xyz2
3. For Task-3
    * From the CLI type = gcc task3.c -o xyz3 -pthread
    * ./xyz3 4
4. For Task-4
    * From the CLI type = gcc lodepng.c task4.c -o xyz4 -pthread
    * ./xyz4

<hr>

## Extra Information and some warning/!!

### <strong> gcc lodepng.c filename -o xyz -pthread </strong>
* gcc is a c compiler which converts c language to machine readable language.
* next in task-4 we have used lodepng.c which is a third-party library to import/export png image and as well to manipulate them.
* now filename which in our case is task1 and so on.
* next we have -o which is used to output object file in c.
* then we have xyz is the compiled file of the task. 
* -phread is used for multithreading in c.

#### In most of the case you will not encounter any error but if you run into some warning like the down below then do not worry because it is simple warning which is saying to change the entry level main function return type from void to int. Here I don't like to change because I always keep main function return type to void for simplicity.
<br>
<pre>
    task1.c:76:1: warning: return type of 'main' is not 'int' [-Wmain-return-type]
    void main()
    ^
    task1.c:76:1: note: change return type to 'int'
    void main()
    ^~~~
    int
    1 warning generated.
</pre>

#### If your are not like me and want to remove this warning then simply navigate to the main funciton and replace "void" with "int" and also set "return 0" at the end of the main function.

### Happy C coding/!! 🙃
