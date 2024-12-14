#ifndef __STELLAR_KEYFRAME_HPP__
#define __STELLAR_KEYFRAME_HPP__
#include "Action.hpp"

namespace Stellar{
using keyframe_action_t = Action<double>;

class KeyFrame{
public:
    KeyFrame();

    void Setup(float frame_duration, keyframe_action_t action);

    /**
     * @returns returns true if the 'action' was called during the specified frame duration
     */
    bool Update(float dt);
    
    bool IsFinished() const;
    
    void Restart();

private:
    float m_ActionDuration, m_ElapsedFrames;
    keyframe_action_t m_Action;
    bool m_IsFinished;
};

}
#endif // __STELLAR_KEYFRAME_HPP__