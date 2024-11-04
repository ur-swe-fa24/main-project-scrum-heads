#include <thread>
#include <chrono>
#include <future>
#include <limits>
#include <random>
#include <iostream>
#include <atomic>
#include "spdlog/spdlog.h"
#include "utils/utils.hpp"
#include "utils/threadsafe_queue.hpp"

enum class Event {
    START,
    STOP,
    QUIT,
    CONTINUE,
    UNKNOWN
};

enum class ErrorType {
    OVERHEAT,
    LOW_BATTERY,
    MOTOR_FAILURE,
    SENSOR_FAILURE,
    SOFTWARE_CRASH
};

// Helper function to convert Event and ErrorType enums to strings.
std::string event_string(Event event){
    switch (event) {
        case Event::START: return "start";
        case Event::STOP: return "stop";
        case Event::QUIT: return "quit";
        case Event::CONTINUE: return "continue";
        default: return "?";
    }
}

std::string error_string(ErrorType error){
    switch (error) {
        case ErrorType::OVERHEAT: return "Overheat";
        case ErrorType::LOW_BATTERY: return "Low Battery";
        case ErrorType::MOTOR_FAILURE: return "Motor Failure";
        case ErrorType::SENSOR_FAILURE: return "Sensor Failure";
        case ErrorType::SOFTWARE_CRASH: return "Software Crash";
        default: return "Unknown Error";
    }
}

class View {
public:
    void prompt(){
        std::cout << "----" << std::endl;
        std::cout << "Enter your command (start, stop, quit, continue): ";
    }
    Event get_input(){
        std::string command;
        std::cin >> command;
        std::cout << "----" << std::endl;
        if (command == "start") return Event::START;
        if (command == "stop") return Event::STOP;
        if (command == "quit") return Event::QUIT;
        if (command == "continue") return Event::CONTINUE;
        return Event::UNKNOWN;
    }
};

int task(int start_value, std::atomic_bool& is_canceled, std::atomic_bool& is_paused, int task_length) {
    spdlog::info("Robot started the task!");

    std::mt19937_64 mt{std::random_device{}()};  // Random number engine
    std::uniform_real_distribution<double> error_chance(0.0, 100.0); // 3% error chance
    std::uniform_int_distribution<int> error_type_dist(0, 4);  // Randomly choose one of five error types

    int task_counter = start_value;
    int progress_increment = task_length / 10; // Update progress at 10% increments

    while (!is_canceled && task_counter < task_length) {
        if (is_paused) {
            spdlog::info("Task paused at progress: {}%", (task_counter * 100) / task_length);
            while (is_paused && !is_canceled) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
            if (is_canceled) {
                spdlog::warn("Task canceled during pause!");
                break;
            }
            spdlog::info("Task resumed.");
        }

        // Randomly decide if an error occurs at this progress step
        if (error_chance(mt) < 3.0) {
            ErrorType error = static_cast<ErrorType>(error_type_dist(mt));
            spdlog::error("Task encountered an error: {}", error_string(error));
            is_canceled = true;
            break;
        }

        // Slow down progress increment delay to 300 milliseconds
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        task_counter += progress_increment;

        int progress = (task_counter * 100) / task_length;
        // Only print progress at 10%, 20%, ..., 100%
        if (progress % 10 == 0) {
            spdlog::info("Task progress: {}%", progress);
        }

        if (progress >= 100) {
            spdlog::info("Task completed successfully with progress: 100%");
            break;
        }
    }

    if (is_canceled && task_counter < task_length) {
        spdlog::warn("Task stopped due to an error or cancellation.");
    }

    return task_counter;
}

int main() {
    std::mt19937_64 mt{std::random_device{}()};  // Random number engine with a seed
    std::uniform_int_distribution<int> rand_int{100, 200}; // Increased range for demonstration

    std::atomic_bool task_cancelled{false};
    std::atomic_bool task_paused{false};

    std::future<int> task_result;
    bool is_task_started = false;
    spdlog::info("Event loop starting!");

    View ui{};

    while (true) {
        ui.prompt();
        auto input_event = ui.get_input();
        spdlog::info("User entered {}", event_string(input_event));

        if (input_event == Event::QUIT) {
            if (is_task_started) {
                task_cancelled = true;
                task_result.wait();
            }
            break;
        } else if (input_event == Event::START && !is_task_started) {
            task_cancelled = false;
            task_paused = false;
            int task_length = rand_int(mt);
            task_result = std::async(
                std::launch::async,
                task,
                0, // Start from 0 for simplicity
                std::ref(task_cancelled),
                std::ref(task_paused),
                task_length
            );
            is_task_started = true;
        } else if (input_event == Event::STOP && is_task_started) {
            task_paused = true;
            spdlog::warn("Task paused by user.");
        } else if (input_event == Event::CONTINUE && is_task_started && task_paused) {
            task_paused = false;
            spdlog::info("Task resumed by user.");
        }
    }

    return 0;
}
