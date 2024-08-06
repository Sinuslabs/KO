namespace About {
	
	const var LAF_logo = Content.createLocalLookAndFeel();
	
	const var incognito_btn = Content.getComponent("incognito_btn");
	const var KO_2_pnl = Content.getComponent("KO_2_pnl");
	
	const var more_btn = Content.getComponent("more_btn");
	const var social_btns = [Content.getComponent("youtube_btn"),
	                         Content.getComponent("instagram_btn"),
	                         Content.getComponent("soundcloud_btn")];
	
	const var version_pnl = Content.getComponent("version_pnl");
	
	const var company_btn = Content.getComponent("company_btn");
	
	KO_2_pnl.setPaintRoutine(KO_Routine);
	
	version_pnl.setPaintRoutine(versionRoutine);
	
	more_btn.setLocalLookAndFeel(Styles.LAF_displayButtonOutline);
	more_btn.setControlCallback(onMore);
	
	incognito_btn.setControlCallback(onIncognito);
	incognito_btn.setLocalLookAndFeel(Styles.LAF_displayIconButton);
	
	company_btn.setControlCallback(onMore);
	company_btn.setLocalLookAndFeel(LAF_logo);
	
	for (btn in social_btns) {
		btn.setLocalLookAndFeel(Styles.LAF_socials);
		btn.setControlCallback(onSocials);
	}
	
	inline function versionRoutine(g) {
		
		local a = this.getLocalBounds(1);
		local text_a = StyleHelpers.addPadding(a, 5);
		
		g.setColour(Primitives.Colors.Red['500']);
		g.setFont(Theme.SemiBold, 16);
		g.fillRoundedRectangle(a, 3);
		g.setColour(Primitives.Colors.Red['100']);
		g.drawAlignedText('V'+Engine.getVersion(), text_a, 'left');
		
	}
	
	inline function onIncognito(component, value) {
		if (!value) return;
		Engine.openWebsite('https://sinuslabs.io/eastereggs');
	}
	
	inline function onSocials(component, value) {
		
		if (!value) return;
		
		switch(component.getId()) {
			case 'youtube_btn':
				Engine.openWebsite('https://www.youtube.com/channel/UCJfRn0mxY61a5cYVBqEc9Zg');
			case 'instagram_btn':
				Engine.openWebsite('https://www.instagram.com/sinuslabs.io/');
			case 'soundcloud_btn':
				Engine.openWebsite('https://soundcloud.com/sinuslabs');
		}
	}
	
	inline function onMore(component, value) {
		
		if (!value) return;
		Engine.openWebsite('https://sinuslabs.io');
		
	}
	
	LAF_logo.registerFunction('drawToggleButton', logo_laf);
	
	inline function logo_laf(g, obj) {
		local a = obj.area;
		
		if (obj.over) {
			g.setColour(Theme.THEME.Colors.Display.on_display_var);
		} else {
			g.setColour(Theme.THEME.Colors.Display.on_display);
		}
		
		g.fillPath(Assets.get.logo, a);
	}
	
	inline function KO_Routine(g) {
		
		local a = this.getLocalBounds(2);
		
		g.setColour(Primitives.Colors.Red['500']);
		g.drawPath(Assets.get['ko'], a, 2);
		
	}
	
	
}