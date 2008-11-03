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
	void setTimespan(const int seconds);
	int getTimespan() const;

	// һ����Ϊ��λMS
	int getTimespanMS() const;

	void setTimeEscapeMS(const int milseconds);
	void setTimeEscape(const int seconds);

	// ��ȡʣ���ʱ����ȥ��ʱ��
	int getTimeEscape() const;
	int getTimeEscapeMS() const;
	int getRemainTime() const;
	int getRemainTimeMS() const;
private:
	friend  class MultiCalculagraph;
	friend  class CalculargraphTest;
	// ��ֵ��ǰ��ʱ��
	void Reset();

	int state_begin_;
	int time_span_;

	// stop the timer
	// ��ֹͣ��ʱ����ʱ�����Ǳ��浱ǰ��ʣ��ʱ��
	// �ڻظ���ʱ����ʱ�򣬸���ʣ���ʱ�������趨state_begin_��ֵ
public:
	bool isStopped() const { return stopped_;}
	void stop();
	void restart();
private:
	bool stopped_;
	int last_time_escape_;
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
	int  getRemainTime()  { return getCurrentCalcu()->getRemainTime();}
	int  getRemainTimeMS() { return getCurrentCalcu()->getRemainTimeMS();}
	void setRemainTime(const int seconds);

	// ���úͻ�ȡʱ����
	void setTimespan(const int seconds, const int type);
	int getTimespan(const int type) const;

	void Reset() { return Reset(getCurrentState());}
	// ǿ�Ƹı�״̬
	int  forceSwitch(int type);

	// ֹͣ��ʱ��
public:
	void stop() {
		getCurrentCalcu()->stop();
	}
	void restart() {
		getCurrentCalcu()->restart();
	}
	bool isStopped() {
		return getCurrentCalcu()->isStopped();
	}
private:
	Calculagraph * getCurrentCalcu() {
		return &(calculagraph_[getCurrentState()]);
	}
	// ��ֵ��ʱ��������Ҫָ����ʱ��������
	void  Reset(const int type);

	// ���õ�ǰ״̬
	void setCurrentState(const int type);
	int getNextState();
	int state_;	// ��ǰ״̬
	Calculagraph calculagraph_[STATE_NUM];
};

// ���õ�ǰ״̬�л���ʣ��ʱ��
template<int STATE_NUM>
void MultiCalculagraph<STATE_NUM>::setRemainTime(const int seconds) {
	int second_escape = calculagraph_[state_].getTimespan() -  seconds;
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
	if (getCurrentCalcu()->trySwitch()) {
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



// ����״̬��TIMESPAN
template<int STATE_NUM>
void MultiCalculagraph<STATE_NUM>::setTimespan(const int seconds, const int type) {
	assert (type < STATE_NUM && type >= 0);
	calculagraph_[type].setTimespan(seconds);
}

template<int STATE_NUM>
int MultiCalculagraph<STATE_NUM>::getTimespan(const int type) const {
	assert (type < STATE_NUM && type >= 0);
	return calculagraph_[type].getTimespan();
}

#endif  // _SETTING_CALULA_GRAPH_H__
