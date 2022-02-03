all:
	echo Making Energy.
	(cd Energy r && make -is clean && make && make -is clean && cd ..)
	echo DONE: TIGRESS_ENERGY.

	echo Making BGO.
	(cd BGO r && make -is clean && make && make -is clean && cd ..)
	echo DONE: BGO.

clean:
	(cd Energy        && make -is clean && cd ..)
	(cd BGO           && make -is clean && cd ..)	
	rm -f *~
