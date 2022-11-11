all:
	echo Making Energy.
	(cd Energy r && make -is clean && make && make -is clean && cd ..)
	echo DONE: CsIArray_ENERGY.

	echo Making PID.
	(cd PID r && make -is clean && make && make -is clean && cd ..)
	echo DONE: CsIArray_PID.

	echo Making Gated.
	(cd Gated r && make -is clean && make && make -is clean && cd ..)
	echo DONE: CsIArray_Gated.

clean:
	(cd Energy        && make -is clean && cd ..)
	(cd PID           && make -is clean && cd ..)
	(cd Gated         && make -is clean && cd ..)
	rm -f *~
