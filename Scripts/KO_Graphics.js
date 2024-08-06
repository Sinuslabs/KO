namespace KO_graphics {
	
	const var KO_panel = Content.getComponent("KO_panel");
	
	const animation = Animations.kokook;
	
	reg frame = 27;
	const startFrame = 20;
	const frames = 83;
	const speed = 1;
	const timer = 20;
	
	reg frame_stop = 0;
	reg reverse = false;
	
	const animations = ["KO_1", "KO_2", "KO_3"];
	reg currentAnimation = "KO_1";
	
	KO_panel.setAnimation(animation);
	KO_panel.setAnimationFrame(startFrame);
	KO_panel.setTimerCallback(nextFrame);
	
	inline function goTo(ani) {
		if (currentAnimation == 'KO_1') {
			if (ani == 'KO_1') {return;}
			if (ani == 'KO_2') {
				frame = 9;
				reverse = false;
				frame_stop = 27;
			}
			
			if (ani == 'KO_3') {
				frame = 79;
				reverse = true;
				frame_stop = 54;
			}
			currentAnimation = ani;
			KO_panel.startTimer(timer);
			return;
		}
		
		if (currentAnimation == 'KO_2') {
			if (ani == 'KO_1') {
				frame = 27;
				reverse = true;
				frame_stop = 5;
			}
			if (ani == 'KO_2') {return;}
			if (ani == 'KO_3') {
				frame = 33;
				reverse = false;
				frame_stop = 54;
			}
			currentAnimation = ani;
			KO_panel.startTimer(timer);
			return;
		}
		
		if (currentAnimation == 'KO_3') {
			if (ani == 'KO_1') {
				frame = 54;
				reverse = false;
				frame_stop = 79;
			}
			if (ani == 'KO_2') {
				frame = 54;
				reverse = true;
				frame_stop = 27;
			}
			if (ani == 'KO_3') { return;}
			currentAnimation = 'KO_1';
			KO_panel.startTimer(timer);
			return;
		}
	}
	
	inline function initAni() {
		Console.print('lets go');
	
		frame = startFrame;
		reverse = true;
		frame_stop = 5;
		KO_panel.startTimer(timer);
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