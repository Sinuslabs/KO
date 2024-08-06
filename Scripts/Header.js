namespace Header {
	
	const var Update_btn = Content.getComponent("Update_btn");
	Update_btn.setControlCallback(onUpdateBtn);
	Update_btn.setLocalLookAndFeel(Styles.LAF_displayIconButton);
	
	const var About_btn = Content.getComponent("About_btn");
	
	const var update_now_btn = Content.getComponent("update_now_btn");
	
	update_now_btn.setLocalLookAndFeel(Styles.LAF_displayButtonOutline);
	update_now_btn.setControlCallback(onUpdateNow);
	
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
	const var clickThreshold = 4; // Number of clicks required to trigger custom function
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