namespace Panic {
	
	const PanicTimeoutTimer = Engine.createTimerObject();
	PanicTimeoutTimer.setTimerCallback(onTimeout);
	
	const PanicKnbsTimer = Engine.createTimerObject();
	PanicKnbsTimer.setTimerCallback(randomKnbs);
	
	const var all = Content.getAllComponents('knb');
	
		// Variable to store the last drawn number
	reg lastNumber = -1;
	
	// Inline function to get a random number between 1 and 3 that is not the same as the last drawn number
	inline function getRandomNumber()
	{
	    local newNumber;
	    for (i = 0; i < 3; i++)
	    {
	        newNumber = Math.floor(Math.random() * 3) + 1; // Generate a number between 1 and 3
	        if (newNumber != lastNumber)
	        {
	            lastNumber = newNumber; // Update lastNumber with the new number
	            return newNumber;
	        }
	    }
	    
	    // Fallback in case the loop doesn't find a new number, though this is highly unlikely
	    newNumber = (lastNumber % 3) + 1;
	    lastNumber = newNumber;
	    return newNumber;
	}
	
	reg counter = 0;
	reg anomaly = false;
	
	inline function onTimeout() {
		
		local idx = Math.round(getRandomNumber()) - 1;
		
		FXs.FX_Selector[idx].setValue(1);
		FXs.FX_Selector[idx].changed();
		
		counter = counter + 1;
		
		if (counter > 8 && anomaly) {
			FXs.FX_Selector[idx].setValue(1);
			FXs.FX_Selector[idx].changed();
			FXs.FX_Selector[idx].setValue(1);
			FXs.FX_Selector[idx].changed();
			FXs.FX_Selector[idx].setValue(1);
			FXs.FX_Selector[idx].changed();
			FXs.FX_Selector[idx].setValue(1);
			FXs.FX_Selector[idx].changed();
			FXs.FX_Selector[idx].setValue(1);
			FXs.FX_Selector[idx].changed();
		}
		
	}
	
	inline function randomKnbs() {
		for (knb in all) {
			
			knb.setValue(Math.random());
			
		}
	}
	
	inline function panic() {
		PanicTimeoutTimer.startTimer(1500);
		PanicKnbsTimer.startTimer(200);
	}
	

}