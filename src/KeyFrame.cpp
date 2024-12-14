#include "KeyFrame.hpp"
namespace Stellar
{
    KeyFrame::KeyFrame() : m_ActionDuration(0), m_ElapsedFrames(0), m_IsFinished(false)
    {
        
    }

    void KeyFrame::Setup(float frame_duration, keyframe_action_t action)
    {
        m_ActionDuration = frame_duration;
        m_ElapsedFrames = 0;
        m_Action = action;
        
        m_IsFinished = false;
    }

    bool KeyFrame::Update(float dt)
    {
        double t = (m_ElapsedFrames / m_ActionDuration);
        if(m_ElapsedFrames >= m_ActionDuration){
            m_IsFinished = true;
            return m_IsFinished;
        }

        m_Action.ExecuteRunTime(t);
        m_ElapsedFrames += dt;

        return m_IsFinished;
    }
    
    bool KeyFrame::IsFinished() const
    {
        return m_IsFinished;
    }
    
    void KeyFrame::Restart()
    {
        m_ElapsedFrames = 0;
        m_IsFinished = false;
    }
    
}