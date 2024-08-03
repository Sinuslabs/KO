#pragma once

#include "Mojo.h"
#include "Mojo.h"
#include "Tube2.h"
// These will improve the readability of the connection definition

#define getT(Idx) template get<Idx>()
#define connectT(Idx, target) template connect<Idx>(target)
#define getParameterT(Idx) template getParameter<Idx>()
#define setParameterT(Idx, value) template setParameter<Idx>(value)
#define setParameterWT(Idx, value) template setWrapParameter<Idx>(value)
using namespace scriptnode;
using namespace snex;
using namespace snex::Types;

namespace Sumo_impl
{
// ==============================| Node & Parameter type declarations |==============================

template <int NV>
using mojo1_t = control::pma<NV, 
                             parameter::plain<project::Mojo<NV>, 0>>;

template <int NV>
using minmax_t = control::minmax<NV, 
                                 parameter::plain<core::gain<NV>, 0>>;

template <int NV> using pma_t = mojo1_t<NV>;

template <int NV>
using smoothed_parameter_mod = parameter::chain<ranges::Identity, 
                                                parameter::plain<mojo1_t<NV>, 0>, 
                                                parameter::plain<minmax_t<NV>, 0>, 
                                                parameter::plain<pma_t<NV>, 0>>;

template <int NV>
using smoothed_parameter_t = wrap::mod<smoothed_parameter_mod<NV>, 
                                       control::smoothed_parameter<NV, smoothers::linear_ramp<NV>>>;

template <int NV>
using minmax1_mod = parameter::chain<ranges::Identity, 
                                     parameter::plain<filters::svf_eq<NV>, 0>, 
                                     parameter::plain<filters::svf_eq<NV>, 0>>;

template <int NV>
using minmax1_t = control::minmax<NV, minmax1_mod<NV>>;

template <int NV>
using minmax2_t = control::minmax<NV, 
                                  parameter::plain<filters::svf_eq<NV>, 1>>;

template <int NV> using minmax3_t = minmax2_t<NV>;

template <int NV>
using smoothed_parameter2_mod = parameter::chain<ranges::Identity, 
                                                 parameter::plain<minmax1_t<NV>, 0>, 
                                                 parameter::plain<minmax2_t<NV>, 0>, 
                                                 parameter::plain<minmax3_t<NV>, 0>>;

template <int NV>
using smoothed_parameter2_t = wrap::mod<smoothed_parameter2_mod<NV>, 
                                        control::smoothed_parameter<NV, smoothers::linear_ramp<NV>>>;

template <int NV>
using minmax4_t = control::minmax<NV, 
                                  parameter::plain<fx::sampleandhold<NV>, 0>>;

template <int NV>
using split_t = container::split<parameter::empty, 
                                 wrap::fix<1, mojo1_t<NV>>, 
                                 pma_t<NV>, 
                                 minmax1_t<NV>, 
                                 minmax2_t<NV>, 
                                 minmax3_t<NV>, 
                                 minmax4_t<NV>>;

template <int NV>
using split1_t = container::split<parameter::empty, 
                                  wrap::fix<1, minmax_t<NV>>>;

template <int NV>
using modchain_t_ = container::chain<parameter::empty, 
                                     wrap::fix<1, split_t<NV>>, 
                                     split1_t<NV>>;

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
using chain_t = container::chain<parameter::empty, 
                                 wrap::fix<2, project::Mojo<NV>>, 
                                 project::Mojo<NV>>;

template <int NV> using dry_wet_mixer1_c0 = dry_wet_mixer_c0<NV>;

template <int NV> using dry_wet_mixer1_c1 = dry_wet_mixer_c0<NV>;

template <int NV>
using dry_wet_mixer1_multimod = parameter::list<dry_wet_mixer1_c0<NV>, dry_wet_mixer1_c1<NV>>;

template <int NV>
using dry_wet_mixer1_t = control::xfader<dry_wet_mixer1_multimod<NV>, 
                                         faders::cosine_half>;

template <int NV>
using dry_path1_t = container::chain<parameter::empty, 
                                     wrap::fix<2, dry_wet_mixer1_t<NV>>, 
                                     core::gain<NV>>;

template <int NV>
using wet_path1_t = container::chain<parameter::empty, 
                                     wrap::fix<2, filters::svf_eq<NV>>, 
                                     filters::svf_eq<NV>, 
                                     core::gain<NV>>;

namespace dry_wet2_t_parameters
{
}

template <int NV>
using dry_wet2_t = container::split<parameter::plain<Sumo_impl::dry_wet_mixer1_t<NV>, 0>, 
                                    wrap::fix<2, dry_path1_t<NV>>, 
                                    wet_path1_t<NV>>;

template <int NV>
using Stomp_t = container::chain<parameter::empty, 
                                 wrap::fix<2, dry_wet2_t<NV>>>;

template <int NV>
using wet_path_t = container::chain<parameter::empty, 
                                    wrap::fix<2, chain_t<NV>>, 
                                    project::Tube2<NV>, 
                                    Stomp_t<NV>, 
                                    fx::sampleandhold<NV>, 
                                    core::gain<NV>, 
                                    core::gain<NV>>;

namespace dry_wet1_t_parameters
{
}

template <int NV>
using dry_wet1_t = container::split<parameter::plain<Sumo_impl::dry_wet_mixer_t<NV>, 0>, 
                                    wrap::fix<2, dry_path_t<NV>>, 
                                    wet_path_t<NV>>;

namespace Sumo_t_parameters
{
// Parameter list for Sumo_impl::Sumo_t ------------------------------------------------------------

template <int NV>
using Heavy = parameter::plain<Sumo_impl::smoothed_parameter_t<NV>, 
                               0>;
template <int NV>
using Mix = parameter::plain<Sumo_impl::dry_wet1_t<NV>, 
                             0>;
template <int NV>
using Weight = parameter::plain<project::Tube2<NV>, 1>;
template <int NV>
using Stomp = parameter::plain<Sumo_impl::smoothed_parameter2_t<NV>, 
                               0>;
template <int NV>
using Crush = parameter::plain<Sumo_impl::minmax4_t<NV>, 
                               0>;
template <int NV>
using Sumo_t_plist = parameter::list<Heavy<NV>, 
                                     Mix<NV>, 
                                     Weight<NV>, 
                                     Stomp<NV>, 
                                     Crush<NV>>;
}

template <int NV>
using Sumo_t_ = container::chain<Sumo_t_parameters::Sumo_t_plist<NV>, 
                                 wrap::fix<2, smoothed_parameter_t<NV>>, 
                                 smoothed_parameter2_t<NV>, 
                                 modchain_t<NV>, 
                                 dry_wet1_t<NV>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public Sumo_impl::Sumo_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(Sumo);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(78)
		{
			0x005B, 0x0000, 0x4800, 0x6165, 0x7976, 0x0000, 0x0000, 0x0000, 
            0x8000, 0x003F, 0x8000, 0x003F, 0x8000, 0x003F, 0x0000, 0x5B00, 
            0x0001, 0x0000, 0x694D, 0x0078, 0x0000, 0x0000, 0x0000, 0x3F80, 
            0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x0000, 0x025B, 0x0000, 
            0x5700, 0x6965, 0x6867, 0x0074, 0x0000, 0x0000, 0x0000, 0x3F80, 
            0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x0000, 0x035B, 0x0000, 
            0x5300, 0x6F74, 0x706D, 0x0000, 0x0000, 0x0000, 0x8000, 0x003F, 
            0x8000, 0x003F, 0x8000, 0x003F, 0x0000, 0x5B00, 0x0004, 0x0000, 
            0x7243, 0x7375, 0x0068, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 
            0x3F80, 0x0000, 0x3F80, 0x0000, 0x0000, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& smoothed_parameter = this->getT(0);                                     // Sumo_impl::smoothed_parameter_t<NV>
		auto& smoothed_parameter2 = this->getT(1);                                    // Sumo_impl::smoothed_parameter2_t<NV>
		auto& modchain = this->getT(2);                                               // Sumo_impl::modchain_t<NV>
		auto& split = this->getT(2).getT(0);                                          // Sumo_impl::split_t<NV>
		auto& mojo1 = this->getT(2).getT(0).getT(0);                                  // Sumo_impl::mojo1_t<NV>
		auto& pma = this->getT(2).getT(0).getT(1);                                    // Sumo_impl::pma_t<NV>
		auto& minmax1 = this->getT(2).getT(0).getT(2);                                // Sumo_impl::minmax1_t<NV>
		auto& minmax2 = this->getT(2).getT(0).getT(3);                                // Sumo_impl::minmax2_t<NV>
		auto& minmax3 = this->getT(2).getT(0).getT(4);                                // Sumo_impl::minmax3_t<NV>
		auto& minmax4 = this->getT(2).getT(0).getT(5);                                // Sumo_impl::minmax4_t<NV>
		auto& split1 = this->getT(2).getT(1);                                         // Sumo_impl::split1_t<NV>
		auto& minmax = this->getT(2).getT(1).getT(0);                                 // Sumo_impl::minmax_t<NV>
		auto& dry_wet1 = this->getT(3);                                               // Sumo_impl::dry_wet1_t<NV>
		auto& dry_path = this->getT(3).getT(0);                                       // Sumo_impl::dry_path_t<NV>
		auto& dry_wet_mixer = this->getT(3).getT(0).getT(0);                          // Sumo_impl::dry_wet_mixer_t<NV>
		auto& dry_gain = this->getT(3).getT(0).getT(1);                               // core::gain<NV>
		auto& wet_path = this->getT(3).getT(1);                                       // Sumo_impl::wet_path_t<NV>
		auto& chain = this->getT(3).getT(1).getT(0);                                  // Sumo_impl::chain_t<NV>
		auto& Mojo = this->getT(3).getT(1).getT(0).getT(0);                           // project::Mojo<NV>
		auto& Mojo1 = this->getT(3).getT(1).getT(0).getT(1);                          // project::Mojo<NV>
		auto& Tube2 = this->getT(3).getT(1).getT(1);                                  // project::Tube2<NV>
		auto& Stomp = this->getT(3).getT(1).getT(2);                                  // Sumo_impl::Stomp_t<NV>
		auto& dry_wet2 = this->getT(3).getT(1).getT(2).getT(0);                       // Sumo_impl::dry_wet2_t<NV>
		auto& dry_path1 = this->getT(3).getT(1).getT(2).getT(0).getT(0);              // Sumo_impl::dry_path1_t<NV>
		auto& dry_wet_mixer1 = this->getT(3).getT(1).getT(2).getT(0).getT(0).getT(0); // Sumo_impl::dry_wet_mixer1_t<NV>
		auto& dry_gain1 = this->getT(3).getT(1).getT(2).getT(0).getT(0).getT(1);      // core::gain<NV>
		auto& wet_path1 = this->getT(3).getT(1).getT(2).getT(0).getT(1);              // Sumo_impl::wet_path1_t<NV>
		auto& svf_eq = this->getT(3).getT(1).getT(2).getT(0).getT(1).getT(0);         // filters::svf_eq<NV>
		auto& svf_eq1 = this->getT(3).getT(1).getT(2).getT(0).getT(1).getT(1);        // filters::svf_eq<NV>
		auto& wet_gain1 = this->getT(3).getT(1).getT(2).getT(0).getT(1).getT(2);      // core::gain<NV>
		auto& sampleandhold = this->getT(3).getT(1).getT(3);                          // fx::sampleandhold<NV>
		auto& gain = this->getT(3).getT(1).getT(4);                                   // core::gain<NV>
		auto& wet_gain = this->getT(3).getT(1).getT(5);                               // core::gain<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		dry_wet2.getParameterT(0).connectT(0, dry_wet_mixer1);  // DryWet -> dry_wet_mixer1::Value
		dry_wet1.getParameterT(0).connectT(0, dry_wet_mixer);   // DryWet -> dry_wet_mixer::Value
		this->getParameterT(0).connectT(0, smoothed_parameter); // Heavy -> smoothed_parameter::Value
		
		this->getParameterT(1).connectT(0, dry_wet1); // Mix -> dry_wet1::DryWet
		
		this->getParameterT(2).connectT(0, Tube2); // Weight -> Tube2::Tube
		
		this->getParameterT(3).connectT(0, smoothed_parameter2); // Stomp -> smoothed_parameter2::Value
		
		this->getParameterT(4).connectT(0, minmax4); // Crush -> minmax4::Value
		
		// Modulation Connections ------------------------------------------------------------------
		
		mojo1.getWrappedObject().getParameter().connectT(0, Mojo);            // mojo1 -> Mojo::Input
		minmax.getWrappedObject().getParameter().connectT(0, gain);           // minmax -> gain::Gain
		pma.getWrappedObject().getParameter().connectT(0, Mojo1);             // pma -> Mojo1::Input
		smoothed_parameter.getParameter().connectT(0, mojo1);                 // smoothed_parameter -> mojo1::Value
		smoothed_parameter.getParameter().connectT(1, minmax);                // smoothed_parameter -> minmax::Value
		smoothed_parameter.getParameter().connectT(2, pma);                   // smoothed_parameter -> pma::Value
		minmax1.getWrappedObject().getParameter().connectT(0, svf_eq);        // minmax1 -> svf_eq::Frequency
		minmax1.getWrappedObject().getParameter().connectT(1, svf_eq1);       // minmax1 -> svf_eq1::Frequency
		minmax2.getWrappedObject().getParameter().connectT(0, svf_eq);        // minmax2 -> svf_eq::Q
		minmax3.getWrappedObject().getParameter().connectT(0, svf_eq1);       // minmax3 -> svf_eq1::Q
		smoothed_parameter2.getParameter().connectT(0, minmax1);              // smoothed_parameter2 -> minmax1::Value
		smoothed_parameter2.getParameter().connectT(1, minmax2);              // smoothed_parameter2 -> minmax2::Value
		smoothed_parameter2.getParameter().connectT(2, minmax3);              // smoothed_parameter2 -> minmax3::Value
		minmax4.getWrappedObject().getParameter().connectT(0, sampleandhold); // minmax4 -> sampleandhold::Counter
		auto& dry_wet_mixer_p = dry_wet_mixer.getWrappedObject().getParameter();
		dry_wet_mixer_p.getParameterT(0).connectT(0, dry_gain); // dry_wet_mixer -> dry_gain::Gain
		dry_wet_mixer_p.getParameterT(1).connectT(0, wet_gain); // dry_wet_mixer -> wet_gain::Gain
		auto& dry_wet_mixer1_p = dry_wet_mixer1.getWrappedObject().getParameter();
		dry_wet_mixer1_p.getParameterT(0).connectT(0, dry_gain1); // dry_wet_mixer1 -> dry_gain1::Gain
		dry_wet_mixer1_p.getParameterT(1).connectT(0, wet_gain1); // dry_wet_mixer1 -> wet_gain1::Gain
		
		// Default Values --------------------------------------------------------------------------
		
		;                                          // smoothed_parameter::Value is automated
		smoothed_parameter.setParameterT(1, 100.); // control::smoothed_parameter::SmoothingTime
		smoothed_parameter.setParameterT(2, 1.);   // control::smoothed_parameter::Enabled
		
		;                                           // smoothed_parameter2::Value is automated
		smoothed_parameter2.setParameterT(1, 100.); // control::smoothed_parameter::SmoothingTime
		smoothed_parameter2.setParameterT(2, 1.);   // control::smoothed_parameter::Enabled
		
		;                                 // mojo1::Value is automated
		mojo1.setParameterT(1, 0.798844); // control::pma::Multiply
		mojo1.setParameterT(2, 0.497479); // control::pma::Add
		
		;                               // pma::Value is automated
		pma.setParameterT(1, 0.350428); // control::pma::Multiply
		pma.setParameterT(2, 0.297274); // control::pma::Add
		
		;                                   // minmax1::Value is automated
		minmax1.setParameterT(1, 5855.78);  // control::minmax::Minimum
		minmax1.setParameterT(2, 20000.);   // control::minmax::Maximum
		minmax1.setParameterT(3, 0.229905); // control::minmax::Skew
		minmax1.setParameterT(4, 0.);       // control::minmax::Step
		minmax1.setParameterT(5, 1.);       // control::minmax::Polarity
		
		;                                  // minmax2::Value is automated
		minmax2.setParameterT(1, 1.);      // control::minmax::Minimum
		minmax2.setParameterT(2, 1.72802); // control::minmax::Maximum
		minmax2.setParameterT(3, 1.);      // control::minmax::Skew
		minmax2.setParameterT(4, 0.);      // control::minmax::Step
		minmax2.setParameterT(5, 1.);      // control::minmax::Polarity
		
		;                                   // minmax3::Value is automated
		minmax3.setParameterT(1, 0.827526); // control::minmax::Minimum
		minmax3.setParameterT(2, 1.08811);  // control::minmax::Maximum
		minmax3.setParameterT(3, 1.);       // control::minmax::Skew
		minmax3.setParameterT(4, 0.);       // control::minmax::Step
		minmax3.setParameterT(5, 1.);       // control::minmax::Polarity
		
		;                                  // minmax4::Value is automated
		minmax4.setParameterT(1, 0.);      // control::minmax::Minimum
		minmax4.setParameterT(2, 2.89084); // control::minmax::Maximum
		minmax4.setParameterT(3, 1.);      // control::minmax::Skew
		minmax4.setParameterT(4, 0.);      // control::minmax::Step
		minmax4.setParameterT(5, 0.);      // control::minmax::Polarity
		
		;                                 // minmax::Value is automated
		minmax.setParameterT(1, -10.);    // control::minmax::Minimum
		minmax.setParameterT(2, 0.);      // control::minmax::Maximum
		minmax.setParameterT(3, 0.46819); // control::minmax::Skew
		minmax.setParameterT(4, 0.1);     // control::minmax::Step
		minmax.setParameterT(5, 1.);      // control::minmax::Polarity
		
		; // dry_wet1::DryWet is automated
		
		; // dry_wet_mixer::Value is automated
		
		;                               // dry_gain::Gain is automated
		dry_gain.setParameterT(1, 20.); // core::gain::Smoothing
		dry_gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		; // Mojo::Input is automated
		
		; // Mojo1::Input is automated
		
		Tube2.setParameterT(0, 0.5); // project::Tube2::Input
		;                            // Tube2::Tube is automated
		
		dry_wet2.setParameterT(0, 0.505539); // container::split::DryWet
		
		; // dry_wet_mixer1::Value is automated
		
		;                                // dry_gain1::Gain is automated
		dry_gain1.setParameterT(1, 20.); // core::gain::Smoothing
		dry_gain1.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                                   // svf_eq::Frequency is automated
		;                                   // svf_eq::Q is automated
		svf_eq.setParameterT(2, 0.0556348); // filters::svf_eq::Gain
		svf_eq.setParameterT(3, 0.01);      // filters::svf_eq::Smoothing
		svf_eq.setParameterT(4, 0.);        // filters::svf_eq::Mode
		svf_eq.setParameterT(5, 1.);        // filters::svf_eq::Enabled
		
		;                               // svf_eq1::Frequency is automated
		;                               // svf_eq1::Q is automated
		svf_eq1.setParameterT(2, 0.);   // filters::svf_eq::Gain
		svf_eq1.setParameterT(3, 0.01); // filters::svf_eq::Smoothing
		svf_eq1.setParameterT(4, 0.);   // filters::svf_eq::Mode
		svf_eq1.setParameterT(5, 1.);   // filters::svf_eq::Enabled
		
		;                                // wet_gain1::Gain is automated
		wet_gain1.setParameterT(1, 20.); // core::gain::Smoothing
		wet_gain1.setParameterT(2, 0.);  // core::gain::ResetValue
		
		; // sampleandhold::Counter is automated
		
		;                           // gain::Gain is automated
		gain.setParameterT(1, 20.); // core::gain::Smoothing
		gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                               // wet_gain::Gain is automated
		wet_gain.setParameterT(1, 20.); // core::gain::Smoothing
		wet_gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		this->setParameterT(0, 1.);
		this->setParameterT(1, 1.);
		this->setParameterT(2, 1.);
		this->setParameterT(3, 1.);
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
using Sumo = wrap::node<Sumo_impl::instance<NV>>;
}


