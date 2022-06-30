all:
	echo Making time_produce_table.
	(cd produce_table && make -is clean && make  && make -is clean && cd ..) 
	echo DONE: TIME_PRODUCE_TABLE.
	echo Making time_diff.
	(cd diff && make -is clean && make  && make -is clean && cd ..)
	echo DONE: TIME_DIFF.

clean:
	(cd produce_table                   && make -is clean && cd ..)
	(cd diff                            && make -is clean && cd ..)
	rm -rf *~
