all:
	echo Making TDiff.
	(cd TDiff r && make -is clean && make && make -is clean && cd ..)
	echo DONE: TIGRESS_BGO_TDIFF.

	echo Making TTHPCal_Map.
	(cd TTHPCal_Map r && make -is clean && make && make -is clean && cd ..)
	echo DONE: TIGRESS_BGO_TTHPCAL_MAP.

clean:
	(cd TDiff             && make -is clean && cd ..)
	(cd TTHPCal_Map       && make -is clean && cd ..)
	rm -f *~
