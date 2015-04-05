#ifndef _RECORD_H
#define _RECORD_H

#include <string>
#include "Ogre.h"
#include "Contador.h"
using namespace std;


class Record {


public:

	Record();
	Record(const Record& r);
	~Record();

	void setNickname(string nickName);
	void setTime(int time);
	void setLevel(int level);

	string getNickName()  const;
	int  getTime()  const;
	string  getTimeStr()  const;
	int getLevel() const;
	string getLevelStr() const;

	bool operator<(const Record& r) const;
	Record& operator=(const Record &r);

private:
	string _nickname;
	int _level;
	int _time;
};
#endif
