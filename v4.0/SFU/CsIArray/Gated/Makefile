all:
	echo Making PID.
	(cd PID r && make -is clean && make && make -is clean && cd ..)
	echo DONE: CsIArray_Gated_PID.

	echo Making Energy.
	(cd Energy r && make -is clean && make && make -is clean && cd ..)
	echo DONE: CsIArray_Gated_Energy.


clean:
	(cd PID              && make -is clean && cd ..)
	(cd Energy           && make -is clean && cd ..)
	rm -f *~
