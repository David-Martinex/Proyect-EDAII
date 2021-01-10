#!/bin/bash

 rm ./out/Compiler.out
 rm ./out/Excecutable.out

 echo Compiling program...

 find  ./src -type "d" >./fonts/H_Files.txt

 find ./src -name "*.c" >./fonts/C_Files.txt

 gcc -Wall -std=c99 -o ./out/Compiler.out ./compiler/Compiler.c

 ./out/Compiler.out

 gcc -Wall -std=c99 ./sqlite3/sqlite3.c -I ./sqlite3/ -c

 gcc -Wall -std=c99 @./fonts/H_Files.txt -I ./sqlite3/  @./fonts/C_Files.txt sqlite3.o -o ./out/Excecutable.out -lpthread -ldl

 echo Compile has been finished!
 echo





 



