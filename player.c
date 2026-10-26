#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <time.h>

#include "frames_data.h"

static volatile sig_atomic_t stop = 0;

static void handle_signal(int signal_number) {
    (void)signal_number;
    stop = 1;
}

static void terminal_on(void) {
    fputs("\033[?1049h\033[?25l\033[2J\033[H", stdout);
    fflush(stdout);
}

static void terminal_off(void) {
    fputs("\033[?25h\033[?1049l", stdout);
    fflush(stdout);
}

static void print_frame(const char *frame) {
    const char *p = frame;
    while (*p != '\0') {
        int first = 1;
        while (*p != '\0' && *p != '\n') {
            if (!first) {
                putchar(' ');
            }
            first = 0;
            if (*p == '#') {
                fputs("█", stdout);
            }
            else {
                putchar(*p);
            }
            p++;
        }
        putchar('\n');
        if (*p == '\n') {
            p++;
        }
    }
}

int main(void) {
    struct sigaction action;
    action.sa_handler = handle_signal;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGTERM, &action, NULL);

    const long frame_ns = 1000000000L / 30;
    struct timespec next;
    clock_gettime(CLOCK_MONOTONIC, &next);

    terminal_on();
    for (size_t i = 0; i < TOTAL_FRAMES && !stop; i++) {
        fputs("\033[H", stdout);
        print_frame(bad_apple_frames[i]);
        fflush(stdout);

        next.tv_nsec += frame_ns;
        while (next.tv_nsec >= 1000000000L) {
            next.tv_sec++;
            next.tv_nsec -= 1000000000L;
        }

        if (i + 1 < TOTAL_FRAMES) {
            while (!stop && clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &next, NULL) == EINTR) {
            }
        }
    }
    terminal_off();
    return stop ? 130 : 0;
}
