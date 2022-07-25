all:
	echo Making Energy.
	(cd Energy r && make -is clean && make && make -is clean && cd ..)
	echo DONE: CsIArray_ENERGY.

	echo Mkaing PID.
	(cd PID r && make -is clean && make && make -is clean && cd ..)
	echo DONE: CsIArray_PID.

clean:
	(cd Energy        && make -is clean && cd ..)
	(cd PID           && make -is clean && cd ..)
	rm -f *~
