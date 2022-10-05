all:
	echo making ECalABSupp.
	(cd ECalABSupp r && make -is clean && make && make -is clean && cd ..)
	echo DONE: ECALABSUPP

	echo making ECalABSuppSum.
	(cd ECalABSuppSum r && make -is clean && make && make -is clean && cd ..)
	echo DONE: ECALABSUPPSUM


clean:
	(cd ECalABSupp          && make -is clean && cd ..)
	(cd ECalABSuppSum       && make -is clean && cd ..)

	rm -f *~
