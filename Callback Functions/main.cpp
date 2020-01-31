// Callback Functions
//
// Mauricio Vives / 2020

#include <functional> // std::bind and std::function
#include <iostream>   // std::cout and std::endl
#include <string>     // std::string
#include <vector>     // std::vector

// A class for dispatching events to registered listener functions.
class EventDispatcher
{
public:
    // A listener (callback) function type definition, accepting a string and returning an integer.
    // NOTE: This uses std::function so that several types of callables can be supported, and with
    // type safety.
    typedef std::function<int(const std::string&)> ListenerFunc;

    // Adds a listener to the event dispatcher.
    void AddListener(const ListenerFunc& func)
    {
        m_listeners.push_back(func);
    }

    // Fires an event with the specified string to all event listeners.
    void Fire(const std::string& value)
    {
        std::cout << "Dispatching with value: " << value << std::endl;
        for (const auto& callback : m_listeners)
        {
            int result = callback(value);
            std::cout << " - Returned " << result << std::endl;
        }
    }

private:
    // An array of listener functions.
    std::vector<ListenerFunc> m_listeners;
};

// A global listener function, i.e. the traditional callback style. 
static int GlobalListener(const std::string& value)
{
    std::cout << "Global function says: " << value;

    return 0;
}

// A class with listener functions.
class TestListener
{
public:
    // Constructor which accepts the instance value, used by the instance member function.
    TestListener(int value) : m_instanceValue(value) {}

    // A static member function as a listener.
    static int StaticListener(const std::string& value)
    {
        std::cout << "Static member function says: " << value;

        return m_staticValue;
    }

    // An instance member function as a listener.
    int InstanceListener(const std::string& value)
    {
        std::cout << "Instance member function says: " << value;

        return m_instanceValue;
    }

private:
    // A value for the static member function to use.
    static const int m_staticValue{ 1 };

    // A value for the instance member function to use.
    int m_instanceValue;
};

int main()
{
    EventDispatcher dispatcher;

    // Add a global function (function pointer) as a listener.
    dispatcher.AddListener(&GlobalListener);

    // Add a class static member function as a listener.
    dispatcher.AddListener(&TestListener::StaticListener);

    // Add a class instance member function as a listener.
    // NOTE: This requires an instance of the class to provide state for the function ("this").
    TestListener testListener(2);
    dispatcher.AddListener(
        std::bind(&TestListener::InstanceListener, &testListener, std::placeholders::_1));

    // Add a lambda (anonymous) function as a listener.
    dispatcher.AddListener(
        [](const std::string& value) -> int
        {
            std::cout << "Lambda function says: " << value;

            return 3;
        });

    // Fire an event.
    dispatcher.Fire("Testing");
}