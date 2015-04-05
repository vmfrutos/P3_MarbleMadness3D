#include "Record.h"


Record::Record(){
	_nickname = "";
	_time = 0;
	_level = 0;
}

Record::Record(const Record& r){
	_nickname = r.getNickName();
	_time = r.getTime();
	_level = r.getLevel();

}

Record::~Record(){

}

void Record::setNickname(string nickName){
	_nickname = nickName;
}

void Record::setTime(int time){
	_time = time;
}

void Record::setLevel(int level){
	_level = level;
}


string Record::getNickName() const{
	return _nickname;
}

int Record::getTime() const{
	return _time;
}

string Record::getTimeStr()  const {
	Contador cont;
	cont.incrementar(getTime());
	return cont.getContadorStr();
}

int Record::getLevel() const{
	return _level;
}

string Record::getLevelStr() const {
	std::ostringstream nivelStr;
	nivelStr << getLevel();
	return nivelStr.str();
}

bool Record::operator<(const Record& r) const{

	if (this->getLevel() == r.getLevel()) {
		return this->getTime() < r.getTime();
	} else {
		return this->getLevel() >  r.getLevel();
	}

}

Record &Record::operator = (const Record &r){
	_level = r.getLevel();
	_nickname = r.getNickName();
	_time = r.getTime();
	return(*this);
}





