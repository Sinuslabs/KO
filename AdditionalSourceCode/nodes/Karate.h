#pragma once

#include "Pressure5.h"
#include "Focus.h"
#include "ClipSoftly.h"
// These will improve the readability of the connection definition

#define getT(Idx) template get<Idx>()
#define connectT(Idx, target) template connect<Idx>(target)
#define getParameterT(Idx) template getParameter<Idx>()
#define setParameterT(Idx, value) template setParameter<Idx>(value)
#define setParameterWT(Idx, value) template setWrapParameter<Idx>(value)
using namespace scriptnode;
using namespace snex;
using namespace snex::Types;

namespace Karate_impl
{
// ==============================| Node & Parameter type declarations |==============================

DECLARE_PARAMETER_RANGE_SKEW(dry_wet_mixer1_c0Range, 
                             -100., 
                             0., 
                             5.42227);

template <int NV>
using dry_wet_mixer1_c0 = parameter::from0To1<core::gain<NV>, 
                                              0, 
                                              dry_wet_mixer1_c0Range>;

template <int NV> using dry_wet_mixer1_c1 = dry_wet_mixer1_c0<NV>;

template <int NV>
using dry_wet_mixer1_multimod = parameter::list<dry_wet_mixer1_c0<NV>, dry_wet_mixer1_c1<NV>>;

template <int NV>
using dry_wet_mixer1_t = control::xfader<dry_wet_mixer1_multimod<NV>, 
                                         faders::linear>;

template <int NV>
using dry_path1_t = container::chain<parameter::empty, 
                                     wrap::fix<2, dry_wet_mixer1_t<NV>>, 
                                     core::gain<NV>>;

using band1_t = container::chain<parameter::empty, 
                                 wrap::fix<2, jdsp::jlinkwitzriley>>;

template <int NV>
using band2_t = container::chain<parameter::empty, 
                                 wrap::fix<2, jdsp::jlinkwitzriley>, 
                                 fx::reverb, 
                                 core::gain<NV>>;

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
                                       wrap::fix<2, band1_t>, 
                                       band2_t<NV>>;

template <int NV>
using wet_path1_t = container::chain<parameter::empty, 
                                     wrap::fix<2, freq_split3_t<NV>>, 
                                     core::gain<NV>>;

namespace dry_wet2_t_parameters
{
}

template <int NV>
using dry_wet2_t = container::split<parameter::plain<Karate_impl::dry_wet_mixer1_t<NV>, 0>, 
                                    wrap::fix<2, dry_path1_t<NV>>, 
                                    wet_path1_t<NV>>;
template <int NV>
using air_t = control::minmax<NV, 
                              parameter::plain<dry_wet2_t<NV>, 0>>;

template <int NV>
using pma1_t = control::pma<NV, 
                            parameter::plain<project::Focus<NV>, 1>>;

template <int NV>
using pma2_t = control::pma<NV, 
                            parameter::plain<project::Focus<NV>, 0>>;

template <int NV>
using split_t = container::split<parameter::empty, 
                                 wrap::fix<1, air_t<NV>>, 
                                 pma1_t<NV>, 
                                 pma2_t<NV>, 
                                 control::minmax<NV, parameter::empty>>;

template <int NV>
using minmax1_t = control::minmax<NV, 
                                  parameter::plain<core::gain<NV>, 0>>;

template <int NV> using minmax_t = minmax1_t<NV>;

template <int NV>
using split1_t = container::split<parameter::empty, 
                                  wrap::fix<1, minmax1_t<NV>>, 
                                  minmax_t<NV>>;

template <int NV>
using modchain_t_ = container::chain<parameter::empty, 
                                     wrap::fix<1, split_t<NV>>, 
                                     split1_t<NV>>;

template <int NV>
using modchain_t = wrap::control_rate<modchain_t_<NV>>;

template <int NV> using dry_wet_mixer_c0 = dry_wet_mixer1_c0<NV>;

template <int NV> using dry_wet_mixer_c1 = dry_wet_mixer1_c0<NV>;

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
using chain_t = container::chain<parameter::empty, 
                                 wrap::fix<2, dry_wet2_t<NV>>>;

template <int NV>
using wet_path_t = container::chain<parameter::empty, 
                                    wrap::fix<2, project::Pressure5<NV>>, 
                                    core::gain<NV>, 
                                    project::Focus<NV>, 
                                    chain_t<NV>, 
                                    wrap::no_process<project::ClipSoftly<NV>>, 
                                    core::gain<NV>, 
                                    core::gain<NV>>;

namespace dry_wet1_t_parameters
{
}

template <int NV>
using dry_wet1_t = container::split<parameter::plain<Karate_impl::dry_wet_mixer_t<NV>, 0>, 
                                    wrap::fix<2, dry_path_t<NV>>, 
                                    wet_path_t<NV>>;

namespace Karate_t_parameters
{
// Parameter list for Karate_impl::Karate_t --------------------------------------------------------

template <int NV>
using Pressure = parameter::chain<ranges::Identity, 
                                  parameter::plain<project::Pressure5<NV>, 0>, 
                                  parameter::plain<Karate_impl::minmax1_t<NV>, 0>>;

template <int NV>
using Focus = parameter::plain<project::Pressure5<NV>, 3>;
template <int NV>
using Mix = parameter::plain<Karate_impl::dry_wet1_t<NV>, 
                             0>;
template <int NV>
using Air = parameter::plain<Karate_impl::air_t<NV>, 0>;
template <int NV>
using Speed = parameter::plain<project::Pressure5<NV>, 1>;
template <int NV>
using Karate_t_plist = parameter::list<Focus<NV>, 
                                       Mix<NV>, 
                                       Air<NV>, 
                                       Pressure<NV>, 
                                       Speed<NV>>;
}

template <int NV>
using Karate_t_ = container::chain<Karate_t_parameters::Karate_t_plist<NV>, 
                                   wrap::fix<2, modchain_t<NV>>, 
                                   dry_wet1_t<NV>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public Karate_impl::Karate_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(Karate);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(78)
		{
			0x005B, 0x0000, 0x4600, 0x636F, 0x7375, 0x0000, 0x0000, 0x0000, 
            0x8000, 0x003F, 0x8000, 0x003F, 0x8000, 0x003F, 0x0000, 0x5B00, 
            0x0001, 0x0000, 0x694D, 0x0078, 0x0000, 0x0000, 0x0000, 0x3F80, 
            0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x0000, 0x025B, 0x0000, 
            0x4100, 0x7269, 0x0000, 0x0000, 0x0000, 0x8000, 0x003F, 0x8000, 
            0x003F, 0x8000, 0x003F, 0x0000, 0x5B00, 0x0003, 0x0000, 0x7250, 
            0x7365, 0x7573, 0x6572, 0x0000, 0x0000, 0x0000, 0x8000, 0xA03F, 
            0x1B1B, 0x003F, 0x8000, 0x003F, 0x0000, 0x5B00, 0x0004, 0x0000, 
            0x7053, 0x6565, 0x0064, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 
            0x3F80, 0x0000, 0x3F80, 0x0000, 0x0000, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& modchain = this->getT(0);                                               // Karate_impl::modchain_t<NV>
		auto& split = this->getT(0).getT(0);                                          // Karate_impl::split_t<NV>
		auto& air = this->getT(0).getT(0).getT(0);                                    // Karate_impl::air_t<NV>
		auto& pma1 = this->getT(0).getT(0).getT(1);                                   // Karate_impl::pma1_t<NV>
		auto& pma2 = this->getT(0).getT(0).getT(2);                                   // Karate_impl::pma2_t<NV>
		auto& pressure_gain = this->getT(0).getT(0).getT(3);                          // control::minmax<NV, parameter::empty>
		auto& split1 = this->getT(0).getT(1);                                         // Karate_impl::split1_t<NV>
		auto& minmax1 = this->getT(0).getT(1).getT(0);                                // Karate_impl::minmax1_t<NV>
		auto& minmax = this->getT(0).getT(1).getT(1);                                 // Karate_impl::minmax_t<NV>
		auto& dry_wet1 = this->getT(1);                                               // Karate_impl::dry_wet1_t<NV>
		auto& dry_path = this->getT(1).getT(0);                                       // Karate_impl::dry_path_t<NV>
		auto& dry_wet_mixer = this->getT(1).getT(0).getT(0);                          // Karate_impl::dry_wet_mixer_t<NV>
		auto& dry_gain = this->getT(1).getT(0).getT(1);                               // core::gain<NV>
		auto& wet_path = this->getT(1).getT(1);                                       // Karate_impl::wet_path_t<NV>
		auto& Pressure5 = this->getT(1).getT(1).getT(0);                              // project::Pressure5<NV>
		auto& gain1 = this->getT(1).getT(1).getT(1);                                  // core::gain<NV>
		auto& Focus = this->getT(1).getT(1).getT(2);                                  // project::Focus<NV>
		auto& chain = this->getT(1).getT(1).getT(3);                                  // Karate_impl::chain_t<NV>
		auto& dry_wet2 = this->getT(1).getT(1).getT(3).getT(0);                       // Karate_impl::dry_wet2_t<NV>
		auto& dry_path1 = this->getT(1).getT(1).getT(3).getT(0).getT(0);              // Karate_impl::dry_path1_t<NV>
		auto& dry_wet_mixer1 = this->getT(1).getT(1).getT(3).getT(0).getT(0).getT(0); // Karate_impl::dry_wet_mixer1_t<NV>
		auto& dry_gain1 = this->getT(1).getT(1).getT(3).getT(0).getT(0).getT(1);      // core::gain<NV>
		auto& wet_path1 = this->getT(1).getT(1).getT(3).getT(0).getT(1);              // Karate_impl::wet_path1_t<NV>
		auto& freq_split3 = this->getT(1).getT(1).getT(3).getT(0).getT(1).getT(0);    // Karate_impl::freq_split3_t<NV>
		auto& band1 = this->getT(1).getT(1).getT(3).getT(0).getT(1).getT(0).getT(0);  // Karate_impl::band1_t
		auto& lr1_1 = this->getT(1).getT(1).getT(3).getT(0).                          // jdsp::jlinkwitzriley
                      getT(1).getT(0).getT(0).getT(0);
		auto& band2 = this->getT(1).getT(1).getT(3).getT(0).getT(1).getT(0).getT(1); // Karate_impl::band2_t<NV>
		auto& lr2_1 = this->getT(1).getT(1).getT(3).getT(0).                         // jdsp::jlinkwitzriley
                      getT(1).getT(0).getT(1).getT(0);
		auto& reverb = this->getT(1).getT(1).getT(3).getT(0).                    // fx::reverb
                       getT(1).getT(0).getT(1).getT(1);
		auto& gain2 = this->getT(1).getT(1).getT(3).getT(0).                     // core::gain<NV>
                      getT(1).getT(0).getT(1).getT(2);
		auto& wet_gain1 = this->getT(1).getT(1).getT(3).getT(0).getT(1).getT(1); // core::gain<NV>
		auto& ClipSoftly = this->getT(1).getT(1).getT(4);                        // wrap::no_process<project::ClipSoftly<NV>>
		auto& gain = this->getT(1).getT(1).getT(5);                              // core::gain<NV>
		auto& wet_gain = this->getT(1).getT(1).getT(6);                          // core::gain<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		auto& Band1_p = freq_split3.getParameterT(0);
		Band1_p.connectT(0, lr1_1);                            // Band1 -> lr1_1::Frequency
		Band1_p.connectT(1, lr2_1);                            // Band1 -> lr2_1::Frequency
		dry_wet2.getParameterT(0).connectT(0, dry_wet_mixer1); // DryWet -> dry_wet_mixer1::Value
		dry_wet2.getParameterT(0).connectT(0, dry_wet_mixer1); // DryWet -> dry_wet_mixer1::Value
		dry_wet1.getParameterT(0).connectT(0, dry_wet_mixer);  // DryWet -> dry_wet_mixer::Value
		this->getParameterT(0).connectT(0, Pressure5);         // Focus -> Pressure5::PawClaw
		
		this->getParameterT(1).connectT(0, dry_wet1); // Mix -> dry_wet1::DryWet
		
		this->getParameterT(2).connectT(0, air); // Air -> air::Value
		
		auto& Pressure_p = this->getParameterT(3);
		Pressure_p.connectT(0, Pressure5); // Pressure -> Pressure5::Pressre
		Pressure_p.connectT(1, minmax1);   // Pressure -> minmax1::Value
		
		this->getParameterT(4).connectT(0, Pressure5); // Speed -> Pressure5::Speed
		
		// Modulation Connections ------------------------------------------------------------------
		
		auto& dry_wet_mixer1_p = dry_wet_mixer1.getWrappedObject().getParameter();
		dry_wet_mixer1_p.getParameterT(0).connectT(0, dry_gain1);     // dry_wet_mixer1 -> dry_gain1::Gain
		dry_wet_mixer1_p.getParameterT(1).connectT(0, wet_gain1);     // dry_wet_mixer1 -> wet_gain1::Gain
		air.getWrappedObject().getParameter().connectT(0, dry_wet2);  // air -> dry_wet2::DryWet
		pma1.getWrappedObject().getParameter().connectT(0, Focus);    // pma1 -> Focus::Focus
		pma2.getWrappedObject().getParameter().connectT(0, Focus);    // pma2 -> Focus::Boost
		minmax1.getWrappedObject().getParameter().connectT(0, gain1); // minmax1 -> gain1::Gain
		minmax.getWrappedObject().getParameter().connectT(0, gain);   // minmax -> gain::Gain
		auto& dry_wet_mixer_p = dry_wet_mixer.getWrappedObject().getParameter();
		dry_wet_mixer_p.getParameterT(0).connectT(0, dry_gain); // dry_wet_mixer -> dry_gain::Gain
		dry_wet_mixer_p.getParameterT(1).connectT(0, wet_gain); // dry_wet_mixer -> wet_gain::Gain
		
		// Default Values --------------------------------------------------------------------------
		
		;                               // air::Value is automated
		air.setParameterT(1, 0.);       // control::minmax::Minimum
		air.setParameterT(2, 0.141678); // control::minmax::Maximum
		air.setParameterT(3, 0.658886); // control::minmax::Skew
		air.setParameterT(4, 0.);       // control::minmax::Step
		air.setParameterT(5, 0.);       // control::minmax::Polarity
		
		pma1.setParameterT(0, 0.);          // control::pma::Value
		pma1.setParameterT(1, 0.124434);    // control::pma::Multiply
		pma1.setParameterT(2, -0.00294629); // control::pma::Add
		
		pma2.setParameterT(0, 0.);       // control::pma::Value
		pma2.setParameterT(1, 0.558909); // control::pma::Multiply
		pma2.setParameterT(2, 0.);       // control::pma::Add
		
		pressure_gain.setParameterT(0, 0.); // control::minmax::Value
		pressure_gain.setParameterT(1, 0.); // control::minmax::Minimum
		pressure_gain.setParameterT(2, 1.); // control::minmax::Maximum
		pressure_gain.setParameterT(3, 1.); // control::minmax::Skew
		pressure_gain.setParameterT(4, 0.); // control::minmax::Step
		pressure_gain.setParameterT(5, 0.); // control::minmax::Polarity
		
		;                                   // minmax1::Value is automated
		minmax1.setParameterT(1, -0.8);     // control::minmax::Minimum
		minmax1.setParameterT(2, 0.);       // control::minmax::Maximum
		minmax1.setParameterT(3, 0.100374); // control::minmax::Skew
		minmax1.setParameterT(4, 0.1);      // control::minmax::Step
		minmax1.setParameterT(5, 1.);       // control::minmax::Polarity
		
		minmax.setParameterT(0, 0.);      // control::minmax::Value
		minmax.setParameterT(1, -4.2);    // control::minmax::Minimum
		minmax.setParameterT(2, 0.);      // control::minmax::Maximum
		minmax.setParameterT(3, 5.42227); // control::minmax::Skew
		minmax.setParameterT(4, 0.1);     // control::minmax::Step
		minmax.setParameterT(5, 1.);      // control::minmax::Polarity
		
		; // dry_wet1::DryWet is automated
		
		; // dry_wet_mixer::Value is automated
		
		;                               // dry_gain::Gain is automated
		dry_gain.setParameterT(1, 20.); // core::gain::Smoothing
		dry_gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                                // Pressure5::Pressre is automated
		;                                // Pressure5::Speed is automated
		Pressure5.setParameterT(2, 0.);  // project::Pressure5::Mewines
		;                                // Pressure5::PawClaw is automated
		Pressure5.setParameterT(4, 0.5); // project::Pressure5::Output
		Pressure5.setParameterT(5, 1.);  // project::Pressure5::DryWet
		
		;                            // gain1::Gain is automated
		gain1.setParameterT(1, 20.); // core::gain::Smoothing
		gain1.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                                 // Focus::Boost is automated
		;                                 // Focus::Focus is automated
		Focus.setParameterT(2, 0.329293); // project::Focus::Mode
		Focus.setParameterT(3, 1.);       // project::Focus::Output
		Focus.setParameterT(4, 1.);       // project::Focus::DryWet
		
		; // dry_wet2::DryWet is automated
		
		; // dry_wet_mixer1::Value is automated
		
		;                                // dry_gain1::Gain is automated
		dry_gain1.setParameterT(1, 20.); // core::gain::Smoothing
		dry_gain1.setParameterT(2, 0.);  // core::gain::ResetValue
		
		freq_split3.setParameterT(0, 473.743); // container::split::Band1
		
		;                           // lr1_1::Frequency is automated
		lr1_1.setParameterT(1, 0.); // jdsp::jlinkwitzriley::Type
		
		;                           // lr2_1::Frequency is automated
		lr2_1.setParameterT(1, 1.); // jdsp::jlinkwitzriley::Type
		
		reverb.setParameterT(0, 0.189535); // fx::reverb::Damping
		reverb.setParameterT(1, 0.401075); // fx::reverb::Width
		reverb.setParameterT(2, 0.18788);  // fx::reverb::Size
		
		gain2.setParameterT(0, 27.4); // core::gain::Gain
		gain2.setParameterT(1, 20.);  // core::gain::Smoothing
		gain2.setParameterT(2, 0.);   // core::gain::ResetValue
		
		;                                // wet_gain1::Gain is automated
		wet_gain1.setParameterT(1, 20.); // core::gain::Smoothing
		wet_gain1.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                           // gain::Gain is automated
		gain.setParameterT(1, 20.); // core::gain::Smoothing
		gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                               // wet_gain::Gain is automated
		wet_gain.setParameterT(1, 20.); // core::gain::Smoothing
		wet_gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		this->setParameterT(0, 1.);
		this->setParameterT(1, 1.);
		this->setParameterT(2, 1.);
		this->setParameterT(3, 0.60589);
		this->setParameterT(4, 1.);
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
using Karate = wrap::node<Karate_impl::instance<NV>>;
}


