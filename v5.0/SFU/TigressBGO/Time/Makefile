all:
	echo Making Tigress_BGO_TDiff.
	(cd TDiff r && make -is clean && make && make -is clean && cd ..)
	echo DONE: TIGRESS_BGO_TDIFF.

clean:
	(cd TDiff             && make -is clean && cd ..)
	rm -f *~
