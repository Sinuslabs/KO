#pragma once

#include "Drive.h"
#include "Tube2.h"
#include "Tube2.h"
#include "DrumSlam.h"
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

template <int NV>
using minmax3_t = control::minmax<NV, 
                                  parameter::plain<core::gain<NV>, 0>>;

struct cable_table1_t_data
{
	span<float, 512> data =
	{
		0.f, 0.00189608f, 0.00379217f, 0.00568825f, 0.00758427f, 0.00948036f,
		0.0113764f, 0.0132725f, 0.0151686f, 0.0170647f, 0.0189608f, 0.0208568f,
		0.0227529f, 0.024649f, 0.026545f, 0.0284411f, 0.0303372f, 0.0322332f,
		0.0341293f, 0.0360254f, 0.0379215f, 0.0398176f, 0.0417137f, 0.0436097f,
		0.0455058f, 0.0474018f, 0.0492979f, 0.051194f, 0.0530901f, 0.0549862f,
		0.0568823f, 0.0587783f, 0.0606744f, 0.0625705f, 0.0644665f, 0.0663626f,
		0.0682587f, 0.0701548f, 0.0720509f, 0.0739469f, 0.075843f, 0.0777391f,
		0.0796351f, 0.0815312f, 0.0834273f, 0.0853233f, 0.0872194f, 0.0891155f,
		0.0910116f, 0.0929077f, 0.0948038f, 0.0966998f, 0.0985959f, 0.100492f,
		0.102388f, 0.104284f, 0.10618f, 0.108076f, 0.109972f, 0.111868f,
		0.113764f, 0.115661f, 0.117557f, 0.119453f, 0.121349f, 0.123245f,
		0.125141f, 0.127037f, 0.128933f, 0.130829f, 0.132725f, 0.134621f,
		0.136517f, 0.138413f, 0.14031f, 0.142206f, 0.144102f, 0.145998f,
		0.147894f, 0.14979f, 0.151686f, 0.153582f, 0.155478f, 0.157374f,
		0.15927f, 0.161166f, 0.163062f, 0.164958f, 0.166855f, 0.168751f,
		0.170647f, 0.172543f, 0.174439f, 0.176335f, 0.178231f, 0.180127f,
		0.182023f, 0.183919f, 0.185815f, 0.187711f, 0.189608f, 0.191504f,
		0.1934f, 0.195296f, 0.197192f, 0.199088f, 0.200984f, 0.20288f,
		0.204776f, 0.206672f, 0.208568f, 0.210464f, 0.21236f, 0.214256f,
		0.216153f, 0.218049f, 0.219945f, 0.221841f, 0.223737f, 0.225633f,
		0.227529f, 0.229425f, 0.231321f, 0.233217f, 0.235113f, 0.237009f,
		0.238905f, 0.240801f, 0.242698f, 0.244594f, 0.24649f, 0.248386f,
		0.250282f, 0.252178f, 0.254074f, 0.25597f, 0.257866f, 0.259762f,
		0.261658f, 0.263554f, 0.26545f, 0.267347f, 0.269243f, 0.271139f,
		0.273035f, 0.274931f, 0.276827f, 0.278723f, 0.280619f, 0.282515f,
		0.284411f, 0.286307f, 0.288203f, 0.290099f, 0.291996f, 0.293892f,
		0.295788f, 0.297684f, 0.29958f, 0.301476f, 0.303372f, 0.305268f,
		0.307164f, 0.30906f, 0.310956f, 0.312852f, 0.314748f, 0.316644f,
		0.318541f, 0.320437f, 0.322333f, 0.324229f, 0.326125f, 0.328021f,
		0.329917f, 0.331813f, 0.333709f, 0.335605f, 0.337501f, 0.339397f,
		0.341293f, 0.343189f, 0.345086f, 0.346982f, 0.348878f, 0.350774f,
		0.35267f, 0.354566f, 0.356462f, 0.358358f, 0.360254f, 0.36215f,
		0.364046f, 0.365942f, 0.367839f, 0.369735f, 0.371631f, 0.373527f,
		0.375423f, 0.377319f, 0.379215f, 0.381111f, 0.383007f, 0.384903f,
		0.386799f, 0.388695f, 0.390591f, 0.392487f, 0.394384f, 0.39628f,
		0.398176f, 0.400072f, 0.401968f, 0.403864f, 0.40576f, 0.407656f,
		0.409552f, 0.411448f, 0.413344f, 0.41524f, 0.417136f, 0.419033f,
		0.420929f, 0.422825f, 0.424721f, 0.426617f, 0.428513f, 0.430409f,
		0.432305f, 0.434201f, 0.436097f, 0.437993f, 0.439889f, 0.441785f,
		0.443681f, 0.445578f, 0.447474f, 0.44937f, 0.451266f, 0.453162f,
		0.455058f, 0.456954f, 0.45885f, 0.460746f, 0.462642f, 0.464538f,
		0.466434f, 0.46833f, 0.470227f, 0.472123f, 0.474019f, 0.475915f,
		0.477811f, 0.479707f, 0.481603f, 0.483499f, 0.485395f, 0.487291f,
		0.489187f, 0.491083f, 0.492979f, 0.494875f, 0.496772f, 0.498668f,
		0.500564f, 0.50246f, 0.504356f, 0.506252f, 0.508148f, 0.510044f,
		0.51194f, 0.513836f, 0.515732f, 0.517628f, 0.519524f, 0.52142f,
		0.523317f, 0.525213f, 0.527109f, 0.529005f, 0.530901f, 0.532797f,
		0.534693f, 0.536589f, 0.538485f, 0.601993f, 0.651804f, 0.652016f,
		0.652229f, 0.652441f, 0.652654f, 0.652866f, 0.653078f, 0.653291f,
		0.653503f, 0.653716f, 0.653928f, 0.654141f, 0.654353f, 0.654565f,
		0.654778f, 0.65499f, 0.655203f, 0.655415f, 0.655627f, 0.65584f,
		0.656052f, 0.656265f, 0.656477f, 0.65669f, 0.656902f, 0.657114f,
		0.657327f, 0.657539f, 0.657752f, 0.657964f, 0.658176f, 0.658389f,
		0.658601f, 0.658814f, 0.659026f, 0.659238f, 0.659451f, 0.659663f,
		0.659876f, 0.660088f, 0.660301f, 0.660513f, 0.660725f, 0.660938f,
		0.66115f, 0.661363f, 0.661575f, 0.661788f, 0.662f, 0.662212f,
		0.662425f, 0.662637f, 0.66285f, 0.695221f, 0.744007f, 0.792791f,
		0.809131f, 0.809343f, 0.809555f, 0.809768f, 0.80998f, 0.810193f,
		0.810405f, 0.810618f, 0.81083f, 0.811042f, 0.811255f, 0.811467f,
		0.81168f, 0.811892f, 0.812104f, 0.812317f, 0.812529f, 0.812742f,
		0.812954f, 0.813166f, 0.813379f, 0.813591f, 0.813804f, 0.814016f,
		0.814229f, 0.814441f, 0.814653f, 0.814866f, 0.815078f, 0.815291f,
		0.815503f, 0.815715f, 0.815928f, 0.81614f, 0.816353f, 0.816565f,
		0.816778f, 0.81699f, 0.817202f, 0.817415f, 0.817627f, 0.81784f,
		0.818052f, 0.818264f, 0.818477f, 0.818689f, 0.818902f, 0.819114f,
		0.819327f, 0.819539f, 0.819751f, 0.819964f, 0.820176f, 0.837595f,
		0.860112f, 0.882627f, 0.905143f, 0.927659f, 0.950175f, 0.972691f,
		0.995206f, 1.f, 1.f, 1.f, 1.f, 1.f,
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
		1.f, 1.f
	};
};

