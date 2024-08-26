namespace Styles {
	
	const var LAF_FXSelectorBtn = Content.createLocalLookAndFeel();
	LAF_FXSelectorBtn.registerFunction('drawToggleButton', FXSelectorBtn_LAF);
	
	inline function FXSelectorBtn_LAF(g, obj) {
		
		local a = StyleHelpers.addPadding(obj.area, 8);
		local innerA = StyleHelpers.addPadding(a, 3);
		
		if (obj.text === 'FX_1_btn') {
			g.setColour(Primitives.Colors.Red['500']);
		}
		
		if (obj.text === 'FX_2_btn') {
			g.setColour(Primitives.Colors.Yellow['500']);
		}
		
		if (obj.text === 'FX_3_btn') {
			g.setColour(Primitives.Colors.Purple['500']);
		}
		
		if (obj.text === 'bypass') {
			g.setColour(Theme.THEME.Colors.Display.on_display_disabled);
		}
		
		if (!obj.enabled) {
			g.setColour(Theme.THEME.Colors.Display.on_display_disabled);

		}
		
		g.drawEllipse(a, 2);
		
		if (obj.value) {
			if (obj.text === 'bypass') {
				g.setColour(Primitives.Colors.Red['500']);
			}
			g.fillEllipse(innerA);
		}
	}
	
	const LAF_displayIconButton = Content.createLocalLookAndFeel();
	LAF_displayIconButton.registerFunction("drawToggleButton", displayIconButtonLAF);
	inline function displayIconButtonLAF(g, obj) {
		local a = obj.area;
		local iconArea = StyleHelpers.addPadding(a, 0);
		local SIZE = 15;
		
		local width = a[2];
		local height = a[3];
		
		iconArea = StyleHelpers.withSizeKeepingCentre(a, SIZE, SIZE);
		g.setColour(Theme.THEME.Colors.Display.on_display_var);
		
		obj.over && g.setColour(Theme.THEME.Colors.Display.on_display);
		obj.value && g.setColour(Theme.THEME.Colors.Display.on_display);
		
		
		if (!obj.enabled) {
			g.setColour(Theme.THEME.Colors.Display.on_display_disabled);
		}
		
		if (obj.text.contains('$outline')) {
			obj.text = obj.text.replace('$outline', '');
			g.drawPath(Assets.get[obj.text], [iconArea[0], iconArea[1], SIZE, SIZE], 0.5);								
		} else {
			g.fillPath(Assets.get[obj.text], [iconArea[0], iconArea[1], SIZE, SIZE]);
		}
	}
	
	const var LAF_DisplayKnobSimple = Content.createLocalLookAndFeel();
	LAF_DisplayKnobSimple.registerFunction('drawRotarySlider', DisplayKnobSimple_LAF);
	
	inline function DisplayKnobSimple_LAF(g, obj) {
		
		local a = obj.area;
		
		a = StyleHelpers.addPadding(a, 0);
		
		local start = 2.5;
		local end = start * 2 * obj.valueNormalized - start;
		local text = obj.text;
		
		if ((obj.hover || obj.clicked) && obj.enabled) {
			text = obj.valueAsText;
		}
		
		local ARC_THICKNESS = 6;
		local text_area = [a[0], a[3] * 0.8, a[2], a[3] * 0.2];
		
		local arcThickness = ARC_THICKNESS / 100;
		local arcThickness_base = ARC_THICKNESS / 100;
		local arcThickness_hover = ARC_THICKNESS / 100;
		local arcWidth = (1.0 - 2.0 * arcThickness) + arcThickness;
		local arcWidth_base = (1.0 - 2.0 * arcThickness_base) + arcThickness_base;
		
		g.setColour(Theme.THEME.Colors.UI.on_background_var);
		local arcPath_static = Content.createPath();
				arcPath_static.addArc(
					[arcThickness_base / 2, arcThickness_base / 2,arcWidth_base , arcWidth_base],
					-start,
					2.5
				 );
				
		local pathArea = arcPath_static.getBounds(a[2]);
		pathArea = [pathArea[0], pathArea[1], pathArea[2], pathArea[3]];
		g.drawPath(arcPath_static, pathArea, a[2] * arcThickness );
		
		local arcPath_value = Content.createPath();
		arcPath_value.addArc(
			[arcThickness / 2, arcThickness / 2,arcWidth , arcWidth],
			-start,
			end
		 );
		 
		 
 		g.setColour(Theme.THEME.Colors.Display.on_display);
 		
 		
 		if (obj.hover || obj.clicked) {
 			g.setColour(Theme.THEME.Colors.Display.on_display);
 		}
 		
 		if (!obj.enabled) {
	 		g.setColour(Theme.THEME.Colors.Display.on_display_disabled);
 		}
		
		local pathArea2 = arcPath_value.getBounds(a[2]);
		pathArea2 = [pathArea2[0], pathArea2[1], pathArea2[2], pathArea2[3]];
		g.drawPath(arcPath_value, pathArea2, a[2] * arcThickness );
		
		if (!obj.enabled) {
			 		g.setColour(Theme.THEME.Colors.Display.on_display_disabled);
		}
		
		g.setFont(Theme.Regular, 18);
		g.drawAlignedText(text.toUpperCase(), text_area, 'centred');
	}
	
	const var LAF_LimitBtn = Content.createLocalLookAndFeel();
	LAF_LimitBtn.registerFunction('drawToggleButton', LimitBtn_LAF);
	
	inline function LimitBtn_LAF(g, obj) {
		
		local a = obj.area;
		
		local dotArea = [a[2] - 15, a[3] / 2 - 2.5, 5, 5];
		
		if (!obj.value) {
			g.setColour(Primitives.Colors.Yellow['500']);
		} else {
			g.setColour(Theme.THEME.Colors.Display.on_display_disabled);
		}
		
		if (!obj.enabled) {
			g.setColour(Theme.THEME.Colors.Display.on_display_disabled);
		}
		
		if (obj.over) {
			g.setColour(Primitives.Colors.Yellow['200']);
		}
		
		if (obj.over && !obj.value) {
			g.setColour(Primitives.Colors.Yellow['500']);
		}
		
		g.setFont(Theme.Regular, 16);
		g.drawAlignedText('CLIP', a, 'left');
		
		g.fillEllipse(dotArea);
		
	}
	
	const LAF_displayButtonLogic = Content.createLocalLookAndFeel();
	LAF_displayButtonLogic.registerFunction('drawToggleButton', displayButtonLogic_LAF);
	
	inline function displayButtonLogic_LAF(g, obj) {
		
		local a = obj.area;
		local paddedA = StyleHelpers.addPadding(a, 5);
		local textA = StyleHelpers.addPadding(paddedA, 9);
		local BORDER_RADIUS = 2;
		
		if (obj.enabled) {
			g.setColour(Theme.THEME.Colors.Display.on_display);
		} else {
			g.setColour(Theme.THEME.Colors.Display.on_display_disabled);
		}
		
		if (obj.over) {
			g.setColour(Theme.THEME.Colors.Display.on_display_var);
		}
		
		g.drawRoundedRectangle(paddedA, BORDER_RADIUS, 1);
		
		if (obj.value) {
			g.setColour(Theme.THEME.Colors.Display.on_display_var);
			g.fillRoundedRectangle(paddedA, BORDER_RADIUS);
			g.setColour(Theme.THEME.Colors.Display.on_display_contrast);
		}
		
		g.setFont(Theme.Regular, 18);
		g.drawAlignedText(obj.text, textA, 'centred');
	}
	
	
	const LAF_displayButtonOutline = Content.createLocalLookAndFeel();
	LAF_displayButtonOutline.registerFunction('drawToggleButton', displayButtonOutlineLAF);
	
	inline function displayButtonOutlineLAF(g, obj) {
		
		local a = obj.area;
		local paddedA = StyleHelpers.addPadding(a, 1);
		local textA = StyleHelpers.addPadding(paddedA, 9);
		local BORDER_RADIUS = 2;
		
		if (obj.enabled) {
			g.setColour(Theme.THEME.Colors.Display.on_display);
		} else {
			g.setColour(Theme.THEME.Colors.Display.on_display_var);
		}
		
		if (obj.over) {
			g.setColour(Theme.THEME.Colors.Display.on_display_var);
		}
		
		g.drawRoundedRectangle(paddedA, BORDER_RADIUS, 1);
		
		if (obj.value) {
			g.setColour(Theme.THEME.Colors.Display.on_display_var);
			g.fillRoundedRectangle(paddedA, BORDER_RADIUS);
			g.setColour(Theme.THEME.Colors.Display.on_display_contrast);
		}
		
		g.setFont(Theme.Regular, 18);
		g.drawAlignedText(obj.text, textA, 'centred');
	}
	
	const LAF_displayButtonFill = Content.createLocalLookAndFeel();
	LAF_displayButtonFill.registerFunction('drawToggleButton', displayButtonFillLAF);
	
	inline function displayButtonFillLAF(g, obj) {
		
		local a = obj.area;
		local paddedA = StyleHelpers.addPadding(a, 1);
		local textA = StyleHelpers.addPadding(paddedA, 9);
		local BORDER_RADIUS = 2;
		
		if (obj.enabled) {
			g.setColour(Theme.THEME.Colors.Display.on_display);
		} else {
			g.setColour(Theme.THEME.Colors.Display.on_display_var);
		}
		
		if (obj.over) {
			g.setColour(Theme.THEME.Colors.Display.on_display_var);
		}
		
		g.fillRoundedRectangle(paddedA, BORDER_RADIUS);
		g.setColour(Theme.THEME.Colors.Display.on_display_contrast);
		
		if (obj.value) {
			g.setColour(Theme.THEME.Colors.Display.on_display);
			g.fillRoundedRectangle(paddedA, BORDER_RADIUS);
			g.setColour(Theme.THEME.Colors.Display.on_display_contrast);
		}
		
		g.setFont(Theme.Regular, 18);
		g.drawAlignedText(obj.text, textA, 'centred');
	}
	
	const LAF_wtfBtn = Content.createLocalLookAndFeel();
	LAF_wtfBtn.registerFunction("drawToggleButton", wtfLAF);
	inline function wtfLAF(g, obj) {
		
		local a = [
			9,
			8,
			15,
			18
		];
		
		local SIZE = 18;
		
		local width = a[2];
		local height = a[3];
		
		g.setColour(Theme.THEME.Colors.Display.on_display_var);
		
		obj.over && g.setColour(Theme.THEME.Colors.Display.on_display);
		
		if (!obj.value && obj.enabled) {
			g.fillPath(Assets.get['wtf_selected'], a);
		} else {
			g.fillPath(Assets.get['wtf_outline'], a);
		}
	}
	
	const LAF_socials = Content.createLocalLookAndFeel();
	LAF_socials.registerFunction("drawToggleButton", socialsLAF);
	inline function socialsLAF(g, obj) {
		local a = obj.area;
		local iconArea = StyleHelpers.addPadding(a, 0);
		local SIZE = 18;
		
		local width = a[2];
		local height = a[3];
		
		
		iconArea = StyleHelpers.withSizeKeepingCentre(a, 18, 18);
		if (obj.text === 'youtube') {
			iconArea = StyleHelpers.withSizeKeepingCentre(a, 22, 16);
		}
		
		if (obj.text === 'instagram') {
			iconArea = StyleHelpers.withSizeKeepingCentre(a, 18, 18);
		}
		
		if (obj.text === 'soundcloud') {
			iconArea = StyleHelpers.withSizeKeepingCentre(a, 25, 15);
		}
		
		
		
		g.setColour(Theme.THEME.Colors.Display.on_display);
		
		obj.over && g.setColour(Theme.THEME.Colors.Display.on_display_var);
		
		g.fillPath(Assets.get[obj.text], iconArea);
	}
	
	const var LAF_Mix = Content.createLocalLookAndFeel();
	LAF_Mix.registerFunction('drawRotarySlider', Mix_LAF);
	
	inline function Mix_LAF(g, obj) {
		
		local a = obj.area;
		local GAP = 5;
		local BAR_HEIGHT = 7;
		
		local upperA = [0, 0, a[2], BAR_HEIGHT];
		local lowerA = [0, a[3] / 2 + GAP, a[2], a[3] / 2 - GAP];
		local text = obj.text;
		
		if (obj.hover || obj.clicked) {
			text = obj.valueAsText;
		}

		local statusBarArea = [upperA[0], upperA[1], upperA[2] * obj.value, upperA[3]];
		
		g.setColour(Theme.THEME.Colors.Display.on_display_disabled);
		if (!obj.enabled) {
			g.setColour(Theme.THEME.Colors.Display.on_display_disabled);
		} 
		
		if (!obj.enabled) {
			g.setColour(Theme.THEME.Colors.Display.on_display_disabled);
		}
		
		
		g.setColour(Theme.THEME.Colors.UI.on_background_var);
		g.fillRoundedRectangle(upperA, 2);
		g.setColour(Theme.THEME.Colors.Display.on_display);
		
		if (!obj.enabled) {
			g.setColour(Theme.THEME.Colors.Display.on_display_disabled);
		}
		
		g.fillRoundedRectangle(statusBarArea, 2);
		
		
		if (obj.hover || obj.clicked) {
			g.setColour(Theme.THEME.Colors.Display.on_display);
		}
		
		if (!obj.enabled) {
			g.setColour(Theme.THEME.Colors.Display.on_display_disabled);
		}
		
		g.setFont(Theme.Regular, 14);
		g.drawAlignedText(text.toUpperCase(), lowerA, 'centred');
		
	}
	
}