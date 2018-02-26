#ifndef MESSAGE_H
#define MESSAGE_H

using boost::asio::ip::tcp;


class Message
{
public:
    Message() = default;
    Message(const std::string& msg);

    const char* data() const;
    char* data();
    static std::size_t size() { return _size; }

private:
    static const std::size_t _size = 1024;
    std::array<char, _size> _msg{};
};

#endif // MESSAGE_H
