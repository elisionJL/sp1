#pragma once
#include<string>
class player
{
	private:
		int level;
		int exp;
		std::string name;
		int charactersowned;
		int coins;
		int characterlvlupmat;
		std::string type;
	public:
		player(std::string a,std::string b);
		~player();
		void checklevelup();
		void gacha(int x);
		void stagecleared(int x, int y, int z);
		void uselvlupmat(int x);
		int getplayerinfo(int x);
		std::string getplayerstrinfo(int x);
};

