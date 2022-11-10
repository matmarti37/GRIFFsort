all:
	echo making ECalABSupp.
	(cd ECalABSupp r && make -is clean && make && make -is clean && cd ..)
	echo DONE: ECALABSUPP

	echo making ECalABSuppSum.
	(cd ECalABSuppSum r && make -is clean && make && make -is clean && cd ..)
	echo DONE: ECALABSUPPSUM

	echo making ECalABSuppSumEGated.
	(cd ECalABSuppSumEGated r && make -is clean && make && make -is clean && cd ..)
	echo DONE: ECALABSUPPSUMEGATED


clean:
	(cd ECalABSupp            && make -is clean && cd ..)
	(cd ECalABSuppSum         && make -is clean && cd ..)
	(cd ECalABSuppSumEGated   && make -is clean && cd ..)

	rm -f *~
