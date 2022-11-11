all:
	echo Making Tigress_ERaw.
	(cd ERaw r && make -is clean && make && make -is clean && cd ..)
	echo DONE: TIGRESS_ERAW.

	echo Making Tigress_ECal.
	(cd ECal r && make -is clean && make && make -is clean && cd ..)
	echo DONE: TIGRESS_ECAL.

	echo Making Tigress_ECalSum.
	(cd ECalSum r && make -is clean && make && make -is clean && cd ..)
	echo DONE: TIGRESS_ECALSUM.

	echo Making Tigress_ECalSumCrystal.
	(cd ECalSumCrystal r && make -is clean && make && make -is clean && cd ..)
	echo DONE: TIGRESS_ECALSUMCRYSTAL.

	echo Making Tigress_HP.
	(cd ECalSumCrystal r && make -is clean && make && make -is clean && cd ..)
	echo DONE: TIGRESS_HP.

clean:
	(cd ERaw                && make -is clean && cd ..)
	(cd ECal                && make -is clean && cd ..)
	(cd ECalSum             && make -is clean && cd ..)
	(cd ECalSumCrystal      && make -is clean && cd ..)
	(cd HP                  && make -is clean && cd ..)
	rm -f *~