template <int NV>
using cable_table1_t = wrap::data<control::cable_table<parameter::plain<minmax3_t<NV>, 0>>, 
                                  data::embedded::table<cable_table1_t_data>>;
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
                                        parameter::plain<pma_t<NV>, 0>, 
                                        parameter::plain<cable_table1_t<NV>, 0>>;

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

template <int NV> using minmax_t = minmax3_t<NV>;

struct cable_table_t_data
{
	span<float, 512> data =
	{
		0.f, 0.00742543f, 0.0148509f, 0.0222763f, 0.0297018f, 0.0371273f,
		0.0445527f, 0.0519782f, 0.0594036f, 0.0668291f, 0.0742545f, 0.0816799f,
		0.0891054f, 0.0965309f, 0.103956f, 0.111382f, 0.118807f, 0.126233f,
		0.133658f, 0.141084f, 0.148509f, 0.155934f, 0.16336f, 0.170785f,
		0.178211f, 0.185636f, 0.193062f, 0.200487f, 0.207913f, 0.215338f,
		0.222764f, 0.230189f, 0.237614f, 0.24504f, 0.252465f, 0.259891f,
		0.267316f, 0.274742f, 0.282167f, 0.289593f, 0.297018f, 0.304443f,
		0.311869f, 0.319294f, 0.32672f, 0.334145f, 0.341571f, 0.348752f,
		0.353515f, 0.358278f, 0.363041f, 0.367804f, 0.372567f, 0.37733f,
		0.382093f, 0.386856f, 0.391619f, 0.396382f, 0.401145f, 0.405908f,
		0.410671f, 0.415433f, 0.420196f, 0.424959f, 0.429722f, 0.434485f,
		0.439248f, 0.444011f, 0.448774f, 0.453537f, 0.4583f, 0.463063f,
		0.467826f, 0.469336f, 0.463261f, 0.460231f, 0.458152f, 0.456382f,
		0.454894f, 0.45359f, 0.452479f, 0.451367f, 0.450516f, 0.449665f,
		0.448826f, 0.448166f, 0.447506f, 0.446846f, 0.446285f, 0.445771f,
		0.445257f, 0.444743f, 0.444325f, 0.443926f, 0.443528f, 0.443129f,
		0.442781f, 0.442476f, 0.442171f, 0.441866f, 0.441561f, 0.441316f,
		0.441088f, 0.44086f, 0.440632f, 0.440404f, 0.440214f, 0.440051f,
		0.439888f, 0.439725f, 0.439562f, 0.439399f, 0.439287f, 0.439179f,
		0.439071f, 0.438964f, 0.438856f, 0.438748f, 0.438679f, 0.438619f,
		0.438559f, 0.438499f, 0.438438f, 0.438378f, 0.438329f, 0.43831f,
		0.438291f, 0.438273f, 0.438254f, 0.438235f, 0.438216f, 0.438189f,
		0.438137f, 0.438085f, 0.438033f, 0.437981f, 0.437909f, 0.437743f,
		0.437576f, 0.43741f, 0.437244f, 0.43702f, 0.436723f, 0.436425f,
		0.436127f, 0.435828f, 0.435377f, 0.434927f, 0.434477f, 0.434026f,
		0.433412f, 0.432783f, 0.432153f, 0.431492f, 0.430649f, 0.429807f,
		0.428964f, 0.427938f, 0.426838f, 0.425738f, 0.424446f, 0.423027f,
		0.421607f, 0.419859f, 0.418036f, 0.416022f, 0.413672f, 0.411154f,
		0.408083f, 0.404565f, 0.400455f, 0.39478f, 0.386649f, 0.37182f,
		0.374877f, 0.377935f, 0.380993f, 0.38405f, 0.387108f, 0.390166f,
		0.393224f, 0.396281f, 0.399339f, 0.402397f, 0.405455f, 0.408512f,
		0.41157f, 0.414628f, 0.417685f, 0.420743f, 0.423801f, 0.426858f,
		0.429916f, 0.432974f, 0.436032f, 0.439089f, 0.442147f, 0.445205f,
		0.448263f, 0.45132f, 0.454378f, 0.457436f, 0.460493f, 0.463551f,
		0.466609f, 0.469666f, 0.472724f, 0.475782f, 0.47884f, 0.481897f,
		0.484955f, 0.488013f, 0.49107f, 0.494128f, 0.497186f, 0.500244f,
		0.503301f, 0.506359f, 0.509417f, 0.512474f, 0.515532f, 0.51859f,
		0.521648f, 0.524705f, 0.527763f, 0.530821f, 0.533878f, 0.536936f,
		0.539994f, 0.543052f, 0.546109f, 0.549167f, 0.552225f, 0.555282f,
		0.55834f, 0.561398f, 0.564456f, 0.567513f, 0.570571f, 0.573629f,
		0.576686f, 0.579744f, 0.582802f, 0.58586f, 0.588917f, 0.591975f,
		0.595033f, 0.59809f, 0.601148f, 0.604206f, 0.607264f, 0.610321f,
		0.613379f, 0.616437f, 0.619449f, 0.622417f, 0.625384f, 0.628351f,
		0.631318f, 0.634286f, 0.637253f, 0.64022f, 0.643187f, 0.646154f,
		0.649122f, 0.652089f, 0.655056f, 0.658023f, 0.66099f, 0.663958f,
		0.666925f, 0.669892f, 0.672859f, 0.675826f, 0.678794f, 0.681761f,
		0.684728f, 0.687695f, 0.690663f, 0.69363f, 0.696597f, 0.699564f,
		0.702531f, 0.705499f, 0.708466f, 0.711433f, 0.7144f, 0.717367f,
		0.720335f, 0.723302f, 0.726269f, 0.729236f, 0.732204f, 0.735171f,
		0.738138f, 0.741105f, 0.744072f, 0.74704f, 0.750007f, 0.752974f,
		0.755941f, 0.758908f, 0.761876f, 0.764843f, 0.76781f, 0.770777f,
		0.773744f, 0.776712f, 0.779679f, 0.782646f, 0.785613f, 0.788581f,
		0.791548f, 0.794515f, 0.797482f, 0.800449f, 0.803417f, 0.806384f,
		0.809351f, 0.812318f, 0.815285f, 0.818253f, 0.82122f, 0.824187f,
		0.827154f, 0.830121f, 0.833089f, 0.836056f, 0.839023f, 0.84199f,
		0.844957f, 0.847925f, 0.850892f, 0.853859f, 0.856826f, 0.859794f,
		0.862761f, 0.865728f, 0.868695f, 0.871662f, 0.87463f, 0.877597f,
		0.880564f, 0.883531f, 0.886498f, 0.889466f, 0.892433f, 0.8954f,
		0.898367f, 0.901335f, 0.904302f, 0.907269f, 0.910236f, 0.913203f,
		0.91617f, 0.919138f, 0.922105f, 0.925072f, 0.928039f, 0.931007f,
		0.933974f, 0.936941f, 0.939908f, 0.942875f, 0.945843f, 0.94881f,
		0.951777f, 0.954744f, 0.957711f, 0.960679f, 0.963646f, 0.966613f,
		0.96958f, 0.972548f, 0.975515f, 0.978482f, 0.981449f, 0.984416f,
		0.987384f, 0.990351f, 0.993318f, 0.996285f, 0.999252f, 1.f,
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
		1.f, 1.f
	};
};

