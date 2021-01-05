#include "simple_log.hpp"
int main() {
    simple_log slog;
    slog.log_debug("%d", 123);
    slog.log_info("%s %d", "hello simple log", 11821);
    
    return 0;
}