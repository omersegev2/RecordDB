#ifndef __RECORDS_DB_H__
#define __RECORDS_DB_H__

#include "pr2ex4.h"

/*
* ADT module interface for managing a records database.
* 
* Below you'll find the functions you need to implement for this module.
* Each function has a description of what it should do and what it's input and output are.
* 
*/


/* The ADT main structure type definition */
typedef struct RecordsDB_s *RecordsDB;

/*
 * recordsDbCreate
 *
 *  Description:
 *      Creates a new empty records data base.
 *  Parameters:
 *      None
 *  Result:
 *      NULL - In case of memory allocation failure.
 *      A new RecordsDB - In case of success.
 */
RecordsDB recordsDbCreate();

/*
 * recordsDbDestroy
 *
 *  Description:
 *      Destroys an existing records data base.
 *  Parameters:
 *      The RecordsDB to destroy.
 */
void recordsDbDestroy(RecordsDB records_db);

/*
 * recordsDbAddRecord
 *
 *  Description:
 *      Adds a new record to the data base.
 *  Parameters:
 *      rdb - An existing records data base.
 *      name - The name of the record to add.
 *      year - The year of the record to add.
 *      category - The category of the record to add RecordsCategory type is defined at pr2ex4.h.
 *  Result:
 *      NULL_ARGUMENT - If rdb or name are NULL.
 *      INVALID_YEAR - If year is not above 1900.
 *      INVALID_CATEGORY - If category is not a valid category.
 *      RECORD_ALREADY_EXISTS - If a record with the same name already exists in the data base.
 *      SUCCESS - In case of success.
 */
RecordsResult recordsDbAddRecord(RecordsDB rdb, char *name, int year, RecordsCategory category);

/*
 * recordsDbRemoveRecord
 *
 *  Description:
 *      Removes a record from the data base.
 *            Note: This function should also remove all the tracks of the record.
 *  Parameters:
 *      rdb - An existing records data base.
 *      name - The name of the record to remove.
 *  Result:
 *      NULL_ARGUMENT - If rdb or name are NULL.
 *      RECORD_DOESNT_EXIST - If a record with the same name does not exist in the data base.
 *      SUCCESS - In case of success.
 */
RecordsResult recordsDbRemoveRecord (RecordsDB rdb, char *name);

/*
 * recordsDbAddTrackToRecord
 *
 *  Description:
 *      Adds a new track to a record in the data base. The track should be added in the end of the tracks list.
 *  Parameters:
 *      rdb - An existing records data base.
 *      recordName - The name of the record to add the track to.
 *      trackName - The name of the track to add.
 *      trackLength - The length of the track to add.
 *  Result:
 *      NULL_ARGUMENT - If rdb, recordName or trackName are NULL.
 *      RECORD_DOESNT_EXIST - If a record with the same name does not exist in the data base.
 *      INVALID_TRACK_LENGTH - If trackLength is not above 0.
 *      TRACK_ALREADY_EXISTS - If a track with the same name already exists in the record.
 *      SUCCESS - In case of success.
 */
RecordsResult recordsDbAddTrackToRecord (RecordsDB rdb, char *recordName, char *trackName, int trackLength);

/*
 * recordsDbRemoveTrackFromRecord
 *
 *  Description:
 *      Removes a track from a record in the data base.
 *  Parameters:
 *      rdb - An existing records data base.
 *      recordName - The name of the record to remove the track from.
 *      trackName - The name of the track to remove.
 *  Result:
 *      NULL_ARGUMENT - If rdb, recordName or trackName are NULL.
 *      RECORD_DOESNT_EXIST - If a record with the same name does not exist in the data base.
 *      TRACK_DOESNT_EXIST - If a track with the same name does not exist in the record.
 *      SUCCESS - In case of success.
 */
RecordsResult recordsDbRemoveTrackFromRecord (RecordsDB rdb, char *recordName, char *trackName);

/*
 * recordDbReportRecords
 * 
 * Description:
 *     Reports all the records in the data base of a given category.
 *     To report all records of all categoriues, use ALL_CATEGORIES defined at pr2ex4.h.
 *     The records should be sorted by their name.
 * Parameters:
 *    rdb - An existing records data base.
 *    category - The category of the records to report.
 * Result:
 *   NULL_ARGUMENT - If rdb is NULL.
 *   INVALID_CATEGORY - If category is not a valid category.
 *   NO_RECORDS - If there are no records in the data base with the given category.
 *   SUCCESS - In case of success.
*/
RecordsResult recordsDbReportRecords (RecordsDB rdb, RecordsCategory category);

/*
 * recordsDbReportTracksOfRecord
 *
 *  Description:
 *      Reports all the tracks of a given record in the data base.
 *      The tracks should be sorted as inserted order.
 *  Parameters:
 *      rdb - An existing records data base.
 *      name - The name of the record to report the tracks of.
 *  Result:
 *      NULL_ARGUMENT - If rdb or name are NULL.
 *      RECORD_DOESNT_EXIST - If a record with the same name does not exist in the data base.
 *      NO_TRACKS - If the record has no tracks.
 *      SUCCESS - In case of success.
 */
RecordsResult recordsDbReportTracksOfRecord (RecordsDB rdb, char *recordName);

/*
 * recordsDbReportRecordsContainingTracks
 *
 *  Description:
 *      Reports all the records in the data base that contain a given track.
 *      The records should be sorted by their name.
 *  Parameters:
 *      rdb - An existing records data base.
 *      trackName - The name of the track to search for.
 *  Result:
 *      NULL_ARGUMENT - If rdb or name are NULL.
 *      NO_RECORDS - If there are no records in the data base that contain the track.
 *      SUCCESS - In case of success.
 */
RecordsResult recordsDbReportContainingRecords (RecordsDB rdb, char *trackName);

#endif
