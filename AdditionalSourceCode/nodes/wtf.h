#pragma once

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

namespace wtf_impl
{
// ==============================| Node & Parameter type declarations |==============================

template <int NV>
using band1_t = container::chain<parameter::empty, 
                                 wrap::fix<2, jdsp::jlinkwitzriley>, 
                                 jdsp::jlinkwitzriley, 
                                 math::mul<NV>>;
using updown_comp1_t = wrap::no_data<dynamics::updown_comp>;

using band2_t = container::chain<parameter::empty, 
                                 wrap::fix<2, jdsp::jlinkwitzriley>, 
                                 jdsp::jlinkwitzriley, 
                                 updown_comp1_t>;
using updown_comp2_t = updown_comp1_t;

using band3_t = container::chain<parameter::empty, 
                                 wrap::fix<2, jdsp::jlinkwitzriley>, 
                                 jdsp::jlinkwitzriley, 
                                 updown_comp2_t>;

namespace freq_split4_t_parameters
{
// Parameter list for wtf_impl::freq_split4_t ------------------------------------------------------

DECLARE_PARAMETER_RANGE_SKEW(Band1_0Range, 
                             20., 
                             20000., 
                             0.229905);

using Band1_0 = parameter::from0To1<jdsp::jlinkwitzriley, 
                                    0, 
                                    Band1_0Range>;

using Band1_1 = Band1_0;

using Band1_2 = Band1_0;

using Band1 = parameter::chain<ranges::Identity, 
                               Band1_0, 
                               Band1_1, 
                               Band1_2>;

using Band2_0 = Band1_0;

using Band2_1 = Band1_0;

using Band2_2 = Band1_0;

using Band2 = parameter::chain<ranges::Identity, 
                               Band2_0, 
                               Band2_1, 
                               Band2_2>;

using freq_split4_t_plist = parameter::list<Band1, Band2>;
}

template <int NV>
using freq_split4_t = container::split<freq_split4_t_parameters::freq_split4_t_plist, 
                                       wrap::fix<2, band1_t<NV>>, 
                                       band2_t, 
                                       band3_t>;

template <int NV>
using mid_chain_t = container::chain<parameter::empty, 
                                     wrap::fix<1, math::mul<NV>>, 
                                     fx::sampleandhold<NV>>;

template <int NV>
using side_chain_t = container::chain<parameter::empty, 
                                      wrap::fix<1, math::mul<NV>>, 
                                      fx::bitcrush<NV>>;

template <int NV>
using ms_splitter_t = container::multi<parameter::empty, 
                                       wrap::fix<1, mid_chain_t<NV>>, 
                                       wrap::fix<1, side_chain_t<NV>>>;

template <int NV>
using mid_side1_t = container::chain<parameter::empty, 
                                     wrap::fix<2, routing::ms_decode>, 
                                     ms_splitter_t<NV>, 
                                     routing::ms_encode>;

template <int NV>
using wet_path_t = container::chain<parameter::empty, 
                                    wrap::fix<2, freq_split4_t<NV>>, 
                                    mid_side1_t<NV>, 
                                    project::ClipSoftly<NV>>;

template <int NV>
using soft_bypass_t_ = container::chain<parameter::empty, 
                                        wrap::fix<2, wet_path_t<NV>>>;

template <int NV>
using soft_bypass_t = bypass::smoothed<20, soft_bypass_t_<NV>>;

template <int NV>
using wtf_t_ = container::chain<parameter::empty, 
                                wrap::fix<2, soft_bypass_t<NV>>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public wtf_impl::wtf_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(wtf);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(2)
		{
			0x0000, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& soft_bypass = this->getT(0);                                           // wtf_impl::soft_bypass_t<NV>
		auto& wet_path = this->getT(0).getT(0);                                      // wtf_impl::wet_path_t<NV>
		auto& freq_split4 = this->getT(0).getT(0).getT(0);                           // wtf_impl::freq_split4_t<NV>
		auto& band1 = this->getT(0).getT(0).getT(0).getT(0);                         // wtf_impl::band1_t<NV>
		auto& lr1_1 = this->getT(0).getT(0).getT(0).getT(0).getT(0);                 // jdsp::jlinkwitzriley
		auto& lr1_2 = this->getT(0).getT(0).getT(0).getT(0).getT(1);                 // jdsp::jlinkwitzriley
		auto& dummy1 = this->getT(0).getT(0).getT(0).getT(0).getT(2);                // math::mul<NV>
		auto& band2 = this->getT(0).getT(0).getT(0).getT(1);                         // wtf_impl::band2_t
		auto& lr2_1 = this->getT(0).getT(0).getT(0).getT(1).getT(0);                 // jdsp::jlinkwitzriley
		auto& lr2_2 = this->getT(0).getT(0).getT(0).getT(1).getT(1);                 // jdsp::jlinkwitzriley
		auto& updown_comp1 = this->getT(0).getT(0).getT(0).getT(1).getT(2);          // wtf_impl::updown_comp1_t
		auto& band3 = this->getT(0).getT(0).getT(0).getT(2);                         // wtf_impl::band3_t
		auto& lr3_1 = this->getT(0).getT(0).getT(0).getT(2).getT(0);                 // jdsp::jlinkwitzriley
		auto& lr3_2 = this->getT(0).getT(0).getT(0).getT(2).getT(1);                 // jdsp::jlinkwitzriley
		auto& updown_comp2 = this->getT(0).getT(0).getT(0).getT(2).getT(2);          // wtf_impl::updown_comp2_t
		auto& mid_side1 = this->getT(0).getT(0).getT(1);                             // wtf_impl::mid_side1_t<NV>
		auto& decoder = this->getT(0).getT(0).getT(1).getT(0);                       // routing::ms_decode
		auto& ms_splitter = this->getT(0).getT(0).getT(1).getT(1);                   // wtf_impl::ms_splitter_t<NV>
		auto& mid_chain = this->getT(0).getT(0).getT(1).getT(1).getT(0);             // wtf_impl::mid_chain_t<NV>
		auto& mid_gain = this->getT(0).getT(0).getT(1).getT(1).getT(0).getT(0);      // math::mul<NV>
		auto& sampleandhold = this->getT(0).getT(0).getT(1).getT(1).getT(0).getT(1); // fx::sampleandhold<NV>
		auto& side_chain = this->getT(0).getT(0).getT(1).getT(1).getT(1);            // wtf_impl::side_chain_t<NV>
		auto& side_gain = this->getT(0).getT(0).getT(1).getT(1).getT(1).getT(0);     // math::mul<NV>
		auto& bitcrush = this->getT(0).getT(0).getT(1).getT(1).getT(1).getT(1);      // fx::bitcrush<NV>
		auto& encoder = this->getT(0).getT(0).getT(1).getT(2);                       // routing::ms_encode
		auto& ClipSoftly = this->getT(0).getT(0).getT(2);                            // project::ClipSoftly<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		auto& Band1_p = freq_split4.getParameterT(0);
		Band1_p.connectT(0, lr1_1); // Band1 -> lr1_1::Frequency
		Band1_p.connectT(1, lr2_1); // Band1 -> lr2_1::Frequency
		Band1_p.connectT(2, lr3_1); // Band1 -> lr3_1::Frequency
		
		auto& Band2_p = freq_split4.getParameterT(1);
		Band2_p.connectT(0, lr1_2); // Band2 -> lr1_2::Frequency
		Band2_p.connectT(1, lr2_2); // Band2 -> lr2_2::Frequency
		Band2_p.connectT(2, lr3_2); // Band2 -> lr3_2::Frequency
		
		// Default Values --------------------------------------------------------------------------
		
		freq_split4.setParameterT(0, 68.0681); // container::split::Band1
		freq_split4.setParameterT(1, 1000.);   // container::split::Band2
		
		;                           // lr1_1::Frequency is automated
		lr1_1.setParameterT(1, 0.); // jdsp::jlinkwitzriley::Type
		
		;                           // lr1_2::Frequency is automated
		lr1_2.setParameterT(1, 2.); // jdsp::jlinkwitzriley::Type
		
		dummy1.setParameterT(0, 1.); // math::mul::Value
		
		;                           // lr2_1::Frequency is automated
		lr2_1.setParameterT(1, 1.); // jdsp::jlinkwitzriley::Type
		
		;                           // lr2_2::Frequency is automated
		lr2_2.setParameterT(1, 0.); // jdsp::jlinkwitzriley::Type
		
		updown_comp1.setParameterT(0, -100.);    // dynamics::updown_comp::LowThreshold
		updown_comp1.setParameterT(1, 0.2);      // dynamics::updown_comp::LowRatio
		updown_comp1.setParameterT(2, -5.91981); // dynamics::updown_comp::HighThreshold
		updown_comp1.setParameterT(3, 25.5193);  // dynamics::updown_comp::HighRatio
		updown_comp1.setParameterT(4, 0.25704);  // dynamics::updown_comp::Knee
		updown_comp1.setParameterT(5, 0.);       // dynamics::updown_comp::Attack
		updown_comp1.setParameterT(6, 11.9614);  // dynamics::updown_comp::Release
		updown_comp1.setParameterT(7, 1.);       // dynamics::updown_comp::RMS
		
		;                           // lr3_1::Frequency is automated
		lr3_1.setParameterT(1, 2.); // jdsp::jlinkwitzriley::Type
		
		;                           // lr3_2::Frequency is automated
		lr3_2.setParameterT(1, 1.); // jdsp::jlinkwitzriley::Type
		
		updown_comp2.setParameterT(0, -100.);    // dynamics::updown_comp::LowThreshold
		updown_comp2.setParameterT(1, 2.27531);  // dynamics::updown_comp::LowRatio
		updown_comp2.setParameterT(2, -8.90128); // dynamics::updown_comp::HighThreshold
		updown_comp2.setParameterT(3, 5.2251);   // dynamics::updown_comp::HighRatio
		updown_comp2.setParameterT(4, 0.15);     // dynamics::updown_comp::Knee
		updown_comp2.setParameterT(5, 0.);       // dynamics::updown_comp::Attack
		updown_comp2.setParameterT(6, 50.);      // dynamics::updown_comp::Release
		updown_comp2.setParameterT(7, 1.);       // dynamics::updown_comp::RMS
		
		mid_gain.setParameterT(0, 1.); // math::mul::Value
		
		sampleandhold.setParameterT(0, 2.); // fx::sampleandhold::Counter
		
		side_gain.setParameterT(0, 1.); // math::mul::Value
		
		bitcrush.setParameterT(0, 13.); // fx::bitcrush::BitDepth
		bitcrush.setParameterT(1, 0.);  // fx::bitcrush::Mode
		
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
		
		this->getT(0).getT(0).getT(0).getT(1).getT(2).setExternalData(b, index); // wtf_impl::updown_comp1_t
		this->getT(0).getT(0).getT(0).getT(2).getT(2).setExternalData(b, index); // wtf_impl::updown_comp2_t
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
using wtf = wrap::node<wtf_impl::instance<NV>>;
}


