all:
	echo Making display_RawEvent.
	(cd RawEvent r && make -is clean && make && make -is clean && cd ..)
	echo DONE: DISPLAY_RawEvent.

	echo Making display_Tigress.
	(cd Tigress r && make -is clean && make && make -is clean && cd ..)
	echo DONE: DISPLAY_TIGRESS.

	echo Making display_channelHP_CC.
	(cd channelHP_CC r && make -is clean && make && make -is clean && cd ..)
	echo DONE: DISPLAY_CHANNELHP_CC.

clean:
	(cd RawEvent      && make -is clean && cd ..)
	(cd Tigress       && make -is clean && cd ..)
	(cd channelHP_CC  && make -is clean && cd ..)
	rm -f *~

very-clean:
	(cd RawEvent      && make -is very-clean && cd ..)
	(cd Tigress       && make -is very-clean && cd ..)
	(cd channelHP_CC  && make -is very-clean && cd ..)
	rm -f *~
	echo DONE: Making very-clean.
