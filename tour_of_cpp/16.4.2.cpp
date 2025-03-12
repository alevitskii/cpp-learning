#include <type_traits>


template<typename T>
concept Class = std::is_class_v<T> || std::is_union_v<T>; // unions are classes

template<typename T> class Smart_pointer
{
  // ...
  T& operator*() const;
  T* operator->() const
    requires Class<T>; // -> is defined if and only if T is a class or a union
};

template<typename T> class Smart_pointer2
{
  // ...
  T& operator*();
  std::enable_if<std::is_class_v<T>, T&> operator->(); // -> is defined if and only if T is a class, SFINAE
};
