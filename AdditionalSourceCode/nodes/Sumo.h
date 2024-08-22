#pragma once

#include "Mojo.h"
#include "Mojo.h"
#include "Tube2.h"
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

template <int NV> using pma_t = mojo1_t<NV>;

template <int NV>
using minmax_t = control::minmax<NV, 
                                 parameter::plain<core::gain<NV>, 0>>;

struct cable_table_t_data
{
	span<float, 512> data =
	{
		0.0898876f, 0.0896062f, 0.0893247f, 0.0890433f, 0.0887618f, 0.0884804f,
		0.0881989f, 0.0879175f, 0.0876361f, 0.0873546f, 0.0870731f, 0.0867917f,
		0.0865102f, 0.0862288f, 0.0859473f, 0.0856659f, 0.0853844f, 0.085103f,
		0.0848215f, 0.0845401f, 0.0842587f, 0.0839772f, 0.0836958f, 0.0834143f,
		0.0831329f, 0.0828514f, 0.08257f, 0.0822885f, 0.0820071f, 0.0817256f,
		0.0814441f, 0.0811627f, 0.0808812f, 0.0805998f, 0.0803184f, 0.0800369f,
		0.0797555f, 0.079474f, 0.0791926f, 0.0789111f, 0.0788186f, 0.0809556f,
		0.0830925f, 0.0852294f, 0.0873663f, 0.0895032f, 0.0916402f, 0.0937771f,
		0.095914f, 0.098051f, 0.100188f, 0.102325f, 0.104462f, 0.106599f,
		0.108736f, 0.110873f, 0.113009f, 0.115146f, 0.117283f, 0.11942f,
		0.121557f, 0.123694f, 0.125831f, 0.127968f, 0.130105f, 0.132242f,
		0.134379f, 0.136516f, 0.138653f, 0.140789f, 0.142926f, 0.145063f,
		0.1472f, 0.149337f, 0.151474f, 0.153611f, 0.155748f, 0.157885f,
		0.160022f, 0.162159f, 0.164296f, 0.166432f, 0.168569f, 0.170706f,
		0.172843f, 0.17498f, 0.177117f, 0.179254f, 0.181391f, 0.183528f,
		0.185665f, 0.187802f, 0.189939f, 0.192076f, 0.194213f, 0.196349f,
		0.198486f, 0.200623f, 0.20276f, 0.204897f, 0.207034f, 0.209171f,
		0.211308f, 0.213445f, 0.215582f, 0.217719f, 0.219856f, 0.221993f,
		0.224129f, 0.226266f, 0.228403f, 0.23054f, 0.232677f, 0.234814f,
		0.236951f, 0.239088f, 0.241225f, 0.243362f, 0.245499f, 0.247636f,
		0.249773f, 0.251909f, 0.254046f, 0.256183f, 0.25832f, 0.260457f,
		0.262594f, 0.264731f, 0.266868f, 0.269005f, 0.271142f, 0.273279f,
		0.275416f, 0.277553f, 0.27969f, 0.281826f, 0.283963f, 0.2861f,
		0.288237f, 0.290374f, 0.292511f, 0.294648f, 0.296785f, 0.298922f,
		0.301059f, 0.303196f, 0.305333f, 0.307469f, 0.309606f, 0.311743f,
		0.31388f, 0.316017f, 0.318154f, 0.320291f, 0.322428f, 0.324565f,
		0.326702f, 0.328839f, 0.330976f, 0.333113f, 0.33525f, 0.337386f,
		0.339523f, 0.34166f, 0.343797f, 0.345934f, 0.348071f, 0.350208f,
		0.352345f, 0.354482f, 0.356619f, 0.358756f, 0.360893f, 0.36303f,
		0.365166f, 0.367303f, 0.36944f, 0.371577f, 0.373714f, 0.375851f,
		0.377988f, 0.380125f, 0.382262f, 0.384399f, 0.386536f, 0.388673f,
		0.39081f, 0.392946f, 0.395083f, 0.39722f, 0.399357f, 0.401494f,
		0.403631f, 0.405768f, 0.407905f, 0.410042f, 0.412179f, 0.414316f,
		0.416453f, 0.41859f, 0.420727f, 0.422863f, 0.425f, 0.427137f,
		0.429274f, 0.431411f, 0.433548f, 0.435685f, 0.437822f, 0.439959f,
		0.442096f, 0.444233f, 0.44637f, 0.448507f, 0.450643f, 0.45278f,
		0.454917f, 0.457054f, 0.459191f, 0.461328f, 0.463465f, 0.465602f,
		0.467739f, 0.469876f, 0.472013f, 0.47415f, 0.476287f, 0.478423f,
		0.48056f, 0.482697f, 0.484834f, 0.486971f, 0.489108f, 0.491245f,
		0.493382f, 0.495519f, 0.497656f, 0.499793f, 0.50193f, 0.504067f,
		0.506204f, 0.50834f, 0.510477f, 0.512614f, 0.514751f, 0.516888f,
		0.519025f, 0.521162f, 0.523299f, 0.525436f, 0.527573f, 0.52971f,
		0.531847f, 0.533983f, 0.53612f, 0.538257f, 0.540394f, 0.542531f,
		0.544668f, 0.546805f, 0.548942f, 0.551079f, 0.553216f, 0.555353f,
		0.55749f, 0.559627f, 0.561764f, 0.5639f, 0.566037f, 0.568174f,
		0.570311f, 0.572448f, 0.574585f, 0.576722f, 0.578859f, 0.580996f,
		0.583133f, 0.58527f, 0.587407f, 0.589544f, 0.59168f, 0.593817f,
		0.595954f, 0.598091f, 0.600228f, 0.602365f, 0.604502f, 0.606639f,
		0.608776f, 0.610913f, 0.61305f, 0.615187f, 0.617324f, 0.619461f,
		0.621597f, 0.623734f, 0.625871f, 0.628008f, 0.630145f, 0.632282f,
		0.634419f, 0.636556f, 0.638693f, 0.64083f, 0.642967f, 0.645104f,
		0.647241f, 0.649377f, 0.651514f, 0.653651f, 0.655788f, 0.657925f,
		0.660062f, 0.662199f, 0.664336f, 0.666473f, 0.66861f, 0.670747f,
		0.672884f, 0.675021f, 0.677157f, 0.679294f, 0.681431f, 0.683568f,
		0.685705f, 0.687842f, 0.689979f, 0.692116f, 0.694253f, 0.69639f,
		0.698527f, 0.700664f, 0.702801f, 0.704938f, 0.707074f, 0.709211f,
		0.711348f, 0.713485f, 0.715622f, 0.717759f, 0.719896f, 0.722033f,
		0.72417f, 0.726307f, 0.728444f, 0.730581f, 0.732717f, 0.734854f,
		0.736991f, 0.739128f, 0.741265f, 0.743402f, 0.745539f, 0.747676f,
		0.749813f, 0.75195f, 0.754087f, 0.756224f, 0.758361f, 0.760498f,
		0.762634f, 0.764771f, 0.766908f, 0.769045f, 0.771182f, 0.773319f,
		0.775456f, 0.777593f, 0.77973f, 0.781867f, 0.784004f, 0.786141f,
		0.788278f, 0.790415f, 0.792551f, 0.794688f, 0.796825f, 0.798962f,
		0.801099f, 0.803236f, 0.805373f, 0.80751f, 0.809647f, 0.811784f,
		0.813921f, 0.816058f, 0.818194f, 0.820331f, 0.822468f, 0.824605f,
		0.826742f, 0.828879f, 0.831016f, 0.833153f, 0.83529f, 0.837427f,
		0.839564f, 0.841701f, 0.843838f, 0.845975f, 0.848111f, 0.850248f,
		0.852385f, 0.854522f, 0.856659f, 0.858796f, 0.860933f, 0.86307f,
		0.865207f, 0.867344f, 0.869481f, 0.871618f, 0.873755f, 0.875891f,
		0.878028f, 0.880165f, 0.882302f, 0.884439f, 0.886576f, 0.888713f,
		0.89085f, 0.892987f, 0.895124f, 0.897261f, 0.899398f, 0.901534f,
		0.903671f, 0.905808f, 0.907945f, 0.910082f, 0.912219f, 0.914356f,
		0.916493f, 0.91863f, 0.920767f, 0.922904f, 0.925041f, 0.927178f,
		0.929315f, 0.931451f, 0.933588f, 0.935725f, 0.937862f, 0.939999f,
		0.942136f, 0.944273f, 0.94641f, 0.948547f, 0.950684f, 0.952821f,
		0.954958f, 0.957094f, 0.959232f, 0.961368f, 0.963505f, 0.965642f,
		0.967779f, 0.969916f, 0.972053f, 0.97419f, 0.976327f, 0.978464f,
		0.980601f, 0.982738f, 0.984875f, 0.987011f, 0.989148f, 0.991285f,
		0.993422f, 0.995559f, 0.997696f, 0.999833f, 0.982616f, 0.963759f,
		0.944902f, 0.926045f, 0.907188f, 0.888331f, 0.869474f, 0.850617f,
		0.83176f, 0.812903f, 0.794046f, 0.775189f, 0.756331f, 0.737474f,
		0.718617f, 0.69976f, 0.680903f, 0.662046f, 0.643189f, 0.624332f,
		0.605475f, 0.586618f, 0.567761f, 0.548904f, 0.530047f, 0.51119f,
		0.492333f, 0.473476f, 0.454618f, 0.435761f, 0.416904f, 0.398047f,
		0.37919f, 0.360333f, 0.341476f, 0.322619f, 0.303762f, 0.284905f,
		0.266048f, 0.247191f
	};
};

