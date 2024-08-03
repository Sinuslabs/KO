import("stdfaust.lib");

WINDOW = 30 / 1000;

low_cutoff = hslider("v:Whetstone Transient Shaper/[2]Low Cutoff[unit:Hz]",10,10,20000,10);
high_cutoff = hslider("v:Whetstone Transient Shaper/[3]High Cutoff[unit:Hz]", 20000,20,20000,10);
do_monitor = button("v:Whetstone Transient Shaper/h:[4]Monitoring/[0]Monitor selected band") : ba.toggle : vbargraph("v:Whetstone Transient Shaper/h:[4]Monitoring/[1]ON[style:led]", 0, 1);
attack = hslider("v:Whetstone Transient Shaper/[0]Attack[unit:dB]",0,-12,+12,0.1) : ba.db2linear : si.smoo;
sustain = hslider("v:Whetstone Transient Shaper/[1]Sustain[unit:dB]",0,-12,+12,0.1) : ba.db2linear : si.smoo;

process = sp.stereoize(split_shape_merge);

split_shape_merge = _ : split_active_and_passive : (_ <: _ * get_gain(_ : change)), ba.bypass1(do_monitor != 1, *(0)) :> _;

//split signal into two parts $active, $passive
//$active is resonant low- and high-passed between low_cutoff and high_cutoff respectively. This is fed directly to output if monitoring is on
//$passive is resonant high- and low-passed between low_cutoff and high-cutoff respectively
split_active_and_passive = _ <:     (fi.resonhp(low_cutoff, 1, 1) : fi.resonlp(high_cutoff, 1, 1)),
                                    (fi.resonlp(low_cutoff, 1, 1) + fi.resonhp(high_cutoff, 1, 1));

//$active is analyzed with RMS over N ms divided by a lag filter applied to the RMS to get a rise speed over time to get $change
change = ba.slidingRMS(ba.sec2samp(WINDOW)) <: _ - si.lag_ud(WINDOW, WINDOW);

//If $change is positive, $gain is $attack
//If $change is negative, $gain is $sustain
//Smooth $gain
get_gain(x) = ba.if(x > 0, attack,sustain) : si.lag_ud(WINDOW,WINDOW);