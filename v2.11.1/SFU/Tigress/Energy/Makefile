all:
	echo making Energy_NoAddBack Programs.
	(cd NoAddBack r && make -is clean && make && make -is clean && cd ..)
	echo DONE: NOADDBACK.


clean:
	(cd NoAddBack   && make -is clean && cd ..)

	rm -f *~
