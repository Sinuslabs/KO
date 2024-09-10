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
		0.168539f, 0.170148f, 0.171756f, 0.173364f, 0.174972f, 0.176581f,
		0.178189f, 0.179797f, 0.181406f, 0.183014f, 0.184622f, 0.18623f,
		0.187839f, 0.189447f, 0.191055f, 0.192663f, 0.194272f, 0.19588f,
		0.197488f, 0.199097f, 0.200705f, 0.202313f, 0.203921f, 0.20553f,
		0.207138f, 0.208746f, 0.210355f, 0.211963f, 0.213571f, 0.215179f,
		0.216788f, 0.218396f, 0.220004f, 0.221613f, 0.223221f, 0.224829f,
		0.226437f, 0.228046f, 0.229654f, 0.231262f, 0.23287f, 0.234479f,
		0.236087f, 0.237695f, 0.239304f, 0.240912f, 0.24252f, 0.244128f,
		0.245737f, 0.247345f, 0.248953f, 0.250561f, 0.25217f, 0.253778f,
		0.255386f, 0.256995f, 0.258968f, 0.263912f, 0.268857f, 0.273802f,
		0.278746f, 0.283691f, 0.288635f, 0.29358f, 0.298197f, 0.302572f,
		0.306947f, 0.311322f, 0.315697f, 0.320072f, 0.324447f, 0.328822f,
		0.333012f, 0.336902f, 0.340792f, 0.344682f, 0.348573f, 0.352463f,
		0.356353f, 0.360243f, 0.364133f, 0.367802f, 0.371275f, 0.374747f,
		0.37822f, 0.381692f, 0.385165f, 0.388637f, 0.39211f, 0.395583f,
		0.399048f, 0.402157f, 0.405266f, 0.408375f, 0.411484f, 0.414593f,
		0.417702f, 0.420811f, 0.42392f, 0.427029f, 0.430138f, 0.432976f,
		0.435766f, 0.438556f, 0.441345f, 0.444135f, 0.446925f, 0.449715f,
		0.452504f, 0.455294f, 0.458084f, 0.460868f, 0.463375f, 0.465882f,
		0.468389f, 0.470896f, 0.473403f, 0.47591f, 0.478417f, 0.480924f,
		0.483431f, 0.485938f, 0.488445f, 0.490818f, 0.493073f, 0.495328f,
		0.497583f, 0.499838f, 0.502093f, 0.504348f, 0.506603f, 0.508858f,
		0.511113f, 0.513368f, 0.515623f, 0.517791f, 0.519819f, 0.521848f,
		0.523878f, 0.525906f, 0.527935f, 0.529964f, 0.531993f, 0.534022f,
		0.536051f, 0.53808f, 0.540109f, 0.542138f, 0.544048f, 0.545873f,
		0.547698f, 0.549523f, 0.551348f, 0.553173f, 0.554998f, 0.556823f,
		0.558648f, 0.560473f, 0.562298f, 0.564123f, 0.565948f, 0.567752f,
		0.569392f, 0.571032f, 0.572672f, 0.574312f, 0.575952f, 0.577592f,
		0.579232f, 0.580872f, 0.582512f, 0.584152f, 0.585792f, 0.587433f,
		0.589073f, 0.590713f, 0.592185f, 0.593657f, 0.595128f, 0.5966f,
		0.598072f, 0.599543f, 0.601015f, 0.602487f, 0.603958f, 0.60543f,
		0.606902f, 0.608373f, 0.609845f, 0.611317f, 0.612755f, 0.614073f,
		0.61539f, 0.616708f, 0.618026f, 0.619343f, 0.620661f, 0.621978f,
		0.623296f, 0.624613f, 0.625931f, 0.627249f, 0.628566f, 0.629884f,
		0.631201f, 0.632519f, 0.633727f, 0.634903f, 0.636079f, 0.637255f,
		0.638432f, 0.639608f, 0.640784f, 0.64196f, 0.643136f, 0.644312f,
		0.645488f, 0.646665f, 0.647841f, 0.649017f, 0.650193f, 0.651369f,
		0.652457f, 0.653503f, 0.654549f, 0.655595f, 0.65664f, 0.657686f,
		0.658732f, 0.659778f, 0.660824f, 0.661869f, 0.662915f, 0.663961f,
		0.665007f, 0.666053f, 0.667098f, 0.668144f, 0.66919f, 0.670125f,
		0.671051f, 0.671976f, 0.672901f, 0.673827f, 0.674752f, 0.675677f,
		0.676603f, 0.677528f, 0.678453f, 0.679379f, 0.680304f, 0.681229f,
		0.682155f, 0.68308f, 0.684005f, 0.684931f, 0.684646f, 0.68315f,
		0.681655f, 0.68016f, 0.678665f, 0.67717f, 0.675674f, 0.674179f,
		0.672684f, 0.671189f, 0.669694f, 0.668198f, 0.666703f, 0.665208f,
		0.663713f, 0.662218f, 0.660722f, 0.659227f, 0.657732f, 0.656237f,
		0.654742f, 0.653247f, 0.651751f, 0.650256f, 0.648761f, 0.647266f,
		0.645771f, 0.644275f, 0.64278f, 0.641285f, 0.63979f, 0.638295f,
		0.636799f, 0.635304f, 0.633809f, 0.632314f, 0.630819f, 0.629323f,
		0.627828f, 0.626333f, 0.624838f, 0.623343f, 0.621847f, 0.620352f,
		0.618857f, 0.617362f, 0.615867f, 0.614371f, 0.612876f, 0.611381f,
		0.609886f, 0.608391f, 0.606895f, 0.6054f, 0.603905f, 0.60241f,
		0.600915f, 0.599419f, 0.597924f, 0.596429f, 0.594934f, 0.593439f,
		0.591944f, 0.590448f, 0.588953f, 0.587458f, 0.585963f, 0.584468f,
		0.582972f, 0.581477f, 0.579982f, 0.578487f, 0.576992f, 0.575496f,
		0.574001f, 0.572506f, 0.571011f, 0.569516f, 0.56802f, 0.566525f,
		0.56503f, 0.563535f, 0.56204f, 0.560544f, 0.559049f, 0.557554f,
		0.556059f, 0.554564f, 0.553068f, 0.551573f, 0.550078f, 0.548583f,
		0.547088f, 0.545592f, 0.544097f, 0.542602f, 0.541107f, 0.539612f,
		0.538116f, 0.536621f, 0.535126f, 0.533631f, 0.532136f, 0.53064f,
		0.529145f, 0.52765f, 0.526155f, 0.52466f, 0.523165f, 0.521669f,
		0.520174f, 0.518679f, 0.517184f, 0.515689f, 0.514193f, 0.512698f,
		0.511203f, 0.509708f, 0.508213f, 0.506717f, 0.505222f, 0.503727f,
		0.502232f, 0.500737f, 0.499241f, 0.497746f, 0.496251f, 0.494756f,
		0.493261f, 0.491765f, 0.49027f, 0.488775f, 0.48728f, 0.485785f,
		0.484289f, 0.482794f, 0.481299f, 0.479804f, 0.478309f, 0.476813f,
		0.475318f, 0.473823f, 0.472328f, 0.470833f, 0.469337f, 0.467842f,
		0.466347f, 0.464852f, 0.463357f, 0.461861f, 0.460366f, 0.458871f,
		0.457376f, 0.455881f, 0.454386f, 0.45289f, 0.451395f, 0.4499f,
		0.448405f, 0.44691f, 0.445414f, 0.443919f, 0.442424f, 0.440929f,
		0.439434f, 0.437938f, 0.436443f, 0.434948f, 0.433453f, 0.431958f,
		0.430462f, 0.428967f, 0.427472f, 0.425977f, 0.424482f, 0.422986f,
		0.421491f, 0.419996f, 0.418501f, 0.417006f, 0.41551f, 0.414015f,
		0.41252f, 0.411025f, 0.40953f, 0.408034f, 0.406539f, 0.405044f,
		0.403549f, 0.402054f, 0.400558f, 0.399063f, 0.397568f, 0.396073f,
		0.394578f, 0.393082f, 0.391587f, 0.390092f, 0.388597f, 0.387102f,
		0.385607f, 0.384111f, 0.382616f, 0.381121f, 0.379626f, 0.378131f,
		0.376635f, 0.37514f, 0.373645f, 0.37215f, 0.370655f, 0.369159f,
		0.367664f, 0.366169f, 0.364674f, 0.363179f, 0.361683f, 0.360188f,
		0.358693f, 0.357198f, 0.355703f, 0.354207f, 0.352712f, 0.351217f,
		0.349722f, 0.348227f, 0.346731f, 0.345236f, 0.343741f, 0.342246f,
		0.340751f, 0.339255f, 0.33776f, 0.336265f, 0.33477f, 0.333275f,
		0.331779f, 0.330284f, 0.328789f, 0.327294f, 0.325799f, 0.324304f,
		0.322808f, 0.321313f, 0.319818f, 0.318323f, 0.316828f, 0.315332f,
		0.313837f, 0.312342f, 0.310847f, 0.309352f, 0.307856f, 0.306361f,
		0.304866f, 0.303371f
	};
};

