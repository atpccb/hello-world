//==============================================================================
//
//  File        : mmps_oaep.h
//  Description : OAEP setting
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================
/**
 *  @file mmps_oaep.h
 *  @brief Header File for OAEP processing
 *  @author Penguin Torng
 *  @version 1.0
 */



#ifndef _MMPS_OAEP_H_
#define _MMPS_OAEP_H_


/** @addtogroup MMPS_AUDIO
@{
*/


//==============================================================================
//
//                              COMPILER OPTION
//
//==============================================================================



//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================


//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================
MMP_ERR  MMPS_OAEP_SetEffectType(MMP_ULONG ulEffectType);
MMP_ERR  MMPS_OAEP_SetPlayingMode(MMP_ULONG ulPlayingMode);
MMP_ERR  MMPS_OAEP_SetAudioOutType(MMP_ULONG ulAudioOutType);
/// @}

#endif // _MMPS_OAEP_H_
