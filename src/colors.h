// * Daniel Medina | A01286980
// * Wednesday September 25th, 2025

// ANSI Color Codes Utility Header
// Provides constants for text colors, background colors, and text formatting

#ifndef COLORS_H
#define COLORS_H

// Reset
#define RESET "\033[0m"

// Text Colors
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

// Bright Text Colors
#define BRIGHT_BLACK "\033[90m"
#define BRIGHT_RED "\033[91m"
#define BRIGHT_GREEN "\033[92m"
#define BRIGHT_YELLOW "\033[93m"
#define BRIGHT_BLUE "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN "\033[96m"
#define BRIGHT_WHITE "\033[97m"

// Background Colors
#define BG_BLACK "\033[40m"
#define BG_RED "\033[41m"
#define BG_GREEN "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_BLUE "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN "\033[46m"
#define BG_WHITE "\033[47m"

// Bright Background Colors
#define BG_BRIGHT_BLACK "\033[100m"
#define BG_BRIGHT_RED "\033[101m"
#define BG_BRIGHT_GREEN "\033[102m"
#define BG_BRIGHT_YELLOW "\033[103m"
#define BG_BRIGHT_BLUE "\033[104m"
#define BG_BRIGHT_MAGENTA "\033[105m"
#define BG_BRIGHT_CYAN "\033[106m"
#define BG_BRIGHT_WHITE "\033[107m"

// Text Formatting
#define BOLD "\033[1m"
#define DIM "\033[2m"
#define ITALIC "\033[3m"
#define UNDERLINE "\033[4m"
#define BLINK "\033[5m"
#define REVERSE "\033[7m"
#define STRIKETHROUGH "\033[9m"

// Combined Styles for Common Use Cases
#define HEADER_STYLE BOLD BRIGHT_BLUE
#define SUCCESS_STYLE BOLD BRIGHT_GREEN
#define ERROR_STYLE BOLD BRIGHT_RED
#define WARNING_STYLE BOLD BRIGHT_YELLOW
#define INFO_STYLE BRIGHT_CYAN
#define TIMESTAMP_STYLE DIM BRIGHT_WHITE
#define RESTAURANT_STYLE BOLD MAGENTA
#define ITEM_STYLE CYAN
#define PRICE_STYLE BOLD YELLOW

// Section Headers with Background
#define SECTION_HEADER BG_BLUE WHITE BOLD
#define SUCCESS_HEADER BG_GREEN BLACK BOLD
#define ERROR_HEADER BG_RED WHITE BOLD
#define WARNING_HEADER BG_YELLOW BLACK BOLD

#endif  // COLORS_H