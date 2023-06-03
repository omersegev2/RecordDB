#ifndef __PROG2_EX4_H__
#define __PROG2_EX4_H__

#include <stdio.h>

/*
 * This file contains the function prototypes for the functions you need to
 * implement for exercises of programming2 course.
 * You should not change this file.
 *
 * Author:  David Avdat
 */

/******************************************************************************
 * enum RecordsResult
 */

typedef enum RecordsResult_e {
    RDB_SUCCESS,
    RDB_NULL_ARGUMENT,
    RDB_RECORD_DOESNT_EXIST,
    RDB_INVALID_YEAR,
    RDB_INVALID_CATEGORY,
    RDB_RECORD_ALREADY_EXISTS,
    RDB_NO_RECORDS,
    RDB_INVALID_TRACK_LENGTH,
    RDB_TRACK_ALREADY_EXISTS,
    RDB_NO_TRACKS,
    RDB_TRACK_DOESNT_EXIST,
    RDB_OUT_OF_MEMORY
} RecordsResult;

#define ALL_CATEGORIES 9999

/******************************************************************************
 * enum record_category_e
 */
typedef enum {
    ROCK,
    POP,
    JAZZ,
    BLUES,
    HIP_HOP,
    COUNTRY,
    CLASSIC, 
} RecordsCategory;


/******************************************************************************
 * Function: prog2_report_record
 * Description: This function prints record details to a given output stream.
 * Parameters:
 *    out - the output stream
 *    name - the record name
 *    year - the record year
 *    num_of_tracks - the number of tracks
 *    category - the record category
 * Returns: Nothing.
 */ 
 void prog2_report_record(FILE *out, const char *name, unsigned int year, unsigned int num_of_tracks_added, RecordsCategory category);


/******************************************************************************
 * Function: prog2_report_track
 * Description: This function prints track details to a given output stream.
 * Parameters:
 *   out - the output stream
 *   name - the track name
 *   position - the track position
 *   duration - the track length
 * Returns: Nothing.
 */
void prog2_report_track(FILE *out, const char *name, unsigned int duration);

#endif /* __PROG2_EX1_H__ */
