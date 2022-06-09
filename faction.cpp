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
	//TODO->
	std::cout << worldTime.getHour() << ":" << worldTime.getMin() << " " << s;
}

std::ostream& wow::Output::operator<<(std::string s)
{
	textOut(s); return std::cout;
}
