// client.cpp
#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <string>

using boost::asio::ip::tcp;

void read_from_server(tcp::socket& socket) {
    try {
        for (;;) {
            char reply[1024];
            boost::system::error_code error;
            size_t reply_length = socket.read_some(boost::asio::buffer(reply), error);

            if (error == boost::asio::error::eof) {
                std::cerr << "Connection closed cleanly by peer.\n";
                break;
            } else if (error) {
                throw boost::system::system_error(error);
            }

            std::cout << "Reply from server: ";
            std::cout.write(reply, reply_length);
            std::cout << "\n";
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

int main() {
    try {
        boost::asio::io_context io_context;

        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "12345");

        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        std::thread reader_thread(read_from_server, std::ref(socket));

        std::string msg;
        std::cout << "Enter messages to send to the server. Type 'exit' to quit.\n";

        while (true) {
            std::cout << "> ";
            std::getline(std::cin, msg);

            if (msg == "exit") {
                break;
            }

            boost::asio::write(socket, boost::asio::buffer(msg));
        }

        socket.close();
        reader_thread.join();

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
