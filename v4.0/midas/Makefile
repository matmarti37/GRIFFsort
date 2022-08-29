all:
	echo Making decoder.
	(cd decoder && make -is very-clean && make && make -is clean && cd ..)
	echo DONE: DECODER.
	echo Making map.
	(cd map && make -is very-clean && make  && make -is clean && cd ..)
	echo DONE: MAP.
	echo Making state-machine.
	(cd state-machine && make -is very-clean && make  && make -is clean && cd ..)
	echo DONE: STATE-MACHINE.
	echo Making view.
	(cd view && make -is clean && make && make -is clean && cd ..)
	echo DONE: VIEW.
	echo Making wfit.
	(cd wfit && make -is clean && make && make -is clean && cd ..)
	echo DONE: WFIT.
	echo Making project.
	(cd project && make -is clean && make && make -is clean && cd ..)
	echo DONE: PROJECT.	
	echo Making TIP_cal.
	(cd TIP_cal && make -is clean && make && make -is clean && cd ..)
	echo DONE: TIP_CAL.
	echo Making midas2list.
	(cd midas2list && make -is clean && make && make -is clean && cd ..)
	echo DONE: MIDAS2LIST.

clean:
	(cd decoder       && make -is clean && cd ..)
	(cd map           && make -is clean && cd ..)
	(cd state-machine && make -is clean && cd ..)
	(cd view          && make -is clean && cd ..)
	(cd wfit          && make -is clean && cd ..)
	(cd project       && make -is clean && cd ..)
	(cd TIP_cal       && make -is clean && cd ..)
	(cd midas2list    && make -is clean && cd ..)
	rm -f *~

very-clean:
	echo Making very-clean all directories and bin.
	(cd decoder && make -is very-clean && cd ..)
	(cd map           && make -is very-clean && cd ..)
	(cd state-machine && make -is very-clean && cd ..)
	(cd view          && make -is clean && cd ..)
	(cd wfit          && make -is clean && cd ..)
	(cd project       && make -is clean && cd ..)
	(cd TIP_cal       && make -is clean && cd ..)
	(cd midas2list    && make -is clean && cd ..)
	rm -f *~
	echo DONE: Making very-clean.

