#pragma once

#include "Tube2.h"
#include "Tube2.h"
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
using pma_t = control::pma<NV, 
                           parameter::plain<project::Tube2<NV>, 1>>;
template <int NV>
using envelope_follower_t = wrap::mod<parameter::plain<pma_t<NV>, 0>, 
                                      wrap::no_data<dynamics::envelope_follower>>;
template <int NV>
using minmax1_t = control::minmax<NV, 
                                  parameter::plain<envelope_follower_t<NV>, 0>>;

template <int NV>
using minmax2_t = control::minmax<NV, 
                                  parameter::plain<envelope_follower_t<NV>, 1>>;

using faust_multimod = parameter::list<parameter::empty>;

template <int NV>
using faust_t = project::Transient<NV, faust_multimod>;
DECLARE_PARAMETER_RANGE_STEP(Attack_modRange, 
                             -12., 
                             12., 
                             0.1);

template <int NV>
using Attack_mod = parameter::from0To1<faust_t<NV>, 
                                       0, 
                                       Attack_modRange>;

template <int NV>
using Attack_t = control::pma<NV, Attack_mod<NV>>;

template <int NV>
using sustain_mod = parameter::from0To1<faust_t<NV>, 
                                        1, 
                                        Attack_modRange>;

template <int NV>
using sustain_t = control::pma<NV, sustain_mod<NV>>;

template <int NV> using pma1_t = pma_t<NV>;

template <int NV>
using pma2_t = control::pma<NV, 
                            parameter::plain<project::Focus<NV>, 0>>;

template <int NV>
using minmax_t = control::minmax<NV, 
                                 parameter::plain<core::gain<NV>, 0>>;

template <int NV>
using split_t = container::split<parameter::empty, 
                                 wrap::fix<1, minmax1_t<NV>>, 
                                 minmax2_t<NV>, 
                                 Attack_t<NV>, 
                                 sustain_t<NV>, 
                                 pma1_t<NV>, 
                                 pma2_t<NV>, 
                                 minmax_t<NV>>;

template <int NV>
using modchain_t_ = container::chain<parameter::empty, 
                                     wrap::fix<1, split_t<NV>>>;

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
                                 wrap::fix<2, pma_t<NV>>, 
                                 faust_t<NV>, 
                                 project::Tube2<NV>, 
                                 project::Tube2<NV>, 
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
using Punch = parameter::chain<ranges::Identity, 
                               parameter::plain<Boxer_impl::Attack_t<NV>, 0>, 
                               parameter::plain<Boxer_impl::minmax_t<NV>, 0>, 
                               parameter::plain<Boxer_impl::sustain_t<NV>, 0>>;

template <int NV>
using Wut = parameter::chain<ranges::Identity, 
                             parameter::plain<Boxer_impl::pma1_t<NV>, 0>, 
                             parameter::plain<Boxer_impl::pma2_t<NV>, 0>>;

template <int NV>
using Speed = parameter::chain<ranges::Identity, 
                               parameter::plain<Boxer_impl::minmax1_t<NV>, 0>, 
                               parameter::plain<Boxer_impl::minmax2_t<NV>, 0>>;

template <int NV>
using Mix = parameter::plain<Boxer_impl::dry_wet1_t<NV>, 
                             0>;
template <int NV>
using Boxer_t_plist = parameter::list<Punch<NV>, 
                                      Wut<NV>, 
                                      Speed<NV>, 
                                      Mix<NV>>;
}

