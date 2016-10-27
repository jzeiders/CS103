CSCI 103 Programming Assignment 1, Hailstone, Spring 2015

Name: John Zeiders

Email Address: zeiders@usc.edu

NOTE: You can delete the questions, we only need your responses.

NOTE: It is helpful if you write at most 80 characters per line,
and avoid including special characters, so we can read your responses.

Please summarize the help you found useful for this assignment, which
may include office hours, discussion with peers, tutors, et cetera.
Saying "a CP on Tuesday" is ok if you don't remember their name.
If none, say "none".

:

================================ Questions ==================================

1. Which kind of a loop did you use for the first program? Why?
  I used a while loop as I did not the number of iterations
  it would take before I ran the code.
:

2a. Once you've completed the second program, run hailstats on the following
inputs, and record your results in the table below:

  input range  | minimum length | achieved by | maximum length | achieved by
-----------------------------------------------------------------------------
    50 100     |       6        |       64    |      11        |     97
   100 200     |       7        |       128   |      124       |     171
   200 400     |       8        |       256   |      143       |     327

2b. What pattern do you think there is in the values achieving minimum length?
Can you explain why it holds?
  The minimum length increases by 1, as the double of the minimum in the
  smaller range exists in the larger range.
:

3a. Let X be the smallest integer whose length is greater than 150.
By running your hailstats program several times on carefully chosen inputs,
determine what is the value of X.

X is : 2279

3b. Explain, briefly, the way in which you used your hailstats program
(i.e., which inputs you gave it) to find this answer.
  I created a separate program that brute forced the solution, incrementing x
  until the hailstone of x == 151.
:

================================ Remarks ====================================

Filling in anything here is OPTIONAL.

Approximately how long did you spend on this assignment?
  30 minutes
:

Were there any specific problems you encountered? This is especially useful to
know if you turned it in incomplete.
  Nope
:

Do you have any other remarks?

:
