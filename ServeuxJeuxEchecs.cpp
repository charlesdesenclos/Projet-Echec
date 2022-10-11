
#include <iostream>
#include <mosquitto.h>

void ServeurJeuxEchecs(int argc, char **argv)
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
		std::cout << "Vous n'�tes pas connecter";
	}

	mosquitto_lib_cleanup();

}