template <int NV>
using Boxer_t_ = container::chain<Boxer_t_parameters::Boxer_t_plist<NV>, 
                                  wrap::fix<2, modchain_t<NV>>, 
                                  envelope_follower_t<NV>, 
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
            0x8000, 0x003F, 0x0000, 0x0000, 0x8000, 0x003F, 0x0000, 0x5B00, 
            0x0001, 0x0000, 0x7557, 0x0074, 0x0000, 0x0000, 0x0000, 0x3F80, 
            0xE7AC, 0x3ED3, 0x0000, 0x3F80, 0x0000, 0x0000, 0x025B, 0x0000, 
            0x5300, 0x6570, 0x6465, 0x0000, 0x0000, 0x0000, 0x8000, 0xF63F, 
            0x2B7F, 0x003F, 0x8000, 0x003F, 0x0000, 0x5B00, 0x0003, 0x0000, 
            0x694D, 0x0078, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x3F80, 
            0x0000, 0x3F80, 0x0000, 0x0000, 0x0000, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& modchain = this->getT(0);                      // Boxer_impl::modchain_t<NV>
		auto& split = this->getT(0).getT(0);                 // Boxer_impl::split_t<NV>
		auto& minmax1 = this->getT(0).getT(0).getT(0);       // Boxer_impl::minmax1_t<NV>
		auto& minmax2 = this->getT(0).getT(0).getT(1);       // Boxer_impl::minmax2_t<NV>
		auto& Attack = this->getT(0).getT(0).getT(2);        // Boxer_impl::Attack_t<NV>
		auto& sustain = this->getT(0).getT(0).getT(3);       // Boxer_impl::sustain_t<NV>
		auto& pma1 = this->getT(0).getT(0).getT(4);          // Boxer_impl::pma1_t<NV>
		auto& pma2 = this->getT(0).getT(0).getT(5);          // Boxer_impl::pma2_t<NV>
		auto& minmax = this->getT(0).getT(0).getT(6);        // Boxer_impl::minmax_t<NV>
		auto& envelope_follower = this->getT(1);             // Boxer_impl::envelope_follower_t<NV>
		auto& dry_wet1 = this->getT(2);                      // Boxer_impl::dry_wet1_t<NV>
		auto& dry_path = this->getT(2).getT(0);              // Boxer_impl::dry_path_t<NV>
		auto& dry_wet_mixer = this->getT(2).getT(0).getT(0); // Boxer_impl::dry_wet_mixer_t<NV>
		auto& dry_gain = this->getT(2).getT(0).getT(1);      // core::gain<NV>
		auto& wet_path = this->getT(2).getT(1);              // Boxer_impl::wet_path_t<NV>
		auto& chain = this->getT(2).getT(1).getT(0);         // Boxer_impl::chain_t<NV>
		auto& pma = this->getT(2).getT(1).getT(0).getT(0);   // Boxer_impl::pma_t<NV>
		auto& faust = this->getT(2).getT(1).getT(0).getT(1); // Boxer_impl::faust_t<NV>
		auto& Tube2 = this->getT(2).getT(1).getT(0).getT(2); // project::Tube2<NV>
		auto& Tube3 = this->getT(2).getT(1).getT(0).getT(3); // project::Tube2<NV>
		auto& Focus = this->getT(2).getT(1).getT(0).getT(4); // project::Focus<NV>
		auto& gain = this->getT(2).getT(1).getT(0).getT(5);  // core::gain<NV>
		auto& wet_gain = this->getT(2).getT(1).getT(1);      // core::gain<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		dry_wet1.getParameterT(0).connectT(0, dry_wet_mixer); // DryWet -> dry_wet_mixer::Value
		auto& Punch_p = this->getParameterT(0);
		Punch_p.connectT(0, Attack);  // Punch -> Attack::Value
		Punch_p.connectT(1, minmax);  // Punch -> minmax::Value
		Punch_p.connectT(2, sustain); // Punch -> sustain::Value
		
		auto& Wut_p = this->getParameterT(1);
		Wut_p.connectT(0, pma1); // Wut -> pma1::Value
		Wut_p.connectT(1, pma2); // Wut -> pma2::Value
		
		auto& Speed_p = this->getParameterT(2);
		Speed_p.connectT(0, minmax1); // Speed -> minmax1::Value
		Speed_p.connectT(1, minmax2); // Speed -> minmax2::Value
		
		this->getParameterT(3).connectT(0, dry_wet1); // Mix -> dry_wet1::DryWet
		
		// Modulation Connections ------------------------------------------------------------------
		
		pma.getWrappedObject().getParameter().connectT(0, Tube2);                 // pma -> Tube2::Tube
		envelope_follower.getParameter().connectT(0, pma);                        // envelope_follower -> pma::Value
		minmax1.getWrappedObject().getParameter().connectT(0, envelope_follower); // minmax1 -> envelope_follower::Attack
		minmax2.getWrappedObject().getParameter().connectT(0, envelope_follower); // minmax2 -> envelope_follower::Release
		auto& faust_p = faust.getWrappedObject().getParameter();
		Attack.getWrappedObject().getParameter().connectT(0, faust);  // Attack -> faust::Attack
		sustain.getWrappedObject().getParameter().connectT(0, faust); // sustain -> faust::Sustain
		pma1.getWrappedObject().getParameter().connectT(0, Tube3);    // pma1 -> Tube3::Tube
		pma2.getWrappedObject().getParameter().connectT(0, Focus);    // pma2 -> Focus::Boost
		minmax.getWrappedObject().getParameter().connectT(0, gain);   // minmax -> gain::Gain
		auto& dry_wet_mixer_p = dry_wet_mixer.getWrappedObject().getParameter();
		dry_wet_mixer_p.getParameterT(0).connectT(0, dry_gain); // dry_wet_mixer -> dry_gain::Gain
		dry_wet_mixer_p.getParameterT(1).connectT(0, wet_gain); // dry_wet_mixer -> wet_gain::Gain
		
		// Default Values --------------------------------------------------------------------------
		
		;                                    // minmax1::Value is automated
		minmax1.setParameterT(1, 0.0162056); // control::minmax::Minimum
		minmax1.setParameterT(2, 1.88407);   // control::minmax::Maximum
		minmax1.setParameterT(3, 1.);        // control::minmax::Skew
		minmax1.setParameterT(4, 0.);        // control::minmax::Step
		minmax1.setParameterT(5, 1.);        // control::minmax::Polarity
		
		;                                    // minmax2::Value is automated
		minmax2.setParameterT(1, 0.0532886); // control::minmax::Minimum
		minmax2.setParameterT(2, 8.98969);   // control::minmax::Maximum
		minmax2.setParameterT(3, 1.);        // control::minmax::Skew
		minmax2.setParameterT(4, 0.);        // control::minmax::Step
		minmax2.setParameterT(5, 1.);        // control::minmax::Polarity
		
		;                                  // Attack::Value is automated
		Attack.setParameterT(1, 0.500938); // control::pma::Multiply
		Attack.setParameterT(2, 0.5);      // control::pma::Add
		
		;                                   // sustain::Value is automated
		sustain.setParameterT(1, 0.340944); // control::pma::Multiply
		sustain.setParameterT(2, 0.500664); // control::pma::Add
		
		;                           // pma1::Value is automated
		pma1.setParameterT(1, 0.5); // control::pma::Multiply
		pma1.setParameterT(2, 0.5); // control::pma::Add
		
		;                                // pma2::Value is automated
		pma2.setParameterT(1, 0.248868); // control::pma::Multiply
		pma2.setParameterT(2, 0.);       // control::pma::Add
		
		;                                 // minmax::Value is automated
		minmax.setParameterT(1, -2.1);    // control::minmax::Minimum
		minmax.setParameterT(2, 0.);      // control::minmax::Maximum
		minmax.setParameterT(3, 5.42227); // control::minmax::Skew
		minmax.setParameterT(4, 0.1);     // control::minmax::Step
		minmax.setParameterT(5, 1.);      // control::minmax::Polarity
		
		;                                       // envelope_follower::Attack is automated
		;                                       // envelope_follower::Release is automated
		envelope_follower.setParameterT(2, 0.); // dynamics::envelope_follower::ProcessSignal
		
		; // dry_wet1::DryWet is automated
		
		; // dry_wet_mixer::Value is automated
		
		;                               // dry_gain::Gain is automated
		dry_gain.setParameterT(1, 20.); // core::gain::Smoothing
		dry_gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                               // pma::Value is automated
		pma.setParameterT(1, 1.0873);   // control::pma::Multiply
		pma.setParameterT(2, 0.368207); // control::pma::Add
		
		;                               // faust::Attack is automated
		;                               // faust::Sustain is automated
		faust.setParameterT(2, 10.);    // core::faust::LowCutoff
		faust.setParameterT(3, 20000.); // core::faust::HighCutoff
		faust.setParameterT(4, 0.);     // core::faust::Monitorselectedband
		
		Tube2.setParameterT(0, 0.496235); // project::Tube2::Input
		;                                 // Tube2::Tube is automated
		
		Tube3.setParameterT(0, 0.5); // project::Tube2::Input
		;                            // Tube3::Tube is automated
		
		;                           // Focus::Boost is automated
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
		
		this->setParameterT(0, 0.);
		this->setParameterT(1, 0.413877);
		this->setParameterT(2, 0.669921);
		this->setParameterT(3, 1.);
		this->setExternalData({}, -1);
	}
	~instance() override
	{
		// Cleanup external data references --------------------------------------------------------
		
		this->setExternalData({}, -1);
	}
	
	static constexpr bool isPolyphonic() { return NV > 1; };
	
	static constexpr bool hasTail() { return true; };
	
	static constexpr bool isSuspendedOnSilence() { return false; };
	
	void setExternalData(const ExternalData& b, int index)
	{
		// External Data Connections ---------------------------------------------------------------
		
		this->getT(1).setExternalData(b, index); // Boxer_impl::envelope_follower_t<NV>
	}
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


