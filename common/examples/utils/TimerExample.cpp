#define _GLIBCXX_USE_NANOSLEEP

#include <thread>
#include "utils/Timer.hpp"

int main() {
    ds::utils::Timer t("Test", true);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    t.pause();

    std::this_thread::sleep_for(std::chrono::milliseconds(300)); // won't count

    t.resume();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    t.stop();
    t.print<ds::utils::ms>();  // 输出约 700ms
}
