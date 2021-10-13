all:
	echo Making TIP_cal_amplitude.
	(cd amplitude r && make -is clean && make  && make -is clean && cd ..) 
	echo DONE: TIP_CAL_AMPLITUDE.

clean:
	(cd amplitude					&& make -is clean && cd ..)
	rm -rf *~
