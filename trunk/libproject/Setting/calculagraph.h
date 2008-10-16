#ifndef _SETTING_CALULA_GRAPH_H__
#define _SETTING_CALULA_GRAPH_H__

#include <assert.h>

template<int STATE_NUM>
class MultiCalculagraph;

// ����״̬�Ķ�ʱ�л�
// ����ȷ��һ��ʱ���Ƿ�Ӧ�÷���
class Calculagraph {
public:
	Calculagraph(void);
	~Calculagraph(void);
public:
	void initialize() {Reset();}

	// �����л�״̬������ɹ��� �򷵻�true
	// ���ʧ���򷵻�false
	bool trySwitch();

	// ����
	void setTimespan(const DWORD seconds);
	DWORD getTimespan() const;

	void setTimeEscape(const DWORD seconds);
private:
	friend  class MultiCalculagraph;

	// ��ֵ��ǰ��ʱ��
	void Reset();
	DWORD getTimeEscape() const;
	DWORD state_begin_;
	DWORD time_span_;
};


// class MultiCalculagraph
// ���״̬�Ķ�ʱ�л�
template<int STATE_NUM>
class MultiCalculagraph {
public:
	MultiCalculagraph() {}
	~MultiCalculagraph() {}

public:
	void initialize(int type) { setCurrentState(type);}

	// �����л�״̬������ɹ��� �򷵻�true
	// ���ʧ���򷵻�false
	bool trySwitch();
	
	// ��ȡ��ǰ״̬
	int  getCurrentState() const { return state_; }

	// ��ȡ�л�״̬��ʣ��ʱ��
	int  getRemainTime() const { return (getCurrentTimespan() - getCurrentTimeEscape());}
	void setRemainTime(const DWORD seconds);

	// ���úͻ�ȡʱ����
	void setTimespan(const DWORD seconds, const int type);
	DWORD getTimespan(const int type) const;

	void Reset() { return Reset(getCurrentState());}
	// ǿ�Ƹı�״̬
	int  forceSwitch(int type);
private:
	// ��ֵ��ʱ��������Ҫָ����ʱ��������
	void  Reset(const int type);

	// ���õ�ǰ״̬
	void setCurrentState(const int type);
	int getNextState();
	DWORD getCurrentTimeEscape() const;
	DWORD getCurrentTimespan() const;
	int state_;	// ��ǰ״̬
	Calculagraph calculagraph_[STATE_NUM];
};

// ���õ�ǰ״̬�л���ʣ��ʱ��
template<int STATE_NUM>
void MultiCalculagraph<STATE_NUM>::setRemainTime(const DWORD seconds) {
	DWORD second_escape = calculagraph_[state_].getTimespan() -  seconds;
	calculagraph_[state_].setTimeEscape(second_escape);
}

template<int STATE_NUM>
int MultiCalculagraph<STATE_NUM>::getNextState() {
	return (state_ + 1) % STATE_NUM;
}

// ǿ�Ƹı�״̬
template<int STATE_NUM>
int  MultiCalculagraph<STATE_NUM>::forceSwitch(int type) {
	setCurrentState(type);
	Reset(type);
	return 0;
}
// ���õ�ǰ״̬
template<int STATE_NUM>
void MultiCalculagraph<STATE_NUM>::setCurrentState(const int type) {
	assert (type < STATE_NUM && type >= 0);
	state_ = type;
	Reset(type);
}	

// �����л�״̬
template<int STATE_NUM>
bool MultiCalculagraph<STATE_NUM>::trySwitch() {
	if (getCurrentTimeEscape() > getCurrentTimespan()) {
		state_ = getNextState();
		Reset(state_);
		return true;
	} else {
		return false;
	}
}


template<int STATE_NUM>
void  MultiCalculagraph<STATE_NUM>::Reset(const int type) {
	assert (type < STATE_NUM && type >= 0);
	calculagraph_[type].Reset();
}


template<int STATE_NUM>
DWORD MultiCalculagraph<STATE_NUM>::getCurrentTimeEscape() const {
	return calculagraph_[state_].getTimeEscape();
}

// ��ȡ��ǰ��Timespan
template<int STATE_NUM>
DWORD MultiCalculagraph<STATE_NUM>::getCurrentTimespan() const {
	return getTimespan(state_);
}

// ����״̬��TIMESPAN
template<int STATE_NUM>
void MultiCalculagraph<STATE_NUM>::setTimespan(const DWORD seconds, const int type) {
	assert (type < STATE_NUM && type >= 0);
	calculagraph_[type].setTimespan(seconds);
}

template<int STATE_NUM>
DWORD MultiCalculagraph<STATE_NUM>::getTimespan(const int type) const {
	assert (type < STATE_NUM && type >= 0);
	return calculagraph_[type].getTimespan();
}

#endif  // _SETTING_CALULA_GRAPH_H__
