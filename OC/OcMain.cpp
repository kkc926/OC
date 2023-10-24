#include "OcMain.h"

using namespace std;

int main()
{
	OcCommManager	OcCommManager;

	OcCommManager.Run();


	//(void)OcCommManager.InitializeWinSock();
	//thread t{ &OcCommManager::OcMssTcpServerThread, &OcCommManager };
	//thread t2{ &OcCommManager::OcAtsTcpServerThread, &OcCommManager };
	//thread t3{ &OcCommManager::OcLcsTcpServerThread, &OcCommManager };
	//thread t4{ &OcCommManager::OcAdrsTcpServerThread, &OcCommManager };
	//t.join();
	//t2.join();
	//t3.join();
	//t4.join();

	return 0;
}