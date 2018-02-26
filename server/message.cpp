#include "message.h"

Message::Message(const std::string& msg)
{
    std::copy(msg.begin(), msg.begin() + std::min(msg.size(), _size), _msg.begin());
}

const char* Message::data() const
{
    return _msg.data();
}

char* Message::data()
{
    return _msg.data();
}
