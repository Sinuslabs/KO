namespace FXs {
	
	const var FX_Selector = [Content.getComponent("FX_1_btn"),
	                         Content.getComponent("FX_2_btn"),
	                         Content.getComponent("FX_3_btn")];
	                         
    const var Boxer = Synth.getEffect("Boxer");
    const var Karate = Synth.getEffect("Karate");
    const var Sumo = Synth.getEffect("Sumo");
	
	for (btn in FX_Selector) {
		btn.setLocalLookAndFeel(Styles.LAF_FXSelectorBtn);
		btn.setControlCallback(onFX_btn);
	}
	
	const var Boxer_knbs = [Content.getComponent("Boxer_Punch_knb"),
                        Content.getComponent("Boxer_Wut_knb"),
                        Content.getComponent("Boxer_Speed_knb")];

	const var Sumo_knbs = [Content.getComponent("Sumo_Heavy_knb"),
	                       Content.getComponent("Sumo_Weight_knb"),
	                       Content.getComponent("Sumo_Stomp_knb"),
	                       Content.getComponent("Sumo_Crush_knb")];
	
	
	const var Karate_knbs = [Content.getComponent("Karate_Sustain_knb"),
	                         Content.getComponent("Karate_Focus_knb"),
	                         Content.getComponent("Karate_Air_knb")];
	
	for (knb in Boxer_knbs) {
		knb.setLocalLookAndFeel(Styles.LAF_DisplayKnobSimple);
		knb.setControlCallback(onBoxerKnbs);
	}
	
	for (knb in Sumo_knbs) {
		knb.setLocalLookAndFeel(Styles.LAF_DisplayKnobSimple);
		knb.setControlCallback(onSumoKnbs);
	}
	
	for (knb in Karate_knbs) {
		knb.setLocalLookAndFeel(Styles.LAF_DisplayKnobSimple);
		knb.setControlCallback(onKarateKnbs);
	}
	
	inline function onBoxerKnbs(component, value) {
		
		switch(component.getId()) {
			case 'Boxer_Punch_knb':
				Boxer.setAttribute(Boxer.Punch, value);
			case 'Boxer_Wut_knb':
				Boxer.setAttribute(Boxer.Wut, value);
			case 'Boxer_Speed_knb':
				Boxer.setAttribute(Boxer.Speed, value);
		}
		
	}
	
	inline function onKarateKnbs(component, value) {
		
		switch(component.getId()) {
			case 'Karate_Sustain_knb':
				Karate.setAttribute(Karate.Sustain, value);
			case 'Karate_Focus_knb':
				Karate.setAttribute(Karate.Focus, value);
		}
		
	}
	
	inline function onSumoKnbs(component, value) {
		
		switch(component.getId()) {
			case 'Sumo_Heavy_knb':
				Sumo.setAttribute(Sumo.Heavy, value);
			case 'Sumo_Weight_knb':
				Sumo.setAttribute(Sumo.Weight, value);
			case 'Sumo_Stomp_knb':
				Sumo.setAttribute(Sumo.Stomp, value);
			case 'Sumo_Crush_knb':
				Sumo.setAttribute(Sumo.Crush, value);
		}
	}
	
	inline function onFX_btn(component, value) {

		KO_graphics.KO_panel.repaint();
		
		switch(component.getId()) {
			case 'FX_1_btn':
				Router.goTo('Algo1_Route');
				Boxer.setBypassed(false);
				Karate.setBypassed(true);
				Sumo.setBypassed(true);
				Globals.currentEffect = 'Boxer';
			case 'FX_2_btn':
				Router.goTo('Algo2_Route');
				Boxer.setBypassed(true);
				Karate.setBypassed(false);
				Sumo.setBypassed(true);
				Globals.currentEffect = 'Karate';
			case 'FX_3_btn':
				Router.goTo('Algo3_Route');
				Boxer.setBypassed(true);
				Karate.setBypassed(true);
				Sumo.setBypassed(false);
				Globals.currentEffect = 'Sumo';
		}
	}
}