template <int NV>
using cable_table_t = wrap::data<control::cable_table<parameter::plain<minmax_t<NV>, 0>>, 
                                 data::embedded::table<cable_table_t_data>>;

template <int NV> using HeavyGainMatch_t = minmax_t<NV>;

template <int NV>
using smoothed_parameter_mod = parameter::chain<ranges::Identity, 
                                                parameter::plain<mojo1_t<NV>, 0>, 
                                                parameter::plain<pma_t<NV>, 0>, 
                                                parameter::plain<cable_table_t<NV>, 0>, 
                                                parameter::plain<HeavyGainMatch_t<NV>, 0>>;

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
using minmax4_mod = parameter::chain<ranges::Identity, 
                                     parameter::plain<fx::sampleandhold<NV>, 0>, 
                                     parameter::plain<wrap::no_process<fx::bitcrush<NV>>, 0>>;

template <int NV>
using minmax4_t = control::minmax<NV, minmax4_mod<NV>>;

template <int NV>
using split_t = container::split<parameter::empty, 
                                 wrap::fix<1, mojo1_t<NV>>, 
                                 pma_t<NV>, 
                                 minmax1_t<NV>, 
                                 minmax2_t<NV>, 
                                 minmax3_t<NV>, 
                                 minmax4_t<NV>>;

