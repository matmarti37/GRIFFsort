all:
	echo Making ECal.
	(cd ECal r && make -is clean && make && make -is clean && cd ..)
	echo DONE: CsIArray_ECal.

	echo Making ECalSum.
	(cd ECalSum r && make -is clean && make && make -is clean && cd ..)
	echo DONE: CsIArray_ECalSum.

	echo Making ERaw.
	(cd ERaw r && make -is clean && make && make -is clean && cd ..)
	echo DONE: CsIArray_ERaw.

	echo Making ERawSum.
	(cd ERawSum r && make -is clean && make && make -is clean && cd ..)
	echo DONE: CsIArray_ERawSum.

clean:
	(cd ECal              && make -is clean && cd ..)
	(cd ERaw              && make -is clean && cd ..)
	(cd ERawSum           && make -is clean && cd ..)
	(cd ECalSum           && make -is clean && cd ..)
	rm -f *~
