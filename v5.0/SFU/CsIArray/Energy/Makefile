all:
	echo Making ECal.
	(cd ECal r && make -is clean && make && make -is clean && cd ..)
	echo DONE: CsIArray_ECal.

clean:
	(cd ECal              && make -is clean && cd ..)	
	rm -f *~
