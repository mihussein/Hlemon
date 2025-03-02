#include "lemonOutput.h"
#include "battery.h"
#include "brightness.h"
#include "volume.h"
#include "mic.h"
#include "workspaces.h"
#include "clock.h"
#include <iostream>
#include <string>

FILE *bar = nullptr;

void initLemonbar() {
    bar = popen("lemonbar -B \"#000000\" -g x25 -f \"Font Awesome 6 Pro Solid:size=11\" -f \"JetBrains Mono NL:size=11\" -d", "w");
    if (!bar) {
        std::cerr << "Error initializing lemonbar\n";
        exit(1);
    }
}

void updateLemonbar(const std::string& content) {
    if (bar) {
        fprintf(bar, "%s\n", content.c_str());
        fflush(bar);
    }
}

std::string lemonOutput() {
		return
			"%{l} "
            + Workspaces::getWorkspaces()
            + "%{r}"
            + Volume::getVolume() + "%{F#777777}|%{F-}"
			+ Mic::getMicVolume() + "%{F#777777}|%{F-}"
            + Brightness::getBrightness() + "%{F#777777}|%{F-}"
            + Battery::getBattery() + "%{F#777777}|%{F-}"
      	    + getClock()
            + " ";
}
