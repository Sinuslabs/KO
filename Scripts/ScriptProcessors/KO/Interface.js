include("Core/Primitives.js");
include("Core/ThemeData.js");
include("Core/Theme.js");

include("StyleHelpers.js");
include("Styles.js");
include("Assets.js");

include("Animations.js");

include("KO_Graphics.js");

include("VuMeterSlider.js");

include("UserSettings.js");
include("ZoomHandler.js");
include("UI.js");
include("Router.js");
include("Randomization.js");

include("Header.js");
include("x.js");
include("FXs.js");

include("Panic.js");

Content.makeFrontInterface(780, 350);

const var OutGain = Synth.getEffect("OutGain");
const var SoftClip = Synth.getEffect("SoftClip");

Globals.x = false;
Globals.OS = Engine.getOS();
UserSettings.load();

inline function onClose_PresetBrowser_btnControl(component, value)
{
	Router.goTo('Main');
};


Content.getComponent("Close_PresetBrowser_btn").setControlCallback(onClose_PresetBrowser_btnControl);




Content.callAfterDelay(10, afterDelay, {});

inline function afterDelay() {

	Globals.currentEffect = 'Boxer';
	KO_graphics.KO_panel.repaint();
	
	FXs.FX_Selector[0].setValue(1);
	FXs.FX_Selector[0].changed();
	
	Router.goTo('Main');
	//Panic.panic();
	
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
 