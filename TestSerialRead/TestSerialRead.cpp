#include <vector>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>

void serial_read_line(boost::asio::serial_port& serial, std::string& line);

int main()
{
	std::cout << "TestSerialRead\n";

	boost::asio::io_service io;
	boost::asio::serial_port serial(io, "CNCB0");

	serial.set_option(boost::asio::serial_port_base::baud_rate(9600));

	std::string line;
	while (line != "!QUIT")
	{
		serial_read_line(serial, line);

		std::cout << "Line: " << line << std::endl;
		if (line == "!QUIT") break;

		std::vector<std::string> parts;

		boost::split(parts, line, [](const char c) { return c == ' '; });

		for (auto i = 0; i < parts.size(); ++i)
		{
			std::cout << "Index: " << i << "; Part: " << parts[i] << std::endl;
		}
	}

	return 0;
}

void serial_read_line(boost::asio::serial_port& serial, std::string& line)
{
	char c = '\0';
	std::ostringstream oss;

	while (c != '\n')
	{
		boost::asio::read(serial, boost::asio::buffer(&c, 1));
		switch (c)
		{
		case '\r':
			break;

		case '\n':
			line = oss.str();
			return;

		default:
			oss << c;
		}
	}

	line = oss.str();
}
