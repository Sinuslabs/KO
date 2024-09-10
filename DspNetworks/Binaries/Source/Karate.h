#pragma once

#include "DrumSlam.h"
#include "Focus.h"
#include "Drive.h"
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

template <int NV>
using minmax2_t = control::minmax<NV, 
                                  parameter::plain<project::Drive<NV>, 0>>;

template <int NV>
using minmax_t = control::minmax<NV, 
                                 parameter::plain<core::gain<NV>, 0>>;

struct cable_table1_t_data
{
	span<float, 512> data =
	{
		0.f, 0.00271022f, 0.00542051f, 0.00813073f, 0.010841f, 0.0135512f,
		0.0162615f, 0.0189717f, 0.021682f, 0.0243922f, 0.0271025f, 0.0298127f,
		0.0325229f, 0.0352332f, 0.0379434f, 0.0406537f, 0.0433639f, 0.0460742f,
		0.0487844f, 0.0514947f, 0.0542049f, 0.0569152f, 0.0596254f, 0.0623357f,
		0.0650459f, 0.0677561f, 0.0704664f, 0.0731766f, 0.0758869f, 0.0785971f,
		0.0813074f, 0.0840176f, 0.0867279f, 0.0894381f, 0.0921484f, 0.0948586f,
		0.0975689f, 0.100279f, 0.102989f, 0.1057f, 0.10841f, 0.11112f,
		0.11383f, 0.116541f, 0.119251f, 0.121961f, 0.124671f, 0.127382f,
		0.130092f, 0.132802f, 0.135512f, 0.138223f, 0.140933f, 0.143643f,
		0.146353f, 0.149063f, 0.151774f, 0.154484f, 0.157194f, 0.159904f,
		0.162615f, 0.165325f, 0.168035f, 0.170745f, 0.173456f, 0.176166f,
		0.178876f, 0.181586f, 0.184297f, 0.187007f, 0.189717f, 0.192427f,
		0.195138f, 0.197848f, 0.200558f, 0.203268f, 0.205979f, 0.208689f,
		0.211399f, 0.214109f, 0.21682f, 0.21953f, 0.22224f, 0.22495f,
		0.227661f, 0.230371f, 0.233081f, 0.235791f, 0.238502f, 0.241212f,
		0.243922f, 0.246632f, 0.249343f, 0.252053f, 0.254763f, 0.257473f,
		0.260184f, 0.262894f, 0.265604f, 0.268314f, 0.271025f, 0.273735f,
		0.276445f, 0.279155f, 0.281865f, 0.284576f, 0.287286f, 0.289996f,
		0.292706f, 0.295417f, 0.298127f, 0.300837f, 0.303548f, 0.306258f,
		0.308968f, 0.311678f, 0.314388f, 0.317099f, 0.319809f, 0.322519f,
		0.325229f, 0.32794f, 0.33065f, 0.33336f, 0.33607f, 0.338781f,
		0.341491f, 0.344201f, 0.346911f, 0.349622f, 0.352332f, 0.355042f,
		0.357752f, 0.360463f, 0.363173f, 0.365883f, 0.368593f, 0.371304f,
		0.374014f, 0.376724f, 0.379434f, 0.382145f, 0.384855f, 0.387565f,
		0.390275f, 0.392986f, 0.395696f, 0.398406f, 0.401116f, 0.403827f,
		0.406537f, 0.409247f, 0.411957f, 0.414667f, 0.417378f, 0.420088f,
		0.422798f, 0.425508f, 0.428219f, 0.430929f, 0.433639f, 0.43635f,
		0.43906f, 0.44177f, 0.44448f, 0.447191f, 0.449901f, 0.452611f,
		0.455321f, 0.458031f, 0.460742f, 0.463452f, 0.466162f, 0.468872f,
		0.471583f, 0.474293f, 0.477003f, 0.479713f, 0.482424f, 0.485134f,
		0.487844f, 0.490554f, 0.493265f, 0.495975f, 0.498685f, 0.501395f,
		0.504106f, 0.506816f, 0.509526f, 0.512236f, 0.514947f, 0.517657f,
		0.520367f, 0.523077f, 0.525788f, 0.528498f, 0.531208f, 0.533918f,
		0.536629f, 0.539339f, 0.542049f, 0.544759f, 0.54747f, 0.55018f,
		0.55289f, 0.5556f, 0.558311f, 0.561021f, 0.563731f, 0.566441f,
		0.569152f, 0.571862f, 0.574572f, 0.577282f, 0.579993f, 0.582703f,
		0.585338f, 0.587871f, 0.590404f, 0.592937f, 0.59547f, 0.598003f,
		0.600536f, 0.60307f, 0.605603f, 0.608136f, 0.610669f, 0.613202f,
		0.615735f, 0.618268f, 0.620801f, 0.623334f, 0.625867f, 0.6284f,
		0.630933f, 0.633466f, 0.635999f, 0.638532f, 0.641065f, 0.643598f,
		0.646131f, 0.648664f, 0.651197f, 0.65373f, 0.656263f, 0.658796f,
		0.661329f, 0.663862f, 0.666395f, 0.668929f, 0.671462f, 0.673995f,
		0.676528f, 0.679061f, 0.681594f, 0.684127f, 0.685593f, 0.685992f,
		0.686391f, 0.68679f, 0.687189f, 0.687588f, 0.687988f, 0.688387f,
		0.688786f, 0.689239f, 0.689698f, 0.690156f, 0.690615f, 0.691074f,
		0.691533f, 0.691992f, 0.69245f, 0.692942f, 0.693464f, 0.693985f,
		0.694507f, 0.695029f, 0.69555f, 0.696072f, 0.696594f, 0.697139f,
		0.697727f, 0.698316f, 0.698904f, 0.699492f, 0.70008f, 0.700668f,
		0.701256f, 0.701873f, 0.702531f, 0.703189f, 0.703847f, 0.704506f,
		0.705164f, 0.705822f, 0.70648f, 0.707189f, 0.707922f, 0.708654f,
		0.709386f, 0.710119f, 0.710851f, 0.711583f, 0.712331f, 0.713142f,
		0.713953f, 0.714764f, 0.715575f, 0.716386f, 0.717197f, 0.718008f,
		0.718894f, 0.719788f, 0.720683f, 0.721577f, 0.722472f, 0.723366f,
		0.724261f, 0.725229f, 0.726213f, 0.727196f, 0.728179f, 0.729163f,
		0.730146f, 0.731129f, 0.732206f, 0.733284f, 0.734362f, 0.73544f,
		0.736518f, 0.737596f, 0.73871f, 0.739889f, 0.741069f, 0.742248f,
		0.743427f, 0.744606f, 0.745785f, 0.747067f, 0.748354f, 0.749642f,
		0.750929f, 0.752217f, 0.753505f, 0.754879f, 0.756283f, 0.757687f,
		0.759091f, 0.760494f, 0.761898f, 0.763399f, 0.764928f, 0.766457f,
		0.767986f, 0.769515f, 0.771046f, 0.77271f, 0.774374f, 0.776038f,
		0.777702f, 0.779365f, 0.7811f, 0.78291f, 0.78472f, 0.78653f,
		0.78834f, 0.790176f, 0.792144f, 0.794113f, 0.796081f, 0.79805f,
		0.80003f, 0.802171f, 0.804313f, 0.806454f, 0.808595f, 0.810772f,
		0.813102f, 0.815433f, 0.817763f, 0.820093f, 0.822533f, 0.825071f,
		0.827609f, 0.830147f, 0.832703f, 0.83547f, 0.838238f, 0.841005f,
		0.843772f, 0.846757f, 0.849778f, 0.8528f, 0.855821f, 0.859084f,
		0.862389f, 0.865694f, 0.869019f, 0.872643f, 0.876266f, 0.879889f,
		0.883691f, 0.887674f, 0.891657f, 0.895701f, 0.900094f, 0.904487f,
		0.908888f, 0.913753f, 0.918618f, 0.923541f, 0.928954f, 0.934368f,
		0.940047f, 0.946106f, 0.952165f, 0.958946f, 0.965775f, 0.973242f,
		0.981008f, 0.989522f, 0.998448f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f, 1.f, 0.988745f,
		0.97608f, 0.963415f, 0.950749f, 0.938084f, 0.925419f, 0.912754f,
		0.900088f, 0.887423f, 0.874758f, 0.862093f, 0.849428f, 0.836763f,
		0.824097f, 0.811432f, 0.798767f, 0.807564f, 0.81823f, 0.828895f,
		0.83956f, 0.850226f, 0.860891f, 0.871557f, 0.882222f, 0.892888f,
		0.903553f, 0.914218f, 0.924884f, 0.935549f, 0.946215f, 0.95688f,
		0.967546f, 0.978211f, 0.988876f, 0.999542f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
		1.f, 1.f
	};
};