template <int NV>
using WEIGHT_EQ_t = control::minmax<NV, 
                                    parameter::plain<filters::svf_eq<NV>, 2>>;

template <int NV>
using split1_t = container::split<parameter::empty, 
                                  wrap::fix<1, cable_table_t<NV>>, 
                                  minmax_t<NV>, 
                                  WEIGHT_EQ_t<NV>>;

template <int NV> using minmax5_t = minmax_t<NV>;

struct cable_table1_t_data
{
	span<float, 512> data =
	{
		0.f, 0.000646949f, 0.0012939f, 0.00194085f, 0.0025878f, 0.00323474f,
		0.00388169f, 0.00452864f, 0.00517553f, 0.00582248f, 0.00646943f, 0.00711638f,
		0.00776333f, 0.00842786f, 0.00915521f, 0.00988263f, 0.01061f, 0.0113373f,
		0.0120648f, 0.0127921f, 0.0135195f, 0.0142469f, 0.0149743f, 0.0157017f,
		0.016429f, 0.0171564f, 0.0179468f, 0.0187588f, 0.0195707f, 0.0203826f,
		0.0211945f, 0.0220065f, 0.0228184f, 0.0236303f, 0.0244422f, 0.0252541f,
		0.0260661f, 0.0268779f, 0.0277417f, 0.0286427f, 0.0295435f, 0.0304444f,
		0.0313452f, 0.0322461f, 0.033147f, 0.0340478f, 0.0349488f, 0.0358496f,
		0.0367505f, 0.0376514f, 0.0386207f, 0.0396153f, 0.0406098f, 0.0416045f,
		0.042599f, 0.0435936f, 0.0445882f, 0.0455828f, 0.0465774f, 0.047572f,
		0.0485666f, 0.0495796f, 0.0506731f, 0.0517666f, 0.05286f, 0.0539535f,
		0.055047f, 0.0561404f, 0.0572339f, 0.0583274f, 0.0594208f, 0.0605143f,
		0.0616078f, 0.0628008f, 0.0639987f, 0.0651967f, 0.0663946f, 0.0675926f,
		0.0687905f, 0.0699885f, 0.0711864f, 0.0723844f, 0.0735824f, 0.0747833f,
		0.0760919f, 0.0774004f, 0.0787089f, 0.0800175f, 0.081326f, 0.0826346f,
		0.0839431f, 0.0852516f, 0.0865602f, 0.0878688f, 0.0892256f, 0.0906513f,
		0.0920771f, 0.0935029f, 0.0949286f, 0.0963544f, 0.0977801f, 0.0992059f,
		0.100632f, 0.102057f, 0.103496f, 0.105047f, 0.106597f, 0.108147f,
		0.109697f, 0.111248f, 0.112798f, 0.114348f, 0.115898f, 0.117449f,
		0.119014f, 0.120696f, 0.122379f, 0.124062f, 0.125744f, 0.127427f,
		0.12911f, 0.130792f, 0.132475f, 0.134158f, 0.1359f, 0.137724f,
		0.139548f, 0.141372f, 0.143196f, 0.145019f, 0.146843f, 0.148667f,
		0.150491f, 0.152322f, 0.154297f, 0.156271f, 0.158246f, 0.160221f,
		0.162195f, 0.16417f, 0.166145f, 0.168119f, 0.170094f, 0.172227f,
		0.174363f, 0.176499f, 0.178635f, 0.180771f, 0.182907f, 0.185044f,
		0.18718f, 0.189354f, 0.191664f, 0.193973f, 0.196283f, 0.198592f,
		0.200901f, 0.203211f, 0.20552f, 0.20783f, 0.210283f, 0.212779f,
		0.215275f, 0.217771f, 0.220267f, 0.222763f, 0.225259f, 0.227755f,
		0.230378f, 0.233075f, 0.235772f, 0.23847f, 0.241167f, 0.243864f,
		0.246561f, 0.249258f, 0.25213f, 0.255045f, 0.25796f, 0.260875f,
		0.26379f, 0.266705f, 0.26962f, 0.272602f, 0.275754f, 0.278905f,
		0.282057f, 0.285208f, 0.28836f, 0.291511f, 0.294681f, 0.29809f,
		0.3015f, 0.304909f, 0.308318f, 0.311727f, 0.315136f, 0.318594f,
		0.322285f, 0.325976f, 0.329667f, 0.333358f, 0.337049f, 0.34074f,
		0.344611f, 0.348612f, 0.352612f, 0.356613f, 0.360614f, 0.364615f,
		0.368717f, 0.37306f, 0.377402f, 0.381745f, 0.386087f, 0.39043f,
		0.394896f, 0.399617f, 0.404339f, 0.409061f, 0.413782f, 0.418504f,
		0.423506f, 0.428651f, 0.433795f, 0.43894f, 0.444084f, 0.449376f,
		0.454995f, 0.460615f, 0.466234f, 0.471854f, 0.477616f, 0.483772f,
		0.489929f, 0.496085f, 0.502242f, 0.508723f, 0.515491f, 0.52226f,
		0.529028f, 0.535871f, 0.543344f, 0.550816f, 0.558289f, 0.565762f,
		0.574045f, 0.582336f, 0.590628f, 0.599096f, 0.608351f, 0.617606f,
		0.626861f, 0.636907f, 0.647313f, 0.657718f, 0.663289f, 0.664024f,
		0.66476f, 0.665495f, 0.666231f, 0.666966f, 0.667702f, 0.668437f,
		0.669173f, 0.669908f, 0.670643f, 0.671379f, 0.672114f, 0.67285f,
		0.673585f, 0.674321f, 0.675056f, 0.675792f, 0.676527f, 0.677262f,
		0.677998f, 0.678733f, 0.679469f, 0.680204f, 0.68094f, 0.681675f,
		0.682411f, 0.683146f, 0.683881f, 0.684617f, 0.685352f, 0.686088f,
		0.686823f, 0.687559f, 0.688294f, 0.68903f, 0.689765f, 0.6905f,
		0.691236f, 0.691971f, 0.692707f, 0.693442f, 0.694178f, 0.694913f,
		0.695649f, 0.696384f, 0.697119f, 0.697855f, 0.69859f, 0.699326f,
		0.700061f, 0.700797f, 0.701532f, 0.702268f, 0.703003f, 0.703738f,
		0.704474f, 0.705209f, 0.705945f, 0.70668f, 0.707416f, 0.708151f,
		0.708887f, 0.709622f, 0.710357f, 0.711093f, 0.711828f, 0.712564f,
		0.713299f, 0.714035f, 0.71477f, 0.715506f, 0.716241f, 0.716976f,
		0.717712f, 0.718447f, 0.719183f, 0.719918f, 0.720654f, 0.721389f,
		0.722125f, 0.72286f, 0.723595f, 0.724331f, 0.725066f, 0.725802f,
		0.726537f, 0.727273f, 0.728008f, 0.728744f, 0.729479f, 0.730214f,
		0.73095f, 0.731685f, 0.732421f, 0.733156f, 0.733892f, 0.734627f,
		0.735363f, 0.736098f, 0.736833f, 0.737569f, 0.738304f, 0.73904f,
		0.739775f, 0.740511f, 0.741246f, 0.741982f, 0.742717f, 0.743452f,
		0.744188f, 0.744923f, 0.745659f, 0.746394f, 0.74713f, 0.747865f,
		0.7486f, 0.749336f, 0.750071f, 0.750807f, 0.751542f, 0.752278f,
		0.753013f, 0.753749f, 0.754484f, 0.755219f, 0.755955f, 0.75669f,
		0.757426f, 0.758161f, 0.758897f, 0.759632f, 0.760368f, 0.761103f,
		0.761838f, 0.762574f, 0.763309f, 0.764045f, 0.76478f, 0.765516f,
		0.766251f, 0.766987f, 0.767722f, 0.768457f, 0.769193f, 0.769928f,
		0.770664f, 0.771399f, 0.772135f, 0.77287f, 0.773606f, 0.774341f,
		0.775076f, 0.775812f, 0.776547f, 0.777283f, 0.778018f, 0.778754f,
		0.779489f, 0.780225f, 0.78096f, 0.781695f, 0.782431f, 0.783166f,
		0.783902f, 0.784637f, 0.785373f, 0.786108f, 0.786844f, 0.787579f,
		0.788314f, 0.78905f, 0.789785f, 0.790521f, 0.791256f, 0.791992f,
		0.792727f, 0.793463f, 0.794198f, 0.794933f, 0.795669f, 0.796404f,
		0.79714f, 0.797875f, 0.798611f, 0.799346f, 0.800082f, 0.800817f,
		0.801552f, 0.802288f, 0.803023f, 0.803759f, 0.804494f, 0.80523f,
		0.805965f, 0.806701f, 0.807436f, 0.808171f, 0.808907f, 0.762967f,
		0.711181f, 0.659395f, 0.607608f, 0.555822f, 0.550173f, 0.54974f,
		0.549307f, 0.548874f, 0.548441f, 0.548008f, 0.547575f, 0.547142f,
		0.546709f, 0.546276f, 0.545843f, 0.54541f, 0.544977f, 0.544544f,
		0.544111f, 0.543678f, 0.543245f, 0.542812f, 0.542379f, 0.541946f,
		0.541513f, 0.54108f, 0.540647f, 0.540214f, 0.539781f, 0.539348f,
		0.538915f, 0.538482f, 0.538049f, 0.537616f, 0.537183f, 0.53675f,
		0.536317f, 0.535884f, 0.535451f, 0.535018f, 0.534585f, 0.534152f,
		0.533719f, 0.533286f, 0.532853f, 0.53242f, 0.531987f, 0.531554f,
		0.531121f, 0.530688f, 0.530255f, 0.529822f, 0.529389f, 0.528956f,
		0.528523f, 0.52809f
	};
};

