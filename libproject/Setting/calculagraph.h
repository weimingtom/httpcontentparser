#ifndef _SETTING_CALULA_GRAPH_H__
#define _SETTING_CALULA_GRAPH_H__

#include <assert.h>

template<int STATE_NUM>
class MultiCalculagraph;

// 单个状态的定时切换
// 可以确定一个时间是否应该发生
class Calculagraph {
public:
	Calculagraph(void);
	~Calculagraph(void);
public:
	void initialize() {Reset();}

	// 尝试切换状态，如果成功， 则返回true
	// 如果失败则返回false
	bool trySwitch();

	// 设置
	void setTimespan(const int seconds);
	int getTimespan() const;

	// 一毫秒为单位MS
	int getTimespanMS() const;

	void setTimeEscapeMS(const int milseconds);
	void setTimeEscape(const int seconds);

	// 获取剩余的时间或过去的时间
	int getTimeEscape() const;
	int getTimeEscapeMS() const;
	int getRemainTime() const;
	int getRemainTimeMS() const;
private:
	friend  class MultiCalculagraph;
	friend  class CalculargraphTest;
	// 充值当前计时器
	void Reset();

	int state_begin_;
	int time_span_;

	// stop the timer
	// 当停止计时器的时候，我们保存当前的剩余时间
	// 在回复计时器的时候，根据剩余的时间重新设定state_begin_的值
public:
	bool isStopped() const { return stopped_;}
	void stop();
	void restart();
private:
	bool stopped_;
	int last_time_escape_;
};


// class MultiCalculagraph
// 多个状态的定时切换
template<int STATE_NUM>
class MultiCalculagraph {
public:
	MultiCalculagraph() {}
	~MultiCalculagraph() {}

public:
	void initialize(int type) { setCurrentState(type);}

	// 尝试切换状态，如果成功， 则返回true
	// 如果失败则返回false
	bool trySwitch();
	
	// 获取当前状态
	int  getCurrentState() const { return state_; }

	// 获取切换状态的剩余时间
	int  getRemainTime()  { return getCurrentCalcu()->getRemainTime();}
	int  getRemainTimeMS() { return getCurrentCalcu()->getRemainTimeMS();}
	void setRemainTime(const int seconds);

	// 设置和获取时间间隔
	void setTimespan(const int seconds, const int type);
	int getTimespan(const int type) const;

	void Reset() { return Reset(getCurrentState());}
	// 强制改变状态
	int  forceSwitch(int type);

	// 停止计时器
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
	// 充值及时器，但需要指明及时器的种类
	void  Reset(const int type);

	// 设置当前状态
	void setCurrentState(const int type);
	int getNextState();
	int state_;	// 当前状态
	Calculagraph calculagraph_[STATE_NUM];
};

// 设置当前状态切换的剩余时间
template<int STATE_NUM>
void MultiCalculagraph<STATE_NUM>::setRemainTime(const int seconds) {
	int second_escape = calculagraph_[state_].getTimespan() -  seconds;
	calculagraph_[state_].setTimeEscape(second_escape);
}

template<int STATE_NUM>
int MultiCalculagraph<STATE_NUM>::getNextState() {
	return (state_ + 1) % STATE_NUM;
}

// 强制改变状态
template<int STATE_NUM>
int  MultiCalculagraph<STATE_NUM>::forceSwitch(int type) {
	setCurrentState(type);
	Reset(type);
	return 0;
}
// 设置当前状态
template<int STATE_NUM>
void MultiCalculagraph<STATE_NUM>::setCurrentState(const int type) {
	assert (type < STATE_NUM && type >= 0);
	state_ = type;
	Reset(type);
}	

// 尝试切换状态
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



// 设置状态的TIMESPAN
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
