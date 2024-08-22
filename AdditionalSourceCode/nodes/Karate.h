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

struct cable_table_t_data
{
	span<float, 512> data =
	{
		0.f, 0.00424212f, 0.00848424f, 0.0127264f, 0.0169685f, 0.0212106f,
		0.0254527f, 0.0296949f, 0.033937f, 0.0381791f, 0.0424212f, 0.0466633f,
		0.0509055f, 0.0551476f, 0.0593897f, 0.0636318f, 0.067874f, 0.0721161f,
		0.0763582f, 0.0806003f, 0.0848424f, 0.0890846f, 0.0933267f, 0.0975689f,
		0.101811f, 0.106053f, 0.110295f, 0.114537f, 0.118779f, 0.123022f,
		0.127264f, 0.131506f, 0.135748f, 0.13999f, 0.144232f, 0.148474f,
		0.152716f, 0.156959f, 0.161201f, 0.165443f, 0.169685f, 0.173927f,
		0.178169f, 0.182411f, 0.186653f, 0.190896f, 0.195138f, 0.19938f,
		0.203622f, 0.207864f, 0.212106f, 0.216348f, 0.22059f, 0.224833f,
		0.229075f, 0.233317f, 0.237559f, 0.241801f, 0.246043f, 0.250285f,
		0.254527f, 0.25877f, 0.263012f, 0.267254f, 0.271496f, 0.275738f,
		0.27998f, 0.284222f, 0.288464f, 0.292657f, 0.296533f, 0.300409f,
		0.304284f, 0.30816f, 0.312036f, 0.315911f, 0.319787f, 0.323663f,
		0.327538f, 0.331414f, 0.33529f, 0.339165f, 0.343041f, 0.346917f,
		0.350792f, 0.354668f, 0.358544f, 0.362419f, 0.366295f, 0.370171f,
		0.374047f, 0.377922f, 0.381798f, 0.385674f, 0.389549f, 0.393425f,
		0.397301f, 0.401176f, 0.405052f, 0.408928f, 0.412803f, 0.416679f,
		0.420555f, 0.42443f, 0.428306f, 0.432182f, 0.436058f, 0.439933f,
		0.443809f, 0.447685f, 0.45156f, 0.455436f, 0.459312f, 0.463187f,
		0.467063f, 0.470939f, 0.474814f, 0.47869f, 0.482566f, 0.486441f,
		0.490317f, 0.494193f, 0.498068f, 0.501944f, 0.50582f, 0.509696f,
		0.513571f, 0.517447f, 0.521323f, 0.525198f, 0.529074f, 0.53295f,
		0.536825f, 0.540701f, 0.544577f, 0.548452f, 0.552328f, 0.556204f,
		0.560079f, 0.563955f, 0.567831f, 0.571706f, 0.575582f, 0.579458f,
		0.583334f, 0.587209f, 0.591085f, 0.594961f, 0.598836f, 0.602712f,
		0.606588f, 0.610463f, 0.614339f, 0.618215f, 0.62209f, 0.625966f,
		0.629842f, 0.633717f, 0.637593f, 0.641469f, 0.645344f, 0.64922f,
		0.653096f, 0.656972f, 0.660847f, 0.664723f, 0.668599f, 0.672474f,
		0.67635f, 0.680226f, 0.684101f, 0.687977f, 0.691853f, 0.695728f,
		0.699604f, 0.70348f, 0.707355f, 0.711231f, 0.715107f, 0.718983f,
		0.722858f, 0.726734f, 0.73061f, 0.734485f, 0.738361f, 0.742237f,
		0.746112f, 0.749988f, 0.753864f, 0.757739f, 0.761615f, 0.765491f,
		0.769367f, 0.773242f, 0.777118f, 0.780993f, 0.784869f, 0.788745f,
		0.792621f, 0.796496f, 0.800372f, 0.804248f, 0.808123f, 0.811999f,
		0.815875f, 0.81975f, 0.823626f, 0.827502f, 0.831377f, 0.835253f,
		0.839129f, 0.843004f, 0.84688f, 0.850756f, 0.854632f, 0.858507f,
		0.862383f, 0.866259f, 0.870134f, 0.87401f, 0.877886f, 0.881761f,
		0.885637f, 0.889513f, 0.893388f, 0.897264f, 0.90114f, 0.905015f,
		0.908891f, 0.912767f, 0.916642f, 0.920518f, 0.924394f, 0.92827f,
		0.932145f, 0.936021f, 0.939897f, 0.943772f, 0.947648f, 0.951524f,
		0.955399f, 0.959275f, 0.963151f, 0.967026f, 0.970902f, 0.974778f,
		0.978653f, 0.982529f, 0.986405f, 0.99028f, 0.994156f, 0.998032f,
		1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 0.995183f, 0.988693f, 0.982204f, 0.975714f,
		0.969224f, 0.962734f, 0.956244f, 0.949754f, 0.943264f, 0.936774f,
		0.930285f, 0.923795f, 0.917305f, 0.910815f, 0.904325f, 0.897835f,
		0.891345f, 0.884855f, 0.878366f, 0.871876f, 0.865386f, 0.858896f,
		0.852406f, 0.845916f, 0.839426f, 0.832936f, 0.826447f, 0.819957f,
		0.813467f, 0.806977f, 0.800487f, 0.793997f, 0.787507f, 0.781017f,
		0.774528f, 0.768038f, 0.761548f, 0.755058f, 0.748568f, 0.742078f,
		0.735588f, 0.729098f, 0.722609f, 0.716119f, 0.709629f, 0.703139f,
		0.696649f, 0.690159f, 0.683669f, 0.677179f, 0.67069f, 0.6642f,
		0.65771f, 0.65122f, 0.64473f, 0.63824f, 0.63175f, 0.62526f,
		0.618771f, 0.612281f, 0.605791f, 0.599301f, 0.592811f, 0.586321f,
		0.579831f, 0.573342f, 0.566852f, 0.560362f, 0.553872f, 0.547382f,
		0.540892f, 0.534402f, 0.527912f, 0.521423f, 0.514933f, 0.508443f,
		0.501953f, 0.495463f, 0.488973f, 0.482483f, 0.475993f, 0.469504f,
		0.463014f, 0.456524f, 0.450034f, 0.446175f, 0.442582f, 0.438989f,
		0.435396f, 0.431803f, 0.42821f, 0.424617f, 0.421024f, 0.417431f,
		0.413838f, 0.410246f, 0.406652f, 0.40306f, 0.399467f, 0.395874f,
		0.392281f, 0.388688f, 0.385095f, 0.381502f, 0.377909f, 0.374316f,
		0.370723f, 0.36713f, 0.363537f, 0.359944f, 0.356351f, 0.352758f,
		0.349165f, 0.345572f, 0.341979f, 0.338386f, 0.334793f, 0.3312f,
		0.327607f, 0.324014f, 0.320421f, 0.316828f, 0.313236f, 0.309643f,
		0.30605f, 0.302457f, 0.298864f, 0.295271f, 0.291678f, 0.288085f,
		0.284492f, 0.280899f
	};
};

