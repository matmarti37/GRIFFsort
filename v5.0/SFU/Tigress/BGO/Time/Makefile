all:
	echo Making TCal.
	(cd TCal r && make -is clean && make && make -is clean && cd ..)
	echo DONE: TIGRESS_BGO_TCAL.


clean:
	(cd TCal          && make -is clean && cd ..)
	rm -f *~
