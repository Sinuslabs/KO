namespace Styles {
	
	const var LAF_FXSelectorBtn = Content.createLocalLookAndFeel();
	LAF_FXSelectorBtn.registerFunction('drawToggleButton', FXSelectorBtn_LAF);
	
	inline function FXSelectorBtn_LAF(g, obj) {
		
		local a = StyleHelpers.addPadding(obj.area, 3);
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
	
		g.drawEllipse(a, 1);
		
		if (obj.value) {
			g.fillEllipse(innerA);
		}
	}
	
	const var LAF_DisplayKnobSimple = Content.createLocalLookAndFeel();
	LAF_DisplayKnobSimple.registerFunction('drawRotarySlider', DisplayKnobSimple_LAF);
	
	inline function DisplayKnobSimple_LAF(g, obj) {
		
		local a = obj.area;
		
		local start = 2.5;
		local end = start * 2 * obj.valueNormalized - start;
		local text = obj.text;
		
		if (obj.hover || obj.clicked) {
			text = obj.valueAsText;
		}
		
		local ARC_THICKNESS = 6;
		local text_area = [a[0], a[3] * 0.8, a[2], a[3] * 0.2];
		
		local arcThickness = ARC_THICKNESS / 100;
		local arcWidth = (1.0 - 2.0 * arcThickness) + arcThickness;
		
		g.setColour(Theme.THEME.Colors.Display.on_display_disabled);
		local arcPath_static = Content.createPath();
				arcPath_static.addArc(
					[arcThickness / 2, arcThickness / 2,arcWidth , arcWidth],
					-start,
					2.5
				 );
				
		local pathArea = arcPath_static.getBounds(a[2]);
		pathArea = [pathArea[0], pathArea[1], pathArea[2], pathArea[3]];
		g.drawPath(arcPath_static, pathArea, a[2] * arcThickness );
		
		g.setColour(Theme.THEME.Colors.Display.on_display);
		local arcPath_value = Content.createPath();
		arcPath_value.addArc(
			[arcThickness / 2, arcThickness / 2,arcWidth , arcWidth],
			-start,
			end
		 );
		
		local pathArea2 = arcPath_value.getBounds(a[2]);
		pathArea2 = [pathArea2[0], pathArea2[1], pathArea2[2], pathArea2[3]];
		g.drawPath(arcPath_value, pathArea2, a[2] * arcThickness );
	
		g.setFont(Theme.Regular, 14);
		g.drawAlignedText(text, text_area, 'centred');
	}
	
}