#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define FAN_CONTROL_PATH "/sys/devices/platform/asus-nb-wmi/hwmon/hwmon5/pwm1_enable"

int main(int argc, char *argv[]) {
    if (argc != 2 || (strcmp(argv[1], "on") != 0 && strcmp(argv[1], "off") != 0)) {
        fprintf(stderr, "Usage: fanctl on|off\n");
        return 1;
    }

    int fd = open(FAN_CONTROL_PATH, O_WRONLY);
    if (fd == -1) {
        perror("Error opening fan control file");
        return 1;
    }

    char *value = strcmp(argv[1], "on") == 0 ? "0" : "2";
    if (write(fd, value, strlen(value)) == -1) {
        perror("Error writing to fan control file");
        close(fd);
        return 1;
    }

    close(fd);
    printf("Fan turned %s\n", argv[1]);
    return 0;
}
