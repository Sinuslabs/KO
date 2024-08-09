include("Core/Primitives.js");
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
 