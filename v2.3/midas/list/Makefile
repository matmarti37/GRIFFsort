all:
	echo Making read.
	(cd read r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: READ

	echo Making display.
	(cd display r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: DISPLAY

	echo Making display_subruns.
	(cd display_subruns r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: DISPLAY_SUBRUNS

	echo Making midas2list.
	(cd midas2list r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: MIDAS2LIST

	echo Making midas2list_subruns.
	(cd midas2list_subruns r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: MIDAS2LIST
clean:
	(cd read               && make -is clean && cd ..)
	(cd display            && make -is clean && cd ..)
	(cd display_subruns    && make -is clean && cd ..)
	(cd midas2list         && make -is clean && cd ..)
	(cd midas2list_subruns && make -is clean && cd ..)
	rm -f *~
