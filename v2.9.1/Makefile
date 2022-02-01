all:
	rm -rf ../bin
	echo Setting up directories.
	(mkdir ../bin && mkdir ../bin/midas)

	echo Making utils.
	(cd utils && make -is very-clean && make && make -is clean && cd ..)
	echo DONE: UTILS.

	echo Making SFU-format.
	(cd SFU-format && make -is very-clean && make && make -is clean && cd ..)
	echo DONE: SFU-FORMAT.

	echo Making midas.
	(cd midas && make -is clean && make && make -is clean && cd ..)
	echo DONE: MIDAS.


clean:
	echo Making clean all directories and bin.
	rm -rf ../bin/*
	rmdir ../bin
	(cd utils      && make -is clean && cd ..)
	(cd SFU-format && make -is clean && cd ..)
	(cd midas      && make -is clean && cd ..)
	rm -f *~
	echo DONE: Making clean.

very-clean:
	echo Making very-clean all directories and bin.
	(cd utils      && make -is very-clean && cd ..)
	(cd SFU-format && make -is very-clean && cd ..)
	(cd midas      && make -is very-clean && cd ..)
	rm -f *~
	echo DONE: Making very-clean.
