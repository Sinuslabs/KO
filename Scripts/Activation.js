namespace Activation {
    const var loading_indicator = Content.getComponent("loading_indicator");
    const var LAF_not_activated = Content.createLocalLookAndFeel();
    const var Activation_pnl = Content.getComponent("Activation_pnl");
    const var Backdrop_overlay_pnl = Content.getComponent("Backdrop_overlay_pnl");
    const var not_activated_btn = Content.getComponent("not_activated_btn");
    const var Paste_btn = Content.getComponent("Paste_btn");
    const var Buy_now_btn = Content.getComponent("Buy_now_btn");
    const var Activate = Content.getComponent("Activate");
    const var close_activate_btn = Content.getComponent("close_activate_btn");
    const var serial_code_lbl = Content.getComponent("serial_code_lbl");
    const var serial_error_label = Content.getComponent("serial_error_label");

    const animation = Animations.loading;
    const timer = 30;
    reg frame = 0;
    const frames = 32;
    reg speed = 1;
    
    not_activated_btn.set('visible', true);

    serial_error_label.set('visible', false);
    loading_indicator.set('visible', false);
    loading_indicator.setAnimation(animation);
    loading_indicator.setTimerCallback(nextFrame);
    loading_indicator.startTimer(timer);

    not_activated_btn.setLocalLookAndFeel(LAF_not_activated);
    Paste_btn.setLocalLookAndFeel(Styles.LAF_displayButtonOutline);
    Activate.setLocalLookAndFeel(Styles.LAF_displayButtonFill);
    Buy_now_btn.setLocalLookAndFeel(Styles.LAF_displayButtonOutline);
    close_activate_btn.setLocalLookAndFeel(Styles.LAF_displayIconButton);

    Buy_now_btn.setControlCallback(onBuyNow);
    Paste_btn.setControlCallback(onPaste);
    Activate.setControlCallback(onActivate);
    close_activate_btn.setControlCallback(onClose);
    not_activated_btn.setControlCallback(onNotActivated);

    Activation_pnl.setPaintRoutine(activation_routine);
    Backdrop_overlay_pnl.setMouseCallback(onBackdrop);

    LAF_not_activated.registerFunction('drawToggleButton', not_activated_laf);

    inline function onBackdrop(event) {
        if (event.clicked) {
            Activation_pnl.set('visible', false);
            Backdrop_overlay_pnl.set('visible', false);
        }
    }

    inline function nextFrame() {
        loading_indicator.setAnimationFrame(frame);
        frame += speed;
        if (frame >= frames) frame = 0;
    }

    inline function onBuyNow(component, value) {
        if (!value) return;
        Engine.openWebsite('https://sinuslabsio.gumroad.com/l/KO');
    }

    inline function unlockDemoLimitations() {
	    Globals.activated = true;
        GainReduction.setBypassed(true);
        GainReductionTimer.stopTimer();
        not_activated_btn.set('visible', false);
        
    }

    inline function onActivate(component, value) {
        if (value) {
            serial_error_label.set('visible', false);
            if (Engine.getOS() == 'LINUX') {
                Supabase.unlockProduct();
                return;
            }
            Supabase.activate(serial_code_lbl.get('text'));
            loading_indicator.set('visible', true);
        }
    }

    inline function onPaste(component, value) {
        if (!value) return;
        local clipboard = Engine.getClipboardContent();
        serial_code_lbl.set('text', clipboard);
    }

    inline function onClose(component, value) {
        if (!value) return;
        Activation_pnl.set('visible', false);
        Backdrop_overlay_pnl.set('visible', false);
    }

    inline function onNotActivated(component, value) {
        if (!value) return;
        Activation_pnl.set('visible', true);
        Backdrop_overlay_pnl.set('visible', true);
        serial_code_lbl.grabFocus();
    }

    inline function activation_routine(g) {
        local a = this.getLocalBounds(1);
        g.setColour(Theme.THEME.Colors.Display.display);
        g.fillRoundedRectangle(a, 4);
        g.setColour(Theme.THEME.Colors.Display.on_display_disabled);
        g.drawRoundedRectangle(a, 4, 2);
    }

    inline function not_activated_laf(g, obj) {
        local a = obj.area;
        g.setColour(Primitives.Colors.Red['400']);
        if (obj.over) g.setColour(Primitives.Colors.Red['500']);
        g.setFont(Theme.Regular, 18);
        g.drawAlignedText(obj.text, a, 'centred');
    }
}