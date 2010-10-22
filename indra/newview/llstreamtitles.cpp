/* Copyright (c) 2010 Katharine Berry All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 *   1. Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above
 *      copyright notice, this list of conditions and the following
 *      disclaimer in the documentation and/or other materials provided
 *      with the distribution.
 *   3. Neither the name Katharine Berry nor the names of any contributors
 *      may be used to endorse or promote products derived from this
 *      software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY KATHARINE BERRY AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL KATHARINE BERRY OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "llviewerprecompiledheaders.h"

#include "llstreamtitles.h"

#include "llsd.h"
#include "llaudioengine.h"
#include "llstartup.h"
#include "llstreamingaudio.h"
#include "llnotificationsutil.h"
#include "llviewercontrol.h"

#include <boost/bind.hpp>

LLStreamTitles::LLStreamTitles() : LLEventTimer(1.0)
{
	if(!gAudiop)
	{
		// We're too early... do we need to handle this?
		LL_WARNS("StreamTitles") << "No audio system! Bailing out." << LL_ENDL;
		delete this;
		return;
	}
	if(gAudiop->getStreamingAudioImpl()->getMetadataSignal() == NULL)
	{
		LL_WARNS("StreamTitles") << "Streaming audio implementation doesn't support metadata; bailing out." << LL_ENDL;
		delete this;
		return;
	}
	LL_INFOS("StreamTitles") << "Stream titles initialised without incident." << LL_ENDL;
	gAudiop->getStreamingAudioImpl()->getMetadataSignal()->connect(boost::bind(&LLStreamTitles::onStreamMetadata, this, _1, _2));
}

// We have to poll this, because if we just send the notification from the metadata callback, SL eventually tries to
// perform OpenGL operations from the audio streaming thread and promptly crashes.
// There's probably a better solution to this, but...
BOOL LLStreamTitles::tick()
{
	if(!mNewData)
		return false;
	mNewData = false;

	LLSD args;
	args["TITLE"] = mTitle;
	if(mArtist.length() > 0)
	{
		args["ARTIST"] = mArtist;
		LLNotificationsUtil::add("StreamMetadata", args);
	}
	else
	{
		LLNotificationsUtil::add("StreamMetadataNoArtist", args);
	}
	return false;
}

void LLStreamTitles::onStreamMetadata(const std::string& artist, const std::string& title)
{
	if(title.length() == 0)
		return;

	LL_INFOS("StreamTitles") << "Got stream metadata; now playing '" << title << "' by '" << artist << "'." << LL_ENDL;
	if(gSavedSettings.getBOOL("ShowStreamMetadata"))
	{
		mNewData = true;
		mArtist = artist;
		mTitle = title;
	}
}
