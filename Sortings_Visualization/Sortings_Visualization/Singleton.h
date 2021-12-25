#pragma once

#include <stdexcept>

/// <summary>
/// The class is created to override the operator =
/// </summary>
class NonCopyable {
public:
    NonCopyable() = default;
    NonCopyable(const NonCopyable& other) = delete;
    virtual ~NonCopyable() = default;
    NonCopyable& operator =(const NonCopyable& other) = delete;
};

/// <summary>
/// The class is created to override the operator =
/// </summary>
class NonMoveable {
public:
    NonMoveable() = default;
    NonMoveable(NonMoveable&& other) = delete;
    virtual ~NonMoveable() = default;
    NonMoveable& operator =(NonMoveable&& other) = delete;
};

template <typename T>
class Singleton : public NonCopyable, public NonMoveable {
public:
    /// <summary>
    /// The main method of the pattern. The method creates a static variable of the given type
    /// </summary>
    /// <returns>
    ///  Returns a pointer to the created variable or throws the exception if one already exists
    /// </returns>
    template <typename... Args>
    static T* Create(const Args&... args) {
        if (s_Instance) {
            throw std::runtime_error("Already created!");
        }

        return s_Instance = new T(args...);
    }

    /// <summary>
    /// Delete variable
    /// </summary>
    static void Destroy() {
        delete s_Instance;
        s_Instance = nullptr;
    }

    /// <returns>
    ///  Returns a pointer to a variable if it exists
    /// </returns>
    static inline T& Get() {
        if (!s_Instance) {
            throw std::runtime_error("Didn't created yet!");
        }
        return *s_Instance;
    }

protected:
    Singleton() = default;
    static inline T* s_Instance = nullptr;
};
