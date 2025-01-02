#ifndef __MEMENTO_HPP__
#define __MEMENTO_HPP__
#include <stack>

template <typename TSnapObj>
class Memento{
  public:
  Memento() = default;
  Memento(const TSnapObj& obj);
  ~Memento() = default;

  /**
   * @brief Saves state of the 'SnapObj'
   */
  void Save(const TSnapObj& obj);
  
  /**
   * @brief pushes snapshot of the obj on the top of the stack
   */
  void Push(const TSnapObj& obj);
  /**
   * @brief Gets the last state
  */
  TSnapObj GetState() const;

  /**
   * @brief Restores last state of the 'SnapObj'
  */
  void Restore(TSnapObj& obj);
  
  /**
   * @brief Clear stack of snapshots
   */
  void ClearSnapshots();
  
  bool IsEmpty() const {return m_SnaphotsStack.empty();}

  explicit constexpr operator bool() const {return !IsEmpty();}

  private:
  std::stack<TSnapObj> m_SnaphotsStack;
};

template <typename TSnapObj>
Memento<TSnapObj>::Memento(const TSnapObj& obj){
    Save(obj);
}

template <typename TSnapObj>
void Memento<TSnapObj>::Save(const TSnapObj &obj)
{
    if(!m_SnaphotsStack.empty()){
        ClearSnapshots();
    }
    m_SnaphotsStack.push(obj);
}

template <typename TSnapObj>
void Memento<TSnapObj>::Push(const TSnapObj &obj)
{
    m_SnaphotsStack.push(obj);
}

template <typename TSnapObj>
TSnapObj Memento<TSnapObj>::GetState() const
{
    return (m_SnaphotsStack.empty()) ? TSnapObj(): m_SnaphotsStack.top();
}

template <typename TSnapObj>
void Memento<TSnapObj>::Restore(TSnapObj& obj)
{
    if(m_SnaphotsStack.empty()) 
      return;

    obj = m_SnaphotsStack.top();
    m_SnaphotsStack.pop();
}

template <typename TSnapObj>
void Memento<TSnapObj>::ClearSnapshots()
{
    if(m_SnaphotsStack.empty()){
        return;
    }
    
     for(size_t i = 0;i < m_SnaphotsStack.size();i++){
      m_SnaphotsStack.pop();
    }
}

#endif