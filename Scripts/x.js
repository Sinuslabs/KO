namespace x {
	
	const animation = Animations.glitch;
	
	const var x_fx = Synth.getEffect("x");

	const var AnimationPanel = Content.getComponent("glitch_pnl");
	const var wtf_btn = Content.getComponent("wtf_btn");
	const var x_code_pnl = Content.getComponent("x_code_pnl");
	
	const var wtf_icon_btn = Content.getComponent("wtf_icon_btn");
	
	x_code_pnl.setPaintRoutine(code_routine);
	
	wtf_icon_btn.setLocalLookAndFeel(Styles.LAF_wtfBtn);
	wtf_icon_btn.setControlCallback(onWtfIcon);
	
	wtf_btn.setControlCallback(on_wtf);
	wtf_btn.setLocalLookAndFeel(Styles.LAF_displayButtonOutline);
	
	wtf_icon_btn.set('visible', false);
	
	inline function code_routine(g) {
		
		local a = this.getLocalBounds(0);
		
		g.setColour(Theme.THEME.Colors.Display.on_display_var);
		g.fillPath(Assets.get['code'], a);
	}
	
	
	inline function onWtfIcon(component, value) {
		
		x_fx.setBypassed(value);
		
	}
	
	inline function on_wtf(component, value) {
		if (!value) return;
		
		Router.goTo('Main');
		UserSettings.save('wtf', true);
		wtf_icon_btn.set('visible', true);
		
	} 
	
	reg frame = 0;
	const frames = 60;
	const speed = 1;
	const timer = 30;
	reg frame_stop = 15;
	
	AnimationPanel.setAnimation(animation);
	AnimationPanel.setTimerCallback(nextFrame);
	AnimationPanel.startTimer(timer);
	
	inline function nextFrame() {	
		AnimationPanel.setAnimationFrame(frame);
		frame += speed;
		if (frame >= frames) frame = 0;
	}
	
}