template <int NV>
using cable_table_t = wrap::data<control::cable_table<parameter::plain<minmax_t<NV>, 0>>, 
                                 data::embedded::table<cable_table_t_data>>;

template <int NV>
using Punch_smooth_mod = parameter::chain<ranges::Identity, 
                                          parameter::plain<minmax1_t<NV>, 0>, 
                                          parameter::plain<minmax2_t<NV>, 0>, 
                                          parameter::plain<pma1_t<NV>, 0>, 
                                          parameter::plain<project::DrumSlam<NV>, 0>, 
                                          parameter::plain<cable_table_t<NV>, 0>>;

template <int NV>
using Punch_smooth_t = wrap::mod<Punch_smooth_mod<NV>, 
                                 control::smoothed_parameter<NV, smoothers::linear_ramp<NV>>>;

template <int NV>
using split_t = container::split<parameter::empty, 
                                 wrap::fix<1, minmax1_t<NV>>, 
                                 minmax2_t<NV>, 
                                 cable_table_t<NV>, 
                                 minmax_t<NV>>;

template <int NV>
using split1_t = container::split<parameter::empty, 
                                  wrap::fix<1, cable_table1_t<NV>>, 
                                  minmax3_t<NV>>;

template <int NV>
using modchain_t_ = container::chain<parameter::empty, 
                                     wrap::fix<1, split_t<NV>>, 
                                     split1_t<NV>, 
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
using filterminmax_t = control::minmax<NV, 
                                       parameter::plain<filters::svf_eq<NV>, 0>>;

