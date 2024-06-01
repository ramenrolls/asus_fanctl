#include <gtk/gtk.h> // GTK+ GUI library
#include <stdbool.h> // Boolean data type
#include <stdio.h>   // Standard input/output
#include <unistd.h>  // POSIX operating system API
#include <fcntl.h>   // File control operations
#include <string.h>  // String manipulation

#define FAN_CONTROL_PATH "/sys/devices/platform/asus-nb-wmi/hwmon/hwmon5/pwm1_enable" // Fan control file path

bool fan_state = false; // Initial fan state: off

// Function to control the fan directly
void control_fan(bool state) {
    int fd = open(FAN_CONTROL_PATH, O_WRONLY); // Open fan control file in write-only mode
    if (fd == -1) { // Check if file opened successfully
        perror("Error opening fan control file");
        return; 
    }

    char *value = state ? "0" : "2";  // Set value to write ("0" for on, "2" for off)
    if (write(fd, value, strlen(value)) == -1) { // Write value to the file
        perror("Error writing to fan control file");
        close(fd); // Close the file on error
        return;
    }
    close(fd); // Close the file
}

// Function to toggle the fan state when the switch is changed
void toggle_fan(GtkSwitch *switch_button, gpointer user_data) {
    fan_state = gtk_switch_get_active(switch_button); // Get the new state of the switch
    control_fan(fan_state); // Call the fan control function
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv); // Initialize GTK+

    // Create main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Fan Control");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 100);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL); // Quit when window is closed

    // Create a switch button
    GtkWidget *switch_button = gtk_switch_new();
    g_signal_connect(switch_button, "notify::active", G_CALLBACK(toggle_fan), NULL); // Connect signal to toggle function

    // Create a box layout to hold the switch
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10); 
    gtk_box_pack_start(GTK_BOX(box), switch_button, TRUE, TRUE, 0); // Add switch to the box

    // Add the box to the window
    gtk_container_add(GTK_CONTAINER(window), box); 

    gtk_widget_show_all(window); // Show all widgets
    gtk_main(); // Start the GTK+ main loop

    return 0; // Exit successfully
}
