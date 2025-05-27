#pragma once

#include <chrono>
#include <string>
#include <iostream>
#include <iomanip>

namespace ds::utils {

/**
 * @brief Type aliases for common time units.
 */
using ns  = std::chrono::nanoseconds;
using us  = std::chrono::microseconds;
using ms  = std::chrono::milliseconds;
using s   = std::chrono::seconds;
using min = std::chrono::minutes;
using h   = std::chrono::hours;

/**
 * @class Timer
 * @brief A utility class for measuring elapsed time with support for pause and resume.
 *
 * This class provides a simple way to measure the time taken by a section of code.
 * It supports automatic start on construction, and allows pausing and resuming the timer.
 * The timer prints the result when destroyed if it is still running.
 */
class Timer {
public:
    /**
     * @brief Constructs a Timer instance.
     * @param name Optional name used in print output.
     * @param autoStart Whether to start timing immediately upon construction.
     */
    Timer(const std::string& name = "", bool autoStart = true)
        : name_(name), running_(false), paused_(false),
          pausedDuration_(Clock::duration::zero()) {
        if (autoStart) start();
    }

    /**
     * @brief Starts or restarts the timer.
     * 
     * Resets all state including paused duration.
     */
    void start() {
        startTime_ = Clock::now();
        pausedDuration_ = Clock::duration::zero();
        running_ = true;
        paused_ = false;
    }

    /**
     * @brief Stops the timer.
     *
     * If the timer is paused, it automatically resumes to capture the final duration.
     */
    void stop() {
        if (running_) {
            if (paused_) resume(); // Ensure paused time is counted
            endTime_ = Clock::now();
            running_ = false;
        }
    }

    /**
     * @brief Pauses the timer.
     *
     * Does nothing if the timer is already paused or not running.
     */
    void pause() {
        if (running_ && !paused_) {
            pauseTime_ = Clock::now();
            paused_ = true;
        }
    }

    /**
     * @brief Resumes the timer after being paused.
     *
     * Adds the paused duration to the total paused time.
     */
    void resume() {
        if (running_ && paused_) {
            auto resumeTime = Clock::now();
            pausedDuration_ += (resumeTime - pauseTime_);
            paused_ = false;
        }
    }

    /**
     * @brief Returns the elapsed time since start, excluding any paused duration.
     * @tparam duration_t The desired time unit (default: milliseconds).
     * @return The elapsed time in the specified unit.
     */
    template <class duration_t = ms>
    typename duration_t::rep count() const {
        auto end = running_ ? Clock::now() : endTime_;
        auto effectiveDuration = end - startTime_ - pausedDuration_;
        return std::chrono::duration_cast<duration_t>(effectiveDuration).count();
    }

    /**
     * @brief Prints the measured duration to std::cout.
     * @tparam duration_t The desired time unit (default: milliseconds).
     */
    template <class duration_t = ms>
    void print() const {
        std::cout << std::fixed << std::setprecision(3);
        std::cout << "[Timer] " << name_ << ": " << count<duration_t>() << " " << unitName<duration_t>() << std::endl;
    }

    /**
     * @brief Destructor.
     *
     * Automatically stops and prints the result if the timer was still running.
     */
    ~Timer() {
        if (running_) {
            stop();
            print();
        }
    }

private:
    using Clock = std::chrono::high_resolution_clock;  ///< Clock type used for timing.

    std::string name_;                      ///< Name for the timer, used in output.
    bool running_;                          ///< Whether the timer is currently running.
    bool paused_;                           ///< Whether the timer is currently paused.
    Clock::time_point startTime_;           ///< Timestamp when the timer was started.
    Clock::time_point pauseTime_;           ///< Timestamp when the timer was paused.
    Clock::time_point endTime_;             ///< Timestamp when the timer was stopped.
    Clock::duration pausedDuration_;        ///< Accumulated paused duration.

    /**
     * @brief Returns a string representing the unit name for a given duration type.
     * @tparam duration_t The duration type.
     * @return A string representing the unit.
     */
    template <class duration_t>
    static constexpr const char* unitName();
};

// Template specializations for unit names.
template <> constexpr const char* Timer::unitName<ns>()  { return "ns"; }
template <> constexpr const char* Timer::unitName<us>()  { return "us"; }
template <> constexpr const char* Timer::unitName<ms>()  { return "ms"; }
template <> constexpr const char* Timer::unitName<s>()   { return "s"; }
template <> constexpr const char* Timer::unitName<min>() { return "min"; }
template <> constexpr const char* Timer::unitName<h>()   { return "h"; }

} // namespace ds::utils