template <int NV>
using cable_table1_t = wrap::data<control::cable_table<parameter::plain<minmax5_t<NV>, 0>>, 
                                  data::embedded::table<cable_table1_t_data>>;

template <int NV>
using split2_t = container::split<parameter::empty, 
                                  wrap::fix<1, HeavyGainMatch_t<NV>>, 
                                  cable_table1_t<NV>, 
                                  minmax5_t<NV>>;

template <int NV>
using modchain_t_ = container::chain<parameter::empty, 
                                     wrap::fix<1, split_t<NV>>, 
                                     split1_t<NV>, 
                                     split2_t<NV>>;

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
                                 project::Mojo<NV>, 
                                 core::gain<NV>>;

template <int NV>
using chain1_t = container::chain<parameter::empty, 
                                  wrap::fix<2, filters::svf_eq<NV>>, 
                                  project::Tube2<NV>, 
                                  project::Tube2<NV>, 
                                  core::gain<NV>>;

template <int NV> using dry_wet_mixer2_c0 = dry_wet_mixer_c0<NV>;

template <int NV> using dry_wet_mixer2_c1 = dry_wet_mixer_c0<NV>;

template <int NV>
using dry_wet_mixer2_multimod = parameter::list<dry_wet_mixer2_c0<NV>, dry_wet_mixer2_c1<NV>>;

