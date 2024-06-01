### Fan Control: The Duct Tape of Thermal Management

**Tired of your fans not working?** This expertly crafted C code and GTK magic lets you wrestle control of your fan speed

**Disclaimer:** This is the "duct tape and paperclip" approach to fan control, My system fans refuse to cooperate, thanks to the lovely *asus_wmi_sensors* driver. Working under high CPU load, often times leads to thermal throttling. Power related shutdowns. This will let me compile without my system spontaneously combusting. It's not pretty, but it's keeping the lights on (for now).


**Installation (Choose Your Poison):**

* **Debian/Ubuntu:** `sudo apt install libgtk-3-dev`
* **Fedora:** `sudo dnf install gtk3-devel`
* **Arch Linux:** `sudo pacman -S gtk3`

**Depends:**

1. Compile :  
   ```bash
   gcc -o fanctl_gui fanctl_gui.c `pkg-config --cflags --libs gtk+-3.0`
   ```
2. Run it:
   ```bash
   sudo ./fanctl_gui
   ```
3. Click the shiny switch and hope for the best.

**Features (or Lack Thereof):**

* A single, glorious toggle switch that may or may not actually work.
* No warranty, expressed or implied.
* May cause spontaneous combustion of nearby electronics.

**Contributing:**
Perfect example of how *not* to do things.