template <int NV>
using cable_table_t = wrap::data<control::cable_table<parameter::plain<minmax1_t<NV>, 0>>, 
                                 data::embedded::table<cable_table_t_data>>;

template <int NV>
using split1_t = container::split<parameter::empty, 
                                  wrap::fix<1, minmax1_t<NV>>, 
                                  cable_table_t<NV>>;

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
                                  parameter::plain<Karate_impl::cable_table_t<NV>, 0>>;

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
            0x8000, 0xEA3F, 0x850F, 0x003E, 0x8000, 0x003F, 0x0000, 0x5B00, 
            0x0001, 0x0000, 0x694D, 0x0078, 0x0000, 0x0000, 0x0000, 0x3F80, 
            0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x0000, 0x025B, 0x0000, 
            0x4100, 0x7269, 0x0000, 0x0000, 0x0000, 0x8000, 0x003F, 0x8000, 
            0x003F, 0x8000, 0x003F, 0x0000, 0x5B00, 0x0003, 0x0000, 0x7250, 
            0x7365, 0x7573, 0x6572, 0x0000, 0x0000, 0x0000, 0x8000, 0xD93F, 
            0x014E, 0x003F, 0x8000, 0x003F, 0x0000, 0x5B00, 0x0004, 0x0000, 
            0x7053, 0x6565, 0x0064, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 
            0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 0x0000
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
		auto& cable_table = this->getT(0).getT(1).getT(1);                            // Karate_impl::cable_table_t<NV>
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
		Pressure_p.connectT(0, Pressure5);   // Pressure -> Pressure5::Pressre
		Pressure_p.connectT(1, cable_table); // Pressure -> cable_table::Value
		
		this->getParameterT(4).connectT(0, Pressure5); // Speed -> Pressure5::Speed
		
		// Modulation Connections ------------------------------------------------------------------
		
		auto& dry_wet_mixer1_p = dry_wet_mixer1.getWrappedObject().getParameter();
		dry_wet_mixer1_p.getParameterT(0).connectT(0, dry_gain1);           // dry_wet_mixer1 -> dry_gain1::Gain
		dry_wet_mixer1_p.getParameterT(1).connectT(0, wet_gain1);           // dry_wet_mixer1 -> wet_gain1::Gain
		air.getWrappedObject().getParameter().connectT(0, dry_wet2);        // air -> dry_wet2::DryWet
		pma1.getWrappedObject().getParameter().connectT(0, Focus);          // pma1 -> Focus::Focus
		pma2.getWrappedObject().getParameter().connectT(0, Focus);          // pma2 -> Focus::Boost
		minmax1.getWrappedObject().getParameter().connectT(0, gain1);       // minmax1 -> gain1::Gain
		cable_table.getWrappedObject().getParameter().connectT(0, minmax1); // cable_table -> minmax1::Value
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
		minmax1.setParameterT(1, -3.4);     // control::minmax::Minimum
		minmax1.setParameterT(2, 2.);       // control::minmax::Maximum
		minmax1.setParameterT(3, 0.991903); // control::minmax::Skew
		minmax1.setParameterT(4, 0.1);      // control::minmax::Step
		minmax1.setParameterT(5, 1.);       // control::minmax::Polarity
		
		; // cable_table::Value is automated
		
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
		
		gain.setParameterT(0, 0.);  // core::gain::Gain
		gain.setParameterT(1, 20.); // core::gain::Smoothing
		gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                               // wet_gain::Gain is automated
		wet_gain.setParameterT(1, 20.); // core::gain::Smoothing
		wet_gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		this->setParameterT(0, 0.259887);
		this->setParameterT(1, 1.);
		this->setParameterT(2, 1.);
		this->setParameterT(3, 0.505109);
		this->setParameterT(4, 0.);
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
		
		this->getT(0).getT(1).getT(1).setExternalData(b, index); // Karate_impl::cable_table_t<NV>
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
using Karate = wrap::node<Karate_impl::instance<NV>>;
}


