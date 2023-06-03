#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "set.h"
#include "pr2ex4.h"
#include "records_db.h"
#include "tracks_db.h"

#define MIN_YEAR 1900

struct RecordsDB_s {
    Set set;
    int num_of_records;
};

typedef struct {
    char *name;
    unsigned int year;
    unsigned int num_of_tracks_added;
    TracksDB tracks;
    RecordsCategory category;
}record_db, *Record;

/* Implement copy, match, compare print and destroy
 * 
 */

static int compareRecordsByName(SetElement element1, SetElement element2){
    
    if(element1 == NULL || element2 == NULL){
        return 0;
    }

    Record record1 = (Record)element1;
    Record record2 = (Record)element2;

    return strcmp(record1->name,record2->name);
}

static SetElement copyRecord(SetElement element){
    
    if(element == NULL) return NULL;

    Record record = (Record)element;

    Record new_record = (Record)malloc(sizeof(record_db));
    if(new_record == NULL) return NULL;

    new_record->name = (char *)malloc(strlen(record->name)+1);
    if(new_record->name == NULL){
        free(new_record);
        return NULL;
    }

    strcpy(new_record->name,record->name);
    new_record->num_of_tracks_added = record->num_of_tracks_added;
    new_record->category = record->category;
    new_record->year = record->year;
    
    new_record->tracks = tracksDbTracksCopy(record->tracks);
    
    return new_record;
}

static void freeRecord(SetElement element){
   
   if(element){

        Record record = (Record)element;

        if(record->tracks != NULL){
            tracksDbDestroy(record->tracks);
        }

        free(record->name);
        free(record);
    }
}

static void printRecord(FILE* out, SetElement element){
    
    if(element == NULL) return;

    Record record = (Record)element;

    prog2_report_record(out, record->name, record->year, record->num_of_tracks_added, record->category);

    tracksDbReportTracks(record->tracks, out);
}

// This will be used to find record by name
static int matchRecordByName(SetElement element, KeyForSetElement key){

    if(element == NULL || key == NULL){
        return 0;
    }

    Record record = (Record)element;
    char *name = (char *)key;

    return strcmp(record->name, name)? 0 : 1;
}

// This will be used to filter record by category
static int matchRecordByCategory(SetElement element, KeyForSetElement key){
    
    if(element == NULL) return 0;
    
    Record record = (Record)element;
    RecordsCategory category = (RecordsCategory)key;

    if(category == ALL_CATEGORIES) return 1;

    return record->category == category;
}

// This will be used to filter record with containing track
static int matchRecordByTrackName(SetElement element, KeyForSetElement key){
    
    if(element == NULL) return 0;
    
    Record record = (Record)element;
    char *track_name = (char *)key;

    //if findTrackInRecord return 1 its add record to set
    return findTrackInRecord(record->tracks, track_name);

}
///////////////////////////////////////////////////////////////////////////////
/* API functions implementation */

RecordsDB recordsDbCreate(){

    RecordsDB new_records_db = (RecordsDB)malloc(sizeof(struct RecordsDB_s));
    if(new_records_db == NULL) return NULL;

    new_records_db->num_of_records = 0;

    if(setCreate(&(new_records_db->set), compareRecordsByName, copyRecord, freeRecord, printRecord) != SET_SUCCESS){
        free(new_records_db);
        return NULL;
    }

    return new_records_db;
}

void recordsDbDestroy(RecordsDB records_db){

    if(records_db == NULL) return;

    if(records_db->set == NULL) {
        free(records_db);
        return;
    }

    setDestroy(records_db->set);
    free(records_db);
}
    
RecordsResult recordsDbAddRecord(RecordsDB rdb, const char *name, int year, RecordsCategory category){

    if(rdb == NULL || name == NULL) return RDB_NULL_ARGUMENT;

    record_db record;

    if(year < MIN_YEAR){
        return RDB_INVALID_YEAR;
    }
    record.year = year;

    record.name = (char *)malloc(strlen(name)+1);
    if(record.name == NULL){
        return RDB_OUT_OF_MEMORY;
    }
    strcpy(record.name, name);
    
    if(category > CLASSIC || category < ROCK){
        free(record.name);
        return RDB_INVALID_CATEGORY;
    }
    record.category = category;

    record.tracks = tracksDbCreate();
    record.num_of_tracks_added = 0;

    if(setIsIn(rdb->set, &record) == SET_ELEMENT_EXISTS){
        free(record.name);
        tracksDbDestroy(record.tracks);
        return RDB_RECORD_ALREADY_EXISTS;
    }

    if(setAdd(rdb->set, &record) != SET_SUCCESS){
        free(record.name);
        tracksDbDestroy(record.tracks);
        return RDB_OUT_OF_MEMORY;
    }

    free(record.name);
    tracksDbDestroy(record.tracks);

    rdb->num_of_records++;

    return RDB_SUCCESS;
}

