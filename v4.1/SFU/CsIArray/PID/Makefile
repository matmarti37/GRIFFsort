all:
	echo Making PID.
	(cd PID r && make -is clean && make && make -is clean && cd ..)
	echo DONE: CsIArray_PID.

clean:
	(cd PID              && make -is clean && cd ..)	
	rm -f *~
