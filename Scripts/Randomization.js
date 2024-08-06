namespace Randomization {
	
	const var Boxer_knbs = [Content.getComponent("Boxer_Wut_knb"),
	                        Content.getComponent("Boxer_Punch_knb")];
	
	const var FX_selectors = [Content.getComponent("FX_1_btn"),
	                          Content.getComponent("FX_2_btn"),
	                          Content.getComponent("FX_3_btn")];
	
	const var Karate_knbs = [Content.getComponent("Karate_Pressure_knb"),
	                        Content.getComponent("Karate_Focus_knb"),
	                        Content.getComponent("Karate_Air_knb"),
	                        Content.getComponent("Karate_Speed_knb")];
	
	const var Sumo_knbs = [Content.getComponent("Sumo_Stomp_knb"),
	                       Content.getComponent("Sumo_Crush_knb"),
	                       Content.getComponent("Sumo_Weight_knb"),
	                       Content.getComponent("Sumo_Heavy_knb")];
	
	const var randomPanelButton = Content.getComponent("randomize_pnl_btn");
	
	randomPanelButton.setPaintRoutine(randomPanelRoutine);
	randomPanelButton.setMouseCallback(onRandomPanel);
	
	reg p = {'hover': false, 'clicked': false};
	reg ellipseData = []; // Store ellipse data
	
	calculateEllipses();
	randomPanelButton.repaint();
	
	inline function onRandomPanel(event) {
		
		p = {
			'hover': event.hover,
			'clicked': event.clicked && !event.mouseUp
		};
	
		this.setValue(p);
	
		if (event.rightClick && event.result) {
			Router.goTo('PresetBrowser');
		}
		
		if (p.clicked) {
			//randomPreset();
			randomizeAllKnobs();
			calculateEllipses(); // Calculate ellipses on click
		}
		
		randomPanelButton.repaint();
	}
	
	inline function randomPreset() {
		
		Engine.loadNextUserPreset(true);
		Engine.performUndoAction(
			{},
			function(isUndo) {
				if (isUndo) Engine.loadPreviousUserPreset(true);
			});
		
	}
	
	inline function randomizeAllKnobs() {
		
		local idx = getRandomInt(3);
		FX_selectors[idx].setValue(1);
		FX_selectors[idx].changed();
		
		
		if (idx == 0) {
			randomizeKnobs(Boxer_knbs);
		}
		
		if (idx == 1) {
			randomizeKnobs(Karate_knbs);
		}
		
		if (idx == 2) {
			randomizeKnobs(Sumo_knbs);
		}
		
	}
	
	inline function randomizeKnobs(knobs) {
	    for (knob in knobs) {
	        local u = Math.random();
	        local v = Math.random();
	        local randomValue = (u + v) / 2; // Triangular distribution
	        knob.setValueNormalized(randomValue);
	        knob.changed();
	    }
	}
	
	inline function getRandomInt(upperBound) {
		return parseInt(Math.floor(Math.random() * upperBound));
	}
	
	inline function calculateEllipses() {
	    local a = randomPanelButton.getLocalBounds(0);
	    ellipseData.clear();
	    
	    local padding = 8;
	
	    local width = a[2] - 2 * padding;
	    local height = a[3] - 2 * padding;
	
	    local cellWidth = width / 3;
	    local cellHeight = height / 3;
	
	    local smallSize = Math.min(cellWidth, cellHeight) * 0.4; // 50% of the smallest dimension of the cell
	    local bigSize = Math.min(cellWidth, cellHeight) * 0.6; // 80% of the smallest dimension of the cell
	
	    for(i = 0; i < 3; i++) {
	        for(j = 0; j < 3; j++) {
	            local centerX = padding + (j + 0.5) * cellWidth;
	            local centerY = padding + (i + 0.5) * cellHeight;
	
	            local ellipseSize = Math.randInt(0, 2) == 0 ? smallSize : bigSize;
	            ellipseData.push({'centerX': centerX, 'centerY': centerY, 'size': ellipseSize});
	        }
	    }
	}
	
	inline function randomPanelRoutine(g) {
	    local a = this.getLocalBounds(0);
	    local data = this.getValue();
	    
		if (!data.hover) {
		    g.setColour(Theme.THEME.Colors.Display.on_display_var);
		} else {
			g.setColour(Theme.THEME.Colors.Display.on_display);
		}
		
		
	    for(i = 0; i < ellipseData.length; i++) {
	        local centerX = ellipseData[i].centerX;
	        local centerY = ellipseData[i].centerY;
	        local size = ellipseData[i].size;
	        
	        g.fillEllipse([
	            centerX - size / 2, 
	            centerY - size / 2, 
	            size, 
	            size
	        ]);
	    }
	}
}
