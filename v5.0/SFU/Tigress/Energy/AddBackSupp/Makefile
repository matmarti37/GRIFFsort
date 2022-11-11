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

	echo making ECalABSuppSumCrystal.
	(cd ECalABSuppSumCrystal r && make -is clean && make && make -is clean && cd ..)
	echo DONE: ECALABSUPPSUMCRYSTAL


clean:
	(cd ECalABSupp            && make -is clean && cd ..)
	(cd ECalABSuppSum         && make -is clean && cd ..)
	(cd ECalABSuppSumEGated   && make -is clean && cd ..)
	(cd ECalABSuppSumCrystal  && make -is clean && cd ..)

	rm -f *~
