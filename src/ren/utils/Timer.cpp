#include "ren/utils/Timer.hpp"

namespace ren::utils
{
    void Timer::start()
    {
        m_startTime = std::chrono::high_resolution_clock::now();
        m_lastFrameTime = m_startTime;
        m_elapsedTime = 0.0;
        m_deltaTime = 0.0;
        m_paused = false;
    }

    void Timer::update()
    {
        if (m_paused)
        {
            m_deltaTime = 0.0;
            return;
        }
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> frameDuration = now - m_lastFrameTime;
        m_deltaTime = frameDuration.count() * m_timeScale;
        m_elapsedTime += m_deltaTime;
        m_lastFrameTime = now;
    }

    void Timer::pause()
    {
        if (!m_paused)
        {
            m_paused = true;
            m_pauseTime = std::chrono::high_resolution_clock::now();
        }
    }

    void Timer::resume()
    {
        if (m_paused)
        {
            auto now = std::chrono::high_resolution_clock::now();
            m_lastFrameTime += (now - m_pauseTime);
            m_paused = false;
        }
    }

    void Timer::reset()
    {
        m_startTime = std::chrono::high_resolution_clock::now();
        m_lastFrameTime = m_startTime;
        m_elapsedTime = 0.0;
        m_deltaTime = 0.0;
        m_paused = false;
    }

    double Timer::getDeltaTime() const
    {
        return m_deltaTime;
    }

    double Timer::getElapsedTime() const
    {
        return m_elapsedTime;
    }

    bool Timer::isPaused() const
    {
        return m_paused;
    }

    void Timer::setTimeScale(double scale)
    {
        m_timeScale = scale;
    }

    double Timer::getTimeScale() const
    {
        return m_timeScale;
    }
}