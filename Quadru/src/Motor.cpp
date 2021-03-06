#include "Motor.h"
#include "CinderImGui.h"

#include <sstream>
#include "Unions.h"
/*#include <chrono> 
#include <windows.h>
#include "Processthreadsapi.h"
using namespace std::chrono;*/

using namespace ci;
using namespace ci::app;
using namespace std;

MotorRef Motor::create()
{
	return make_shared<Motor>();
}

void Motor::setup(uint8_t _id, std::string _name, std::string _port)
{
	id = _id;
	name = _name;
    port = _port;

    unsigned long baud = 115200;
    
    try {
        my_serial = new serial::Serial(port, baud);

        if (my_serial->isOpen()) {

            my_serial->flush();
            motorThread = std::thread(&Motor::loop, this);
        }
        else 
        {
            connectionFailed = true;
        }
    }
    catch (...) 
    {
        connectionFailed = true;
    }
    if (connectionFailed) { 
        console() << "Failed to connect to " << (int)id << " " << name << " " << port << endl; 
    }
    else 
    {
        console() << "Connected to " << (int)id << " " << name << " " << port << endl;
        
    }
   

}
void Motor::loop()
{
    bool nComplete = true;
    std::vector<uint8_t> buffer;
    while (nComplete)
    {
        inMutex.lock();
        float maxSpeed = motorSpeed; 
        float  angleTarget = motorAngle;
        float  kpR = kp;
        inMutex.unlock();

        //speed = dps*100

        uint32_t speedR= maxSpeed;
        int64_t  angleR = (angleTarget + 180.f) * 100.f * 6.f;

        float angleChange = abs(prevAngleTarget - angleTarget);
        uint32_t speed = angleChange *60 * kpR;
        if (speed < speedR && speed !=0)speedR = speed;
        console() << angleChange <<" "<< speed << " " << speedR << endl;
        prevAngleTarget = angleTarget;
        

        setPosition(id, angleR, speedR);

        size_t bytes_wrote = my_serial->write(data);


        while ((my_serial->available() != 13))
        {

        }
        buffer.clear();
        my_serial->read(buffer, 13);

        Union16 Utorque;
        Utorque.b[0] = buffer[6];
        Utorque.b[1] = buffer[7];

        Union16 Uspeed;
        Uspeed.b[0] = buffer[8];
        Uspeed.b[1] = buffer[9];

        UnionU16 Uencoder;
        Uencoder.b[0] = buffer[10];
        Uencoder.b[1] = buffer[11];

        outMutex.lock();
        motorData.x = Utorque.r;
        motorData.y = Uspeed.r;
        motorData.z = Uencoder.r;
        outMutex.unlock();
       // console() << (float)Utorque.r / 2048.f * 33.f << " " << (float)Uspeed.r << " " << (float)Uencoder.r << endl;
    }
}


void Motor::drawGui()
{
    ImGui::PushID(name.c_str());
    if (ImGui::CollapsingHeader(name.c_str()))
    {
      
        if (ImGui::SliderFloat("motorAngle", &angleTarget, -180.f, 180.f)) { setMotorAngle(angleTarget); }
        if (ImGui::SliderFloat("motorSpeed", &speedTarget, 0.f, 200000.f)) { setMotorMaxSpeed(speedTarget); }
        if (ImGui::SliderFloat("motorKp", &kpTarget, 0.f, 2000.f)) { inMutex.lock(); kp = kpTarget;     inMutex.unlock();}
    }
    ImGui::PopID();
}

void Motor::setMotorAngle(float target)
{
    inMutex.lock();
    motorAngle = target;

   
    inMutex.unlock();
}
void Motor::setMotorMaxSpeed(float target)
{
    inMutex.lock();
    motorSpeed =target;

   
    inMutex.unlock();
}

vec4 Motor::getData() 
{
    vec4 data;
    outMutex.lock();
    data = motorData;
    outMutex.unlock();
    return data;
}


//////////////////////////////////////////////////////////
void Motor::setPosition(uint8_t id, int64_t angleControl, int32_t maxSpeed)
{
    angleControl = angleControl;
    makeHeader(0xA4, 1, 0x0C);
    data.push_back(*(uint8_t*)(&angleControl));
    data.push_back(*((uint8_t*)(&angleControl) + 1));
    data.push_back(*((uint8_t*)(&angleControl) + 2));
    data.push_back(*((uint8_t*)(&angleControl) + 3));
    data.push_back(*((uint8_t*)(&angleControl) + 4));
    data.push_back(*((uint8_t*)(&angleControl) + 5));
    data.push_back(*((uint8_t*)(&angleControl) + 6));
    data.push_back(*((uint8_t*)(&angleControl) + 7));
    data.push_back(*(uint8_t*)(&maxSpeed));
    data.push_back(*((uint8_t*)(&maxSpeed) + 1));
    data.push_back(*((uint8_t*)(&maxSpeed) + 2));
    data.push_back(*((uint8_t*)(&maxSpeed) + 3));

    addCheckSum();

}

void Motor::makeHeader(uint8_t command, uint8_t id, uint8_t dataLength)
{
    data.clear();
    data.push_back(0x3E);
    data.push_back(command);
    data.push_back(id);
    data.push_back(dataLength);

    uint8_t ssum = 0x3E + command + id + dataLength;
    data.push_back(ssum);
}
void Motor::addCheckSum()
{
    uint8_t ssum = data[5];
    for (int i = 6; i < data.size(); i++)
    {
        ssum += data[i];
    }
    data.push_back(ssum);
}

void Motor::logData()
{
    for (int i = 0; i < data.size(); i++)
    {
        console() << toHexString(data[i]) << " ";
    }
    console() << endl;
}
std::string Motor::toHexString(uint8_t b)
{
    std::stringstream str;
    str << std::hex << static_cast<int>((b));
    std::string result(str.str());
    if (result.size() == 1) result = "0" + result;
    std::for_each(result.begin(), result.end(), [](char& c) {
        c = ::toupper(c);
        });
    return result;

}