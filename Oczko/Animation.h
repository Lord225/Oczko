#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"

#define ANIM_DEBUG

// Ogólna klasa animacji, handeluje wszystkie powtarzalne czynnosci
// Automatycznie œledzi up³yw czasu, zarz¹dza blokadami wejœæ ect.
class Animation
{
	float lerp_time;
	float actual_time;
	bool block_input;
	bool _isPlaying;
public:
	Animation(float lerp_time, bool block_input)
	: lerp_time(lerp_time), block_input(block_input), _isPlaying(false), actual_time(0){}

	void TriggerAnimation() {
#ifdef ANIM_DEBUG
		std::cout << "Triggered animation" << std::endl;
#endif
		_isPlaying = true;
		actual_time = 0;
		if (block_input) {
			Button::isAllButtonsBloced += 1;
		}
	}

	void Update(float delta_time) {
		actual_time += delta_time;
		if (actual_time > lerp_time) {
			_isPlaying = false;
			if (block_input) {
				Button::isAllButtonsBloced -= 1;
			}
#ifdef ANIM_DEBUG
			std::cout << "Animation Ended" << std::endl;
#endif
			return;
		}
		UpdateFunction(actual_time / lerp_time, delta_time);
	}

	virtual void UpdateFunction(float time, float delta_time) = 0;
	
	bool isPlaying() {
		return _isPlaying;
	}

};

