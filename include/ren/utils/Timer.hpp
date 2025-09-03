#pragma once

#include <chrono>

namespace ren::utils
{
    class Timer {
    public:
        void start();
        void update();
        void pause();
        void resume();
        void reset();
    
        double getDeltaTime() const;     
        double getElapsedTime() const;
        bool isPaused() const;
    
        void setTimeScale(double scale);
        double getTimeScale() const;
    
    private:
        std::chrono::high_resolution_clock::time_point m_startTime;
        std::chrono::high_resolution_clock::time_point m_lastFrameTime;
        std::chrono::high_resolution_clock::time_point m_pauseTime;
    
        double m_elapsedTime = 0.0;
        double m_deltaTime = 0.0;
        double m_timeScale = 1.0;
        bool m_paused = false;
    };
}

