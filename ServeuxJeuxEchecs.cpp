
#include <iostream>
#include <mosquitto.h>

#include "ServeurJeuxEchecs.h"




void ServeurJeuxEchecs()
{
	mosquitto_lib_init();

	struct mosquitto * client = mosquitto_new(NULL, true, NULL);

	int test = mosquitto_connect(client, "192.168.64.55", 1883, 10);
	if (test == MOSQ_ERR_SUCCESS)
	{
		std::cout << "Vous etes connecter";
	}
	else
	{
		std::cout << "Vous n'étes pas connecter";


	}
	int mid;
	char msg[] = "Test message";
	mosquitto_publish(client, &mid, "topictest", strlen(msg) + 1, msg, 0, true);

	//mosquitto_subscribe(client, &mid, sub, 2);

	int timeout; int max_packets;

	mosquitto_loop(client, timeout, max_packets);

	mosquitto_lib_cleanup();

}



