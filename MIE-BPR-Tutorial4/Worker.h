#pragma once


class Worker{
	public:
		Worker();
		~Worker();
		void run();
	
	private:
		Server* server;
		std::string readConfigurationFile();
		int createConfigurationFile(const wchar_t* path);
		std::string serializeTime(Message* m);

		void reply(Message* m);

		void getSystemTime(Message* m);
		void setSystemTime(Message* m);
};

