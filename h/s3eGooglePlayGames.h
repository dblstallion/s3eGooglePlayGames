/*
 * (C) 2001-2012 Marmalade. All Rights Reserved.
 *
 * This document is protected by copyright, and contains information
 * proprietary to Marmalade.
 *
 * This file consists of source code released by Marmalade under
 * the terms of the accompanying End User License Agreement (EULA).
 * Please do not use this program/source code before you have read the
 * EULA and have agreed to be bound by its terms.
 */
/*
 * WARNING: this is an autogenerated file and will be overwritten by
 * the extension interface script.
 */
#ifndef S3E_EXT_GOOGLEPLAYGAMES_H
#define S3E_EXT_GOOGLEPLAYGAMES_H

#include <s3eTypes.h>
#include "IwDebug.h"

/**
 * @author David Hunt (Units of a Human) for Fluid Games
 */

/**
 * @name Google Play Games extension for Marmalade
 */

/**	
 *	Note In Marmalade all callbacks are queued up and trigger after the next s3eDeviceYield()
 *	
 *	Your callback needs to be of the form int32 MyCallback(void *systemData,void *userData)
 *	You can specify userData when you register the callback, it is simply passed back to your callback and
 *	could be used to help the callback identify context.
 *  The return value you set is ignored in all cases.
 *  You can register by passing an s3eCallback format function to the s3eGCRegisterCallback function. 
 *	systemData has the following meaning depending on the specific callback.
 *
 */

enum s3eGPGCallbackType
{
/**
 * Initialization callback - systemData is a (s3eGPGInitializationResult*)
 */
	S3EGPG_INITIALIZATION,
	S3EGPG_MAX_ID
};

/**
 * Enum of values indicating asynchronous initialization status
 * (extension note : needs to be kept in synch with the Java GoogleGameStatus enum)
 */

enum s3eGPGInitializationResultEnum
{
	/**
	 * The service is in the process of initializing. 
	 */
	INITIALIZING,		
	/** 
	 * The user successfully signed in and we're connected 
	 */		
	SERVICE_CONNECTED,		
	/**
	 * The user failed to connect, see the errorMsg parameter on s3eGPGInitializationResult
	 */
	SERVICE_FAILED,	
	/**
	 * The License Check failed. Android only, will only happen if you've enabled anti-piracy. 
	 */		
	SERVICE_YARRRR
};

/**
 * Structure passed back to the S3EGPG_INITIALIZATION callback.
 *
 * @param error - boolean indicating if an error was returned
 * @param errorMsg - a diagnostic string that will be empty if no error
 */

struct s3eGPGInitializationResult
{
	s3eGPGInitializationResultEnum status;
	const char* errorMsg;	
};
// \cond HIDDEN_DEFINES
S3E_BEGIN_C_DECL
// \endcond

/**
 * Returns S3E_TRUE if the GooglePlayGames extension is available.
 */
s3eBool s3eGooglePlayGamesAvailable();

/**
 * @name Initialisation of Google Play Games
 */
/**
 * Initialize the Google Play Games extension and then attempt to log the user in.
 *
 * This should be in response to a user initiated request to login the first time - see Google sing in guidelines.
 * Initialization will take place asynchronously, you need to register for the S3EGPG_INITIALIZATION callback to check for completion.
 */
s3eResult s3eGPGInitialize();

/**
 * Close down Google Play Games
 * This should be called if you no longer need the service regardless of the completion status of Initialize
 */
void s3eGPGDeInitialize();

/**
 * Function to register your callbacks that the Google Games service will call on certain events
 *
 * note Callbacks are queued up and trigger after the next s3eDeviceYield(). 
 * @param callbackID A member of the s3eGPGCallbackType enum
 * @param callbackFn Your s3eCallback format function see callback definitions above for specifics
 * @param userData Optional opaque pointer you can provide that will be passed back to your callback function in the userData parameter, this is for your convenience to provide context to your callback 
 * the extension doesn't know or care what it points at.
 */
void s3eGPGRegisterCallback(s3eGPGCallbackType callbackID,s3eCallback callbackFn,void* userData);

/**
 * Function to unregister a previously registered callback.
 *
 * @param callbackID A member of the s3eGPGCallbackType enum
 * @param callbackFn Your s3eCallback format function see callback definitions above for specifics
 */
void s3eGPGUnRegisterCallback(s3eGPGCallbackType callbackID,s3eCallback callbackFn);

/**
 * @name Achievements
 */
/**
 * Unlock a named Achievement using the name field you entered in Google Play Games console
 *
 * @param id - the ID string of the achievement 
 */
void s3eGPGUnlockAchievement(const char* id);

/**
 * Increment a named Achievement usimg the name field you entered in Google Play Games console
 *
 * Use this call with the "incremental" type of achievements.
 * @param id - the ID string of the achievement 
 * @param increment - the amount to increase by (typically 1)
 */
void s3eGPGUnlockIncrementalAchievement(const char* id,int increment);

/**
 * Display the default achievements UI. Your App will go into the background while this is showing.
 */
void s3eGPGShowAchievementsUI();

/**
 * @name Achievements
 */
/**
 * Submit a score to a leaderboard for this user.
 * 
 * Pass the ID of the Leaderboard you created in the Google Play Games console
 * 
 * Implementation Note : While Google Play Games supports 64 bit scores Marmalade can't pass int64_t (long) through s3eEdkThreadRunOnOS and so we fallback to int, 
 * bear this in mind while designing you leaderboards.
 * 
 * @param leaderboardID - a string identifying the leaderboard you set up in the Google Play console.
 * @param score - an integer score to submit
 */
void s3eGPGSubmitLeaderboardScore(const char* leaderboardID, int score);

/**
 * Display a leaderboard
 * 
 * @param leaderboardID - a string identifying the leaderboard you set up in the Google Play console. Your App will go into the background while this is showing.
 */
void s3eGPGShowLeaderboardUI(const char* leaderboardID);

/**
 * Check if the user is signed in
 */
bool s3eGPGIsSignedIn();

void s3eGPGShowAllLeaderBoardsUI();

S3E_END_C_DECL

#endif /* !S3E_EXT_GOOGLEPLAYGAMES_H */
