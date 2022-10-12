#pragma once
#include <iostream>
#include <mosquitto.h>


class MQTTClient
{
private:
	static MQTTClient * instance;
	MQTTClient(const char * serverIP, int serverPort);

	struct mosquitto * client;

public:
	static MQTTClient * getInstance();

	void loopOnce();
	void sendMessage(std::string topic, std::string message);
	void subscribe(std::string topic);
};
