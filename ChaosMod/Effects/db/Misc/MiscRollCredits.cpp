#include <stdafx.h>

static void OnStart()
{
	HUD::REQUEST_ADDITIONAL_TEXT("CREDIT", 0);
	while (!HAS_ADDITIONAL_TEXT_LOADED(0))
	{
		WAIT(0);
	}
	AUDIO::PLAY_END_CREDITS_MUSIC(1);
	MISC::SET_CREDITS_ACTIVE(1);
	AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(1);
	AUDIO::SET_MOBILE_PHONE_RADIO_STATE(1);
	AUDIO::SET_RADIO_TO_STATION_NAME("RADIO_16_SILVERLAKE");
	//DO_SCREEN_FADE_OUT(2500);
	auto song = Random::GetRandomInt(0, 2);
	if (song == 0)
	{
		AUDIO::SET_CUSTOM_RADIO_TRACK_LIST("RADIO_16_SILVERLAKE", "END_CREDITS_SAVE_MICHAEL_TREVOR", 1);
	}
	else if (song == 1)
	{
		AUDIO::SET_CUSTOM_RADIO_TRACK_LIST("RADIO_16_SILVERLAKE", "END_CREDITS_KILL_MICHAEL", 1);
	}
	else
	{
		AUDIO::SET_CUSTOM_RADIO_TRACK_LIST("RADIO_16_SILVERLAKE", "END_CREDITS_KILL_TREVOR", 1);
	}
}

static void OnTick()
{
	static int alpha = 0;
	SET_RADIO_TO_STATION_NAME("RADIO_16_SILVERLAKE");
	DRAW_RECT(.5f, .5f, 1.f, 1.f, 0, 0, 0, alpha, false); // taken from PlayerBlind.cpp, DO_SCREEN_FADE_OUT causes effect to not end?
	if (alpha < 255)
	{
		alpha++;
	}
}

static void OnStop()
{
	AUDIO::PLAY_END_CREDITS_MUSIC(0);
	AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(0);
	AUDIO::SET_MOBILE_PHONE_RADIO_STATE(0);
	MISC::SET_CREDITS_ACTIVE(0);
	AUDIO::PLAY_END_CREDITS_MUSIC(0);
	//Reset everything finale_credits sets to restore playability.
	//DO_SCREEN_FADE_IN(2500);
}

static RegisterEffect registerEffect(EFFECT_MISC_CREDITS, OnStart, OnStop, OnTick);