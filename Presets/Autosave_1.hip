Processor 
Type SynthChain ID KO Bypassed Gain 	      �?Balance 	        VoiceLimit 	      P@KillFadeTime 	      4@IconColour 0 packageName  BuildVersion �  EditorStates BodyShown 0 Visible 1 Solo 0 Folded 0  ChildProcessors  Processor Type MidiProcessorChain ID Midi Processor Bypassed EditorStates BodyShown 1 Visible 0 Solo 0  ChildProcessors  Processor Type ScriptProcessor ID Interface Bypassed Script "include("Core/Primitives.js");
include("Core/ThemeData.js");
include("Core/Theme.js");

include("Config.js");

include("StyleHelpers.js");
include("Styles.js");
include("Assets.js");

include("Animations.js");

include("KO_Graphics.js");
include("UpdateChecker.js");

include("VuMeterSlider.js");

include("UserSettings.js");
include("ZoomHandler.js");
include("UI.js");
include("Router.js");
include("Randomization.js");

include("Header.js");
include("x.js");
include("FXs.js");

include("About.js");
include("Supabase.js");
include("Panic.js");

include("Activation.js");

Content.makeFrontInterface(780, 350);

const var OutGain = Synth.getEffect("OutGain");
const var SoftClip = Synth.getEffect("SoftClip");
const var BypassGain = Synth.getEffect("BypassGain");

Globals.x = false;
Globals.xLocked = true;
Globals.OS = Engine.getOS();
Globals.activated = false;
Globals.canUpdate = false;
Globals.bypassed = false;

const var DryGain = Synth.getEffect("DryGain");
const var WetGain = Synth.getEffect("WetGain");
const var Matrix1 = Synth.getEffect("Matrix1");
const var Matrix2 = Synth.getEffect("Matrix2");

Supabase.getActivationStatus();
UserSettings.load();

const UP = Engine.createUserPresetHandler();

if (Globals.OS !== 'LINUX') {
	Globals.canUpdate = UpdateChecker.checkUpdate(onUpdate);
}

inline function onUpdate(canUpdate) {
	Header.Update_btn.showControl(canUpdate);
	Header.update_now_btn.showControl(canUpdate);
}

inline function onClose_PresetBrowser_btnControl(component, value) {
	Router.goTo('Main');
};

Content.getComponent("Close_PresetBrowser_btn").setControlCallback(onClose_PresetBrowser_btnControl);

//KO_graphics.initAni();

Content.callAfterDelay(10, afterDelay, {});
inline function afterDelay() {

	Globals.currentEffect = 'Boxer';
	
	FXs.FX_Selector[0].setValue(1);
	FXs.FX_Selector[0].changed();
	
	Router.goTo('Main');
	Console.print('yes');
	
	//Panic.panic();
}



// preventing initial x trigger
Content.callAfterDelay(200, afterDelay2, {});
inline function afterDelay2() {

	Globals.xLocked = false;
	Header.formatHeader();
}

const var GainReduction = Synth.getEffect("DemoGain");
const var GainReductionTimer = Engine.createTimerObject();
const var TimeoutCounter = 15000;

var TimeoutCurrent = 0;
	
GainReductionTimer.setTimerCallback(function() {
	
	if (Globals.bypassed) {return;}

    TimeoutCurrent += 1000;
    
    if (TimeoutCurrent == TimeoutCounter) {
      TimeoutCurrent = 0;  
    }
    if (TimeoutCurrent > 13000) {
       GainReduction.setBypassed(false);
    } else {
        GainReduction.setBypassed(true);
    }
});

inline function addVisualGuide() {
	
	Content.addVisualGuide([WIDTH / 2, 0], Colours.yellow);
	Content.addVisualGuide([490, 0], Colours.red);
	Content.addVisualGuide([670, 0], Colours.red);
}

//addVisualGuide();

if (!Globals.activated) {
	GainReduction.setBypassed(false);
	GainReductionTimer.startTimer(1000);		
} else {
	Activation.unlockDemoLimitations();
}





