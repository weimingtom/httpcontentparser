#ifndef _PACKETGRASPER_PROGRESSCHECK_H__
#define _PACKETGRASPER_PROGRESSCHECK_H__

// class class ProgressCheck
class ProgressCheck {
public:
	ProgressCheck(void);
	~ProgressCheck(void);

public:
	void checkCallProgress();

	bool isEnabled() const { return enabled_;}

private:
	bool enabled_;
};

#endif  // _PACKETGRASPER_PROGRESSCHECK_H__