// Klayton Kowalski

#ifndef ANIMATION_H
#define ANIMATION_H

// All graphic classes that have an animation to them should inherit from Animation
// or one of its subclasses. Inheriting from this class will allow you
// to display each animation step with no binding time step.
class Animation {

public:

	// Constructor takes the initial animation step to start on, the total amount of animation steps,
	// the width of a single frame of the animation, and the height of a single frame of the animation.
	Animation(unsigned int initAnimStep, unsigned int totalAnimSteps, unsigned int frameWidth, unsigned int frameHeight);
	~Animation();

	// Sets the current animation step to be rendered.
	void setCurrAnimStep(unsigned int step);

	// Retrieves the current animation step.
	unsigned int getCurrAnimStep() const;

	// Retrieves the total amount of animation steps that exist.
	unsigned int getTotalAnimSteps() const;

	// Retrieves the width of a single frame of the animation.
	unsigned int getFrameWidth() const;

	// Retrieves the height of a single frame of the animation.
	unsigned int getFrameHeight() const;

protected:

	// Current animation step being rendered.
	unsigned int m_CurrAnimStep;

	// Total amount of animation steps that exist.
	unsigned int m_TotalAnimSteps;

	// Width of a single frame of the animation, in pixel units.
	unsigned int m_FrameWidth;

	// Height of a single frame of the animation, in pixel units.
	unsigned int m_FrameHeight;

};

#endif