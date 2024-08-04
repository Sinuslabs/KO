namespace Header {
	
	reg clickCounter = 0;
	const var clickThreshold = 4; // Number of clicks required to trigger custom function
	const var decreaseInterval = 100;
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
	
}