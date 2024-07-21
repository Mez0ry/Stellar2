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

template <typename... Ts> 
class Action {
private:
  std::function<void(Ts...)> m_Action;
  std::tuple<Ts...> m_Args;
public:
  Action() = default;
  ~Action() = default;

  void operator()(){
    Execute();
  }

  template <typename _CbType, typename... _ArgTs>
  Action(_CbType &&action, _ArgTs &&... args)
      : m_Action(std::forward<_CbType>(action)),
        m_Args(std::forward<_ArgTs>(args)...) {}

  template <typename... _ArgTs, int... Is>
  void Execute(std::tuple<_ArgTs...> &tup, helper::index<Is...>) {
    m_Action(std::get<Is>(tup)...);
  }

  template <typename... _ArgTs> 
  void Execute(std::tuple<_ArgTs...> &tup) {
    Execute(tup, helper::gen_seq<sizeof...(_ArgTs)>{});
  }

  void Execute() { 
    Execute(m_Args); 
  }
  explicit operator bool() const noexcept { return static_cast<bool>(m_Action); }
};

template <typename _CbType, typename... _ArgTs>
inline Action<_ArgTs...> MakeAction(_CbType &&cb, _ArgTs &&...args) {
  return Action<_ArgTs...>(std::forward<_CbType>(cb), std::forward<_ArgTs>(args)...);
}


template <typename _Rep, typename _Period, typename _ActionTy>
class TimedAction {
public:
  TimedAction(std::chrono::duration<_Rep, _Period> duration,
              const _ActionTy &action)
      : m_Duration(duration), m_Action(action) {}
  ~TimedAction() = default;

  auto operator()() { return TimedAction::Execute(m_Duration, m_Action); }

  [[nodiscard]] static std::future<void>
  Execute(std::chrono::duration<_Rep, _Period> duration,
          const _ActionTy &action) {
    return (std::async(std::launch::async, [duration, action]() {
      std::this_thread::sleep_for(duration);
      action.Execute();
    }));
  }

private:
  std::chrono::duration<_Rep, _Period> m_Duration;
  const _ActionTy &m_Action;
};

#endif //!__STELLAR_ACTION_HPP__