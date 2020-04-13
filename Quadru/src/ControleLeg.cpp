
#include "ControleLeg.h"

using namespace ci;
using namespace ci::app;
using namespace std;

ControleLegRef ControleLeg::create()
{
	ControleLegRef ref = std::make_shared<ControleLeg>();
	return ref;
}