template <int NV>
using cable_table1_t = wrap::data<control::cable_table<parameter::plain<minmax_t<NV>, 0>>, 
                                  data::embedded::table<cable_table1_t_data>>;

template <int NV>
using focus_smooth_mod = parameter::chain<ranges::Identity, 
                                          parameter::plain<minmax2_t<NV>, 0>, 
                                          parameter::plain<project::Focus<NV>, 0>, 
                                          parameter::plain<cable_table1_t<NV>, 0>>;

template <int NV>
using focus_smooth_t = wrap::mod<focus_smooth_mod<NV>, 
                                 control::smoothed_parameter<NV, smoothers::linear_ramp<NV>>>;
template <int NV>
using focus_slam_minmax_t = control::minmax<NV, 
                                            parameter::plain<focus_smooth_t<NV>, 0>>;

template <int NV>
using split_t = container::split<parameter::empty, 
                                 wrap::fix<1, minmax2_t<NV>>>;

template <int NV> using minmax1_t = minmax_t<NV>;

struct cable_table_t_data
{
	span<float, 512> data =
	{
		0.f, 0.00925654f, 0.0185131f, 0.0277696f, 0.0370261f, 0.0462826f,
		0.0555392f, 0.0647957f, 0.0740522f, 0.0833088f, 0.0925653f, 0.101822f,
		0.111078f, 0.120335f, 0.129591f, 0.138848f, 0.148104f, 0.157361f,
		0.166618f, 0.175874f, 0.185131f, 0.194387f, 0.203644f, 0.2129f,
		0.222157f, 0.231413f, 0.24067f, 0.249926f, 0.259183f, 0.268439f,
		0.277696f, 0.286952f, 0.296209f, 0.305466f, 0.314722f, 0.323979f,
		0.333235f, 0.342492f, 0.351748f, 0.361005f, 0.370261f, 0.379518f,
		0.388774f, 0.398031f, 0.407287f, 0.416249f, 0.422146f, 0.428044f,
		0.433942f, 0.439582f, 0.445015f, 0.450448f, 0.455881f, 0.460951f,
		0.465959f, 0.470967f, 0.475975f, 0.480598f, 0.485216f, 0.489834f,
		0.494452f, 0.498728f, 0.502988f, 0.507247f, 0.511506f, 0.515516f,
		0.519443f, 0.523371f, 0.527298f, 0.531107f, 0.534728f, 0.538348f,
		0.541968f, 0.545589f, 0.548966f, 0.552301f, 0.555636f, 0.558971f,
		0.561666f, 0.5608f, 0.559934f, 0.559068f, 0.558202f, 0.557336f,
		0.55647f, 0.555604f, 0.554738f, 0.553872f, 0.553006f, 0.55214f,
		0.551274f, 0.550408f, 0.549542f, 0.548676f, 0.54781f, 0.546944f,
		0.546078f, 0.545212f, 0.544346f, 0.54348f, 0.542614f, 0.541748f,
		0.540882f, 0.540016f, 0.53915f, 0.538284f, 0.537418f, 0.536552f,
		0.535686f, 0.53482f, 0.533954f, 0.533088f, 0.532222f, 0.531356f,
		0.53049f, 0.529624f, 0.528758f, 0.527892f, 0.527026f, 0.52616f,
		0.525294f, 0.524428f, 0.523562f, 0.522696f, 0.52183f, 0.520964f,
		0.520098f, 0.519232f, 0.518366f, 0.5175f, 0.516248f, 0.51386f,
		0.511472f, 0.509083f, 0.506695f, 0.504307f, 0.501919f, 0.499531f,
		0.497143f, 0.494755f, 0.492367f, 0.489979f, 0.487591f, 0.485203f,
		0.482815f, 0.480427f, 0.478039f, 0.475651f, 0.473263f, 0.470875f,
		0.468487f, 0.466099f, 0.46371f, 0.461322f, 0.458934f, 0.456546f,
		0.454158f, 0.45177f, 0.449382f, 0.446994f, 0.444606f, 0.442218f,
		0.43983f, 0.437442f, 0.435054f, 0.432666f, 0.430278f, 0.42789f,
		0.425502f, 0.423114f, 0.420726f, 0.418338f, 0.41595f, 0.413562f,
		0.411173f, 0.408785f, 0.406397f, 0.404009f, 0.401621f, 0.399233f,
		0.396845f, 0.394457f, 0.392069f, 0.389681f, 0.387293f, 0.384905f,
		0.382517f, 0.380129f, 0.377741f, 0.375353f, 0.372965f, 0.370577f,
		0.368189f, 0.3658f, 0.363412f, 0.361024f, 0.360262f, 0.36212f,
		0.363978f, 0.365836f, 0.367694f, 0.369552f, 0.37141f, 0.373269f,
		0.375127f, 0.376985f, 0.378843f, 0.380701f, 0.382559f, 0.384417f,
		0.386275f, 0.388133f, 0.389992f, 0.39185f, 0.393708f, 0.395566f,
		0.397424f, 0.399282f, 0.40114f, 0.402998f, 0.404856f, 0.406714f,
		0.408573f, 0.410431f, 0.412289f, 0.414147f, 0.416005f, 0.417863f,
		0.419721f, 0.421579f, 0.423437f, 0.425296f, 0.427154f, 0.429012f,
		0.43087f, 0.432728f, 0.434586f, 0.436444f, 0.438302f, 0.44016f,
		0.442019f, 0.443877f, 0.445735f, 0.447593f, 0.449451f, 0.451309f,
		0.453167f, 0.455025f, 0.456883f, 0.458742f, 0.4606f, 0.462458f,
		0.464316f, 0.466174f, 0.468032f, 0.46989f, 0.471748f, 0.473606f,
		0.475464f, 0.477323f, 0.479181f, 0.481039f, 0.482897f, 0.484755f,
		0.486613f, 0.488471f, 0.490329f, 0.492187f, 0.494046f, 0.495904f,
		0.497762f, 0.49962f, 0.501478f, 0.503336f, 0.505194f, 0.507052f,
		0.50891f, 0.510769f, 0.512627f, 0.514485f, 0.516343f, 0.518201f,
		0.520059f, 0.521917f, 0.523775f, 0.525633f, 0.527492f, 0.52935f,
		0.531208f, 0.533066f, 0.534924f, 0.536782f, 0.53864f, 0.540498f,
		0.542356f, 0.544214f, 0.546073f, 0.547931f, 0.549789f, 0.551647f,
		0.553505f, 0.555363f, 0.557221f, 0.559079f, 0.560937f, 0.562796f,
		0.564654f, 0.566512f, 0.56837f, 0.570228f, 0.572086f, 0.573944f,
		0.575802f, 0.57766f, 0.579518f, 0.581377f, 0.583235f, 0.585093f,
		0.586951f, 0.588809f, 0.590667f, 0.592525f, 0.594383f, 0.596241f,
		0.5981f, 0.599958f, 0.601816f, 0.603674f, 0.605532f, 0.60739f,
		0.609248f, 0.611106f, 0.612965f, 0.614823f, 0.616681f, 0.618539f,
		0.620397f, 0.622255f, 0.624113f, 0.625971f, 0.627829f, 0.629687f,
		0.631546f, 0.633404f, 0.635262f, 0.63712f, 0.638978f, 0.640836f,
		0.642694f, 0.644552f, 0.64641f, 0.648268f, 0.650127f, 0.651985f,
		0.653843f, 0.655701f, 0.657559f, 0.659417f, 0.661275f, 0.663133f,
		0.664991f, 0.666849f, 0.668708f, 0.670566f, 0.672424f, 0.674282f,
		0.67614f, 0.677998f, 0.679856f, 0.681714f, 0.683573f, 0.685431f,
		0.687289f, 0.689147f, 0.691005f, 0.692863f, 0.694721f, 0.696579f,
		0.698437f, 0.700295f, 0.702154f, 0.704012f, 0.70587f, 0.707728f,
		0.709586f, 0.711444f, 0.713302f, 0.71516f, 0.717018f, 0.718877f,
		0.720735f, 0.722593f, 0.724451f, 0.726309f, 0.728167f, 0.730025f,
		0.731883f, 0.733741f, 0.7356f, 0.737458f, 0.739316f, 0.741174f,
		0.743421f, 0.745775f, 0.748129f, 0.750483f, 0.752837f, 0.755191f,
		0.757545f, 0.759899f, 0.762253f, 0.764607f, 0.766961f, 0.769315f,
		0.771668f, 0.774022f, 0.776376f, 0.77873f, 0.781084f, 0.783438f,
		0.785792f, 0.788146f, 0.7905f, 0.792854f, 0.795208f, 0.797562f,
		0.799916f, 0.80227f, 0.804624f, 0.806977f, 0.809331f, 0.811685f,
		0.814039f, 0.816393f, 0.818747f, 0.821101f, 0.823455f, 0.825809f,
		0.828163f, 0.830517f, 0.832871f, 0.835225f, 0.837579f, 0.839933f,
		0.842286f, 0.84464f, 0.846994f, 0.849348f, 0.851702f, 0.854056f,
		0.85641f, 0.858764f, 0.861118f, 0.863472f, 0.865826f, 0.86818f,
		0.870534f, 0.872888f, 0.875242f, 0.877595f, 0.879949f, 0.882303f,
		0.884657f, 0.887011f, 0.889365f, 0.891719f, 0.894073f, 0.896427f,
		0.898781f, 0.901135f, 0.903489f, 0.905843f, 0.908197f, 0.910551f,
		0.912904f, 0.915258f, 0.917612f, 0.919966f, 0.92232f, 0.924674f,
		0.927028f, 0.929382f, 0.931736f, 0.93409f, 0.936444f, 0.938798f,
		0.941152f, 0.943506f, 0.94586f, 0.948213f, 0.950567f, 0.952921f,
		0.955275f, 0.957629f, 0.959983f, 0.962337f, 0.964691f, 0.967045f,
		0.969399f, 0.971753f, 0.974107f, 0.976461f, 0.978815f, 0.981169f,
		0.983522f, 0.985876f, 0.98823f, 0.990584f, 0.992938f, 0.995292f,
		0.997646f, 1.f
	};
};

