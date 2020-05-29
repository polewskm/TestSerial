#include <iostream>
#include <boost/asio.hpp>

int main()
{
	std::cout << "TestSerialWrite\n";

	boost::asio::io_service io;
	boost::asio::serial_port serial(io, "CNCA0");

	serial.set_option(boost::asio::serial_port_base::baud_rate(9600));

	std::string line;
	while (line != "!QUIT")
	{
		std::getline(std::cin, line);

		auto message = line + '\n';
		
		boost::asio::write(serial, boost::asio::buffer(message.c_str(), message.size()));
	}

	return 0;
}
