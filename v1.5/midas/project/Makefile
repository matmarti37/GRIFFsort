all:
	echo Making project_channel.
	(cd channel r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: PROJECT_CHANNEL.

	echo Making project_channelHP.
	(cd channelHP r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: PROJECT_CHANNELHP.

clean:
	(cd channel    && make -is clean && cd ..)
	(cd channelHP  && make -is clean && cd ..)
	rm -f *~
