#ifndef __FADEHELPER_HPP__
#define __FADEHELPER_HPP__
#include <chrono>
#include "Core.hpp"
#include "Action.hpp"
#include "Timer.hpp"

/// @brief 
/// @tparam TRep 
/// @tparam TPeriod 
/// @tparam TActionArgs type args for action callback
template<typename TRep, typename TPeriod, typename ... TActionArgs>
class FadeHelper{
public:
    FadeHelper() : m_StartFadeTimerOnce(false), m_IsFinished(false) {}

    template <typename TAction>
    void Setup(std::chrono::duration<TRep,TPeriod> duration, TAction action){
        m_Duration = duration;
        m_Action = action;
        
        m_StartFadeTimerOnce = false;
        m_IsFinished = false;
    }

    /**
     * @brief executes 'action' when specified duration time is elapsed
     */
    auto AsyncExecuteAfter(){
        TimedAction<TRep,TPeriod,Action<TActionArgs ...> > action(m_Duration,m_Action);
        return action();
    }
    
    /**
     * @brief executes 'action' during specified duration
     * @returns true if 'action' successfully finished false otherwise
     */
    bool ExecuteFor(){
        if(m_FadeTimer.GetTicks() < m_Duration.count()){
            if(!m_StartFadeTimerOnce){
                m_FadeTimer.Start();
                m_StartFadeTimerOnce = !m_StartFadeTimerOnce;
            }

            m_Action();

        }else{
            m_IsFinished = true;
        }

        return m_IsFinished;
    }
    
    bool IsFinished() const {return m_IsFinished;}

    void Reset(){
        m_FadeTimer.Stop();
        m_StartFadeTimerOnce = false;
        m_IsFinished = false;
    }

    Timer& GetFadeTimer(){
        return m_FadeTimer;
    }
    
private:
    std::chrono::duration<TRep,TPeriod> m_Duration;
    Action<TActionArgs ...> m_Action;
    bool m_StartFadeTimerOnce;
    Timer m_FadeTimer;
    bool m_IsFinished;
};

#endif // __FADEHELPER_HPP__
