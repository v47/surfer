#include <iostream>
#include <boost/asio.hpp>
#include <algorithm>

using namespace std;
using namespace boost::asio;

int main()
{
    io_service service;
    ip::tcp::resolver resolver(service);
    vector<string> iplist (0);
    while(true){
        ip::tcp::resolver::query query("http://en.wikipedia.org", "80");
        ip::tcp::resolver::iterator iter = resolver.resolve( query);
        ip::tcp::endpoint ep = *iter;
        ip::tcp::socket socket(service);
        socket.connect(ep);
        boost::asio::streambuf request;
        std::ostream request_stream(&request);
        request_stream << "GET / HTTP/1.0\r\n";
        request_stream << "Host: " << "http://en.wikipedia.org" << "\r\n";
        request_stream << "Accept: */*\r\n";
        request_stream << "Connection: close\r\n\r\n";
        // Send the request.
        boost::asio::write(socket, request);
        boost::asio::streambuf buf;
        boost::system::error_code ec;
        read(socket, buf,boost::asio::transfer_all(), ec);
        socket.shutdown(ip::tcp::socket::shutdown_receive);
        socket.close();
        iplist.push_back(ep.address().to_string());
        std::cout << ep.address().to_string() << std::endl;
        //std::ostream out(&buf);
        std::cout << &buf <<std::endl;
        sleep(1);
    }
    return 0;
}

