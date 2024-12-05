#ifndef __FADEHELPER_HPP__
#define __FADEHELPER_HPP__
#include <chrono>
#include "Core.hpp"
#include "Action.hpp"
#include "Timer.hpp"

/// @brief 
/// @tparam TRep 
/// @tparam TPeriod 
/// @tparam TAction callback that will be used if 
/// @tparam ...TArgs 
template<typename TRep, typename TPeriod, typename ... TArgs>
class FadeHelper{
public:
    FadeHelper() : m_StartFadeTimerOnce(false), m_IsFinished(false) {}

    template <typename _TAction>
    void Setup(std::chrono::duration<TRep,TPeriod> duration, _TAction action){
        m_Duration = duration;
        m_Action = action;
        
        m_StartFadeTimerOnce = false;
        m_IsFinished = false;
    }

    void Update(){
        if(m_FadeTimer.GetTicks() < m_Duration.count()){
            if(!m_StartFadeTimerOnce){
                m_FadeTimer.Start();
                m_StartFadeTimerOnce = !m_StartFadeTimerOnce;
            }

        }else{
            m_IsFinished = true;
        }
    }
    
    bool IsFinished() const {return m_IsFinished;}
    
    void Execute(){
        m_Action();
    }

    void Reset(){
        m_FadeTimer.Stop();
        m_StartFadeTimerOnce = false;
    }

    Timer& GetFadeTimer(){
        return m_FadeTimer;
    }

private:
    std::chrono::duration<TRep,TPeriod> m_Duration;
    Action<TArgs ...> m_Action;
    bool m_StartFadeTimerOnce;
    Timer m_FadeTimer;
    bool m_IsFinished;
};

#endif // __FADEHELPER_HPP__