template <int NV>
using cable_table_t = wrap::data<control::cable_table<parameter::plain<minmax1_t<NV>, 0>>, 
                                 data::embedded::table<cable_table_t_data>>;

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
                                         faders::cosine_half>;

template <int NV>
using dry_path1_t = container::chain<parameter::empty, 
                                     wrap::fix<2, dry_wet_mixer1_t<NV>>, 
                                     core::gain<NV>>;

using band1_t = container::chain<parameter::empty, 
                                 wrap::fix<2, jdsp::jlinkwitzriley>>;

using band2_t = container::chain<parameter::empty, 
                                 wrap::fix<2, jdsp::jlinkwitzriley>, 
                                 fx::reverb>;

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

using freq_split3_t = container::split<freq_split3_t_parameters::Band1, 
                                       wrap::fix<2, band1_t>, 
                                       band2_t>;

template <int NV>
using wet_path1_t = container::chain<parameter::empty, 
                                     wrap::fix<2, freq_split3_t>, 
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
using split1_t = container::split<parameter::empty, 
                                  wrap::fix<1, cable_table_t<NV>>, 
                                  minmax1_t<NV>, 
                                  air_t<NV>, 
                                  cable_table1_t<NV>, 
                                  minmax_t<NV>>;

template <int NV>
using split2_t = container::split<parameter::empty, 
                                  wrap::fix<1, control::minmax<NV, parameter::empty>>>;

