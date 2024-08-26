#pragma once

#include "Drive.h"
#include "Tube2.h"
#include "Tube2.h"
#include "DrumSlam.h"
#include "Logical4.h"
#include "Logical4.h"
#include "Focus.h"
// These will improve the readability of the connection definition

#define getT(Idx) template get<Idx>()
#define connectT(Idx, target) template connect<Idx>(target)
#define getParameterT(Idx) template getParameter<Idx>()
#define setParameterT(Idx, value) template setParameter<Idx>(value)
#define setParameterWT(Idx, value) template setWrapParameter<Idx>(value)
using namespace scriptnode;
using namespace snex;
using namespace snex::Types;

namespace Boxer_impl
{
// ==============================| Node & Parameter type declarations |==============================

template <int NV>
using pma1_t = control::pma<NV, 
                            parameter::plain<project::Drive<NV>, 0>>;

template <int NV>
using pma_mod = parameter::chain<ranges::Identity, 
                                 parameter::plain<project::Tube2<NV>, 1>, 
                                 parameter::plain<project::Tube2<NV>, 1>>;

template <int NV>
using pma_t = control::pma<NV, pma_mod<NV>>;
DECLARE_PARAMETER_RANGE(wut_smooth_mod_0Range, 
                        -1., 
                        1.);

template <int NV>
using wut_smooth_mod_0 = parameter::from0To1<pma1_t<NV>, 
                                             1, 
                                             wut_smooth_mod_0Range>;

template <int NV>
using wut_smooth_mod = parameter::chain<ranges::Identity, 
                                        wut_smooth_mod_0<NV>, 
                                        parameter::plain<pma_t<NV>, 0>>;

template <int NV>
using wut_smooth_t = wrap::mod<wut_smooth_mod<NV>, 
                               control::smoothed_parameter<NV, smoothers::linear_ramp<NV>>>;

using faust_multimod = parameter::list<parameter::empty>;

template <int NV>
using faust_t = project::Transient<NV, faust_multimod>;
template <int NV>
using minmax1_t = control::minmax<NV, 
                                  parameter::plain<faust_t<NV>, 0>>;

template <int NV>
using minmax2_t = control::minmax<NV, 
                                  parameter::plain<faust_t<NV>, 1>>;

template <int NV>
using minmax_t = control::minmax<NV, 
                                 parameter::plain<core::gain<NV>, 0>>;

template <int NV>
using Punch_smooth_mod = parameter::chain<ranges::Identity, 
                                          parameter::plain<minmax1_t<NV>, 0>, 
                                          parameter::plain<minmax2_t<NV>, 0>, 
                                          parameter::plain<minmax_t<NV>, 0>, 
                                          parameter::plain<pma1_t<NV>, 0>, 
                                          parameter::plain<project::DrumSlam<NV>, 0>>;

template <int NV>
using Punch_smooth_t = wrap::mod<Punch_smooth_mod<NV>, 
                                 control::smoothed_parameter<NV, smoothers::linear_ramp<NV>>>;

template <int NV>
using split_t = container::split<parameter::empty, 
                                 wrap::fix<1, minmax1_t<NV>>, 
                                 minmax2_t<NV>, 
                                 minmax_t<NV>>;

template <int NV>
using modchain_t_ = container::chain<parameter::empty, 
                                     wrap::fix<1, split_t<NV>>, 
                                     pma1_t<NV>>;

template <int NV>
using modchain_t = wrap::control_rate<modchain_t_<NV>>;

DECLARE_PARAMETER_RANGE_SKEW(dry_wet_mixer_c0Range, 
                             -100., 
                             0., 
                             5.42227);

template <int NV>
using dry_wet_mixer_c0 = parameter::from0To1<core::gain<NV>, 
                                             0, 
                                             dry_wet_mixer_c0Range>;

template <int NV> using dry_wet_mixer_c1 = dry_wet_mixer_c0<NV>;

template <int NV>
using dry_wet_mixer_multimod = parameter::list<dry_wet_mixer_c0<NV>, dry_wet_mixer_c1<NV>>;

template <int NV>
using dry_wet_mixer_t = control::xfader<dry_wet_mixer_multimod<NV>, 
                                        faders::cosine_half>;

template <int NV>
using dry_path_t = container::chain<parameter::empty, 
                                    wrap::fix<2, dry_wet_mixer_t<NV>>, 
                                    core::gain<NV>>;

template <int NV>
using band1_t = container::chain<parameter::empty, 
                                 wrap::fix<2, jdsp::jlinkwitzriley>, 
                                 project::Logical4<NV>>;

template <int NV> using band2_t = band1_t<NV>;

namespace freq_split3_t_parameters
{
DECLARE_PARAMETER_RANGE_SKEW(Band1_0Range, 
                             20., 
                             20000., 
                             0.229905);

using Band1_0 = parameter::from0To1<jdsp::jlinkwitzriley, 
                                    0, 
                                    Band1_0Range>;

using Band1_1 = Band1_0;

using Band1 = parameter::chain<ranges::Identity, 
                               Band1_0, 
                               Band1_1>;

}

template <int NV>
using freq_split3_t = container::split<freq_split3_t_parameters::Band1, 
                                       wrap::fix<2, band1_t<NV>>, 
                                       band2_t<NV>>;

template <int NV>
using soft_bypass_t_ = container::chain<parameter::empty, 
                                        wrap::fix<2, freq_split3_t<NV>>, 
                                        core::gain<NV>>;

template <int NV>
using soft_bypass_t = bypass::smoothed<20, soft_bypass_t_<NV>>;

template <int NV>
using chain_t = container::chain<parameter::empty, 
                                 wrap::fix<2, pma_t<NV>>, 
                                 project::Drive<NV>, 
                                 project::Tube2<NV>, 
                                 project::Tube2<NV>, 
                                 faust_t<NV>, 
                                 project::DrumSlam<NV>, 
                                 soft_bypass_t<NV>, 
                                 project::Focus<NV>, 
                                 core::gain<NV>>;

template <int NV>
using wet_path_t = container::chain<parameter::empty, 
                                    wrap::fix<2, chain_t<NV>>, 
                                    core::gain<NV>>;

namespace dry_wet1_t_parameters
{
}

template <int NV>
using dry_wet1_t = container::split<parameter::plain<Boxer_impl::dry_wet_mixer_t<NV>, 0>, 
                                    wrap::fix<2, dry_path_t<NV>>, 
                                    wet_path_t<NV>>;

namespace Boxer_t_parameters
{
// Parameter list for Boxer_impl::Boxer_t ----------------------------------------------------------

template <int NV>
using _16oz = parameter::bypass<Boxer_impl::soft_bypass_t<NV>>;

template <int NV>
using Punch = parameter::plain<Boxer_impl::Punch_smooth_t<NV>, 
                               0>;
template <int NV>
using Wut = parameter::plain<Boxer_impl::wut_smooth_t<NV>, 
                             0>;
template <int NV>
using Mix = parameter::plain<Boxer_impl::dry_wet1_t<NV>, 
                             0>;
template <int NV>
using Boxer_t_plist = parameter::list<Punch<NV>, 
                                      Wut<NV>, 
                                      Mix<NV>, 
                                      _16oz<NV>>;
}

template <int NV>
using Boxer_t_ = container::chain<Boxer_t_parameters::Boxer_t_plist<NV>, 
                                  wrap::fix<2, wut_smooth_t<NV>>, 
                                  Punch_smooth_t<NV>, 
                                  modchain_t<NV>, 
                                  dry_wet1_t<NV>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public Boxer_impl::Boxer_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(Boxer);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(62)
		{
			0x005B, 0x0000, 0x5000, 0x6E75, 0x6863, 0x0000, 0x0000, 0x0000, 
            0x8000, 0x873F, 0x36AF, 0x003F, 0x8000, 0x003F, 0x0000, 0x5B00, 
            0x0001, 0x0000, 0x7557, 0x0074, 0x0000, 0x0000, 0x0000, 0x3F80, 
            0x04ED, 0x3F08, 0x0000, 0x3F80, 0x0000, 0x0000, 0x025B, 0x0000, 
            0x4D00, 0x7869, 0x0000, 0x0000, 0x0000, 0x8000, 0x003F, 0x8000, 
            0x003F, 0x8000, 0x003F, 0x0000, 0x5B00, 0x0003, 0x0000, 0x315F, 
            0x6F36, 0x007A, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 
            0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& wut_smooth = this->getT(0);                                               // Boxer_impl::wut_smooth_t<NV>
		auto& Punch_smooth = this->getT(1);                                             // Boxer_impl::Punch_smooth_t<NV>
		auto& modchain = this->getT(2);                                                 // Boxer_impl::modchain_t<NV>
		auto& split = this->getT(2).getT(0);                                            // Boxer_impl::split_t<NV>
		auto& minmax1 = this->getT(2).getT(0).getT(0);                                  // Boxer_impl::minmax1_t<NV>
		auto& minmax2 = this->getT(2).getT(0).getT(1);                                  // Boxer_impl::minmax2_t<NV>
		auto& minmax = this->getT(2).getT(0).getT(2);                                   // Boxer_impl::minmax_t<NV>
		auto& pma1 = this->getT(2).getT(1);                                             // Boxer_impl::pma1_t<NV>
		auto& dry_wet1 = this->getT(3);                                                 // Boxer_impl::dry_wet1_t<NV>
		auto& dry_path = this->getT(3).getT(0);                                         // Boxer_impl::dry_path_t<NV>
		auto& dry_wet_mixer = this->getT(3).getT(0).getT(0);                            // Boxer_impl::dry_wet_mixer_t<NV>
		auto& dry_gain = this->getT(3).getT(0).getT(1);                                 // core::gain<NV>
		auto& wet_path = this->getT(3).getT(1);                                         // Boxer_impl::wet_path_t<NV>
		auto& chain = this->getT(3).getT(1).getT(0);                                    // Boxer_impl::chain_t<NV>
		auto& pma = this->getT(3).getT(1).getT(0).getT(0);                              // Boxer_impl::pma_t<NV>
		auto& Drive = this->getT(3).getT(1).getT(0).getT(1);                            // project::Drive<NV>
		auto& Tube2 = this->getT(3).getT(1).getT(0).getT(2);                            // project::Tube2<NV>
		auto& Tube3 = this->getT(3).getT(1).getT(0).getT(3);                            // project::Tube2<NV>
		auto& faust = this->getT(3).getT(1).getT(0).getT(4);                            // Boxer_impl::faust_t<NV>
		auto& DrumSlam = this->getT(3).getT(1).getT(0).getT(5);                         // project::DrumSlam<NV>
		auto& soft_bypass = this->getT(3).getT(1).getT(0).getT(6);                      // Boxer_impl::soft_bypass_t<NV>
		auto& freq_split3 = this->getT(3).getT(1).getT(0).getT(6).getT(0);              // Boxer_impl::freq_split3_t<NV>
		auto& band1 = this->getT(3).getT(1).getT(0).getT(6).getT(0).getT(0);            // Boxer_impl::band1_t<NV>
		auto& lr1_1 = this->getT(3).getT(1).getT(0).getT(6).getT(0).getT(0).getT(0);    // jdsp::jlinkwitzriley
		auto& Logical4 = this->getT(3).getT(1).getT(0).getT(6).getT(0).getT(0).getT(1); // project::Logical4<NV>
		auto& band2 = this->getT(3).getT(1).getT(0).getT(6).getT(0).getT(1);            // Boxer_impl::band2_t<NV>
		auto& lr2_1 = this->getT(3).getT(1).getT(0).getT(6).getT(0).getT(1).getT(0);    // jdsp::jlinkwitzriley
		auto& Logical5 = this->getT(3).getT(1).getT(0).getT(6).getT(0).getT(1).getT(1); // project::Logical4<NV>
		auto& gain1 = this->getT(3).getT(1).getT(0).getT(6).getT(1);                    // core::gain<NV>
		auto& Focus = this->getT(3).getT(1).getT(0).getT(7);                            // project::Focus<NV>
		auto& gain = this->getT(3).getT(1).getT(0).getT(8);                             // core::gain<NV>
		auto& wet_gain = this->getT(3).getT(1).getT(1);                                 // core::gain<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		auto& Band1_p = freq_split3.getParameterT(0);
		Band1_p.connectT(0, lr1_1);                           // Band1 -> lr1_1::Frequency
		Band1_p.connectT(1, lr2_1);                           // Band1 -> lr2_1::Frequency
		dry_wet1.getParameterT(0).connectT(0, dry_wet_mixer); // DryWet -> dry_wet_mixer::Value
		this->getParameterT(0).connectT(0, Punch_smooth);     // Punch -> Punch_smooth::Value
		
		this->getParameterT(1).connectT(0, wut_smooth); // Wut -> wut_smooth::Value
		
		this->getParameterT(2).connectT(0, dry_wet1); // Mix -> dry_wet1::DryWet
		
		this->getParameterT(3).connectT(0, soft_bypass); // _16oz -> soft_bypass::Bypassed
		
		// Modulation Connections ------------------------------------------------------------------
		
		pma1.getWrappedObject().getParameter().connectT(0, Drive); // pma1 -> Drive::Drive
		pma.getWrappedObject().getParameter().connectT(0, Tube2);  // pma -> Tube2::Tube
		pma.getWrappedObject().getParameter().connectT(1, Tube3);  // pma -> Tube3::Tube
		wut_smooth.getParameter().connectT(0, pma1);               // wut_smooth -> pma1::Multiply
		wut_smooth.getParameter().connectT(1, pma);                // wut_smooth -> pma::Value
		auto& faust_p = faust.getWrappedObject().getParameter();
		minmax1.getWrappedObject().getParameter().connectT(0, faust); // minmax1 -> faust::Attack
		minmax2.getWrappedObject().getParameter().connectT(0, faust); // minmax2 -> faust::Sustain
		minmax.getWrappedObject().getParameter().connectT(0, gain);   // minmax -> gain::Gain
		Punch_smooth.getParameter().connectT(0, minmax1);             // Punch_smooth -> minmax1::Value
		Punch_smooth.getParameter().connectT(1, minmax2);             // Punch_smooth -> minmax2::Value
		Punch_smooth.getParameter().connectT(2, minmax);              // Punch_smooth -> minmax::Value
		Punch_smooth.getParameter().connectT(3, pma1);                // Punch_smooth -> pma1::Value
		Punch_smooth.getParameter().connectT(4, DrumSlam);            // Punch_smooth -> DrumSlam::Drive
		auto& dry_wet_mixer_p = dry_wet_mixer.getWrappedObject().getParameter();
		dry_wet_mixer_p.getParameterT(0).connectT(0, dry_gain); // dry_wet_mixer -> dry_gain::Gain
		dry_wet_mixer_p.getParameterT(1).connectT(0, wet_gain); // dry_wet_mixer -> wet_gain::Gain
		
		// Default Values --------------------------------------------------------------------------
		
		;                                   // wut_smooth::Value is automated
		wut_smooth.setParameterT(1, 151.7); // control::smoothed_parameter::SmoothingTime
		wut_smooth.setParameterT(2, 1.);    // control::smoothed_parameter::Enabled
		
		;                                     // Punch_smooth::Value is automated
		Punch_smooth.setParameterT(1, 250.6); // control::smoothed_parameter::SmoothingTime
		Punch_smooth.setParameterT(2, 1.);    // control::smoothed_parameter::Enabled
		
		;                                      // minmax1::Value is automated
		minmax1.setParameterT(1, 6.66134e-16); // control::minmax::Minimum
		minmax1.setParameterT(2, 9.24388);     // control::minmax::Maximum
		minmax1.setParameterT(3, 1.);          // control::minmax::Skew
		minmax1.setParameterT(4, 0.);          // control::minmax::Step
		minmax1.setParameterT(5, 0.);          // control::minmax::Polarity
		
		;                                      // minmax2::Value is automated
		minmax2.setParameterT(1, 6.66134e-16); // control::minmax::Minimum
		minmax2.setParameterT(2, 6.98184);     // control::minmax::Maximum
		minmax2.setParameterT(3, 1.);          // control::minmax::Skew
		minmax2.setParameterT(4, 0.);          // control::minmax::Step
		minmax2.setParameterT(5, 0.);          // control::minmax::Polarity
		
		;                                  // minmax::Value is automated
		minmax.setParameterT(1, -8.9);     // control::minmax::Minimum
		minmax.setParameterT(2, 0.);       // control::minmax::Maximum
		minmax.setParameterT(3, 0.376976); // control::minmax::Skew
		minmax.setParameterT(4, 0.1);      // control::minmax::Step
		minmax.setParameterT(5, 1.);       // control::minmax::Polarity
		
		;                          // pma1::Value is automated
		;                          // pma1::Multiply is automated
		pma1.setParameterT(2, 0.); // control::pma::Add
		
		; // dry_wet1::DryWet is automated
		
		; // dry_wet_mixer::Value is automated
		
		;                               // dry_gain::Gain is automated
		dry_gain.setParameterT(1, 20.); // core::gain::Smoothing
		dry_gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                         // pma::Value is automated
		pma.setParameterT(1, 1.); // control::pma::Multiply
		pma.setParameterT(2, 0.); // control::pma::Add
		
		;                           // Drive::Drive is automated
		Drive.setParameterT(1, 0.); // project::Drive::Highpass
		Drive.setParameterT(2, 1.); // project::Drive::OutLevel
		Drive.setParameterT(3, 1.); // project::Drive::DryWet
		
		Tube2.setParameterT(0, 0.496235); // project::Tube2::Input
		;                                 // Tube2::Tube is automated
		
		Tube3.setParameterT(0, 0.5); // project::Tube2::Input
		;                            // Tube3::Tube is automated
		
		;                               // faust::Attack is automated
		;                               // faust::Sustain is automated
		faust.setParameterT(2, 10.);    // core::faust::LowCutoff
		faust.setParameterT(3, 20000.); // core::faust::HighCutoff
		faust.setParameterT(4, 0.);     // core::faust::Monitorselectedband
		
		;                              // DrumSlam::Drive is automated
		DrumSlam.setParameterT(1, 1.); // project::DrumSlam::Output
		DrumSlam.setParameterT(2, 1.); // project::DrumSlam::DryWet
		
		freq_split3.setParameterT(0, 239.723); // container::split::Band1
		
		;                           // lr1_1::Frequency is automated
		lr1_1.setParameterT(1, 0.); // jdsp::jlinkwitzriley::Type
		
		Logical4.setParameterT(0, 0.533094); // project::Logical4::Threshold
		Logical4.setParameterT(1, 0.44055);  // project::Logical4::Ratio
		Logical4.setParameterT(2, 0.515527); // project::Logical4::Speed
		Logical4.setParameterT(3, 0.633506); // project::Logical4::MakeupGn
		Logical4.setParameterT(4, 1.);       // project::Logical4::DryWet
		
		;                           // lr2_1::Frequency is automated
		lr2_1.setParameterT(1, 1.); // jdsp::jlinkwitzriley::Type
		
		Logical5.setParameterT(0, 0.588743); // project::Logical4::Threshold
		Logical5.setParameterT(1, 0.483146); // project::Logical4::Ratio
		Logical5.setParameterT(2, 0.776583); // project::Logical4::Speed
		Logical5.setParameterT(3, 0.656789); // project::Logical4::MakeupGn
		Logical5.setParameterT(4, 1.);       // project::Logical4::DryWet
		
		gain1.setParameterT(0, -5.1); // core::gain::Gain
		gain1.setParameterT(1, 20.);  // core::gain::Smoothing
		gain1.setParameterT(2, 0.);   // core::gain::ResetValue
		
		Focus.setParameterT(0, 0.); // project::Focus::Boost
		Focus.setParameterT(1, 0.); // project::Focus::Focus
		Focus.setParameterT(2, 0.); // project::Focus::Mode
		Focus.setParameterT(3, 1.); // project::Focus::Output
		Focus.setParameterT(4, 1.); // project::Focus::DryWet
		
		;                           // gain::Gain is automated
		gain.setParameterT(1, 20.); // core::gain::Smoothing
		gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                               // wet_gain::Gain is automated
		wet_gain.setParameterT(1, 20.); // core::gain::Smoothing
		wet_gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		this->setParameterT(0, 0.713616);
		this->setParameterT(1, 0.531325);
		this->setParameterT(2, 1.);
		this->setParameterT(3, 0.);
	}
	
	static constexpr bool isPolyphonic() { return NV > 1; };
	
	static constexpr bool hasTail() { return true; };
	
	static constexpr bool isSuspendedOnSilence() { return false; };
};
}

#undef getT
#undef connectT
#undef setParameterT
#undef setParameterWT
#undef getParameterT
// ======================================| Public Definition |======================================

namespace project
{
// polyphonic template declaration

template <int NV>
using Boxer = wrap::node<Boxer_impl::instance<NV>>;
}


