namespace UserSettings {
	
	reg settingsObj = {
		'wtf': 0,
		'zoom': 1
	};
	
	const settingsDir = FileSystem.getFolder(FileSystem.UserPresets).getParentDirectory();
	const settingsFile = settingsDir.getChildFile('settings.json');
	
	inline function save(key, value) {
		settingsObj[key] = value;
		settingsFile.writeObject(settingsObj);
	}
	
	inline function load() {
		
		if (settingsExist()) {
			settingsObj = settingsFile.loadAsObject();
		}	
		restoreParameter();
	}
	
	inline function restoreParameter() {
		
		Settings.setZoomLevel(settingsObj['zoom']);
		
		Console.print(settingsObj['wtf']);
		
		Globals.x = settingsObj['wtf'];
		x.wtf_icon_btn.set('visible', settingsObj['wtf']);
	}
	
	inline function settingsExist() { return settingsFile.isFile();}
	
}