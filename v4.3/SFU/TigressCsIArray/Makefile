all:
	echo Making CsIECalSum_TigEGate.
	(cd CsIECalSum_TigEGate r && make -is clean && make && make -is clean && cd ..)
	echo DONE: CsIECalSum_TigEGate.

	echo Making CsIEECalSum_TigEGate.
	(cd CsIEECalSum_TigEGate r && make -is clean && make && make -is clean && cd ..)
	echo DONE: CsIEECalSum_TigEGate.

clean:
	(cd CsIECalSum_TigEGate        && make -is clean && cd ..)
	(cd CsIEECalSum_TigEGate       && make -is clean && cd ..)
	rm -f *~
