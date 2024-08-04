namespace VuMeterSlider {
	
	
	const LAF_VU_Slider = Content.createLocalLookAndFeel();
	const var GainSlider = Content.getComponent("GainSlider");
	
	GainSlider.setLocalLookAndFeel(LAF_VU_Slider);
	GainSlider.setControlCallback(onOutGain);
	
	LAF_VU_Slider.registerFunction('drawRotarySlider', VU_Slider_LAF);
	inline function VU_Slider_LAF(g, obj) {
		local a = obj.area;
		
		local sliderA = [
			a[0],
			a[1],
			a[2],
			a[3] - 30
		];
		
		local DOT_SIZE = 7;
		local thickness = 1;
		
		local SLIDER_HEIGHT = 1;
		local LINE_THICKNESS = 2;
		local DOT_MAX_TRAVEL = 0.96;
		local DOT_RADIUS = 8;
		local LABEL_BOTTOM_PADDING = 12;
		local value = obj.valueNormalized;
	
		if (obj.hover) {
			DOT_SIZE = 9;
		}
		
		local x = sliderA[2] / 2 - DOT_SIZE / 2;
		local y = sliderA[3] * DOT_MAX_TRAVEL * (1 - value);
		local tri_area = [x, y, DOT_SIZE, DOT_SIZE];
		
		local bottomPadding_a = [a[0], a[1], a[2], a[3] - LABEL_BOTTOM_PADDING];
		obj.enabled ?
			g.setColour(Theme.THEME.Colors.Display.on_display)
			: Theme.THEME.Colors.Display.on_display_disabled;
	
		if (obj.hover) {
			g.setColour(Theme.THEME.Colors.Display.on_display);
		}
	
		g.fillEllipse(tri_area);
		g.setColour(Colours.black);
		g.drawEllipse(tri_area, 1);
	
		if (obj.hover || obj.clicked) {
			g.setColour(Theme.THEME.Colors.Display.on_display);
	
			g.setFont(Theme.SemiBold, 16);
			g.drawAlignedText(obj.valueAsText.replace(' dB', ''), bottomPadding_a, 'centredBottom');
			g.setFont(Theme.Regular, 14);
			g.drawAlignedText(obj.suffix, a, 'centredBottom');
		}
	}
	
	inline function onOutGain(component, value) {
		
		
		OutGain.setAttribute(OutGain.Gain, value);
		
	}

	const locl_laf = Content.createLocalLookAndFeel();
	
	locl_laf.registerFunction("drawRotarySlider", function (g, obj) {

		var a = obj.area;
		var bottomTextmargin = 0;
		var thickness = 2;
		var vertpos = obj.valueNormalized;
		
		// Vertical Line Level Meter Fill
		if (obj.text == "PeakMeterVertFill") {
			g.setColour(Theme.THEME.Colors.Display.on_display_var);
			g.fillRoundedRectangle([0, a[3] * (1 - obj.valueNormalized), a[2], a[3] - a[3] * (1 - obj.valueNormalized)], Primitives.BorderRadius.sm);
		}

		// Vertical Line Level Meter Pointer
		else if (obj.text == "PeakMeterVertPointer") {

			g.setColour(Theme.THEME.Colors.Display.on_display_var);
			g.fillRoundedRectangle([0, a[3] - thickness - (a[3] - thickness) * vertpos, a[2], thickness], Primitives.BorderRadius.xs);
		}
	});

	const var OutputPeakMeter = Content.getComponent("OutputPeakMeterFillL");
	const var OutputPeakPoint = Content.getComponent("OutputPeakMeterPointL");

	OutputPeakMeter.setLocalLookAndFeel(locl_laf);
	OutputPeakPoint.setLocalLookAndFeel(locl_laf);

	// Define decay and attack rates
	const var DECAY_RATE_Fill = 0.82; // Adjust these values as needed
	const var ATTACK_RATE_Fill = 0.2; // Adjust these values as needed
	const var DECAY_RATE_Pointer = 0.9; // Adjust these values as needed
	const var ATTACK_RATE_Pointer = 0.4; // Adjust these values as needed

	//Current Values
	var out_curLevelLM_Fill = 0.0;
	var out_curLevelLM_Pointer = 0.0;

	// Timer Callback
	const var t1 = Engine.createTimerObject();

	t1.setTimerCallback(function () {
		
		var Output_LevelLM_Fill = (OutGain.getCurrentLevel(0) + OutGain.getCurrentLevel(1)) / 2;
		var Output_LevelLM_Pointer = (OutGain.getCurrentLevel(0) + OutGain.getCurrentLevel(1)) / 2;

		// Apply different smoothing based on whether the level is rising or falling
		out_curLevelLM_Fill = out_curLevelLM_Fill > Output_LevelLM_Fill ?
			Math.max(Output_LevelLM_Fill, out_curLevelLM_Fill * DECAY_RATE_Fill) :
			(out_curLevelLM_Fill * (1 - ATTACK_RATE_Fill) + Output_LevelLM_Fill * ATTACK_RATE_Fill);

		out_curLevelLM_Pointer = out_curLevelLM_Pointer > Output_LevelLM_Pointer ?
			Math.max(Output_LevelLM_Pointer, out_curLevelLM_Pointer * DECAY_RATE_Pointer) :
			(out_curLevelLM_Pointer * (1 - ATTACK_RATE_Pointer) + Output_LevelLM_Pointer * ATTACK_RATE_Pointer);

		// Decibel Conversion     
		Output_LevelLM_Fill = Engine.getDecibelsForGainFactor(out_curLevelLM_Fill);
		Output_LevelLM_Pointer = Engine.getDecibelsForGainFactor(out_curLevelLM_Pointer);

		// Set Values  
		OutputPeakMeter.setValue(Output_LevelLM_Fill);
		OutputPeakPoint.setValue(Output_LevelLM_Pointer);
	});

	t1.startTimer(20);
}