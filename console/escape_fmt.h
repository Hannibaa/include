/*
 *****************************************************************************
 *                                                                           *
 *                          Platform Independent                             *
 *                     ANSI Escape Code VT100 Library                        *
 *							    VERSION 2.0									 *
 *						UNDER A NAME ESCAPE_FMT								 *
 *                                                                           *
 * Author: KADDA Aoues - haoues_k@yahoo.fr - 2023                            *
 *                                                                           *
 * URL :                                                                     *
 *                                                                           *
 * Copyright notice:                                                         *
 * Free use of the Library escape_fmt                                        *
 * is permitted under the guidelines and in accordance with the most current *
 *                                                                           *
 *****************************************************************************
*/


#pragma once

#include <include/console/escape_code.h>



///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//   ANSI ESCAPE CODE ASCII SEQUENCES
//   FUNCTION AND MACRO PREDEFINED HERE 
// 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//    COMMENT :
//    1. MACRO MOVETO(X,Y), X AND Y ALWAYS INTEGER, DON'T PUT FLOAT NOT WORKING.
//    2. ANSI COLOR 
//       FIRST 0 TO 15 IS ALWAYS USED COLOR
//       FROM 16 TO 231 IS GRADUAL COLOR AND WORKING LIKE SHIFT OF 6 STEP BY COLOR
//         16 + 6 * K ; AND K = 0 TO 36 , 16 + 6 * 36 NOT INCLUDE.
//    3. DEFINE STRUCTURE sCONSOLE_TEXT { text; color_fg,color_bg, coordx,coordy}.
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////
