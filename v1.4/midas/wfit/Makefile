all:
	echo Making wfit_test_CsIBaseline.
	(cd test_CsIBaseline r && make -is clean && make  && make -is clean && cd ..) 
	echo DONE: WFIT_TEST_CSIBASELINE.

	echo Making wfit_amplitude.
	(cd amplitude r && make -is clean && make  && make -is clean && cd ..) 
	echo DONE: WFIT_AMPLITUDE.

	echo Making wfit_show_CsIBaseline.
	(cd show_CsIBaseline r && make -is clean && make  && make -is clean && cd ..) 
	echo DONE: WFIT_SHOW_CSIBASELINE.

	echo Making wfit_show_bad_baseline.
	(cd show_bad_baseline r && make -is clean && make  && make -is clean && cd ..) 
	echo DONE: WFIT_SHOW_BAD_BASELINE

	echo Making wfit_test_CsIExclusionZone.
	(cd test_CsIExclusionZone r && make -is clean && make  && make -is clean && cd ..) 	
	echo DONE: WFIT_TEST_CSIEXCLUSIONZONE

	echo Making wfit_show_CsIExclusionZone.
	(cd show_CsIExclusionZone r && make -is clean && make  && make -is clean && cd ..) 
	echo DONE: WFIT_SHOW_CSIEXCLUSIONZONE

	echo Making wfit_show_bad_CsIExclusionZone.
	(cd show_bad_CsIExclusionZone r && make -is clean && make  && make -is clean && cd ..) 
	echo DONE: WFIT_SHOW_BAD_CSIEXCLUSIONZONE.

	echo Making wfit_show_tmax.
	(cd show_tmax r && make -is clean && make  && make -is clean && cd ..) 
	echo DONE: WFIT_SHOW_TMAX.

	echo Making wfit_show_lin_two_components.
	(cd show_lin_two_components r && make -is clean && make  && make -is clean && cd ..) 
	echo DONE: WFIT_SHOW_LIN_TWO_COMPONENTS.

	echo Making wfit_test_CsIFitChiSq.
	(cd test_lin_two_components_chisq r && make -is clean && make  && make -is clean && cd ..) 	
	echo DONE: WFIT_TEST_LIN_TWO_COMPONENTS_CHISQ

	echo Making wfit_show_CsIFits.
	(cd show_CsIFits && make -is clean && make  && make -is clean && cd ..) 
	echo DONE: WFIT_SHOW_CSIFITS.

	echo Making wfit_show_CsITF.
	(cd show_CsITF && make -is clean && make  && make -is clean && cd ..) 
	echo DONE: WFIT_SHOW_CSITF.

	echo Making wfit_show_CsIExclusionZoneAndFits.
	(cd show_CsIExclusionZoneAndFits && make -is clean && make  && make -is clean && cd ..) 
	echo DONE: WFIT_SHOW_CSIEXCLUSIONZONEANDFITS.

	echo Making wfit_test_CsIFits_chisq.
	(cd test_CsIFits_chisq && make -is clean && make  && make -is clean && cd ..) 
	echo DONE: WFIT_TEST_CSIFITS_CHISQ.

	echo Making wfit_RC.
	(cd RC && make -is clean && make  && make -is clean && cd ..) 
	echo DONE: WFIT_RC

	echo Making wfit_fit_fast_component.
	(cd fit_fast_component && make -is clean && make  && make -is clean && cd ..) 
	echo DONE: WFIT_FIT_FAST_COMPONENT

	echo Making wfit_fit_slow_component.
	(cd fit_slow_component && make -is clean && make  && make -is clean && cd ..) 
	echo DONE: WFIT_FIT_SLOW_COMPONENT

	echo Making wfit_fit_two_component.
	(cd fit_two_component && make -is clean && make  && make -is clean && cd ..) 
	echo DONE: WFIT_FIT_TWO_COMPONENT

	echo Making wfit_show_CsIFit_type.
	(cd  show_CsIFit_type && make -is clean && make  && make -is clean && cd ..) 
	echo DONE: WFIT_SHOW_CSIFIT_TYPE

	echo Making wfit_show_CsIFit_t0.
	(cd  show_CsIFit_t0 && make -is clean && make  && make -is clean && cd ..) 
	echo DONE: WFIT_SHOW_CSIFIT_T0

clean:

	(cd test_CsIBaseline				&& make -is clean && cd ..)
	(cd amplitude					&& make -is clean && cd ..)
	(cd show_CsIBaseline				&& make -is clean && cd ..)
	(cd show_bad_baseline				&& make -is clean && cd ..)
	(cd test_CsIExclusionZone			&& make -is clean && cd ..)
	(cd show_CsIExclusionZone			&& make -is clean && cd ..)
	(cd show_bad_CsIExclusionZone			&& make -is clean && cd ..)
	(cd show_tmax					&& make -is clean && cd ..)
	(cd show_lin_two_components			&& make -is clean && cd ..)
	(cd test_lin_two_components_chisq		&& make -is clean && cd ..)
	(cd show_CsIFits				&& make -is clean && cd ..)
	(cd show_CsITF					&& make -is clean && cd ..)
	(cd show_CsIExclusionZoneAndFits		&& make -is clean && cd ..)
	(cd test_CsIFits_chisq				&& make -is clean && cd ..)
	(cd RC						&& make -is clean && cd ..)
	(cd fit_fast_component				&& make -is clean && cd ..)
	(cd fit_slow_component				&& make -is clean && cd ..)
	(cd fit_two_component				&& make -is clean && cd ..)
	(cd show_CsIFit_type				&& make -is clean && cd ..)
	(cd show_CsIFit_t0				&& make -is clean && cd ..)
	rm -rf *~
