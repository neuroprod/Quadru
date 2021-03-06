#pragma once
#include "cinder/app/App.h"
#include "serial/serial.h"
class Motor;
typedef std::shared_ptr<Motor> MotorRef;

class Motor {
	
	float motorAngle = 0;
	float motorSpeed = 25000;
	void setPosition(uint8_t id, int64_t angle, int32_t speed);
	void makeHeader(uint8_t command, uint8_t id, uint8_t dataLength);
	void addCheckSum();
	void logData();
	std::string toHexString(uint8_t b);
	void loop();

	uint8_t id;
	std::string name;
	std::string port;

	std::thread motorThread;
	std::mutex inMutex;
	std::mutex outMutex;
	std::vector< uint8_t> data;
	serial::Serial* my_serial;
	bool connectionFailed = false;

	float angleTarget = 0;
	float speedTarget = 100000;
	float prevAngleTarget = 0;
	float kpTarget = 580;
	float kp = kpTarget;
	ci::vec4 motorData;
public:
	Motor() {};

	static MotorRef create();
	void setup(uint8_t id, std::string name,std::string port);
	void drawGui();
	
	void setMotorAngle(float angle);
	void setMotorMaxSpeed(float speed);
	ci::vec4 getData();
	
	///////////////////////
	


};