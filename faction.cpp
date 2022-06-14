#include "faction.h"

wow::Time wow::worldTime;

void wow::Debug::Log(std::string s)
{
#ifdef DEBUG
	std::clog.fill('0');
	std::clog.width(3);
	std::clog << worldTime.getHour();
	std::clog << ":";
	std::clog.width(2);
	std::clog << worldTime.getMin() << " log- " << s << std::endl;
#endif // DEBUG
}

void wow::Output::textOut(std::string s)
{
	std::cout.fill('0');
	std::cout.width(3);
	std::cout << wow::worldTime.getHour();
	std::cout << ":";
	std::cout.width(2);
	std::cout << wow::worldTime.getMin() << ' ' << s;
}

std::ostream& wow::Output::operator<<(std::string s)
{
	textOut(s); return std::cout;
}
