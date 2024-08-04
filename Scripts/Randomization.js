namespace Randomization {
	
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
			randomPreset();
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
