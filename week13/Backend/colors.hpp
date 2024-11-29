#ifndef H_COLORS
#define H_COLORS

#include <string>
#include <sstream>
#include <chrono>
#include <thread>

namespace Colors {

    // Standard Colors (Foreground)
    const std::string RESET = "\033[0m";
    const std::string BLACK = "\033[30m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN = "\033[36m";
    const std::string WHITE = "\033[37m";
    const std::string GRAY = "\033[90m";
    const std::string BRIGHT_RED = "\033[91m";
    const std::string BRIGHT_GREEN = "\033[92m";
    const std::string BRIGHT_YELLOW = "\033[93m";
    const std::string BRIGHT_BLUE = "\033[94m";
    const std::string BRIGHT_MAGENTA = "\033[95m";
    const std::string BRIGHT_CYAN = "\033[96m";
    const std::string BRIGHT_WHITE = "\033[97m";

    // Standard Colors (Background)
    const std::string BG_BLACK = "\033[40m";
    const std::string BG_RED = "\033[41m";
    const std::string BG_GREEN = "\033[42m";
    const std::string BG_YELLOW = "\033[43m";
    const std::string BG_BLUE = "\033[44m";
    const std::string BG_MAGENTA = "\033[45m";
    const std::string BG_CYAN = "\033[46m";
    const std::string BG_WHITE = "\033[47m";
    const std::string BG_GRAY = "\033[100m";
    const std::string BG_BRIGHT_RED = "\033[101m";
    const std::string BG_BRIGHT_GREEN = "\033[102m";
    const std::string BG_BRIGHT_YELLOW = "\033[103m";
    const std::string BG_BRIGHT_BLUE = "\033[104m";
    const std::string BG_BRIGHT_MAGENTA = "\033[105m";
    const std::string BG_BRIGHT_CYAN = "\033[106m";
    const std::string BG_BRIGHT_WHITE = "\033[107m";

    const std::string empty = "   ";
    const std::string node = BG_BRIGHT_GREEN + BLACK + " ■ " + RESET;	
    //const std::string v_node = BG_GREEN + BLACK + " ● " + RESET;
    const std::string v_node = BG_GREEN + BLACK + " ■ " + RESET;	
    const std::string start = BG_MAGENTA + BLACK + " ● " + RESET;
    const std::string finish = BG_BRIGHT_BLUE + BLACK + " ● " + RESET;
    const std::string path = BG_GREEN + BRIGHT_WHITE+ " ■ " + RESET;
    const std::string finished = BG_BRIGHT_CYAN + BRIGHT_WHITE+ " ■ " + RESET;
    

    // 256 Colors (Foreground)
    inline std::string fg256(int code) {
        if (code < 0 || code > 255) {
            throw std::out_of_range("256 color code must be between 0 and 255");
        }
        std::ostringstream oss;
        oss << "\033[38;5;" << code << "m";
        return oss.str();
    }

    // 256 Colors (Background)
    inline std::string bg256(int code) {
        if (code < 0 || code > 255) {
            throw std::out_of_range("256 color code must be between 0 and 255");
        }
        std::ostringstream oss;
        oss << "\033[48;5;" << code << "m";
        return oss.str();
    }

    void clearScreen(int time) {
        std::cout << "\033[2J\033[H";  // ANSI escape code to clear screen and reset cursor
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
    }
}

#endif