template <int NV>
using dry_wet_mixer2_t = control::xfader<dry_wet_mixer2_multimod<NV>, 
                                         faders::cosine_half>;

template <int NV>
using dry_path2_t = container::chain<parameter::empty, 
                                     wrap::fix<2, dry_wet_mixer2_t<NV>>, 
                                     core::gain<NV>>;

template <int NV>
using wet_path2_t = container::chain<parameter::empty, 
                                     wrap::fix<2, wrap::no_process<fx::bitcrush<NV>>>, 
                                     fx::sampleandhold<NV>, 
                                     core::gain<NV>>;

namespace dry_wet3_t_parameters
{
}

template <int NV>
using dry_wet3_t = container::split<parameter::plain<Sumo_impl::dry_wet_mixer2_t<NV>, 0>, 
                                    wrap::fix<2, dry_path2_t<NV>>, 
                                    wet_path2_t<NV>>;

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
                                    chain1_t<NV>, 
                                    dry_wet3_t<NV>, 
                                    Stomp_t<NV>, 
                                    core::gain<NV>, 
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
                                parameter::plain<project::Tube2<NV>, 1>, 
                                parameter::plain<Sumo_impl::WEIGHT_EQ_t<NV>, 0>, 
                                parameter::plain<Sumo_impl::cable_table1_t<NV>, 0>>;

