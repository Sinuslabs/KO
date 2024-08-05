namespace Supabase {

    Server.setServerCallback(serverActivity);
    Server.setEnforceTrailingSlash(false);


    inline function setHeader() {

    local Headers = [
            "content_type: application/json",
            "apikey: " + Config.SUPABASE_ANON,
            "Authorization: Bearer " + Config.SUPABASE_ANON,
        ];
    
    local singleHeader = '';
        for (header in Headers) { singleHeader += header + '\n'; }
        Server.setHttpHeader(singleHeader);
    }

	inline function activate(license_key) {

        if (Globals.activated) {
            Console.print('Already activated');
            return;
        }

        Server.setBaseURL(Config.SUPABASE_URL);

        setHeader();
    
    	local parameter = {
            "p_license_key": license_key.trim()
        };

        Server.callWithPOST("/rest/v1/rpc/check_license",
            parameter,
            onLicenseCheck);
    }


	inline function onLicenseCheck(status, data) {
        if (data['valid']) {
            unlockProduct();
        } else {
	        Activation.serial_error_label.set('visible', true);
        }
    }

	inline function unlockProduct() {
	    local data = { 'isActivated': true, date: Engine.getSystemTime(true) };
	    local machineId = FileSystem.getSystemId();
	    local appDateDir = FileSystem.getFolder(FileSystem.UserPresets).getParentDirectory();
        appDateDir.getChildFile("license.dat").writeEncryptedObject(data, machineId);

        Globals.activated = true;
		
		Activation.Activation_pnl.set('visible', false);
		Activation.not_activated_btn.set('visible', false);
		Activation.Backdrop_overlay_pnl.set('visible', false);
		
        Activation.unlockDemoLimitations();
    }

    inline function getActivationStatus() {
        local license = getLocalLicense();
        if (license) Globals.activated = true;
        Console.print('status check: ' + Globals.activated);
    }

	inline function serverActivity(isWaiting) {
		Activation.loading_indicator.set('visible', isWaiting);
    }

    inline function getLocalLicense() {
        local machineId = FileSystem.getSystemId();
        local appDateDir = FileSystem.getFolder(FileSystem.UserPresets).getParentDirectory();
        local license = appDateDir.getChildFile("license.dat").loadEncryptedObject(machineId);
        return license;
    }
}