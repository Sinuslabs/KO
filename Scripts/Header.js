namespace Header {
	
	const var Update_btn = Content.getComponent("Update_btn");
	Update_btn.setControlCallback(onUpdateBtn);
	Update_btn.setLocalLookAndFeel(Styles.LAF_displayIconButton);
	
	const var About_btn = Content.getComponent("About_btn");
	
	const var update_now_btn = Content.getComponent("update_now_btn");
	
	update_now_btn.setLocalLookAndFeel(Styles.LAF_displayButtonOutline);
	update_now_btn.setControlCallback(onUpdateNow);
	update_now_btn.set('visible', false);
	
	inline function onUpdateNow(component, value) {		
		if (value) {		
			switch(Globals.OS) {
				case 'WIN':
					Engine.openWebsite(INFO.repository + INFO.latest_release_windows);
					break;
				case 'OSX':
					Engine.openWebsite(INFO.repository + INFO.latest_release_macos);
					break;
				case 'LINUX':
					Engine.openWebsite(INFO.repository + INFO.latest_release_linux);
					break;
			}	
		}		
	}
	
	About_btn.setControlCallback(onAbout);
	About_btn.setLocalLookAndFeel(Styles.LAF_displayIconButton);
	
	Update_btn.showControl(false);
	
	reg clickCounter = 0;
	const var clickThreshold = 15; // Number of clicks required to trigger custom function
	const var decreaseInterval = 200;
	const var decraseClick = 0.5;
	
	const var easteregg_timer = Engine.createTimerObject();
	easteregg_timer.setTimerCallback(onEastereggTimer);
	
	inline function countClicks() {
		clickCounter++;
		if (!easteregg_timer.isTimerRunning()) {
				easteregg_timer.startTimer(decreaseInterval);
		}
	}
	
	inline function formatHeader() {
		
		local Activation_x = 480;
		local Limit_x = 615;
		
		if (Globals.x) {
			Activation_x = Activation_x - 40;
			Limit_x = Limit_x - 40;
		}
		
		if (Globals.canUpdate) {
			Activation_x = Activation_x - 45;
		}
		
		FXs.Limit_Button.set('x', Limit_x);
		Activation.not_activated_btn.set('x', Activation_x);
		
	}
	
	inline function onEastereggTimer() {
		clickCounter = clickCounter - decraseClick;
	
		if (clickCounter <= 0) easteregg_timer.stopTimer();
		if (clickCounter >= clickThreshold) {
			Router.goTo('x');
			//ConfettiAnimation.burstAnimation();			
			easteregg_timer.stopTimer();
			clickCounter = 0;
		}
	}
	
	inline function onAbout(component, value) {
		if (value) {
			Router.goTo('About');
		} else {
			Router.goTo('Main');
		}
	
	}
	
	inline function onUpdateBtn(component, value) {
		Router.goTo('About');
	}
	
}