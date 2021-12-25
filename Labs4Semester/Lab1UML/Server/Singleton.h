/**
\file
\brief .h file of class Singleton<T>

definition and implementation of Singleton<T> clas
*/

#pragma once

#include <sstream>

/**
\brief Non copyable class, parent of Sigleton<T>
*/
class NonCopyable {
public:
    /**
    \brief default constructor
    */
    NonCopyable() = default;
    /**
    \brief copy constructor is deleted
    */
    NonCopyable(const NonCopyable& other) = delete;

    /**
    \brief default destructor
    */
    virtual ~NonCopyable() = default;

    /**
    \brief copy operator is deleted
    */
    NonCopyable& operator =(const NonCopyable& other) = delete;
};


/**
\brief Non moveable class, parent of Sigleton<T>
*/
class NonMoveable {
public:
    /**
    \brief default constructor
    */
    NonMoveable() = default;

    /**
    \brief move constructor is deleted
    */
    NonMoveable(NonMoveable&& other) = delete;

    /**
    \brief default destructor
    */
    virtual ~NonMoveable() = default;

    /**
    \brief move copy operator is deleted
    */
    NonMoveable& operator =(NonMoveable&& other) = delete;

};

/**
\brief class implementation of Sinfleton pattern

There can't be more than one object of class in program
Class T must be inheritant of Singleton<T> and have it as friend in order to inherit its singleton features
NonMoveable, NonCopyable inheritant
*/
template <typename T>
class Singleton : public NonCopyable, public NonMoveable {
public:

    /**
    \brief creates object

    object can be created only once
    \param args parameters of inheritants
    \throw runtime_error if object already was created
    \return pointer to object
    */
    template <typename... Args>
    static T* Create(Args&... args) {
        if (s_Instance) {
            std::stringstream ss;
            ss << "Engine::Singleton<" << typeid(T).name() << ">::Create: s_Instance is not nullptr!";
            throw std::runtime_error(ss.str());
        }

        return s_Instance = new T(args...);
    }

    /**
    \brief destroys object
    */
    static void Destroy() {
        delete s_Instance;
        s_Instance = nullptr;
    }

    /**
    \brief object getter

    \throw runtime_error if object was not created
    \return reference to object
    */
    static inline T& Get() {
        if (!s_Instance) {
            std::stringstream ss;
            ss << "Engine::Singleton::Get: s_Instance(";
            ss << typeid(T).name();
            ss << ") is nullptr!";

            throw std::runtime_error(ss.str());
        }

        return *s_Instance;
    }


    /**
    \brief object getter

    \return pointer to object
    */
    static inline T* GetPointer() {
        return s_Instance;
    }

protected:

    /**
    \brief default constructor
    */
    Singleton() = default;

    static inline T* s_Instance = nullptr;     ///<pointer to object, nullptr when created

};