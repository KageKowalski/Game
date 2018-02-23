// Klayton Kowalski

#ifndef ANIMATION_H
#define ANIMATION_H

class Animation {

public:

	Animation(unsigned int initAnimStep, unsigned int frameWidth, unsigned int frameHeight);
	~Animation();

	void setCurrAnimStep(unsigned int step);
	unsigned int getCurrAnimStep() const;
	unsigned int getTotalAnimSteps() const;

protected:

	unsigned int m_CurrAnimStep;
	unsigned int m_TotalAnimSteps;
	unsigned int m_FrameWidth;
	unsigned int m_FrameHeight;

};

#endif