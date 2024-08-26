namespace FXs {
	
	const var FX_Selector = [Content.getComponent("FX_1_btn"),
	                         Content.getComponent("FX_2_btn"),
	                         Content.getComponent("FX_3_btn")];
	
	const var Knobs_Container = [Content.getComponent("Algo3_AlgoRoute"),
	                             Content.getComponent("Algo1_AlgoRoute"),
	                             Content.getComponent("Algo2_AlgoRoute")];
	
    const var BoxerFX = Synth.getEffect("BoxerFX");
    const var KarateFX = Synth.getEffect("KarateFX");
    const var SumoFX = Synth.getEffect("SumoFX");
    
    const var fx_select = Content.getComponent("fx_select");
    fx_select.setControlCallback(onFX_select);
    
    const var bypass = Content.getComponent("bypass");
    const var Mix_knb = Content.getComponent("Mix_knb");
    
    Mix_knb.setControlCallback(onMix);
    Mix_knb.setLocalLookAndFeel(Styles.LAF_Mix);
    
    bypass.setControlCallback(onBypass);
    bypass.setLocalLookAndFeel(Styles.LAF_FXSelectorBtn);
    
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
	
	
	const var Karate_knbs = [
	                         Content.getComponent("Karate_Focus_knb"),
	                         Content.getComponent("Karate_Air_knb"),
	                         Content.getComponent("Karate_Pressure_knb")
	                         ];
	
	for (knb in Boxer_knbs) {
		knb.setLocalLookAndFeel(Styles.LAF_DisplayKnobSimple);
		knb.setControlCallback(onBoxerKnbs);
	}
	
	Boxer_6oz_knb.setLocalLookAndFeel(Styles.LAF_displayButtonLogic);
	Boxer_6oz_knb.setControlCallback(on6oz);
	
	for (knb in Sumo_knbs) {
		knb.setLocalLookAndFeel(Styles.LAF_DisplayKnobSimple);
		knb.setControlCallback(onSumoKnbs);
	}
	
	for (knb in Karate_knbs) {
		knb.setLocalLookAndFeel(Styles.LAF_DisplayKnobSimple);
		knb.setControlCallback(onKarateKnbs);
	}
	
	inline function onMix(component, value) {
		DryGain.setAttribute(DryGain.Gain, Engine.getDecibelsForGainFactor(1 - value));
		WetGain.setAttribute(WetGain.Gain, Engine.getDecibelsForGainFactor(value));
		
		local dryAmount = parseInt((1 - value) * 100);
		local wetAmount = parseInt(value * 100);
	};
	
	inline function onLimit(component, value) {
		SoftClip.setBypassed(value);
	}
	
	inline function on6oz(component, value) {
		BoxerFX.setAttribute(BoxerFX._16oz, value);
	}
	
	inline function onFX_select(component, value) {
		
		
		if (value == 0) {
			goToAlgo('Boxer');
		}
		
		if (value == 1) {
			goToAlgo('Karate');
		}
		
		if (value == 2) {
			goToAlgo('Sumo');
		}

	}
	
	inline function onBoxerKnbs(component, value) {
		
		switch(component.getId()) {
			case 'Boxer_Punch_knb':
				BoxerFX.setAttribute(BoxerFX.Punch, value);
			case 'Boxer_Wut_knb':
				BoxerFX.setAttribute(BoxerFX.Wut, value);
		}
	}
	
	reg BoxerFX_bypassed = false;
	reg KarateFX_bypassed = false;
	reg xFx_bypassed = false;
	reg SumoFX_bypassed = false;
	reg SoftClip_bypassed = false;
	
	
	inline function onBypass(component, value) {
		
		for (container in Knobs_Container) {
			container.set('enabled', !value);
		}
		
		Globals.bypassed = value;
		BypassGain.setBypassed(!value);
		KO_graphics.disable(value);
		WetGain.setBypassed(value);
		DryGain.setBypassed(value);
		Mix_knb.set('enabled', !value);
		
		for (btn in FX_Selector) {
			btn.set('enabled', !value);
		}
		
		x.wtf_icon_btn.set('enabled', !value);
		Limit_Button.set('enabled', !value);
		
		Console.print('Boxer bypassed: ' + BoxerFX_bypassed);
		Console.print('Karate bypassed: ' + KarateFX_bypassed);
		Console.print('xFx bypassed: ' + xFx_bypassed);
		Console.print('SumoFX bypassed: ' + SumoFX_bypassed);
		Console.print('SoftClip bypassed: ' + SoftClip_bypassed);
		
		if (value) {
			BoxerFX_bypassed = BoxerFX.isBypassed();
			KarateFX_bypassed = KarateFX.isBypassed();
			xFx_bypassed = x.x_fx.isBypassed();
			SumoFX_bypassed = SumoFX.isBypassed();
			SoftClip_bypassed = SoftClip.isBypassed();
			
			BoxerFX.setBypassed(true);
			KarateFX.setBypassed(true);
			x.x_fx.setBypassed(true);
			SumoFX.setBypassed(true);
			SoftClip.setBypassed(true);
		} else {
			BoxerFX.setBypassed(BoxerFX_bypassed);
			KarateFX.setBypassed(KarateFX_bypassed);
			x.x_fx.setBypassed(xFx_bypassed);
			SumoFX.setBypassed(SumoFX_bypassed);
			SoftClip.setBypassed(SoftClip_bypassed);
		}
		
		OutGain.setBypassed(value);
		fx_select.changed();
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
	
	inline function goToAlgo(algo) {
		
		local seconds = UP.getSecondsSinceLastPresetLoad();
			
		if (!Globals.xLocked && seconds >= 1) {
			Header.countClicks();			
		}
		
		switch(algo) {
			case 'Boxer':
				KO_graphics.goTo('ani_1');
				Router.goToAlgoRoute('Algo1_AlgoRoute');
				BoxerFX.setBypassed(false);
				KarateFX.setBypassed(true);
				SumoFX.setBypassed(true);
				Globals.currentEffect = 'Boxer';
				FX_Selector[0].setValue(1);
				FX_Selector[1].setValue(0);
				FX_Selector[2].setValue(0);
			case 'Karate':
				KO_graphics.goTo('ani_2');
				Router.goToAlgoRoute('Algo2_AlgoRoute');
				BoxerFX.setBypassed(true);
				KarateFX.setBypassed(false);
				SumoFX.setBypassed(true);
				Globals.currentEffect = 'Karate';
				FX_Selector[0].setValue(0);
				FX_Selector[1].setValue(1);
				FX_Selector[2].setValue(0);
			case 'Sumo':
				KO_graphics.goTo('ani_3');
				Router.goToAlgoRoute('Algo3_AlgoRoute');
				BoxerFX.setBypassed(true);
				KarateFX.setBypassed(true);
				SumoFX.setBypassed(false);
				Globals.currentEffect = 'Sumo';
				FX_Selector[0].setValue(0);
				FX_Selector[1].setValue(0);
				FX_Selector[2].setValue(1);
		}
		
		KO_graphics.KO_panel.repaint();
		
		
	}
	
	inline function onFX_btn(component, value) {
		switch(component.getId()) {
			case 'FX_1_btn':
				fx_select.setValue(0);
				fx_select.changed();
			case 'FX_2_btn':
				fx_select.setValue(1);
				fx_select.changed();
			case 'FX_3_btn':
				fx_select.setValue(2);
				fx_select.changed();
		}
		KO_graphics.KO_panel.repaint();
	}
}