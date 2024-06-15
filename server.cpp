// server.cpp
#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <mutex>
#include <set>

using boost::asio::ip::tcp;

std::set<std::shared_ptr<tcp::socket>> clients;
std::mutex clients_mutex;

void broadcast_message(const std::string& message) {
    std::lock_guard<std::mutex> lock(clients_mutex);
    for (const auto& client : clients) {
        boost::asio::write(*client, boost::asio::buffer(message));
    }
}

void session(std::shared_ptr<tcp::socket> socket) {
    try {
        {
            std::lock_guard<std::mutex> lock(clients_mutex);
            clients.insert(socket);
        }

        for (;;) {
            char data[1024];
            boost::system::error_code error;
            size_t length = socket->read_some(boost::asio::buffer(data), error);

            if (error == boost::asio::error::eof) {
                break; // Connection closed cleanly by peer.
            } else if (error) {
                throw boost::system::system_error(error); // Some other error.
            }

            std::string message(data, length);
            broadcast_message(message);
        }
    } catch (std::exception& e) {
        std::cerr << "Exception in thread: " << e.what() << "\n";
    }

    {
        std::lock_guard<std::mutex> lock(clients_mutex);
        clients.erase(socket);
    }
}

int main() {
    try {
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 12345));

        for (;;) {
            auto socket = std::make_shared<tcp::socket>(io_context);
            acceptor.accept(*socket);
            std::thread(session, socket).detach();
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
