all:
	echo Making time_check_ordering.
	(cd amplitude r && make -is clean && make  && make -is clean && cd ..) 
	echo DONE: TIME_CHECK_ORDERING.

clean:
	(cd amplitude					&& make -is clean && cd ..)
	rm -rf *~
