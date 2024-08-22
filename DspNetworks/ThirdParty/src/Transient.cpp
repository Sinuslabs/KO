/* ------------------------------------------------------------
name: "Transient"
Code generated with Faust 2.69.3 (https://faust.grame.fr)
Compilation options: -lang cpp -rui -nvi -ct 1 -cn _Transient -scn ::faust::dsp -es 1 -mcd 16 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___Transient_H__
#define  ___Transient_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _Transient
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif

static float _Transient_faustpower2_f(float value) {
	return value * value;
}

class _Transient final : public ::faust::dsp {
	
 public:
	
	int fSampleRate;
	float fConst1;
	FAUSTFLOAT fHslider0;
	float fConst2;
	float fConst3;
	float fConst4;
	int IOTA0;
	FAUSTFLOAT fHslider1;
	float fRec3[3];
	float fRec2[3];
	float fRec1[8192];
	int iConst5;
	float fRec4[2];
	float fConst6;
	FAUSTFLOAT fHslider2;
	float fConst7;
	float fRec5[2];
	FAUSTFLOAT fHslider3;
	float fRec6[2];
	float fRec0[2];
	FAUSTFLOAT fButton0;
	float fVec0[2];
	int iRec7[2];
	FAUSTFLOAT fVbargraph0;
	float fRec8[3];
	float fRec12[3];
	float fRec11[3];
	float fRec10[8192];
	float fRec13[2];
	float fRec9[2];
	float fRec14[3];
	
 public:
	_Transient() {}

	void metadata(Meta* m) { 
		m->declare("basics.lib/bypass1:author", "Julius Smith");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/tabulateNd", "Copyright (C) 2023 Bart Brouns <bart@magnetophon.nl>");
		m->declare("basics.lib/toggle:author", "Vince");
		m->declare("basics.lib/version", "1.11.1");
		m->declare("compile_options", "-lang cpp -rui -nvi -ct 1 -cn _Transient -scn ::faust::dsp -es 1 -mcd 16 -uim -single -ftz 0");
		m->declare("filename", "Transient.dsp");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/integrator:author", "Julius O. Smith III");
		m->declare("filters.lib/integrator:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/integrator:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/resonhp:author", "Julius O. Smith III");
		m->declare("filters.lib/resonhp:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/resonhp:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/resonlp:author", "Julius O. Smith III");
		m->declare("filters.lib/resonlp:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/resonlp:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "1.3.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.7.0");
		m->declare("name", "Transient");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/onePoleSwitching:author", "Jonatan Liljedahl, revised by Dario Sanfilippo");
		m->declare("signals.lib/onePoleSwitching:licence", "STK-4.3");
		m->declare("signals.lib/version", "1.5.0");
		m->declare("spats.lib/name", "Faust Spatialization Library");
		m->declare("spats.lib/version", "1.1.0");
	}

	static constexpr int getStaticNumInputs() {
		return 2;
	}
	static constexpr int getStaticNumOutputs() {
		return 2;
	}
	int getNumInputs() {
		return 2;
	}
	int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
	}
	
	void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		float fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = 3.1415927f / fConst0;
		fConst2 = 33.333332f / fConst0;
		fConst3 = std::exp(-fConst2);
		fConst4 = 1.0f - fConst3;
		iConst5 = int(std::max<float>(0.0f, 0.03f * fConst0));
		fConst6 = 44.1f / fConst0;
		fConst7 = 1.0f - fConst6;
	}
	
	void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(2e+04f);
		fHslider1 = FAUSTFLOAT(1e+01f);
		fHslider2 = FAUSTFLOAT(0.0f);
		fHslider3 = FAUSTFLOAT(0.0f);
		fButton0 = FAUSTFLOAT(0.0f);
	}
	
	void instanceClear() {
		IOTA0 = 0;
		for (int l0 = 0; l0 < 3; l0 = l0 + 1) {
			fRec3[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 3; l1 = l1 + 1) {
			fRec2[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 8192; l2 = l2 + 1) {
			fRec1[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec4[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec5[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec6[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec0[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fVec0[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			iRec7[l8] = 0;
		}
		for (int l9 = 0; l9 < 3; l9 = l9 + 1) {
			fRec8[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 3; l10 = l10 + 1) {
			fRec12[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 3; l11 = l11 + 1) {
			fRec11[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 8192; l12 = l12 + 1) {
			fRec10[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fRec13[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 2; l14 = l14 + 1) {
			fRec9[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 3; l15 = l15 + 1) {
			fRec14[l15] = 0.0f;
		}
	}
	
	void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	
	void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	_Transient* clone() {
		return new _Transient();
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("Whetstone Transient Shaper");
		ui_interface->declare(&fHslider3, "0", "");
		ui_interface->declare(&fHslider3, "unit", "dB");
		ui_interface->addHorizontalSlider("Attack", &fHslider3, FAUSTFLOAT(0.0f), FAUSTFLOAT(-12.0f), FAUSTFLOAT(12.0f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider2, "1", "");
		ui_interface->declare(&fHslider2, "unit", "dB");
		ui_interface->addHorizontalSlider("Sustain", &fHslider2, FAUSTFLOAT(0.0f), FAUSTFLOAT(-12.0f), FAUSTFLOAT(12.0f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider1, "2", "");
		ui_interface->declare(&fHslider1, "unit", "Hz");
		ui_interface->addHorizontalSlider("Low Cutoff", &fHslider1, FAUSTFLOAT(1e+01f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(2e+04f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fHslider0, "3", "");
		ui_interface->declare(&fHslider0, "unit", "Hz");
		ui_interface->addHorizontalSlider("High Cutoff", &fHslider0, FAUSTFLOAT(2e+04f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(2e+04f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(0, "4", "");
		ui_interface->openHorizontalBox("Monitoring");
		ui_interface->declare(&fButton0, "0", "");
		ui_interface->addButton("Monitor selected band", &fButton0);
		ui_interface->declare(&fVbargraph0, "1", "");
		ui_interface->declare(&fVbargraph0, "style", "led");
		ui_interface->addVerticalBargraph("ON", &fVbargraph0, FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = std::tan(fConst1 * std::max<float>(2e+01f, std::min<float>(2e+04f, float(fHslider0))));
		float fSlow1 = 1.0f / fSlow0;
		float fSlow2 = 1.0f / ((fSlow1 + 1.0f) / fSlow0 + 1.0f);
		float fSlow3 = std::tan(fConst1 * std::max<float>(1e+01f, std::min<float>(2e+04f, float(fHslider1))));
		float fSlow4 = 1.0f / fSlow3;
		float fSlow5 = 1.0f / ((fSlow4 + 1.0f) / fSlow3 + 1.0f);
		float fSlow6 = 1.0f - (1.0f - fSlow4) / fSlow3;
		float fSlow7 = 2.0f * (1.0f - 1.0f / _Transient_faustpower2_f(fSlow3));
		float fSlow8 = 1.0f - (1.0f - fSlow1) / fSlow0;
		float fSlow9 = 2.0f * (1.0f - 1.0f / _Transient_faustpower2_f(fSlow0));
		float fSlow10 = fConst6 * std::pow(1e+01f, 0.05f * std::max<float>(-12.0f, std::min<float>(12.0f, float(fHslider2))));
		float fSlow11 = fConst6 * std::pow(1e+01f, 0.05f * std::max<float>(-12.0f, std::min<float>(12.0f, float(fHslider3))));
		float fSlow12 = float(fButton0);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = float(input0[i0]);
			fRec3[0] = fTemp0 - fSlow5 * (fSlow6 * fRec3[2] + fSlow7 * fRec3[1]);
			float fTemp1 = 2.0f * fRec3[1];
			fRec2[0] = fTemp0 - (fSlow5 * (fRec3[2] + fRec3[0] + fTemp1) + fSlow2 * (fSlow8 * fRec2[2] + fSlow9 * fRec2[1]));
			float fTemp2 = 2.0f * fRec2[1];
			fRec1[IOTA0 & 8191] = fRec1[(IOTA0 - 1) & 8191] + _Transient_faustpower2_f(fSlow2 * (fRec2[2] + fRec2[0] + fTemp2));
			float fTemp3 = std::sqrt(fConst2 * (fRec1[IOTA0 & 8191] - fRec1[(IOTA0 - iConst5) & 8191]));
			fRec4[0] = fConst4 * fTemp3 + fConst3 * fRec4[1];
			fRec5[0] = fSlow10 + fConst7 * fRec5[1];
			fRec6[0] = fSlow11 + fConst7 * fRec6[1];
			fRec0[0] = fConst4 * (((fTemp3 - fRec4[0]) > 0.0f) ? fRec6[0] : fRec5[0]) + fConst3 * fRec0[1];
			fVec0[0] = fSlow12;
			iRec7[0] = iRec7[1] != ((fSlow12 - fVec0[1]) == 1.0f);
			fVbargraph0 = FAUSTFLOAT(float(iRec7[0]));
			int iTemp4 = fVbargraph0 != 1.0f;
			fRec8[0] = fTemp0 - fSlow2 * (fSlow8 * fRec8[2] + fSlow9 * fRec8[1]);
			output0[i0] = FAUSTFLOAT(fSlow2 * fRec0[0] * (fRec2[0] + fRec2[2] + fTemp2) + ((iTemp4) ? fTemp0 + fSlow5 * (fRec3[0] + fRec3[2] + fTemp1) - fSlow2 * (2.0f * fRec8[1] + fRec8[0] + fRec8[2]) : 0.0f));
			float fTemp5 = float(input1[i0]);
			fRec12[0] = fTemp5 - fSlow5 * (fSlow6 * fRec12[2] + fSlow7 * fRec12[1]);
			float fTemp6 = fSlow5 * (fRec12[2] + fRec12[0] + 2.0f * fRec12[1]);
			fRec11[0] = fTemp5 - (fTemp6 + fSlow2 * (fSlow8 * fRec11[2] + fSlow9 * fRec11[1]));
			float fTemp7 = fRec11[2] + fRec11[0] + 2.0f * fRec11[1];
			fRec10[IOTA0 & 8191] = fRec10[(IOTA0 - 1) & 8191] + _Transient_faustpower2_f(fSlow2 * fTemp7);
			float fTemp8 = std::sqrt(fConst2 * (fRec10[IOTA0 & 8191] - fRec10[(IOTA0 - iConst5) & 8191]));
			fRec13[0] = fConst4 * fTemp8 + fConst3 * fRec13[1];
			fRec9[0] = fConst4 * (((fTemp8 - fRec13[0]) > 0.0f) ? fRec6[0] : fRec5[0]) + fConst3 * fRec9[1];
			fRec14[0] = fTemp5 - fSlow2 * (fSlow8 * fRec14[2] + fSlow9 * fRec14[1]);
			output1[i0] = FAUSTFLOAT(fSlow2 * fRec9[0] * fTemp7 + ((iTemp4) ? fTemp5 + fTemp6 - fSlow2 * (fRec14[2] + fRec14[0] + 2.0f * fRec14[1]) : 0.0f));
			IOTA0 = IOTA0 + 1;
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec0[1] = fRec0[0];
			fVec0[1] = fVec0[0];
			iRec7[1] = iRec7[0];
			fRec8[2] = fRec8[1];
			fRec8[1] = fRec8[0];
			fRec12[2] = fRec12[1];
			fRec12[1] = fRec12[0];
			fRec11[2] = fRec11[1];
			fRec11[1] = fRec11[0];
			fRec13[1] = fRec13[0];
			fRec9[1] = fRec9[0];
			fRec14[2] = fRec14[1];
			fRec14[1] = fRec14[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "Transient.dsp"
	#define FAUST_CLASS_NAME "_Transient"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -rui -nvi -ct 1 -cn _Transient -scn ::faust::dsp -es 1 -mcd 16 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 5
	#define FAUST_PASSIVES 1

	FAUST_ADDHORIZONTALSLIDER("Whetstone Transient Shaper/Attack", fHslider3, 0.0f, -12.0f, 12.0f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("Whetstone Transient Shaper/Sustain", fHslider2, 0.0f, -12.0f, 12.0f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("Whetstone Transient Shaper/Low Cutoff", fHslider1, 1e+01f, 1e+01f, 2e+04f, 1e+01f);
	FAUST_ADDHORIZONTALSLIDER("Whetstone Transient Shaper/High Cutoff", fHslider0, 2e+04f, 2e+01f, 2e+04f, 1e+01f);
	FAUST_ADDBUTTON("Whetstone Transient Shaper/[4]Monitoring/Monitor selected band", fButton0);
	FAUST_ADDVERTICALBARGRAPH("Whetstone Transient Shaper/[4]Monitoring/ON", fVbargraph0, 0.0f, 1.0f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, Attack, "Whetstone Transient Shaper/Attack", fHslider3, 0.0f, -12.0f, 12.0f, 0.1f) \
		p(HORIZONTALSLIDER, Sustain, "Whetstone Transient Shaper/Sustain", fHslider2, 0.0f, -12.0f, 12.0f, 0.1f) \
		p(HORIZONTALSLIDER, Low_Cutoff, "Whetstone Transient Shaper/Low Cutoff", fHslider1, 1e+01f, 1e+01f, 2e+04f, 1e+01f) \
		p(HORIZONTALSLIDER, High_Cutoff, "Whetstone Transient Shaper/High Cutoff", fHslider0, 2e+04f, 2e+01f, 2e+04f, 1e+01f) \
		p(BUTTON, Monitor_selected_band, "Whetstone Transient Shaper/[4]Monitoring/Monitor selected band", fButton0, 0.0f, 0.0f, 1.0f, 1.0f) \

	#define FAUST_LIST_PASSIVES(p) \
		p(VERTICALBARGRAPH, ON, "Whetstone Transient Shaper/[4]Monitoring/ON", fVbargraph0, 0.0, 0.0f, 1.0f, 0.0) \

#endif

#endif