RecordsResult recordsDbRemoveRecord(RecordsDB rdb, char *name){

    if(rdb == NULL || name == NULL){
        return RDB_NULL_ARGUMENT;
    }
   
    Record record;

    if(setFind(rdb->set, (SetElement *)&record, name, matchRecordByName) == SET_ELEMENT_DOES_NOT_EXIST){
        return RDB_RECORD_DOESNT_EXIST;
    }

    if(setRemove(rdb->set, (SetElement *)record) == SET_ELEMENT_DOES_NOT_EXIST){
        return RDB_RECORD_DOESNT_EXIST;
    }

    rdb->num_of_records--;

    return RDB_SUCCESS;
}

RecordsResult recordsDbAddTrackToRecord (RecordsDB rdb, char *recordName, char *trackName, int trackLength){

    Record record; 

    if(setFind(rdb->set, (SetElement *)&record, recordName, matchRecordByName) == SET_ELEMENT_DOES_NOT_EXIST){
        return RDB_RECORD_DOESNT_EXIST;
    }

    RecordsResult res;

    res = tracksDbAddTrack(record->tracks,trackName,trackLength);
    if(res != RDB_SUCCESS) return res;
    
    record->num_of_tracks_added++;

    return RDB_SUCCESS;
}

RecordsResult recordsDbRemoveTrackFromRecord (RecordsDB rdb, char *recordName, char *trackName){

    if(rdb == NULL || recordName == NULL || trackName == NULL){
        return RDB_NULL_ARGUMENT;
    }

    Record record; 

    if(setFind(rdb->set, (SetElement *)&record, recordName, matchRecordByName) == SET_ELEMENT_DOES_NOT_EXIST){
        return RDB_RECORD_DOESNT_EXIST;
    }

    RecordsResult res;

    res = tracksDbRemoveTrack(record->tracks,trackName);
    if(res != RDB_SUCCESS) return res;

    record->num_of_tracks_added--;

    return RDB_SUCCESS;
}

RecordsResult recordsDbReportRecords (RecordsDB rdb, RecordsCategory category){

    if(rdb == NULL) return RDB_NULL_ARGUMENT;

    if(rdb->num_of_records == 0) return RDB_NO_RECORDS;

    Set set;

    if(setFilter(rdb->set, &set, (SetElement *)category, matchRecordByCategory) != SET_SUCCESS){
        return RDB_OUT_OF_MEMORY;
    }
    
    if(setGetSize(set) <= 0){
        setDestroy(set);
        return RDB_NO_RECORDS;
    }
    
    if(setPrintSorted(set,stdout,rdb->num_of_records, compareRecordsByName) != SET_SUCCESS){
        setDestroy(set);
        return RDB_NULL_ARGUMENT;
    }

    setDestroy(set);

    return RDB_SUCCESS;
}

RecordsResult recordsDbReportTracksOfRecord(RecordsDB rdb, char *recordName){

    if(rdb == NULL) return RDB_NULL_ARGUMENT;

    if(rdb->num_of_records == 0) return RDB_NO_RECORDS;

    Record record; 

    if(setFind(rdb->set, (SetElement *)&record, recordName, matchRecordByName) == SET_ELEMENT_DOES_NOT_EXIST){
        return RDB_RECORD_DOESNT_EXIST;
    }

    printRecord(stdout,record);

    return RDB_SUCCESS;
}

RecordsResult recordsDbReportContainingRecords(RecordsDB rdb, char *trackName){

    if(rdb == NULL) return RDB_NULL_ARGUMENT;

    if(rdb->num_of_records == 0) return RDB_NO_RECORDS;

    Set set;

    if(setFilter(rdb->set, &set, trackName, matchRecordByTrackName) != SET_SUCCESS){
        return RDB_OUT_OF_MEMORY;
    }

    int size = setGetSize(set);

    if(size <= 0){
        setDestroy(set);
        return RDB_NO_RECORDS;
    }

    if(setPrintSorted(set,stdout, size, compareRecordsByName) != SET_SUCCESS){
        setDestroy(set);
        return RDB_NULL_ARGUMENT;
    }

    setDestroy(set);
  
    return RDB_SUCCESS;
}