template <int NV>
using chain_t = container::chain<parameter::empty, 
                                 wrap::fix<2, filterminmax_t<NV>>, 
                                 pma_t<NV>, 
                                 project::Drive<NV>, 
                                 project::Tube2<NV>, 
                                 project::Tube2<NV>, 
                                 core::gain<NV>, 
                                 faust_t<NV>, 
                                 project::DrumSlam<NV>, 
                                 filters::svf_eq<NV>, 
                                 project::Focus<NV>, 
                                 core::gain<NV>>;

template <int NV>
using wet_path_t = container::chain<parameter::empty, 
                                    wrap::fix<2, chain_t<NV>>, 
                                    core::gain<NV>, 
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
using Punch = parameter::plain<Boxer_impl::Punch_smooth_t<NV>, 
                               0>;
template <int NV>
using Wut = parameter::plain<Boxer_impl::wut_smooth_t<NV>, 
                             0>;
template <int NV>
using Mix = parameter::plain<Boxer_impl::dry_wet1_t<NV>, 
                             0>;
using _16oz = parameter::empty;
template <int NV>
using Filter = parameter::plain<Boxer_impl::filterminmax_t<NV>, 
                                0>;
template <int NV>
using OutGain = parameter::plain<core::gain<NV>, 0>;
template <int NV>
using Boxer_t_plist = parameter::list<Punch<NV>, 
                                      Wut<NV>, 
                                      Mix<NV>, 
                                      _16oz, 
                                      Filter<NV>, 
                                      OutGain<NV>>;
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
		SNEX_METADATA_ENCODED_PARAMETERS(94)
		{
			0x005B, 0x0000, 0x5000, 0x6E75, 0x6863, 0x0000, 0x0000, 0x0000, 
            0x8000, 0xFC3F, 0x0B47, 0x003F, 0x8000, 0x003F, 0x0000, 0x5B00, 
            0x0001, 0x0000, 0x7557, 0x0074, 0x0000, 0x0000, 0x0000, 0x3F80, 
            0xB418, 0x3F1E, 0x0000, 0x3F80, 0x0000, 0x0000, 0x025B, 0x0000, 
            0x4D00, 0x7869, 0x0000, 0x0000, 0x0000, 0x8000, 0x003F, 0x8000, 
            0x003F, 0x8000, 0x003F, 0x0000, 0x5B00, 0x0003, 0x0000, 0x315F, 
            0x6F36, 0x007A, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 
            0x0000, 0x3F80, 0x0000, 0x3F80, 0x045B, 0x0000, 0x4600, 0x6C69, 
            0x6574, 0x0072, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x3F80, 
            0x0000, 0x3F80, 0x0000, 0x0000, 0x055B, 0x0000, 0x4F00, 0x7475, 
            0x6147, 0x6E69, 0x0000, 0xC800, 0x00C2, 0x0000, 0x0000, 0x0000, 
            0x3E00, 0xAD83, 0xCD40, 0xCCCC, 0x003D, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& wut_smooth = this->getT(0);                           // Boxer_impl::wut_smooth_t<NV>
		auto& Punch_smooth = this->getT(1);                         // Boxer_impl::Punch_smooth_t<NV>
		auto& modchain = this->getT(2);                             // Boxer_impl::modchain_t<NV>
		auto& split = this->getT(2).getT(0);                        // Boxer_impl::split_t<NV>
		auto& minmax1 = this->getT(2).getT(0).getT(0);              // Boxer_impl::minmax1_t<NV>
		auto& minmax2 = this->getT(2).getT(0).getT(1);              // Boxer_impl::minmax2_t<NV>
		auto& cable_table = this->getT(2).getT(0).getT(2);          // Boxer_impl::cable_table_t<NV>
		auto& minmax = this->getT(2).getT(0).getT(3);               // Boxer_impl::minmax_t<NV>
		auto& split1 = this->getT(2).getT(1);                       // Boxer_impl::split1_t<NV>
		auto& cable_table1 = this->getT(2).getT(1).getT(0);         // Boxer_impl::cable_table1_t<NV>
		auto& minmax3 = this->getT(2).getT(1).getT(1);              // Boxer_impl::minmax3_t<NV>
		auto& pma1 = this->getT(2).getT(2);                         // Boxer_impl::pma1_t<NV>
		auto& dry_wet1 = this->getT(3);                             // Boxer_impl::dry_wet1_t<NV>
		auto& dry_path = this->getT(3).getT(0);                     // Boxer_impl::dry_path_t<NV>
		auto& dry_wet_mixer = this->getT(3).getT(0).getT(0);        // Boxer_impl::dry_wet_mixer_t<NV>
		auto& dry_gain = this->getT(3).getT(0).getT(1);             // core::gain<NV>
		auto& wet_path = this->getT(3).getT(1);                     // Boxer_impl::wet_path_t<NV>
		auto& chain = this->getT(3).getT(1).getT(0);                // Boxer_impl::chain_t<NV>
		auto& filterminmax = this->getT(3).getT(1).getT(0).getT(0); // Boxer_impl::filterminmax_t<NV>
		auto& pma = this->getT(3).getT(1).getT(0).getT(1);          // Boxer_impl::pma_t<NV>
		auto& Drive = this->getT(3).getT(1).getT(0).getT(2);        // project::Drive<NV>
		auto& Tube2 = this->getT(3).getT(1).getT(0).getT(3);        // project::Tube2<NV>
		auto& Tube3 = this->getT(3).getT(1).getT(0).getT(4);        // project::Tube2<NV>
		auto& gain3 = this->getT(3).getT(1).getT(0).getT(5);        // core::gain<NV>
		auto& faust = this->getT(3).getT(1).getT(0).getT(6);        // Boxer_impl::faust_t<NV>
		auto& DrumSlam = this->getT(3).getT(1).getT(0).getT(7);     // project::DrumSlam<NV>
		auto& svf_eq = this->getT(3).getT(1).getT(0).getT(8);       // filters::svf_eq<NV>
		auto& Focus = this->getT(3).getT(1).getT(0).getT(9);        // project::Focus<NV>
		auto& gain = this->getT(3).getT(1).getT(0).getT(10);        // core::gain<NV>
		auto& gain1 = this->getT(3).getT(1).getT(1);                // core::gain<NV>
		auto& wet_gain = this->getT(3).getT(1).getT(2);             // core::gain<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		dry_wet1.getParameterT(0).connectT(0, dry_wet_mixer); // DryWet -> dry_wet_mixer::Value
		this->getParameterT(0).connectT(0, Punch_smooth);     // Punch -> Punch_smooth::Value
		
		this->getParameterT(1).connectT(0, wut_smooth); // Wut -> wut_smooth::Value
		
		this->getParameterT(2).connectT(0, dry_wet1); // Mix -> dry_wet1::DryWet
		
		this->getParameterT(4).connectT(0, filterminmax); // Filter -> filterminmax::Value
		
		this->getParameterT(5).connectT(0, gain1); // OutGain -> gain1::Gain
		
		// Modulation Connections ------------------------------------------------------------------
		
		pma1.getWrappedObject().getParameter().connectT(0, Drive);           // pma1 -> Drive::Drive
		pma.getWrappedObject().getParameter().connectT(0, Tube2);            // pma -> Tube2::Tube
		pma.getWrappedObject().getParameter().connectT(1, Tube3);            // pma -> Tube3::Tube
		minmax3.getWrappedObject().getParameter().connectT(0, gain3);        // minmax3 -> gain3::Gain
		cable_table1.getWrappedObject().getParameter().connectT(0, minmax3); // cable_table1 -> minmax3::Value
		wut_smooth.getParameter().connectT(0, pma1);                         // wut_smooth -> pma1::Multiply
		wut_smooth.getParameter().connectT(1, pma);                          // wut_smooth -> pma::Value
		wut_smooth.getParameter().connectT(2, cable_table1);                 // wut_smooth -> cable_table1::Value
		auto& faust_p = faust.getWrappedObject().getParameter();
		minmax1.getWrappedObject().getParameter().connectT(0, faust);      // minmax1 -> faust::Attack
		minmax2.getWrappedObject().getParameter().connectT(0, faust);      // minmax2 -> faust::Sustain
		minmax.getWrappedObject().getParameter().connectT(0, gain);        // minmax -> gain::Gain
		cable_table.getWrappedObject().getParameter().connectT(0, minmax); // cable_table -> minmax::Value
		Punch_smooth.getParameter().connectT(0, minmax1);                  // Punch_smooth -> minmax1::Value
		Punch_smooth.getParameter().connectT(1, minmax2);                  // Punch_smooth -> minmax2::Value
		Punch_smooth.getParameter().connectT(2, pma1);                     // Punch_smooth -> pma1::Value
		Punch_smooth.getParameter().connectT(3, DrumSlam);                 // Punch_smooth -> DrumSlam::Drive
		Punch_smooth.getParameter().connectT(4, cable_table);              // Punch_smooth -> cable_table::Value
		auto& dry_wet_mixer_p = dry_wet_mixer.getWrappedObject().getParameter();
		dry_wet_mixer_p.getParameterT(0).connectT(0, dry_gain);             // dry_wet_mixer -> dry_gain::Gain
		dry_wet_mixer_p.getParameterT(1).connectT(0, wet_gain);             // dry_wet_mixer -> wet_gain::Gain
		filterminmax.getWrappedObject().getParameter().connectT(0, svf_eq); // filterminmax -> svf_eq::Frequency
		
		// Default Values --------------------------------------------------------------------------
		
		;                                 // wut_smooth::Value is automated
		wut_smooth.setParameterT(1, 0.1); // control::smoothed_parameter::SmoothingTime
		wut_smooth.setParameterT(2, 1.);  // control::smoothed_parameter::Enabled
		
		;                                   // Punch_smooth::Value is automated
		Punch_smooth.setParameterT(1, 0.1); // control::smoothed_parameter::SmoothingTime
		Punch_smooth.setParameterT(2, 1.);  // control::smoothed_parameter::Enabled
		
		;                                      // minmax1::Value is automated
		minmax1.setParameterT(1, 6.66134e-16); // control::minmax::Minimum
		minmax1.setParameterT(2, 9.24388);     // control::minmax::Maximum
		minmax1.setParameterT(3, 1.);          // control::minmax::Skew
		minmax1.setParameterT(4, 0.);          // control::minmax::Step
		minmax1.setParameterT(5, 0.);          // control::minmax::Polarity
		
		;                                     // minmax2::Value is automated
		minmax2.setParameterT(1, -0.0279075); // control::minmax::Minimum
		minmax2.setParameterT(2, 6.98184);    // control::minmax::Maximum
		minmax2.setParameterT(3, 1.);         // control::minmax::Skew
		minmax2.setParameterT(4, 0.);         // control::minmax::Step
		minmax2.setParameterT(5, 0.);         // control::minmax::Polarity
		
		; // cable_table::Value is automated
		
		;                                  // minmax::Value is automated
		minmax.setParameterT(1, -9.9);     // control::minmax::Minimum
		minmax.setParameterT(2, -2.7);     // control::minmax::Maximum
		minmax.setParameterT(3, 0.684427); // control::minmax::Skew
		minmax.setParameterT(4, 0.);       // control::minmax::Step
		minmax.setParameterT(5, 1.);       // control::minmax::Polarity
		
		; // cable_table1::Value is automated
		
		;                                  // minmax3::Value is automated
		minmax3.setParameterT(1, -6);      // control::minmax::Minimum
		minmax3.setParameterT(2, 0.);      // control::minmax::Maximum
		minmax3.setParameterT(3, 3.25888); // control::minmax::Skew
		minmax3.setParameterT(4, 0.);      // control::minmax::Step
		minmax3.setParameterT(5, 1.);      // control::minmax::Polarity
		
		;                          // pma1::Value is automated
		;                          // pma1::Multiply is automated
		pma1.setParameterT(2, 0.); // control::pma::Add
		
		; // dry_wet1::DryWet is automated
		
		; // dry_wet_mixer::Value is automated
		
		;                               // dry_gain::Gain is automated
		dry_gain.setParameterT(1, 20.); // core::gain::Smoothing
		dry_gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                                        // filterminmax::Value is automated
		filterminmax.setParameterT(1, 1184.49);  // control::minmax::Minimum
		filterminmax.setParameterT(2, 20000.);   // control::minmax::Maximum
		filterminmax.setParameterT(3, 0.229905); // control::minmax::Skew
		filterminmax.setParameterT(4, 0.);       // control::minmax::Step
		filterminmax.setParameterT(5, 0.);       // control::minmax::Polarity
		
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
		
		;                            // gain3::Gain is automated
		gain3.setParameterT(1, 20.); // core::gain::Smoothing
		gain3.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                               // faust::Attack is automated
		;                               // faust::Sustain is automated
		faust.setParameterT(2, 10.);    // core::faust::LowCutoff
		faust.setParameterT(3, 20000.); // core::faust::HighCutoff
		faust.setParameterT(4, 0.);     // core::faust::Monitorselectedband
		
		;                              // DrumSlam::Drive is automated
		DrumSlam.setParameterT(1, 1.); // project::DrumSlam::Output
		DrumSlam.setParameterT(2, 1.); // project::DrumSlam::DryWet
		
		;                                 // svf_eq::Frequency is automated
		svf_eq.setParameterT(1, 1.57713); // filters::svf_eq::Q
		svf_eq.setParameterT(2, 0.);      // filters::svf_eq::Gain
		svf_eq.setParameterT(3, 0.01);    // filters::svf_eq::Smoothing
		svf_eq.setParameterT(4, 0.);      // filters::svf_eq::Mode
		svf_eq.setParameterT(5, 1.);      // filters::svf_eq::Enabled
		
		Focus.setParameterT(0, 0.); // project::Focus::Boost
		Focus.setParameterT(1, 0.); // project::Focus::Focus
		Focus.setParameterT(2, 0.); // project::Focus::Mode
		Focus.setParameterT(3, 1.); // project::Focus::Output
		Focus.setParameterT(4, 1.); // project::Focus::DryWet
		
		;                           // gain::Gain is automated
		gain.setParameterT(1, 20.); // core::gain::Smoothing
		gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                            // gain1::Gain is automated
		gain1.setParameterT(1, 20.); // core::gain::Smoothing
		gain1.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                               // wet_gain::Gain is automated
		wet_gain.setParameterT(1, 20.); // core::gain::Smoothing
		wet_gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		this->setParameterT(0, 0.544067);
		this->setParameterT(1, 0.619935);
		this->setParameterT(2, 1.);
		this->setParameterT(3, 0.);
		this->setParameterT(4, 1.);
		this->setParameterT(5, 0.);
		this->setExternalData({}, -1);
	}
	~instance() override
	{
		// Cleanup external data references --------------------------------------------------------
		
		this->setExternalData({}, -1);
	}
	
	static constexpr bool isPolyphonic() { return NV > 1; };
	
	static constexpr bool hasTail() { return true; };
	
	static constexpr bool isSuspendedOnSilence() { return true; };
	
	void setExternalData(const ExternalData& b, int index)
	{
		// External Data Connections ---------------------------------------------------------------
		
		this->getT(2).getT(0).getT(2).setExternalData(b, index); // Boxer_impl::cable_table_t<NV>
		this->getT(2).getT(1).getT(0).setExternalData(b, index); // Boxer_impl::cable_table1_t<NV>
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


