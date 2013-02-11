/*
 * Copyright (c) 2010 WiYun Inc.
 * Author: luma(stubma@gmail.com)
 *
 * For all entities this program is free software; you can redistribute
 * it and/or modify it under the terms of the 'WiEngine' license with
 * the additional provision that 'WiEngine' must be credited in a manner
 * that can be be observed by end users, for example, in the credits or during
 * start up. (please find WiEngine logo in sdk's logo folder)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "wyBoneTransform.h"
#include "wyUtils.h"
#include "wyLog.h"

wyBoneTransform::wyBoneTransform() :
		m_boneName(NULL) {
}

wyBoneTransform::~wyBoneTransform() {
	for(SlotSkinKeyFrameList::iterator iter = m_sskfList.begin(); iter != m_sskfList.end(); iter++) {
		wyFree((void*)iter->slotName);
		wyFree((void*)iter->skinName);
	}
}

wyBoneTransform* wyBoneTransform::make() {
	wyBoneTransform* bt = WYNEW wyBoneTransform();
	return (wyBoneTransform*)bt->autoRelease();
}

void wyBoneTransform::setBoneName(const char* name) {
	if(m_boneName) {
		wyFree((void*)m_boneName);
		m_boneName = NULL;
	}
	m_boneName = wyUtils::copy(name);
}

void wyBoneTransform::addRotationKeyFrame(RotationKeyFrame kf) {
	m_rkfList.push_back(kf);
}

void wyBoneTransform::addTranslationKeyFrame(TranslationKeyFrame kf) {
	m_tkfList.push_back(kf);
}

void wyBoneTransform::addScaleKeyFrame(ScaleKeyFrame kf) {
	m_skfList.push_back(kf);
}

void wyBoneTransform::addSlotSkinKeyFrame(SlotSkinKeyFrame kf) {
	m_sskfList.push_back(kf);
}

void wyBoneTransform::addSlotColorKeyFrame(SlotColorKeyFrame kf) {
	m_sckfList.push_back(kf);
}

void wyBoneTransform::populateFrame(float time) {
	// process rotation frame
	{
		// set time to current time
		m_currentRotation.time = time;
		
		// if empty, just set to zero
		// if not, found key frame, do interpolation if needed
		if(m_rkfList.empty()) {
			m_currentRotation.angle = 0;
		} else {
			RotationKeyFrameList::iterator iter = m_rkfList.begin();
			for(; iter != m_rkfList.end(); iter++) {
				RotationKeyFrame& kf = *iter;
				if(time < kf.time) {
					if(iter == m_rkfList.begin()) {
						m_currentRotation.angle = kf.angle;
					} else {
						RotationKeyFrame& prevKf = *(iter - 1);
						wyPoint t = getInterpolationTime(prevKf.time, kf.time, time, prevKf.interpolator);
						m_currentRotation.angle = t.x * (kf.angle - prevKf.angle) + prevKf.angle;
					}
					break;
				} else if(time == kf.time) {
					m_currentRotation = kf;
					break;
				}
			}
			
			// if exceed last one
			if(iter == m_rkfList.end()) {
				m_currentRotation.angle = m_rkfList.rbegin()->angle;
			}
		}
	}
	
	// process translation
	{
		// set time to current time
		m_currentTranslation.time = time;
		
		// if empty, just set to zero
		// if not, found key frame, do interpolation if needed
		if(m_tkfList.empty()) {
			m_currentTranslation.x = 0;
			m_currentTranslation.y = 0;
		} else {
			TranslationKeyFrameList::iterator iter = m_tkfList.begin();
			for(; iter != m_tkfList.end(); iter++) {
				TranslationKeyFrame& kf = *iter;
				if(time < kf.time) {
					if(iter == m_tkfList.begin()) {
						m_currentTranslation.x = kf.x;
						m_currentTranslation.y = kf.y;
					} else {
						TranslationKeyFrame& prevKf = *(iter - 1);
						wyPoint t = getInterpolationTime(prevKf.time, kf.time, time, prevKf.interpolator);
						m_currentTranslation.x = t.x * (kf.x - prevKf.x) + prevKf.x;
						m_currentTranslation.y = t.y * (kf.y - prevKf.y) + prevKf.y;
					}
					break;
				} else if(time == kf.time) {
					m_currentTranslation = kf;
					break;
				}
			}
			
			// if exceed last one
			if(iter == m_tkfList.end()) {
				TranslationKeyFrame& kf = *m_tkfList.rbegin();
				m_currentTranslation.x = kf.x;
				m_currentTranslation.y = kf.y;
			}
		}
	}
	
	// process scale
	{
		// set time to current time
		m_currentScale.time = time;
		
		// if empty, just set to zero
		// if not, found key frame, do interpolation if needed
		if(m_skfList.empty()) {
			m_currentScale.scaleX = 1;
			m_currentScale.scaleY = 1;
		} else {
			ScaleKeyFrameList::iterator iter = m_skfList.begin();
			for(; iter != m_skfList.end(); iter++) {
				ScaleKeyFrame& kf = *iter;
				if(time < kf.time) {
					if(iter == m_skfList.begin()) {
						m_currentScale.scaleX = kf.scaleX;
						m_currentScale.scaleY = kf.scaleY;
					} else {
						ScaleKeyFrame& prevKf = *(iter - 1);
						wyPoint t = getInterpolationTime(prevKf.time, kf.time, time, prevKf.interpolator);
						m_currentScale.scaleX = t.x * (kf.scaleX - prevKf.scaleX) + prevKf.scaleX;
						m_currentScale.scaleY = t.y * (kf.scaleY - prevKf.scaleY) + prevKf.scaleY;
					}
					break;
				} else if(time == kf.time) {
					m_currentScale = kf;
					break;
				}
			}
			
			// if exceed last one
			if(iter == m_skfList.end()) {
				ScaleKeyFrame& kf = *m_skfList.rbegin();
				m_currentScale.scaleX = kf.scaleX;
				m_currentScale.scaleY = kf.scaleY;
			}
		}
	}
}

wyPoint wyBoneTransform::getInterpolationTime(float startTime, float endTime, float curTime, Interpolator& interpolator) {
	switch(interpolator.type) {
		case LINEAR:
		{
			float t = (curTime - startTime) / (endTime - startTime);
			return wyp(t, t);
		}
		case BEZIER:
		{
			wyBezierConfig bc = wybcCubic(0, 0, 1, 1, interpolator.cp1X, interpolator.cp1Y, interpolator.cp2X, interpolator.cp2Y);
			float t = (curTime - startTime) / (endTime - startTime);
			return wybcPointAt(bc, t);
		}
		case STEP:
			return curTime >= endTime ? wyp(1, 1) : wypZero;
		default:
			return wypZero;
	}
}

void wyBoneTransform::dump() {
	// dump rotation key frame
	for(RotationKeyFrameList::iterator iter = m_rkfList.begin(); iter != m_rkfList.end(); iter++) {
		RotationKeyFrame& kf = *iter;
		LOGD("rotation key frame, time: %f, angle: %f", kf.time, kf.angle);
	}
	
	// dump translation key frame
	for(TranslationKeyFrameList::iterator iter = m_tkfList.begin(); iter != m_tkfList.end(); iter++) {
		TranslationKeyFrame& kf = *iter;
		LOGD("translation key frame, time: %f, x: %f, y: %f", kf.time, kf.x, kf.y);
	}
	
	// dump scale key frame
	for(ScaleKeyFrameList::iterator iter = m_skfList.begin(); iter != m_skfList.end(); iter++) {
		ScaleKeyFrame& kf = *iter;
		LOGD("scale key frame, time: %f, scalex: %f, scaley: %f", kf.time, kf.scaleX, kf.scaleY);
	}
	
	// dump slot skin key frame
	for(SlotSkinKeyFrameList::iterator iter = m_sskfList.begin(); iter != m_sskfList.end(); iter++) {
		SlotSkinKeyFrame& kf = *iter;
		LOGD("slot skin key frame, time: %f, skin: %s", kf.time, kf.skinName);
	}
	
	// dump slot color key frame
	for(SlotColorKeyFrameList::iterator iter = m_sckfList.begin(); iter != m_sckfList.end(); iter++) {
		SlotColorKeyFrame& kf = *iter;
		LOGD("slot color key frame, time: %f, color: 0x%x", kf.time, kf.color);
	}
}