template <int NV>
using Crush = parameter::chain<ranges::Identity, 
                               parameter::plain<Sumo_impl::minmax4_t<NV>, 0>, 
                               parameter::plain<Sumo_impl::dry_wet3_t<NV>, 0>>;

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
using OutGain = parameter::plain<core::gain<NV>, 0>;
template <int NV>
using Sumo_t_plist = parameter::list<Heavy<NV>, 
                                     Mix<NV>, 
                                     Weight<NV>, 
                                     Stomp<NV>, 
                                     Crush<NV>, 
                                     OutGain<NV>>;
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
		SNEX_METADATA_ENCODED_PARAMETERS(94)
		{
			0x005B, 0x0000, 0x4800, 0x6165, 0x7976, 0x0000, 0x0000, 0x0000, 
            0x8000, 0xAC3F, 0x0101, 0x003F, 0x8000, 0x003F, 0x0000, 0x5B00, 
            0x0001, 0x0000, 0x694D, 0x0078, 0x0000, 0x0000, 0x0000, 0x3F80, 
            0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x0000, 0x025B, 0x0000, 
            0x5700, 0x6965, 0x6867, 0x0074, 0x0000, 0x0000, 0x0000, 0x3F80, 
            0xF04A, 0x3F00, 0x0000, 0x3F80, 0x0000, 0x0000, 0x035B, 0x0000, 
            0x5300, 0x6F74, 0x706D, 0x0000, 0x0000, 0x0000, 0x8000, 0x003F, 
            0x0000, 0x0000, 0x8000, 0x003F, 0x0000, 0x5B00, 0x0004, 0x0000, 
            0x7243, 0x7375, 0x0068, 0x0000, 0x0000, 0x0000, 0x3F80, 0x023D, 
            0x3E4A, 0x0000, 0x3F80, 0x0000, 0x0000, 0x055B, 0x0000, 0x4F00, 
            0x7475, 0x6147, 0x6E69, 0x0000, 0xC800, 0x00C2, 0x0000, 0x0000, 
            0x0000, 0x3E00, 0xAD83, 0xCD40, 0xCCCC, 0x003D
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
		auto& WEIGHT_EQ = this->getT(2).getT(1).getT(2);                              // Sumo_impl::WEIGHT_EQ_t<NV>
		auto& split2 = this->getT(2).getT(2);                                         // Sumo_impl::split2_t<NV>
		auto& HeavyGainMatch = this->getT(2).getT(2).getT(0);                         // Sumo_impl::HeavyGainMatch_t<NV>
		auto& cable_table1 = this->getT(2).getT(2).getT(1);                           // Sumo_impl::cable_table1_t<NV>
		auto& minmax5 = this->getT(2).getT(2).getT(2);                                // Sumo_impl::minmax5_t<NV>
		auto& dry_wet1 = this->getT(3);                                               // Sumo_impl::dry_wet1_t<NV>
		auto& dry_path = this->getT(3).getT(0);                                       // Sumo_impl::dry_path_t<NV>
		auto& dry_wet_mixer = this->getT(3).getT(0).getT(0);                          // Sumo_impl::dry_wet_mixer_t<NV>
		auto& dry_gain = this->getT(3).getT(0).getT(1);                               // core::gain<NV>
		auto& wet_path = this->getT(3).getT(1);                                       // Sumo_impl::wet_path_t<NV>
		auto& chain = this->getT(3).getT(1).getT(0);                                  // Sumo_impl::chain_t<NV>
		auto& Mojo = this->getT(3).getT(1).getT(0).getT(0);                           // project::Mojo<NV>
		auto& Mojo1 = this->getT(3).getT(1).getT(0).getT(1);                          // project::Mojo<NV>
		auto& gain2 = this->getT(3).getT(1).getT(0).getT(2);                          // core::gain<NV>
		auto& chain1 = this->getT(3).getT(1).getT(1);                                 // Sumo_impl::chain1_t<NV>
		auto& svf_eq2 = this->getT(3).getT(1).getT(1).getT(0);                        // filters::svf_eq<NV>
		auto& Tube2 = this->getT(3).getT(1).getT(1).getT(1);                          // project::Tube2<NV>
		auto& Tube3 = this->getT(3).getT(1).getT(1).getT(2);                          // project::Tube2<NV>
		auto& gain3 = this->getT(3).getT(1).getT(1).getT(3);                          // core::gain<NV>
		auto& dry_wet3 = this->getT(3).getT(1).getT(2);                               // Sumo_impl::dry_wet3_t<NV>
		auto& dry_path2 = this->getT(3).getT(1).getT(2).getT(0);                      // Sumo_impl::dry_path2_t<NV>
		auto& dry_wet_mixer2 = this->getT(3).getT(1).getT(2).getT(0).getT(0);         // Sumo_impl::dry_wet_mixer2_t<NV>
		auto& dry_gain2 = this->getT(3).getT(1).getT(2).getT(0).getT(1);              // core::gain<NV>
		auto& wet_path2 = this->getT(3).getT(1).getT(2).getT(1);                      // Sumo_impl::wet_path2_t<NV>
		auto& bitcrush = this->getT(3).getT(1).getT(2).getT(1).getT(0);               // wrap::no_process<fx::bitcrush<NV>>
		auto& sampleandhold = this->getT(3).getT(1).getT(2).getT(1).getT(1);          // fx::sampleandhold<NV>
		auto& wet_gain2 = this->getT(3).getT(1).getT(2).getT(1).getT(2);              // core::gain<NV>
		auto& Stomp = this->getT(3).getT(1).getT(3);                                  // Sumo_impl::Stomp_t<NV>
		auto& dry_wet2 = this->getT(3).getT(1).getT(3).getT(0);                       // Sumo_impl::dry_wet2_t<NV>
		auto& dry_path1 = this->getT(3).getT(1).getT(3).getT(0).getT(0);              // Sumo_impl::dry_path1_t<NV>
		auto& dry_wet_mixer1 = this->getT(3).getT(1).getT(3).getT(0).getT(0).getT(0); // Sumo_impl::dry_wet_mixer1_t<NV>
		auto& dry_gain1 = this->getT(3).getT(1).getT(3).getT(0).getT(0).getT(1);      // core::gain<NV>
		auto& wet_path1 = this->getT(3).getT(1).getT(3).getT(0).getT(1);              // Sumo_impl::wet_path1_t<NV>
		auto& svf_eq = this->getT(3).getT(1).getT(3).getT(0).getT(1).getT(0);         // filters::svf_eq<NV>
		auto& svf_eq1 = this->getT(3).getT(1).getT(3).getT(0).getT(1).getT(1);        // filters::svf_eq<NV>
		auto& wet_gain1 = this->getT(3).getT(1).getT(3).getT(0).getT(1).getT(2);      // core::gain<NV>
		auto& gain = this->getT(3).getT(1).getT(4);                                   // core::gain<NV>
		auto& gain1 = this->getT(3).getT(1).getT(5);                                  // core::gain<NV>
		auto& wet_gain = this->getT(3).getT(1).getT(6);                               // core::gain<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		dry_wet3.getParameterT(0).connectT(0, dry_wet_mixer2);  // DryWet -> dry_wet_mixer2::Value
		dry_wet2.getParameterT(0).connectT(0, dry_wet_mixer1);  // DryWet -> dry_wet_mixer1::Value
		dry_wet1.getParameterT(0).connectT(0, dry_wet_mixer);   // DryWet -> dry_wet_mixer::Value
		this->getParameterT(0).connectT(0, smoothed_parameter); // Heavy -> smoothed_parameter::Value
		
		this->getParameterT(1).connectT(0, dry_wet1); // Mix -> dry_wet1::DryWet
		
		auto& Weight_p = this->getParameterT(2);
		Weight_p.connectT(0, Tube2);        // Weight -> Tube2::Tube
		Weight_p.connectT(1, Tube3);        // Weight -> Tube3::Tube
		Weight_p.connectT(2, WEIGHT_EQ);    // Weight -> WEIGHT_EQ::Value
		Weight_p.connectT(3, cable_table1); // Weight -> cable_table1::Value
		
		this->getParameterT(3).connectT(0, smoothed_parameter2); // Stomp -> smoothed_parameter2::Value
		
		auto& Crush_p = this->getParameterT(4);
		Crush_p.connectT(0, minmax4);  // Crush -> minmax4::Value
		Crush_p.connectT(1, dry_wet3); // Crush -> dry_wet3::DryWet
		
		this->getParameterT(5).connectT(0, gain1); // OutGain -> gain1::Gain
		
		// Modulation Connections ------------------------------------------------------------------
		
		mojo1.getWrappedObject().getParameter().connectT(0, Mojo);            // mojo1 -> Mojo::Input
		pma.getWrappedObject().getParameter().connectT(0, Mojo1);             // pma -> Mojo1::Input
		minmax.getWrappedObject().getParameter().connectT(0, gain);           // minmax -> gain::Gain
		cable_table.getWrappedObject().getParameter().connectT(0, minmax);    // cable_table -> minmax::Value
		HeavyGainMatch.getWrappedObject().getParameter().connectT(0, gain2);  // HeavyGainMatch -> gain2::Gain
		smoothed_parameter.getParameter().connectT(0, mojo1);                 // smoothed_parameter -> mojo1::Value
		smoothed_parameter.getParameter().connectT(1, pma);                   // smoothed_parameter -> pma::Value
		smoothed_parameter.getParameter().connectT(2, cable_table);           // smoothed_parameter -> cable_table::Value
		smoothed_parameter.getParameter().connectT(3, HeavyGainMatch);        // smoothed_parameter -> HeavyGainMatch::Value
		minmax1.getWrappedObject().getParameter().connectT(0, svf_eq);        // minmax1 -> svf_eq::Frequency
		minmax1.getWrappedObject().getParameter().connectT(1, svf_eq1);       // minmax1 -> svf_eq1::Frequency
		minmax2.getWrappedObject().getParameter().connectT(0, svf_eq);        // minmax2 -> svf_eq::Q
		minmax3.getWrappedObject().getParameter().connectT(0, svf_eq1);       // minmax3 -> svf_eq1::Q
		smoothed_parameter2.getParameter().connectT(0, minmax1);              // smoothed_parameter2 -> minmax1::Value
		smoothed_parameter2.getParameter().connectT(1, minmax2);              // smoothed_parameter2 -> minmax2::Value
		smoothed_parameter2.getParameter().connectT(2, minmax3);              // smoothed_parameter2 -> minmax3::Value
		minmax4.getWrappedObject().getParameter().connectT(0, sampleandhold); // minmax4 -> sampleandhold::Counter
		minmax4.getWrappedObject().getParameter().connectT(1, bitcrush);      // minmax4 -> bitcrush::BitDepth
		WEIGHT_EQ.getWrappedObject().getParameter().connectT(0, svf_eq2);     // WEIGHT_EQ -> svf_eq2::Gain
		minmax5.getWrappedObject().getParameter().connectT(0, gain3);         // minmax5 -> gain3::Gain
		cable_table1.getWrappedObject().getParameter().connectT(0, minmax5);  // cable_table1 -> minmax5::Value
		auto& dry_wet_mixer_p = dry_wet_mixer.getWrappedObject().getParameter();
		dry_wet_mixer_p.getParameterT(0).connectT(0, dry_gain); // dry_wet_mixer -> dry_gain::Gain
		dry_wet_mixer_p.getParameterT(1).connectT(0, wet_gain); // dry_wet_mixer -> wet_gain::Gain
		auto& dry_wet_mixer2_p = dry_wet_mixer2.getWrappedObject().getParameter();
		dry_wet_mixer2_p.getParameterT(0).connectT(0, dry_gain2); // dry_wet_mixer2 -> dry_gain2::Gain
		dry_wet_mixer2_p.getParameterT(1).connectT(0, wet_gain2); // dry_wet_mixer2 -> wet_gain2::Gain
		auto& dry_wet_mixer1_p = dry_wet_mixer1.getWrappedObject().getParameter();
		dry_wet_mixer1_p.getParameterT(0).connectT(0, dry_gain1); // dry_wet_mixer1 -> dry_gain1::Gain
		dry_wet_mixer1_p.getParameterT(1).connectT(0, wet_gain1); // dry_wet_mixer1 -> wet_gain1::Gain
		
		// Default Values --------------------------------------------------------------------------
		
		;                                         // smoothed_parameter::Value is automated
		smoothed_parameter.setParameterT(1, 0.1); // control::smoothed_parameter::SmoothingTime
		smoothed_parameter.setParameterT(2, 1.);  // control::smoothed_parameter::Enabled
		
		;                                          // smoothed_parameter2::Value is automated
		smoothed_parameter2.setParameterT(1, 0.1); // control::smoothed_parameter::SmoothingTime
		smoothed_parameter2.setParameterT(2, 1.);  // control::smoothed_parameter::Enabled
		
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
		
		;                                   // minmax4::Value is automated
		minmax4.setParameterT(1, 0.);       // control::minmax::Minimum
		minmax4.setParameterT(2, 50.);      // control::minmax::Maximum
		minmax4.setParameterT(3, 0.678303); // control::minmax::Skew
		minmax4.setParameterT(4, 0.);       // control::minmax::Step
		minmax4.setParameterT(5, 0.);       // control::minmax::Polarity
		
		; // cable_table::Value is automated
		
		;                                  // minmax::Value is automated
		minmax.setParameterT(1, -8);       // control::minmax::Minimum
		minmax.setParameterT(2, -2.9);     // control::minmax::Maximum
		minmax.setParameterT(3, 0.576205); // control::minmax::Skew
		minmax.setParameterT(4, 0.033978); // control::minmax::Step
		minmax.setParameterT(5, 1.);       // control::minmax::Polarity
		
		;                                     // WEIGHT_EQ::Value is automated
		WEIGHT_EQ.setParameterT(1, 0.);       // control::minmax::Minimum
		WEIGHT_EQ.setParameterT(2, 5.);       // control::minmax::Maximum
		WEIGHT_EQ.setParameterT(3, 0.982838); // control::minmax::Skew
		WEIGHT_EQ.setParameterT(4, 0.1);      // control::minmax::Step
		WEIGHT_EQ.setParameterT(5, 0.);       // control::minmax::Polarity
		
		;                                            // HeavyGainMatch::Value is automated
		HeavyGainMatch.setParameterT(1, -6.7);       // control::minmax::Minimum
		HeavyGainMatch.setParameterT(2, 0.);         // control::minmax::Maximum
		HeavyGainMatch.setParameterT(3, 0.524067);   // control::minmax::Skew
		HeavyGainMatch.setParameterT(4, 0.00692749); // control::minmax::Step
		HeavyGainMatch.setParameterT(5, 1.);         // control::minmax::Polarity
		
		; // cable_table1::Value is automated
		
		;                                     // minmax5::Value is automated
		minmax5.setParameterT(1, -2.3);       // control::minmax::Minimum
		minmax5.setParameterT(2, 1.4);        // control::minmax::Maximum
		minmax5.setParameterT(3, 0.684645);   // control::minmax::Skew
		minmax5.setParameterT(4, 0.00857764); // control::minmax::Step
		minmax5.setParameterT(5, 1.);         // control::minmax::Polarity
		
		; // dry_wet1::DryWet is automated
		
		; // dry_wet_mixer::Value is automated
		
		;                               // dry_gain::Gain is automated
		dry_gain.setParameterT(1, 20.); // core::gain::Smoothing
		dry_gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		; // Mojo::Input is automated
		
		; // Mojo1::Input is automated
		
		;                            // gain2::Gain is automated
		gain2.setParameterT(1, 20.); // core::gain::Smoothing
		gain2.setParameterT(2, 0.);  // core::gain::ResetValue
		
		svf_eq2.setParameterT(0, 153.273); // filters::svf_eq::Frequency
		svf_eq2.setParameterT(1, 1.);      // filters::svf_eq::Q
		;                                  // svf_eq2::Gain is automated
		svf_eq2.setParameterT(3, 0.01);    // filters::svf_eq::Smoothing
		svf_eq2.setParameterT(4, 2.);      // filters::svf_eq::Mode
		svf_eq2.setParameterT(5, 1.);      // filters::svf_eq::Enabled
		
		Tube2.setParameterT(0, 0.5); // project::Tube2::Input
		;                            // Tube2::Tube is automated
		
		Tube3.setParameterT(0, 0.5); // project::Tube2::Input
		;                            // Tube3::Tube is automated
		
		;                            // gain3::Gain is automated
		gain3.setParameterT(1, 20.); // core::gain::Smoothing
		gain3.setParameterT(2, 0.);  // core::gain::ResetValue
		
		; // dry_wet3::DryWet is automated
		
		; // dry_wet_mixer2::Value is automated
		
		;                                // dry_gain2::Gain is automated
		dry_gain2.setParameterT(1, 20.); // core::gain::Smoothing
		dry_gain2.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                              // bitcrush::BitDepth is automated
		bitcrush.setParameterT(1, 0.); // fx::bitcrush::Mode
		
		; // sampleandhold::Counter is automated
		
		;                                // wet_gain2::Gain is automated
		wet_gain2.setParameterT(1, 20.); // core::gain::Smoothing
		wet_gain2.setParameterT(2, 0.);  // core::gain::ResetValue
		
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
		
		;                           // gain::Gain is automated
		gain.setParameterT(1, 20.); // core::gain::Smoothing
		gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                            // gain1::Gain is automated
		gain1.setParameterT(1, 20.); // core::gain::Smoothing
		gain1.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                               // wet_gain::Gain is automated
		wet_gain.setParameterT(1, 20.); // core::gain::Smoothing
		wet_gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		this->setParameterT(0, 0.503932);
		this->setParameterT(1, 1.);
		this->setParameterT(2, 0.503667);
		this->setParameterT(3, 0.);
		this->setParameterT(4, 0.197274);
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
		
		this->getT(2).getT(1).getT(0).setExternalData(b, index); // Sumo_impl::cable_table_t<NV>
		this->getT(2).getT(2).getT(1).setExternalData(b, index); // Sumo_impl::cable_table1_t<NV>
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


