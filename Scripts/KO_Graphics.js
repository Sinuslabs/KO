namespace KO_graphics {
	
	const var KO_panel = Content.getComponent("KO_panel");
	
    const animation = Animations.kokook_new;
    const speed = 1;
    const timer = 20;

    reg frame = 0;
    reg reverse = false;
    reg frame_stop = 0;
    reg currentAnimation = "init";
    
    const animations = {
        "init": {"start": 0, "end": 10},
        "ani_1_ani_2": {"start": 10, "end": 30},
        "ani_2_disable": {"start": 30, "end": 39},
        "ani_2_ani_3": {"start": 40, "end": 60},
        "ani_3_disable": {"start": 60, "end": 69},
        "ani_3_ani_1": {"start": 70, "end": 90},
        "ani_1_disable": {"start": 90, "end": 99}
    };
    
	KO_panel.setAnimation(animation);
	KO_panel.setTimerCallback(nextFrame);
	
	const var KO_clicker = Content.getComponent("KO_clicker");
	
	const var LAF_Empty = Content.createLocalLookAndFeel();
	LAF_Empty.registerFunction('drawToggleButton', function(g, obj){});
	
	KO_clicker.setControlCallback(onKO);
	KO_clicker.setLocalLookAndFeel(LAF_Empty);
	
	init();
	
	inline function onKO(component, value) {
		
		if (!value) return;
		
		Console.print(Globals.currentEffect);
		
		if (Globals.currentEffect === 'Boxer') {
			FXs.FX_Selector[1].setValue(1);
			FXs.FX_Selector[1].changed();
			return;
		}
		
		if (Globals.currentEffect === 'Karate') {
			FXs.FX_Selector[2].setValue(1);
			FXs.FX_Selector[2].changed();
			return;
		}
		
		if (Globals.currentEffect === 'Sumo') {
			FXs.FX_Selector[0].setValue(1);
			FXs.FX_Selector[0].changed();
			return;
		}
		
	}

	inline function setAnimationFrames(start, end, rev) {
	    frame = start;
	    frame_stop = end;
	    reverse = rev;
	    KO_panel.startTimer(timer);
	}
	
	inline function init() {
	    currentAnimation = "init";
	    setAnimationFrames(animations["init"].start, animations["init"].end, false);
	}
	
	inline function disable(isDisabled) {
	    if (currentAnimation == "ani_2") {
	        if (isDisabled) {
	            setAnimationFrames(animations["ani_2_disable"].start, animations["ani_2_disable"].end, false);
	        } else {
	            setAnimationFrames(animations["ani_2_disable"].end, animations["ani_2_disable"].start, true);
	        }
	    } else if (currentAnimation == "ani_3") {
	        if (isDisabled) {
	            setAnimationFrames(animations["ani_3_disable"].start, animations["ani_3_disable"].end, false);
	        } else {
	            setAnimationFrames(animations["ani_3_disable"].end, animations["ani_3_disable"].start, true);
	        }
	    } else if (currentAnimation == "ani_1") {
	        if (isDisabled) {
	            setAnimationFrames(animations["ani_1_disable"].start, animations["ani_1_disable"].end, false);
	        } else {
	            setAnimationFrames(animations["ani_1_disable"].end, animations["ani_1_disable"].start, true);
	        }
	    }
	}
	
    inline function goTo(ani) {
        if (currentAnimation == "ani_1" && ani == "ani_2") {
            setAnimationFrames(animations["ani_1_ani_2"].start, animations["ani_1_ani_2"].end, false);
        } else if (currentAnimation == "ani_2" && ani == "ani_3") {
            setAnimationFrames(animations["ani_2_ani_3"].start, animations["ani_2_ani_3"].end, false);
        } else if (currentAnimation == "ani_3" && ani == "ani_1") {
            setAnimationFrames(animations["ani_3_ani_1"].start, animations["ani_3_ani_1"].end, false);
        } else if (currentAnimation == "ani_2" && ani == "ani_1") {
            setAnimationFrames(animations["ani_1_ani_2"].end, animations["ani_1_ani_2"].start, true);
        } else if (currentAnimation == "ani_3" && ani == "ani_2") {
            setAnimationFrames(animations["ani_2_ani_3"].end, animations["ani_2_ani_3"].start, true);
        } else if (currentAnimation == "ani_1" && ani == "ani_3") {
            setAnimationFrames(animations["ani_3_ani_1"].end, animations["ani_3_ani_1"].start, true);
        }
        
        currentAnimation = ani;
    }
	
	inline function nextFrame() {	
		KO_panel.setAnimationFrame(frame);
		
		if (reverse) {
			frame -= speed;
		} else {
			frame += speed;
		}
		if ((reverse && frame <= frame_stop) || (!reverse && frame >= frame_stop)) {
			KO_panel.stopTimer();
		}
	}
	
}