template <int NV>
using modchain_t_ = container::chain<parameter::empty, 
                                     wrap::fix<1, focus_slam_minmax_t<NV>>, 
                                     split_t<NV>, 
                                     split1_t<NV>, 
                                     split2_t<NV>>;

template <int NV>
using modchain_t = wrap::control_rate<modchain_t_<NV>>;

template <int NV>
using pressure_smooth_mod = parameter::chain<ranges::Identity, 
                                             parameter::plain<project::DrumSlam<NV>, 0>, 
                                             parameter::plain<cable_table_t<NV>, 0>>;

template <int NV>
using pressure_smooth_t = wrap::mod<pressure_smooth_mod<NV>, 
                                    control::smoothed_parameter<NV, smoothers::linear_ramp<NV>>>;

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
                                    wrap::fix<2, project::DrumSlam<NV>>, 
                                    core::gain<NV>, 
                                    project::Focus<NV>, 
                                    project::Drive<NV>, 
                                    core::gain<NV>, 
                                    chain_t<NV>, 
                                    core::gain<NV>, 
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
using Air = parameter::chain<ranges::Identity, 
                             parameter::plain<Karate_impl::air_t<NV>, 0>, 
                             parameter::plain<control::minmax<NV, parameter::empty>, 0>>;

template <int NV>
using Focus = parameter::plain<Karate_impl::focus_slam_minmax_t<NV>, 
                               0>;
