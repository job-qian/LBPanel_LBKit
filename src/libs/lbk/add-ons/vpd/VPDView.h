/* --------------------------------------------------------------------------
 *
 * Little Board Application Kit
 * Copyright (C) 2018, Anthony Lee, All Rights Reserved
 *
 * This software is a freeware; it may be used and distributed according to
 * the terms of The MIT License.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 * IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * File: VPDView.h
 * Description:
 *
 * --------------------------------------------------------------------------*/

#ifndef __LBK_VIRTUAL_PANEL_DEVICE_VIEW_H__
#define __LBK_VIRTUAL_PANEL_DEVICE_VIEW_H__

#include <be/Be.h>

#ifdef __cplusplus /* Just for C++ */

class VPDView : public BView {
public:
	VPDView(BRect frame, const char *name, uint32 resizingMode);
	virtual ~VPDView();

	void			SetWidth(uint16 w);
	void			SetHeight(uint16 h);
	void			SetPointSize(uint8 s);
	void			SetLabel(const char *str);

	uint8*			Buffer() const;
	size_t			BufferLength() const;

	void			FillRectOnBuffer(uint16 x, uint16 y,
						 uint16 w, uint16 h,
						 pattern p, bool patternVertical = false);
	void			DrawStringOnBuffer(const char *str,
						   uint16 x, uint16 y,
						   bool erase_mode = false);
	bool			SetFontHeight(uint8 h);
	void			SetPowerState(bool state);

	virtual void		GetPreferredSize(float *width, float *height);
	virtual void		Draw(BRect updateRect);

private:
	uint16 fWidth;
	uint16 fHeight;
	uint8 fPointSize;
	uint8 fDepth;
	char *fLabel;
	uint8 *fBuffer;
	size_t fBufferLength;
	bool fPowerState;

	rgb_color		PixelAt(uint16 x, uint16 y);
	void			ResizeBuffer();
};

#endif /* __cplusplus */

#endif /* __LBK_VIRTUAL_PANEL_DEVICE_VIEW_H__ */
