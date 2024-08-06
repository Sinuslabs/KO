namespace FXs {
	
	const var FX_Selector = [Content.getComponent("FX_1_btn"),
	                         Content.getComponent("FX_2_btn"),
	                         Content.getComponent("FX_3_btn")];
	                         
    const var BoxerFX = Synth.getEffect("BoxerFX");
    const var KarateFX = Synth.getEffect("KarateFX");
    const var SumoFX = Synth.getEffect("SumoFX");
    
    const var Limit_Button = Content.getComponent("Limit_Button");
    
	for (btn in FX_Selector) {
		btn.setLocalLookAndFeel(Styles.LAF_FXSelectorBtn);
		btn.setControlCallback(onFX_btn);
	}
	
	Limit_Button.setControlCallback(onLimit);
	Limit_Button.setLocalLookAndFeel(Styles.LAF_LimitBtn);
	
	const var Boxer_knbs = [Content.getComponent("Boxer_Punch_knb"),
                        Content.getComponent("Boxer_Wut_knb")];

	const var Boxer_6oz_knb = Content.getComponent("Boxer_6oz_knb");
	
	const var Sumo_knbs = [Content.getComponent("Sumo_Heavy_knb"),
	                       Content.getComponent("Sumo_Weight_knb"),
	                       Content.getComponent("Sumo_Stomp_knb"),
	                       Content.getComponent("Sumo_Crush_knb")];
	
	
	const var Karate_knbs = [Content.getComponent("Karate_Speed_knb"),
	                         Content.getComponent("Karate_Focus_knb"),
	                         Content.getComponent("Karate_Air_knb"),
	                         Content.getComponent("Karate_Pressure_knb")
	                         ];
	
	for (knb in Boxer_knbs) {
		knb.setLocalLookAndFeel(Styles.LAF_DisplayKnobSimple);
		knb.setControlCallback(onBoxerKnbs);
	}
	
	Boxer_6oz_knb.setLocalLookAndFeel(Styles.LAF_displayButtonOutline);
	Boxer_6oz_knb.setControlCallback(on6oz);
	
	for (knb in Sumo_knbs) {
		knb.setLocalLookAndFeel(Styles.LAF_DisplayKnobSimple);
		knb.setControlCallback(onSumoKnbs);
	}
	
	for (knb in Karate_knbs) {
		knb.setLocalLookAndFeel(Styles.LAF_DisplayKnobSimple);
		knb.setControlCallback(onKarateKnbs);
	}
	
	inline function onLimit(component, value) {
		SoftClip.setBypassed(value);
	}
	
	inline function on6oz(component, value) {
		BoxerFX.setAttribute(BoxerFX._16oz, value);
	}
	
	inline function onBoxerKnbs(component, value) {
		
		switch(component.getId()) {
			case 'Boxer_Punch_knb':
				BoxerFX.setAttribute(BoxerFX.Punch, value);
			case 'Boxer_Wut_knb':
				BoxerFX.setAttribute(BoxerFX.Wut, value);
		}
		
	}
	
	inline function onKarateKnbs(component, value) {
		
		switch(component.getId()) {
			case 'Karate_Pressure_knb':
				KarateFX.setAttribute(KarateFX.Pressure, value);
			case 'Karate_Focus_knb':
				KarateFX.setAttribute(KarateFX.Focus, value);
			case 'Karate_Speed_knb':
				KarateFX.setAttribute(KarateFX.Speed, value);
			case 'Karate_Air_knb':
				KarateFX.setAttribute(KarateFX.Air, value);
		}
	}
	
	inline function onSumoKnbs(component, value) {
		
		switch(component.getId()) {
			case 'Sumo_Heavy_knb':
				SumoFX.setAttribute(SumoFX.Heavy, value);
			case 'Sumo_Weight_knb':
				SumoFX.setAttribute(SumoFX.Weight, value);
			case 'Sumo_Stomp_knb':
				SumoFX.setAttribute(SumoFX.Stomp, value);
			case 'Sumo_Crush_knb':
				SumoFX.setAttribute(SumoFX.Crush, value);
		}
	}
	
	const var up = Engine.createUserPresetHandler();
	Console.print(up.isInternalPresetLoad());
	
	inline function onFX_btn(component, value) {
		
		if (!value) return;
		
		Console.print('internal load: ' + UP.isInternalPresetLoad());
		
		local seconds = UP.getSecondsSinceLastPresetLoad();
	
		if (!Globals.xLocked && seconds >= 1) {
			Header.countClicks();			
		}
			
		Console.print(component.getId() + ' : value: ' + value);
	
		switch(component.getId()) {
			case 'FX_1_btn':
				KO_graphics.goTo('KO_1');
				Router.goToAlgoRoute('Algo1_AlgoRoute');
				BoxerFX.setBypassed(false);
				KarateFX.setBypassed(true);
				SumoFX.setBypassed(true);
				Globals.currentEffect = 'Boxer';
			case 'FX_2_btn':
				KO_graphics.goTo('KO_2');
				Router.goToAlgoRoute('Algo2_AlgoRoute');
				BoxerFX.setBypassed(true);
				KarateFX.setBypassed(false);
				SumoFX.setBypassed(true);
				Globals.currentEffect = 'Karate';
			case 'FX_3_btn':
				KO_graphics.goTo('KO_3');
				Router.goToAlgoRoute('Algo3_AlgoRoute');
				BoxerFX.setBypassed(true);
				KarateFX.setBypassed(true);
				SumoFX.setBypassed(false);
				Globals.currentEffect = 'Sumo';
		}
		
		KO_graphics.KO_panel.repaint();
	}
}