Manual for “BBCKUP27” Version v1.1-1c (release candidate c1)
-----

-----
AUTHOR:
-----
	Vera Lo


-----
AUTHOR E-MAIL:
-----
	chatblanche767 <AT> gmail <DOT> com


-----
AUTHOR GITHUB:
-----
	https://github.com/decodewitness


-----
Introduction:
-----

BBCKUP27 is a tiny lightweight backup program for operating systems running on a Linux Kernel.
The idea is to have a simple lightweight mechanism to easily backup and archive files, from SOURCE (directory) to the DESTINATION (directory).
You can initiate a trial run first with the -t option, this way you can see what the program does before actually backing up. Using -t the program will go through all the checks, and shows you what it will do, without backing up.

BBCKUP27 comes supplied in a Debian archive you can download at the website.

On the website you can download the program, as well as the manual.



-----
Running the program:
-----

$ bbckup27 <OPTIONS> <SOURCE> <DESTINATION>

-----
Example:
-----

$ ./bbckup27 -t /home/username/Documents /home/username/Downloads

*** This command will backup the Documents directory to the user’s Downloads directory.


-----
Accessing help function:
-----

$ ./bbckup27 -h

or

$ ./bbckup27 -?

-----
Help output:
-----
 
//
//  *** bbckup27 v.0.1-1 (beta) ***
//    -----
// 
// - ARGUMENTS: 2
// 
// -----
// 
// 	Usage:
// 
// 	bbckup27 -[option 1] -[option 2] <SOURCE> <DESTINATION>
// 
// (Specify <SOURCE> first)
// 
// 	Switches:
// 
// 	-v = VERBOSE
// 	-l = ENABLE LOGGING
// 	-t = SIMULATE TEST RUN (NOT ACTUALLY BACK UP)
// 	-d = DEBUG MODE
//	-r = READ LICENSE
// 
// -----
// Copyright (C)(2020) bbckup27
//






END.
// eof