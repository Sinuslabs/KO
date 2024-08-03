namespace KO_graphics {
	
	const var KO_panel = Content.getComponent("KO_panel");
	
	KO_panel.setPaintRoutine(KO_Routine);	
	
	inline function KO_Routine(g) {
		
		local a = this.getLocalBounds(0);
		
		local k_area = [-13, -21, 312, 192];
		local o_area = [31, 192, 320, 112];
		
		
		if (Globals.currentEffect === 'Boxer') {
			g.setColour(Primitives.Colors.Red['500']);
		}
		
		if (Globals.currentEffect === 'Karate') {
			g.setColour(Primitives.Colors.Yellow['500']);
		}
		
		if (Globals.currentEffect === 'Sumo') {
			g.setColour(Primitives.Colors.Purple['500']);
		}
		
		g.drawPath(Assets.get['k'], k_area, 2);
		g.drawPath(Assets.get['o'], o_area, 2);
		
	}
	
}