template <int NV>
using Mix = parameter::plain<Karate_impl::dry_wet1_t<NV>, 
                             0>;
template <int NV>
using Pressure = parameter::plain<Karate_impl::pressure_smooth_t<NV>, 
                                  0>;
using Speed = parameter::empty;
template <int NV>
using OutGain = parameter::plain<core::gain<NV>, 0>;
template <int NV>
using Karate_t_plist = parameter::list<Focus<NV>, 
                                       Mix<NV>, 
                                       Air<NV>, 
                                       Pressure<NV>, 
                                       Speed, 
                                       OutGain<NV>>;
}

template <int NV>
using Karate_t_ = container::chain<Karate_t_parameters::Karate_t_plist<NV>, 
                                   wrap::fix<2, modchain_t<NV>>, 
                                   pressure_smooth_t<NV>, 
                                   focus_smooth_t<NV>, 
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
		SNEX_METADATA_ENCODED_PARAMETERS(94)
		{
			0x005B, 0x0000, 0x4600, 0x636F, 0x7375, 0x0000, 0x0000, 0x0000, 
            0x8000, 0xE63F, 0xFEBE, 0x003E, 0x8000, 0x003F, 0x0000, 0x5B00, 
            0x0001, 0x0000, 0x694D, 0x0078, 0x0000, 0x0000, 0x0000, 0x3F80, 
            0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x0000, 0x025B, 0x0000, 
            0x4100, 0x7269, 0x0000, 0x0000, 0x0000, 0x8000, 0x003F, 0x0000, 
            0x0000, 0x8000, 0x003F, 0x0000, 0x5B00, 0x0003, 0x0000, 0x7250, 
            0x7365, 0x7573, 0x6572, 0x0000, 0x0000, 0x0000, 0x8000, 0xA93F, 
            0x0054, 0x003F, 0x8000, 0x003F, 0x0000, 0x5B00, 0x0004, 0x0000, 
            0x7053, 0x6565, 0x0064, 0x0000, 0x0000, 0x0000, 0x3F80, 0x4B44, 
            0x3B58, 0x0000, 0x3F80, 0x0000, 0x0000, 0x055B, 0x0000, 0x4F00, 
            0x7475, 0x6147, 0x6E69, 0x0000, 0xC800, 0x00C2, 0x4000, 0x0041, 
            0xC800, 0x3E35, 0xAD83, 0xCD40, 0xCCCC, 0x003D
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& modchain = this->getT(0);                                               // Karate_impl::modchain_t<NV>
		auto& focus_slam_minmax = this->getT(0).getT(0);                              // Karate_impl::focus_slam_minmax_t<NV>
		auto& split = this->getT(0).getT(1);                                          // Karate_impl::split_t<NV>
		auto& minmax2 = this->getT(0).getT(1).getT(0);                                // Karate_impl::minmax2_t<NV>
		auto& split1 = this->getT(0).getT(2);                                         // Karate_impl::split1_t<NV>
		auto& cable_table = this->getT(0).getT(2).getT(0);                            // Karate_impl::cable_table_t<NV>
		auto& minmax1 = this->getT(0).getT(2).getT(1);                                // Karate_impl::minmax1_t<NV>
		auto& air = this->getT(0).getT(2).getT(2);                                    // Karate_impl::air_t<NV>
		auto& cable_table1 = this->getT(0).getT(2).getT(3);                           // Karate_impl::cable_table1_t<NV>
		auto& minmax = this->getT(0).getT(2).getT(4);                                 // Karate_impl::minmax_t<NV>
		auto& split2 = this->getT(0).getT(3);                                         // Karate_impl::split2_t<NV>
		auto& Air_gain = this->getT(0).getT(3).getT(0);                               // control::minmax<NV, parameter::empty>
		auto& pressure_smooth = this->getT(1);                                        // Karate_impl::pressure_smooth_t<NV>
		auto& focus_smooth = this->getT(2);                                           // Karate_impl::focus_smooth_t<NV>
		auto& dry_wet1 = this->getT(3);                                               // Karate_impl::dry_wet1_t<NV>
		auto& dry_path = this->getT(3).getT(0);                                       // Karate_impl::dry_path_t<NV>
		auto& dry_wet_mixer = this->getT(3).getT(0).getT(0);                          // Karate_impl::dry_wet_mixer_t<NV>
		auto& dry_gain = this->getT(3).getT(0).getT(1);                               // core::gain<NV>
		auto& wet_path = this->getT(3).getT(1);                                       // Karate_impl::wet_path_t<NV>
		auto& DrumSlam = this->getT(3).getT(1).getT(0);                               // project::DrumSlam<NV>
		auto& gain1 = this->getT(3).getT(1).getT(1);                                  // core::gain<NV>
		auto& Focus = this->getT(3).getT(1).getT(2);                                  // project::Focus<NV>
		auto& Drive = this->getT(3).getT(1).getT(3);                                  // project::Drive<NV>
		auto& gain3 = this->getT(3).getT(1).getT(4);                                  // core::gain<NV>
		auto& chain = this->getT(3).getT(1).getT(5);                                  // Karate_impl::chain_t<NV>
		auto& dry_wet2 = this->getT(3).getT(1).getT(5).getT(0);                       // Karate_impl::dry_wet2_t<NV>
		auto& dry_path1 = this->getT(3).getT(1).getT(5).getT(0).getT(0);              // Karate_impl::dry_path1_t<NV>
		auto& dry_wet_mixer1 = this->getT(3).getT(1).getT(5).getT(0).getT(0).getT(0); // Karate_impl::dry_wet_mixer1_t<NV>
		auto& dry_gain1 = this->getT(3).getT(1).getT(5).getT(0).getT(0).getT(1);      // core::gain<NV>
		auto& wet_path1 = this->getT(3).getT(1).getT(5).getT(0).getT(1);              // Karate_impl::wet_path1_t<NV>
		auto& freq_split3 = this->getT(3).getT(1).getT(5).getT(0).getT(1).getT(0);    // Karate_impl::freq_split3_t
		auto& band1 = this->getT(3).getT(1).getT(5).getT(0).getT(1).getT(0).getT(0);  // Karate_impl::band1_t
		auto& lr1_1 = this->getT(3).getT(1).getT(5).getT(0).                          // jdsp::jlinkwitzriley
                      getT(1).getT(0).getT(0).getT(0);
		auto& band2 = this->getT(3).getT(1).getT(5).getT(0).getT(1).getT(0).getT(1); // Karate_impl::band2_t
		auto& lr2_1 = this->getT(3).getT(1).getT(5).getT(0).                         // jdsp::jlinkwitzriley
                      getT(1).getT(0).getT(1).getT(0);
		auto& reverb = this->getT(3).getT(1).getT(5).getT(0).                    // fx::reverb
                       getT(1).getT(0).getT(1).getT(1);
		auto& wet_gain1 = this->getT(3).getT(1).getT(5).getT(0).getT(1).getT(1); // core::gain<NV>
		auto& gain = this->getT(3).getT(1).getT(6);                              // core::gain<NV>
		auto& gain4 = this->getT(3).getT(1).getT(7);                             // core::gain<NV>
		auto& wet_gain = this->getT(3).getT(1).getT(8);                          // core::gain<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		auto& Band1_p = freq_split3.getParameterT(0);
		Band1_p.connectT(0, lr1_1);                            // Band1 -> lr1_1::Frequency
		Band1_p.connectT(1, lr2_1);                            // Band1 -> lr2_1::Frequency
		dry_wet2.getParameterT(0).connectT(0, dry_wet_mixer1); // DryWet -> dry_wet_mixer1::Value
		dry_wet2.getParameterT(0).connectT(0, dry_wet_mixer1); // DryWet -> dry_wet_mixer1::Value
		dry_wet1.getParameterT(0).connectT(0, dry_wet_mixer);  // DryWet -> dry_wet_mixer::Value
		this->getParameterT(0).connectT(0, focus_slam_minmax); // Focus -> focus_slam_minmax::Value
		
		this->getParameterT(1).connectT(0, dry_wet1); // Mix -> dry_wet1::DryWet
		
		auto& Air_p = this->getParameterT(2);
		Air_p.connectT(0, air);      // Air -> air::Value
		Air_p.connectT(1, Air_gain); // Air -> Air_gain::Value
		
		this->getParameterT(3).connectT(0, pressure_smooth); // Pressure -> pressure_smooth::Value
		
		this->getParameterT(5).connectT(0, gain); // OutGain -> gain::Gain
		
		// Modulation Connections ------------------------------------------------------------------
		
		minmax2.getWrappedObject().getParameter().connectT(0, Drive);                  // minmax2 -> Drive::Drive
		minmax.getWrappedObject().getParameter().connectT(0, gain3);                   // minmax -> gain3::Gain
		cable_table1.getWrappedObject().getParameter().connectT(0, minmax);            // cable_table1 -> minmax::Value
		focus_smooth.getParameter().connectT(0, minmax2);                              // focus_smooth -> minmax2::Value
		focus_smooth.getParameter().connectT(1, Focus);                                // focus_smooth -> Focus::Boost
		focus_smooth.getParameter().connectT(2, cable_table1);                         // focus_smooth -> cable_table1::Value
		focus_slam_minmax.getWrappedObject().getParameter().connectT(0, focus_smooth); // focus_slam_minmax -> focus_smooth::Value
		minmax1.getWrappedObject().getParameter().connectT(0, gain1);                  // minmax1 -> gain1::Gain
		cable_table.getWrappedObject().getParameter().connectT(0, minmax1);            // cable_table -> minmax1::Value
		auto& dry_wet_mixer1_p = dry_wet_mixer1.getWrappedObject().getParameter();
		dry_wet_mixer1_p.getParameterT(0).connectT(0, dry_gain1);    // dry_wet_mixer1 -> dry_gain1::Gain
		dry_wet_mixer1_p.getParameterT(1).connectT(0, wet_gain1);    // dry_wet_mixer1 -> wet_gain1::Gain
		air.getWrappedObject().getParameter().connectT(0, dry_wet2); // air -> dry_wet2::DryWet
		pressure_smooth.getParameter().connectT(0, DrumSlam);        // pressure_smooth -> DrumSlam::Drive
		pressure_smooth.getParameter().connectT(1, cable_table);     // pressure_smooth -> cable_table::Value
		auto& dry_wet_mixer_p = dry_wet_mixer.getWrappedObject().getParameter();
		dry_wet_mixer_p.getParameterT(0).connectT(0, dry_gain); // dry_wet_mixer -> dry_gain::Gain
		dry_wet_mixer_p.getParameterT(1).connectT(0, wet_gain); // dry_wet_mixer -> wet_gain::Gain
		
		// Default Values --------------------------------------------------------------------------
		
		;                                             // focus_slam_minmax::Value is automated
		focus_slam_minmax.setParameterT(1, 0.103039); // control::minmax::Minimum
		focus_slam_minmax.setParameterT(2, 1.);       // control::minmax::Maximum
		focus_slam_minmax.setParameterT(3, 3.13487);  // control::minmax::Skew
		focus_slam_minmax.setParameterT(4, 0.);       // control::minmax::Step
		focus_slam_minmax.setParameterT(5, 0.);       // control::minmax::Polarity
		
		;                                   // minmax2::Value is automated
		minmax2.setParameterT(1, 0.);       // control::minmax::Minimum
		minmax2.setParameterT(2, 0.50397);  // control::minmax::Maximum
		minmax2.setParameterT(3, 0.333267); // control::minmax::Skew
		minmax2.setParameterT(4, 0.);       // control::minmax::Step
		minmax2.setParameterT(5, 0.);       // control::minmax::Polarity
		
		; // cable_table::Value is automated
		
		;                                     // minmax1::Value is automated
		minmax1.setParameterT(1, -8.5);       // control::minmax::Minimum
		minmax1.setParameterT(2, -2.5);       // control::minmax::Maximum
		minmax1.setParameterT(3, 0.566771);   // control::minmax::Skew
		minmax1.setParameterT(4, 0.00734375); // control::minmax::Step
		minmax1.setParameterT(5, 1.);         // control::minmax::Polarity
		
		;                                 // air::Value is automated
		air.setParameterT(1, 0.);         // control::minmax::Minimum
		air.setParameterT(2, 0.0914652);  // control::minmax::Maximum
		air.setParameterT(3, 0.658886);   // control::minmax::Skew
		air.setParameterT(4, 0.00945312); // control::minmax::Step
		air.setParameterT(5, 0.);         // control::minmax::Polarity
		
		; // cable_table1::Value is automated
		
		;                                  // minmax::Value is automated
		minmax.setParameterT(1, -8.6);     // control::minmax::Minimum
		minmax.setParameterT(2, -0.5);     // control::minmax::Maximum
		minmax.setParameterT(3, 0.995091); // control::minmax::Skew
		minmax.setParameterT(4, 0.1);      // control::minmax::Step
		minmax.setParameterT(5, 1.);       // control::minmax::Polarity
		
		;                                // Air_gain::Value is automated
		Air_gain.setParameterT(1, 0.);   // control::minmax::Minimum
		Air_gain.setParameterT(2, 33.2); // control::minmax::Maximum
		Air_gain.setParameterT(3, 10.);  // control::minmax::Skew
		Air_gain.setParameterT(4, 0.1);  // control::minmax::Step
		Air_gain.setParameterT(5, 0.);   // control::minmax::Polarity
		
		;                                        // pressure_smooth::Value is automated
		pressure_smooth.setParameterT(1, 101.4); // control::smoothed_parameter::SmoothingTime
		pressure_smooth.setParameterT(2, 1.);    // control::smoothed_parameter::Enabled
		
		;                                   // focus_smooth::Value is automated
		focus_smooth.setParameterT(1, 0.1); // control::smoothed_parameter::SmoothingTime
		focus_smooth.setParameterT(2, 1.);  // control::smoothed_parameter::Enabled
		
		; // dry_wet1::DryWet is automated
		
		; // dry_wet_mixer::Value is automated
		
		;                               // dry_gain::Gain is automated
		dry_gain.setParameterT(1, 20.); // core::gain::Smoothing
		dry_gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                              // DrumSlam::Drive is automated
		DrumSlam.setParameterT(1, 1.); // project::DrumSlam::Output
		DrumSlam.setParameterT(2, 1.); // project::DrumSlam::DryWet
		
		;                            // gain1::Gain is automated
		gain1.setParameterT(1, 20.); // core::gain::Smoothing
		gain1.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                                 // Focus::Boost is automated
		Focus.setParameterT(1, 0.404601); // project::Focus::Focus
		Focus.setParameterT(2, 1.);       // project::Focus::Mode
		Focus.setParameterT(3, 1.);       // project::Focus::Output
		Focus.setParameterT(4, 1.);       // project::Focus::DryWet
		
		;                           // Drive::Drive is automated
		Drive.setParameterT(1, 0.); // project::Drive::Highpass
		Drive.setParameterT(2, 1.); // project::Drive::OutLevel
		Drive.setParameterT(3, 1.); // project::Drive::DryWet
		
		;                            // gain3::Gain is automated
		gain3.setParameterT(1, 20.); // core::gain::Smoothing
		gain3.setParameterT(2, 0.);  // core::gain::ResetValue
		
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
		
		;                                // wet_gain1::Gain is automated
		wet_gain1.setParameterT(1, 20.); // core::gain::Smoothing
		wet_gain1.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                           // gain::Gain is automated
		gain.setParameterT(1, 20.); // core::gain::Smoothing
		gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		gain4.setParameterT(0, -3);  // core::gain::Gain
		gain4.setParameterT(1, 20.); // core::gain::Smoothing
		gain4.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                               // wet_gain::Gain is automated
		wet_gain.setParameterT(1, 20.); // core::gain::Smoothing
		wet_gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		this->setParameterT(0, 0.49755);
		this->setParameterT(1, 1.);
		this->setParameterT(2, 0.);
		this->setParameterT(3, 0.501292);
		this->setParameterT(4, 0.00330038);
		this->setParameterT(5, 1.49012e-06);
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
		
		this->getT(0).getT(2).getT(0).setExternalData(b, index); // Karate_impl::cable_table_t<NV>
		this->getT(0).getT(2).getT(3).setExternalData(b, index); // Karate_impl::cable_table1_t<NV>
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


