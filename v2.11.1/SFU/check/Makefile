all:
	echo Making check_Triggers.
	(cd Triggers r && make -is clean && make && make -is clean && cd ..)
	echo DONE: CHECK_TRIGGERS.

	echo Making check_TrigBits.
	(cd TrigBits r && make -is clean && make && make -is clean && cd ..)
	echo DONE: CHECK_TRIGBITS.

	echo Making check_Fold.
	(cd Fold r && make -is clean && make && make -is clean && cd ..)
	echo DONE: CHECK_FOLD.

	echo Making check_EventTimeDifference.
	(cd EventTimeDifference r && make -is clean && make && make -is clean && cd ..)
	echo DONE: CHECK_EVENTTIMEDIFFERENCE.

	echo Making Rate.
	(cd Rate r && make -is clean && make && make -is clean && cd ..)
	echo DONE: CHECK_RATE.

	echo Making check_TimeStamps.
	(cd TimeStamps r && make -is clean && make && make -is clean && cd ..)
	echo DONE: CHECK_TIMESTAMPS.

clean:
	(cd EventTimeDifference && make -is clean && cd ..)
	(cd Rate                && make -is clean && cd ..)
	(cd TimeStamps          && make -is clean && cd ..)
	(cd Triggers            && make -is clean && cd ..)
	(cd TrigBits            && make -is clean && cd ..)
	(cd Fold                && make -is clean && cd ..)


	rm -f *~
