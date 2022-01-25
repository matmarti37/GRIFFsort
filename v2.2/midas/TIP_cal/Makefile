all:
	echo Making TIP_cal_amplitude.
	(cd amplitude r && make -is clean && make  && make -is clean && cd ..) 
	echo DONE: TIP_CAL_AMPLITUDE.
	echo Making TIP_cal_PID.
	(cd PID r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: TIP_CAL_PID.
	echo Making TIP_cal_show_waveforms
	(cd show_waveforms r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: TIP_CAL_SHOW_WAVEFORMS

clean:
	(cd amplitude					&& make -is clean && cd ..)
	(cd PID				        	&& make -is clean && cd ..)
	(cd show_waveforms				&& make -is clean && cd ..)
	rm -rf *~
