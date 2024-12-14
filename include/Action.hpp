#ifndef __STELLAR_ACTION_HPP__
#define __STELLAR_ACTION_HPP__
#include <chrono>
#include <functional>
#include <future>
#include <iostream>
#include <thread>

namespace helper {
template <int... Is> struct index {};

template <int N, int... Is> struct gen_seq : gen_seq<N - 1, N - 1, Is...> {};

template <int... Is> struct gen_seq<0, Is...> : index<Is...> {};
} // !namespace helper

template <typename... TArgs> 
class Action {
private:
  std::function<void(TArgs...)> m_Action;
  std::tuple<TArgs...> m_Args;
public:
  Action() = default;
  ~Action() = default;

  void operator()(){
    Execute();
  }

  template <typename TCallback, typename... TsArgs>
  Action(TCallback &&action, TsArgs &&... args)
      : m_Action(std::forward<TCallback>(action)),
        m_Args(std::forward<TsArgs>(args)...) {}

  template <typename... TsArgs, int... Is>
  void Execute(std::tuple<TsArgs...> &tup, helper::index<Is...>) {
    m_Action(std::get<Is>(tup)...);
  }

  template <typename... TsArgs> 
  void Execute(std::tuple<TsArgs...> &tup) {
    Execute(tup, helper::gen_seq<sizeof...(TsArgs)>{});
  }

  void Execute() { 
    Execute(m_Args); 
  }
  
  void ExecuteRunTime(TArgs ... args){
    m_Action(args ...);
  }

  explicit operator bool() const noexcept { return static_cast<bool>(m_Action); }
};

template <typename TCallback, typename... TArgs>
inline Action<TArgs...> MakeAction(TCallback &&cb, TArgs &&...args) {
  return Action<TArgs...>(std::forward<TCallback>(cb), std::forward<TArgs>(args)...);
}


template <typename TRep, typename TPeriod, typename TAction>
class TimedAction {
public:
  TimedAction(std::chrono::duration<TRep, TPeriod> duration, TAction& action)
      : m_Duration(duration), m_Action(action) {}

  ~TimedAction() = default;

  [[nodiscard]]  auto operator()() { return (std::async(std::launch::async, [&]() {
      std::this_thread::sleep_for(m_Duration);
      return m_Action();
    })); 
  }

private:
  std::chrono::duration<TRep, TPeriod> m_Duration;
  TAction &m_Action;
};

#endif //!__STELLAR_ACTION_HPP__