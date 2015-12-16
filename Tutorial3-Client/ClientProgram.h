#pragma once
class ClientProgram{
	public:
		ClientProgram();
		~ClientProgram();
		void run();
	
	private:
		Client* client;
		InputOutput* io;
};

