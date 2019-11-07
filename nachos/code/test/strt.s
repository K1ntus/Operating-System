 







 














 

























 
































 




	.text   
	.org 0
	.long 0xffffffff
	.long 0xffffffff

 








	.org 0x80 

	.globl __start
	.ent	__start
__start:
	jal	main
	move	$4,$0


	move	$4,$2	


	jal	Exit	  
	.end __start

 




	.long 0xffffffff
	.long 0xffffffff

 












	.globl Halt
	.ent	Halt
Halt:
	addiu $2,$0,0 
	syscall
	j	$31
	.end Halt

	.globl Exit
	.ent	Exit
Exit:
	addiu $2,$0,1 
	syscall
	j	$31
	.end Exit

	.globl Exec
	.ent	Exec
Exec:
	addiu $2,$0,2 
	syscall
	j	$31
	.end Exec

	.globl Join
	.ent	Join
Join:
	addiu $2,$0,3 
	syscall
	j	$31
	.end Join

	.globl Create
	.ent	Create
Create:
	addiu $2,$0,4 
	syscall
	j	$31
	.end Create

	.globl Open
	.ent	Open
Open:
	addiu $2,$0,5 
	syscall
	j	$31
	.end Open

	.globl Read
	.ent	Read
Read:
	addiu $2,$0,6 
	syscall
	j	$31
	.end Read

	.globl Write
	.ent	Write
Write:
	addiu $2,$0,7 
	syscall
	j	$31
	.end Write

	.globl Close
	.ent	Close
Close:
	addiu $2,$0,8 
	syscall
	j	$31
	.end Close

	.globl Fork
	.ent	Fork
Fork:
	addiu $2,$0,9 
	syscall
	j	$31
	.end Fork

	.globl Yield
	.ent	Yield
Yield:
	addiu $2,$0,10 
	syscall
	j	$31
	.end Yield


	.global PutChar
	.ent	PutChar
PutChar:
	addiu $2,$0,11 
	syscall
	j	$31
	.end PutChar

	.global GetChar
	.ent	GetChar
GetChar:
	addiu $2,$0,12 
	syscall
	j	$31
	.end GetChar

	.global PutString
	.ent	PutString
PutString:
	addiu $2,$0,13 
	syscall
	j	$31
	.end PutString

	.global GetString
	.ent	GetString
GetString:
	addiu $2,$0,14 
	syscall
	j	$31
	.end	GetString


	.global PutInt
	.ent	PutInt
PutInt:
	addiu $2,$0,15 
	syscall
	j	$31
	.end PutInt

	.global GetInt
	.ent	GetInt
GetInt:
	addiu $2,$0,16 
	syscall
	j	$31




	.end GetInt
	.global ThreadCreate
	.ent	ThreadCreate
ThreadCreate:
	addiu $2,$0,30 
	syscall
	li $6, ThreadExit
	j	$31
	.end ThreadCreate

	.global ThreadExit
	.ent	ThreadExit
ThreadExit:
	addiu $2,$0,31 
	syscall
	j	$31
	.end ThreadExit



 
        .globl  __main
        .ent    __main
__main:
        j       $31
        .end    __main