function onNoteOn()
{
	
}
 function onNoteOff()
{
	
}
 function onController()
{
	
}
 function onTimer()
{
	
}
 function onControl(number, value)
{
	
}
  EditorStates BodyShown 1 Visible 1 Solo 0 contentShown 1 onInitOpen 1  ChildProcessors   Content  Control type ScriptButton id Limit_Button value 	      �? Control type ScriptSlider id Boxer_Punch_knb value 	      �? Control type ScriptSlider id Boxer_Wut_knb value 	      �? Control type ScriptButton id Boxer_6oz_knb value 	         Control type ScriptSlider id Karate_Speed_knb value 	   @33�? Control type ScriptSlider id Karate_Focus_knb value 	      �? Control type ScriptSlider id Karate_Pressure_knb value 	      �? Control type ScriptSlider id Karate_Air_knb value 	      �? Control type ScriptSlider id Sumo_Heavy_knb value 	      �? Control type ScriptSlider id Sumo_Weight_knb value 	      �? Control type ScriptSlider id Sumo_Stomp_knb value 	         Control type ScriptSlider id Sumo_Crush_knb value 	   @33�? Control type ScriptSlider id OutputPeakMeterFillL value 	      Y� Control type ScriptSlider id OutputPeakMeterPointL value 	      Y� Control type ScriptSlider id GainSlider value 	      �> Control type ScriptSlider id 	Mix_knb value 	      �? Control type ScriptButton id Close_PresetBrowser_btn value 	         Control type ScriptButton id update_now_btn value 	         Control type ScriptButton id Update_btn value 	      �? UIData  ContentProperties DeviceType 	Desktop Component type ScriptPanel id background x 	        y 	        width 	     `�@height 	     0v@Component type ScriptPanel id 	display x 	      .@y 	      .@parentComponent background width 	     p�@height 	      t@	Component type ScriptPanel id Main_Route x 	        y 	        width 	     p�@height 	      t@parentComponent 	display Component 	type ScriptButton id Limit_Button x 	?      y 	      $@width 	      N@height 	      9@parentComponent Main_Route isPluginParameter 1 pluginParameterName Limit  Component type ScriptPanel id Algo1_AlgoRoute x 	     Py@y 	      D@parentComponent Main_Route width 	     s@height 	      n@Component type ScriptSlider id Boxer_Punch_knb x 	     @P@y 	      4@parentComponent Algo1_AlgoRoute width 	     �Q@height 	     �V@text Punch mouseSensitivity 	       @mode NormalizedPercentage suffix % middlePosition 	      �?pluginParameterName Punch isPluginParameter 1 defaultValue 	      �? Component type ScriptSlider id Boxer_Wut_knb x 	      g@y 	      4@parentComponent Algo1_AlgoRoute width 	     �Q@height 	     �V@text Wut mouseSensitivity 	       @mode NormalizedPercentage suffix % middlePosition 	      �?pluginParameterName Wut isPluginParameter 1 defaultValue 	      �? Component 
type ScriptButton id Boxer_6oz_knb x 	     �\@y 	      b@width _   height (   text LOGIK parentComponent Algo1_AlgoRoute isPluginParameter 1 pluginParameterName Logik  Component type ScriptPanel id Algo2_AlgoRoute x 	     Py@y 	      D@parentComponent Main_Route width 	     s@height 	      n@visible     Component type ScriptSlider id Karate_Speed_knb x 	     @U@y 	     @`@parentComponent Algo2_AlgoRoute width 	     �K@height 	     �R@text Speed mouseSensitivity 	       @mode NormalizedPercentage suffix % middlePosition 	      �?pluginParameterName Speed isPluginParameter 1 defaultValue 	   @33�? Component type ScriptSlider id Karate_Focus_knb x 	     �e@y 	      4@parentComponent Algo2_AlgoRoute width 	     �Q@height 	     �V@text Focus mouseSensitivity 	       @mode NormalizedPercentage suffix % middlePosition 	      �?pluginParameterName Focus isPluginParameter 1 defaultValue 	      �? Component type ScriptSlider id Karate_Pressure_knb x 	     �R@y 	      4@parentComponent Algo2_AlgoRoute width 	     �Q@height 	     �V@text Druck mouseSensitivity 	       @mode NormalizedPercentage suffix % middlePosition 	      �?pluginParameterName Druck isPluginParameter 1 defaultValue 	      �? Component type ScriptSlider id Karate_Air_knb x 	      g@y 	     @`@parentComponent Algo2_AlgoRoute width 	     �K@height 	     �R@text Air mouseSensitivity 	       @mode NormalizedPercentage suffix % middlePosition 	      �?pluginParameterName Air isPluginParameter 1 defaultValue 	      �? Component type ScriptPanel id Algo3_AlgoRoute x 	     Py@y 	      D@parentComponent Main_Route width 	     s@height 	      n@visible     Component type ScriptSlider id Sumo_Heavy_knb x 	     �R@y 	      4@parentComponent Algo3_AlgoRoute width 	     �Q@height 	     �V@text Heavy mouseSensitivity 	       @mode NormalizedPercentage suffix % middlePosition 	      �?pluginParameterName Heavy isPluginParameter 1 defaultValue 	      �? Component type ScriptSlider id Sumo_Weight_knb x 	     �e@y 	      4@parentComponent Algo3_AlgoRoute width 	     �Q@height 	     �V@text Weight mouseSensitivity 	       @mode NormalizedPercentage suffix % middlePosition 	      �?pluginParameterName Weight isPluginParameter 1 defaultValue 	      �? Component type ScriptSlider id Sumo_Stomp_knb x 	     @U@y 	     @`@parentComponent Algo3_AlgoRoute width 	     �K@height 	     �R@text Stomp mouseSensitivity 	       @mode NormalizedPercentage suffix % middlePosition 	      �?pluginParameterName Stomp isPluginParameter 1  Component type ScriptSlider id Sumo_Crush_knb x 	      g@y 	     @`@parentComponent Algo3_AlgoRoute width 	     �K@height 	     �R@text Crush mouseSensitivity 	       @mode NormalizedPercentage suffix % middlePosition 	      �?pluginParameterName Crush isPluginParameter 1 defaultValue 	   @33�? Component type ScriptPanel id 
KO_panel x 	     �R�y 	        parentComponent Main_Route width 	     `}@height 	      t@Component 
type ScriptButton id KO_clicker x 	     �R@y 	        parentComponent 
KO_panel enableMidiLearn 0 isMomentary 1 saveInPreset 0 width 	     `s@height 	      t@ Component type ScriptButton id 
FX_1_btn x 	     �s@y 	     �R@parentComponent Main_Route width 	      D@height 	      D@enableMidiLearn 0 radioGroup 	      �?saveInPreset 0 isPluginParameter 1 pluginParameterName Algo 1  Component type ScriptButton id 
FX_2_btn x 	     �u@y 	     @`@parentComponent Main_Route width 	      D@height 	      D@enableMidiLearn 0 radioGroup 	      �?saveInPreset 0 pluginParameterName Algo 2 isPluginParameter 1  Component type ScriptButton id 
FX_3_btn x 	     pw@y 	      g@parentComponent Main_Route width 	      D@height 	      D@enableMidiLearn 0 radioGroup 	      �?saveInPreset 0 pluginParameterName Algo 3 isPluginParameter 1  Component type ScriptSlider id OutputPeakMeterFillL x 	     h�@y 	     �K@parentComponent Main_Route width 	      @height 	      g@text PeakMeterVertFill mode 	Decibel min 	      Y�max 	      8@stepSize 	   ����?suffix  dB middlePosition 	      2� Component type ScriptSlider id OutputPeakMeterPointL x 	     h�@y 	     �K@parentComponent Main_Route width 	      @height 	      g@text PeakMeterVertPointer mode 	Decibel min 	      Y�max 	      8@stepSize 	   ����?suffix  dB middlePosition 	      2� Component type ScriptSlider id GainSlider x 	     ��@y 	     �K@parentComponent Main_Route width 	      D@height 	     �k@text PeakMeterVertPointer mode 	Decibel min 	      Y�max 	      8@stepSize 	   ����?suffix  dB middlePosition 	      2�isPluginParameter 1 pluginParameterName 
Out Gain  Component type ScriptButton id bypass x 	     �@y 	     �q@parentComponent Main_Route width 	      >@height 	      >@saveInPreset 0  Component type ScriptSlider id 	Mix_knb x 	     �}@y 	     �p@parentComponent Main_Route width 	     �f@height 	      >@isPluginParameter 1 pluginParameterName Mix middlePosition 	      �?mouseSensitivity 	       @text MIX defaultValue 	      �?mode NormalizedPercentage suffix %  Component type ScriptPanel id PresetBrowser_Route x 	        y 	        parentComponent 	display width 	     p�@height 	      t@visible     Component type ScriptFloatingTile id FloatingTile1 x 	      4@y 	      .@parentComponent PresetBrowser_Route width 	     Ȅ@height 	      r@ContentType PresetBrowser bgColour 4143972352 itemColour 4287692721 itemColour2 0 Data �{
  "ShowSaveButton": true,
  "ShowExpansionsAsColumn": false,
  "ShowFolderButton": true,
  "ShowNotes": false,
  "ShowEditButtons": true,
  "EditButtonOffset": 10,
  "ShowAddButton": true,
  "ShowRenameButton": true,
  "ShowDeleteButton": true,
  "ShowFavoriteIcon": true,
  "ButtonsInsideBorder": false,
  "NumColumns": 1,
  "ColumnWidthRatio": [
    0.3333333333333333,
    0.3333333333333333,
    0.3333333333333333
  ],
  "ListAreaOffset": [
    0,
    0,
    0,
    0
  ],
  "ColumnRowPadding": [
    0,
    0,
    0,
    0
  ],
  "SearchBarBounds": [],
  "MoreButtonBounds": [],
  "SaveButtonBounds": [],
  "FavoriteButtonBounds": []
}  Component type ScriptButton id Close_PresetBrowser_btn x 	     �@y 	      $@parentComponent PresetBrowser_Route width 	     �A@height 	     �A@ Component type ScriptPanel id About_Route x 	        y 	        parentComponent 	display width 	     p�@height 	      t@visible     Component type ScriptPanel id 
KO_2_pnl x 	     �a@y 	     @P@parentComponent About_Route width 	     �e@height 	     `c@ Component type ScriptLabel id Berlin_love_lbl x 	      $@y 	     �q@parentComponent About_Route text FROM BERLIN WITH <3 width 	     �b@height 	      4@ Component type ScriptButton id incognito_btn x 	      $@y 	      $@parentComponent About_Route width 	      >@height 	      >@saveInPreset 0 text incognito enableMidiLearn 0 isMomentary 1  Component 
type ScriptButton id company_btn x 	      �@y 	     �q@parentComponent About_Route width 	     `c@height 	      4@saveInPreset 0 enableMidiLearn 0 isMomentary 1  Component type ScriptPanel id About_Container x 	     �w@y 	      N@parentComponent About_Route width 	     pr@height 	     �i@itemColour2 0 itemColour 0 textColour 0 bgColour 0 Component type ScriptLabel id title_lbl x 	      >@y 	        parentComponent About_Container text KO width 	     �Q@height 	      D@fontName inter-semi fontSize 	      H@alignment left editable 0 textColour 4294573052  Component type ScriptLabel id description_lbl x 	      >@y 	      D@parentComponent About_Container text knockout sound procession width 	     @o@height 	      9@editable 0 alignment left fontName inter-reg fontSize 	      4@textColour 4294573052  Component type ScriptButton id 
more_btn x 	     �K@y 	     �V@parentComponent About_Container text More like this saveInPreset 0 width 	     @e@height 	      D@enableMidiLearn 0 isMomentary 1  Component type ScriptButton id youtube_btn x 	      T@y 	      b@parentComponent About_Container width 	     �A@height 	      >@text 	youtube saveInPreset 0 enableMidiLearn 0 isMomentary 1  Component type ScriptButton id instagram_btn x 	     @`@y 	      b@parentComponent About_Container width 	      >@height 	      >@text instagram saveInPreset 0 enableMidiLearn 0 isMomentary 1  Component type ScriptButton id soundcloud_btn x 	     �e@y 	      b@parentComponent About_Container width 	      >@height 	      >@text soundcloud saveInPreset 0 enableMidiLearn 0 isMomentary 1  Component type ScriptPanel id version_pnl x 	      Y@y 	      $@parentComponent About_Container width 	      J@height 	      9@ Component 	type ScriptButton id update_now_btn x 	     �k@y 	     �n@parentComponent About_Route width 	      d@height 	     �F@text Update Now visible  Component type ScriptPanel id 	x_Route x 	       �y 	        parentComponent 	display width 	     p�@height 	      t@visible     Component type ScriptPanel id glitch_pnl x 	      *�y 	      @parentComponent 	x_Route width 	     pw@height 	     `s@ Component type ScriptLabel id x_anomaly x 	     �o@y 	      9@parentComponent 	x_Route width 	     �~@height 	      Y@text ANOMALY DETECTED fontName inter-semi fontSize 	      H@editable 0 textColour 4294507516  Component type ScriptPanel id x_code_pnl x 	     ��@y 	     �p@parentComponent 	x_Route width 	      a@height 	      ?@ Component type ScriptButton id 	wtf_btn x 	     P{@y 	      d@parentComponent 	x_Route width 	     �[@height 	     �F@text WTF saveInPreset 0 enableMidiLearn 0 isMomentary 1  Component 
type ScriptButton id About_btn x 	     @�@y 	      @parentComponent 	display width 	      >@height 	      >@text 
settings saveInPreset 0 enableMidiLearn 0  Component type ScriptButton id not_activated_btn x 	�      y 	      $@text NOT ACTIVATED enableMidiLearn 0 saveInPreset 0 isMomentary 1 width 	     @_@height 	      9@parentComponent 	display  Component 	type ScriptButton id Update_btn x 	     ��@y 	      @width 	      >@height 	      >@text 
doubleUp visible parentComponent 	display  Component type ScriptPanel id randomize_pnl_btn x 	     �@y 	      @width 	     �A@height 	     �A@allowCallbacks Clicks, Hover & Dragging parentComponent 	display  Component type ScriptButton id wtf_icon_btn x 	      �@y 	      @width 	      >@height 	      >@text wtf_selected isPluginParameter 1 pluginParameterName WTF saveInPreset 0 defaultValue 	      �?parentComponent 	display  Component type ScriptPanel id ZoomPanel x 	     ��@y 	     �t@parentComponent background width 	      >@height 	      9@allowCallbacks Clicks, Hover & Dragging  Component 
type ScriptPanel id Backdrop_overlay_pnl x 	        y 	        width 	     `�@height 	     �u@itemColour2 2499805184 itemColour 2499805184 allowCallbacks Clicks Only visible 0  Component type ScriptPanel id Activation_pnl x 	     �f@y 	      >@width 	     @z@height 	     �q@visible 0 	Component type ScriptLabel id title_lbl1 x 	      $@y 	      $@parentComponent Activation_pnl text 
Activate width 	     �p@height 	      >@fontName inter-reg fontSize 	      @@editable 0 textColour 4294573052 alignment left  Component type ScriptButton id Paste_btn x 	     �d@y 	     �K@saveInPreset 0 enableMidiLearn 0 isMomentary 1 text Paste parentComponent Activation_pnl width 	     @U@height 	     �A@ Component 	type ScriptButton id Buy_now_btn x 	      $@y 	      n@saveInPreset 0 enableMidiLearn 0 isMomentary 1 text 	Buy now parentComponent Activation_pnl  Component 
type ScriptButton id 
Activate x 	     @`@y 	     `c@saveInPreset 0 enableMidiLearn 0 isMomentary 1 width 	      d@height 	     �A@parentComponent Activation_pnl  Component type ScriptPanel id Serial_input_pnl x 	     �Q@y 	      Y@width 	     @p@height 	     �A@parentComponent Activation_pnl borderSize 	      �?bgColour 3087007743 textColour 4244635647 borderRadius 	      @ Component type ScriptLabel id serial_code_lbl x 	     �R@y 	     @Z@width 	     @o@height 	      9@alignment left fontName inter-reg parentComponent Activation_pnl fontSize 	      2@text  textColour 4294573052  Component type ScriptButton id close_activate_btn x 	     �w@y 	        width 	      D@height 	      D@text x enableMidiLearn 0 isMomentary 1 saveInPreset 0 parentComponent Activation_pnl  Component type ScriptPanel id loading_indicator x 	     `h@y 	      i@parentComponent Activation_pnl width 	      >@height 	      >@visible  Component type ScriptLabel id serial_error_label x 	     @`@y 	      i@parentComponent Activation_pnl width 	      d@height 	      >@text License Key not found :() textColour 4294394187 editable 0 fontName inter-reg visible      Processor Type ModulatorChain ID GainModulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID PitchModulation Bypassed Intensity 	        EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type EffectChain ID FX Bypassed EditorStates BodyShown 1 Visible 0 Solo 0  ChildProcessors  Processor Type 	RouteFX ID 	Matrix1 Bypassed EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors   RoutingMatrix 	NumSourceChannels    Channel0     Send0    Channel1    Send1    Channel2 ����Send2 ����Channel3 ����Send3 ���� Processor Type Hardcoded Master FX ID 	BoxerFX Bypassed Network Boxer Punch 	      �?Wut 	      �?Mix 	      �?_16oz 	        EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors   RoutingMatrix 	NumSourceChannels    Channel0 ����Send0 ����Channel1 ����Send1 ����Channel2    Send2 ����Channel3    Send3 ���� Processor 	Type Hardcoded Master FX ID 
KarateFX Bypassed Network Karate Focus 	      �?Mix 	      �?Air 	      �?Pressure 	      �?Speed 	   @33�?EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors   RoutingMatrix 	NumSourceChannels    Channel0 ����Send0 ����Channel1 ����Send1 ����Channel2    Send2 ����Channel3    Send3 ���� Processor 	Type Hardcoded Master FX ID SumoFX Bypassed Network Sumo Heavy 	      �?Mix 	      �?Weight 	      �?Stomp 	        Crush 	   @33�?EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors   RoutingMatrix 	NumSourceChannels    Channel0 ����Send0 ����Channel1 ����Send1 ����Channel2    Send2 ����Channel3    Send3 ���� Processor Type Hardcoded Master FX ID x Bypassed Network wtf EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors   RoutingMatrix 	NumSourceChannels    Channel0 ����Send0 ����Channel1 ����Send1 ����Channel2    Send2 ����Channel3    Send3 ���� Processor Type SimpleGain ID BypassGain Bypassed Gain 	      Y�Delay 	        Width 	      Y@Balance 	        InvertPolarity 	        EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors  Processor Type ModulatorChain ID Gain Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Delay Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Width Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Pan Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   RoutingMatrix 	NumSourceChannels    Channel0 ����Send0 ����Channel1 ����Send1 ����Channel2    Send2 ����Channel3    Send3 ���� Processor Type SimpleGain ID 	WetGain Bypassed Gain 	   �}��Delay 	        Width 	      Y@Balance 	        InvertPolarity 	        EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors  Processor Type ModulatorChain ID Gain Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Delay Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Width Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Pan Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   RoutingMatrix 	NumSourceChannels    Channel0 ����Send0 ����Channel1 ����Send1 ����Channel2    Send2 ����Channel3    Send3 ���� Processor Type SimpleGain ID 	DryGain Bypassed Gain 	   @(�Delay 	        Width 	      Y@Balance 	        InvertPolarity 	        EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors  Processor Type ModulatorChain ID Gain Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Delay Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Width Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Pan Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   RoutingMatrix 	NumSourceChannels    Channel0     Send0 ����Channel1    Send1 ����Channel2 ����Send2 ����Channel3 ����Send3 ���� Processor Type 	RouteFX ID 	Matrix2 Bypassed EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors   RoutingMatrix 	NumSourceChannels    Channel0     Send0 ����Channel1    Send1 ����Channel2 ����Send2     Channel3 ����Send3     Processor Type SimpleGain ID 	OutGain Bypassed Gain 	   �,_�>Delay 	        Width 	      Y@Balance 	        InvertPolarity 	        EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors  Processor Type ModulatorChain ID Gain Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Delay Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Width Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Pan Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   RoutingMatrix 	NumSourceChannels    Channel0     Send0 ����Channel1    Send1 ����Channel2 ����Send2 ����Channel3 ����Send3 ���� Processor Type SimpleGain ID 
DemoGain Bypassed Gain 	   ���;�Delay 	        Width 	      Y@Balance 	        InvertPolarity 	        EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors  Processor Type ModulatorChain ID Gain Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Delay Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Width Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Pan Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   RoutingMatrix 	NumSourceChannels    Channel0     Send0 ����Channel1    Send1 ����Channel2 ����Send2 ����Channel3 ����Send3 ���� Processor Type Hardcoded Master FX ID 
SoftClip Bypassed Network ClipSoftly EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors   RoutingMatrix 	NumSourceChannels    Channel0     Send0 ����Channel1    Send1 ����Channel2 ����Send2 ����Channel3 ����Send3 ���� RoutingMatrix 	NumSourceChannels    Channel0     Send0 ����Channel1    Send1 ����Channel2     Send2 ����Channel3    Send3 ���� macro_controls  macro name 	Macro 1 value 	        midi_cc ���� macro name 	Macro 2 value 	        midi_cc ���� macro name 	Macro 3 value 	        midi_cc ���� macro name 	Macro 4 value 	        midi_cc ���� macro name 	Macro 5 value 	        midi_cc ���� macro name 	Macro 6 value 	        midi_cc ���� macro name 	Macro 7 value 	        midi_cc ���� macro name 	Macro 8 value 	        midi_cc ���� MidiAutomation   MPEData Enabled  