template <int NV>
using cable_table_t = wrap::data<control::cable_table<parameter::plain<minmax_t<NV>, 0>>, 
                                 data::embedded::table<cable_table_t_data>>;

template <int NV>
using smoothed_parameter_mod = parameter::chain<ranges::Identity, 
                                                parameter::plain<mojo1_t<NV>, 0>, 
                                                parameter::plain<pma_t<NV>, 0>, 
                                                parameter::plain<cable_table_t<NV>, 0>>;

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
                                  wrap::fix<1, cable_table_t<NV>>, 
                                  minmax_t<NV>>;

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
using Weight = parameter::chain<ranges::Identity, 
                                parameter::plain<project::Tube2<NV>, 1>, 
                                parameter::plain<project::Tube2<NV>, 1>>;

template <int NV>
using Heavy = parameter::plain<Sumo_impl::smoothed_parameter_t<NV>, 
                               0>;
template <int NV>
using Mix = parameter::plain<Sumo_impl::dry_wet1_t<NV>, 
                             0>;
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
            0x8000, 0xDC3F, 0x001C, 0x003F, 0x8000, 0x003F, 0x0000, 0x5B00, 
            0x0001, 0x0000, 0x694D, 0x0078, 0x0000, 0x0000, 0x0000, 0x3F80, 
            0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x0000, 0x025B, 0x0000, 
            0x5700, 0x6965, 0x6867, 0x0074, 0x0000, 0x0000, 0x0000, 0x3F80, 
            0x0AE5, 0x3F01, 0x0000, 0x3F80, 0x0000, 0x0000, 0x035B, 0x0000, 
            0x5300, 0x6F74, 0x706D, 0x0000, 0x0000, 0x0000, 0x8000, 0x003F, 
            0x0000, 0x0000, 0x8000, 0x003F, 0x0000, 0x5B00, 0x0004, 0x0000, 
            0x7243, 0x7375, 0x0068, 0x0000, 0x0000, 0x0000, 0x3F80, 0xC073, 
            0x3DD8, 0x0000, 0x3F80, 0x0000, 0x0000, 0x0000
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
		auto& cable_table = this->getT(2).getT(1).getT(0);                            // Sumo_impl::cable_table_t<NV>
		auto& minmax = this->getT(2).getT(1).getT(1);                                 // Sumo_impl::minmax_t<NV>
		auto& dry_wet1 = this->getT(3);                                               // Sumo_impl::dry_wet1_t<NV>
		auto& dry_path = this->getT(3).getT(0);                                       // Sumo_impl::dry_path_t<NV>
		auto& dry_wet_mixer = this->getT(3).getT(0).getT(0);                          // Sumo_impl::dry_wet_mixer_t<NV>
		auto& dry_gain = this->getT(3).getT(0).getT(1);                               // core::gain<NV>
		auto& wet_path = this->getT(3).getT(1);                                       // Sumo_impl::wet_path_t<NV>
		auto& chain = this->getT(3).getT(1).getT(0);                                  // Sumo_impl::chain_t<NV>
		auto& Mojo = this->getT(3).getT(1).getT(0).getT(0);                           // project::Mojo<NV>
		auto& Mojo1 = this->getT(3).getT(1).getT(0).getT(1);                          // project::Mojo<NV>
		auto& Tube2 = this->getT(3).getT(1).getT(1);                                  // project::Tube2<NV>
		auto& Tube3 = this->getT(3).getT(1).getT(2);                                  // project::Tube2<NV>
		auto& Stomp = this->getT(3).getT(1).getT(3);                                  // Sumo_impl::Stomp_t<NV>
		auto& dry_wet2 = this->getT(3).getT(1).getT(3).getT(0);                       // Sumo_impl::dry_wet2_t<NV>
		auto& dry_path1 = this->getT(3).getT(1).getT(3).getT(0).getT(0);              // Sumo_impl::dry_path1_t<NV>
		auto& dry_wet_mixer1 = this->getT(3).getT(1).getT(3).getT(0).getT(0).getT(0); // Sumo_impl::dry_wet_mixer1_t<NV>
		auto& dry_gain1 = this->getT(3).getT(1).getT(3).getT(0).getT(0).getT(1);      // core::gain<NV>
		auto& wet_path1 = this->getT(3).getT(1).getT(3).getT(0).getT(1);              // Sumo_impl::wet_path1_t<NV>
		auto& svf_eq = this->getT(3).getT(1).getT(3).getT(0).getT(1).getT(0);         // filters::svf_eq<NV>
		auto& svf_eq1 = this->getT(3).getT(1).getT(3).getT(0).getT(1).getT(1);        // filters::svf_eq<NV>
		auto& wet_gain1 = this->getT(3).getT(1).getT(3).getT(0).getT(1).getT(2);      // core::gain<NV>
		auto& sampleandhold = this->getT(3).getT(1).getT(4);                          // fx::sampleandhold<NV>
		auto& gain = this->getT(3).getT(1).getT(5);                                   // core::gain<NV>
		auto& wet_gain = this->getT(3).getT(1).getT(6);                               // core::gain<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		dry_wet2.getParameterT(0).connectT(0, dry_wet_mixer1);  // DryWet -> dry_wet_mixer1::Value
		dry_wet1.getParameterT(0).connectT(0, dry_wet_mixer);   // DryWet -> dry_wet_mixer::Value
		this->getParameterT(0).connectT(0, smoothed_parameter); // Heavy -> smoothed_parameter::Value
		
		this->getParameterT(1).connectT(0, dry_wet1); // Mix -> dry_wet1::DryWet
		
		auto& Weight_p = this->getParameterT(2);
		Weight_p.connectT(0, Tube2); // Weight -> Tube2::Tube
		Weight_p.connectT(1, Tube3); // Weight -> Tube3::Tube
		
		this->getParameterT(3).connectT(0, smoothed_parameter2); // Stomp -> smoothed_parameter2::Value
		
		this->getParameterT(4).connectT(0, minmax4); // Crush -> minmax4::Value
		
		// Modulation Connections ------------------------------------------------------------------
		
		mojo1.getWrappedObject().getParameter().connectT(0, Mojo);            // mojo1 -> Mojo::Input
		pma.getWrappedObject().getParameter().connectT(0, Mojo1);             // pma -> Mojo1::Input
		minmax.getWrappedObject().getParameter().connectT(0, gain);           // minmax -> gain::Gain
		cable_table.getWrappedObject().getParameter().connectT(0, minmax);    // cable_table -> minmax::Value
		smoothed_parameter.getParameter().connectT(0, mojo1);                 // smoothed_parameter -> mojo1::Value
		smoothed_parameter.getParameter().connectT(1, pma);                   // smoothed_parameter -> pma::Value
		smoothed_parameter.getParameter().connectT(2, cable_table);           // smoothed_parameter -> cable_table::Value
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
		minmax4.setParameterT(2, 4.98228); // control::minmax::Maximum
		minmax4.setParameterT(3, 1.);      // control::minmax::Skew
		minmax4.setParameterT(4, 0.);      // control::minmax::Step
		minmax4.setParameterT(5, 0.);      // control::minmax::Polarity
		
		; // cable_table::Value is automated
		
		;                                  // minmax::Value is automated
		minmax.setParameterT(1, -7.4);     // control::minmax::Minimum
		minmax.setParameterT(2, 0.1);      // control::minmax::Maximum
		minmax.setParameterT(3, 0.116028); // control::minmax::Skew
		minmax.setParameterT(4, 0.1);      // control::minmax::Step
		minmax.setParameterT(5, 1.);       // control::minmax::Polarity
		
		; // dry_wet1::DryWet is automated
		
		; // dry_wet_mixer::Value is automated
		
		;                               // dry_gain::Gain is automated
		dry_gain.setParameterT(1, 20.); // core::gain::Smoothing
		dry_gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		; // Mojo::Input is automated
		
		; // Mojo1::Input is automated
		
		Tube2.setParameterT(0, 0.5); // project::Tube2::Input
		;                            // Tube2::Tube is automated
		
		Tube3.setParameterT(0, 0.5); // project::Tube2::Input
		;                            // Tube3::Tube is automated
		
		dry_wet2.setParameterT(0, 0.501264); // container::split::DryWet
		
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
		
		this->setParameterT(0, 0.50044);
		this->setParameterT(1, 1.);
		this->setParameterT(2, 0.504073);
		this->setParameterT(3, 0.);
		this->setParameterT(4, 0.105836);
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
		
		this->getT(2).getT(1).getT(0).setExternalData(b, index); // Sumo_impl::cable_table_t<NV>
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
using Sumo = wrap::node<Sumo_impl::instance<NV>>;
}


