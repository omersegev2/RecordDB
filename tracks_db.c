#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"
#include "pr2ex4.h"
#include "tracks_db.h"

struct tracks_db {
    LinkedList list;
    int num_of_tracks;
};


typedef struct {
    char* track_name;
    unsigned int track_length;
} track_db, *Track;

/* implement copy, match, compare print and destroy 
 * functions in order use the list
 *
*/

static ListElement copyTrack(ListElement element){

    if(element == NULL) return NULL;

    Track track = (Track)element;

    Track new_track = (Track)malloc(sizeof(track_db));
    if(new_track == NULL) return NULL;

    new_track->track_length = track->track_length;
    
    new_track->track_name = (char *)malloc(strlen(track->track_name) + 1);
    if(track->track_name == NULL){
        free(new_track);
        return NULL;
    }

    strcpy(new_track->track_name,track->track_name);

    return new_track;
}

static void freeTrack(ListElement element){
    
    Track track = (Track)element;
 
    free(track->track_name);
    free(track); 
}

static void printTrack(FILE* out, ListElement element){

    if(element == NULL) return;

    Track track = (Track)element;

    prog2_report_track(out, track->track_name, track->track_length);
}

// This will be used to finde track by name
static int matchTrackByName(ListElement element, KeyForListElement key){

    if (element == NULL || key == NULL) return 0;

    Track track = (Track)element;
    char *name = (char *)key;

    // return 1 if is equals
    return strcmp(track->track_name,name)? 0: 1;
}

// This will be used to copy list with filter function
int copyFuncForFilter(ListElement element, KeyForListElement key){
    return 1;
}

///////////////////////////////////////////////////////////////////////////////
/* API functions implementation */

TracksDB tracksDbCreate(){

    TracksDB new_tracks_db = (TracksDB)malloc(sizeof(struct tracks_db));
    if(new_tracks_db == NULL) return NULL;

    new_tracks_db->num_of_tracks = 0;
    
    if(linkedListCreate(&(new_tracks_db->list),copyTrack,freeTrack,printTrack) != LIST_SUCCESS){
        free(new_tracks_db);
        return NULL;
    }

    return new_tracks_db;
}

void tracksDbDestroy(TracksDB tracks_db){

    if(tracks_db == NULL) return;
    
    linkedListDestroy(tracks_db->list);
    
    free(tracks_db);
}

RecordsResult tracksDbAddTrack(TracksDB tracks_db, char *track_name, int track_length){

    if(tracks_db == NULL || track_name == NULL){
        return RDB_NULL_ARGUMENT;
    }

    track_db track;

    if(track_length <= 0) return RDB_INVALID_TRACK_LENGTH;
    track.track_length = track_length;

    if(linkedListFind(tracks_db->list,track_name,matchTrackByName) == LIST_SUCCESS){
        return RDB_TRACK_ALREADY_EXISTS;
    }

    track.track_name = (char *)malloc(strlen(track_name) + 1);
    if(track.track_name == NULL){
        return RDB_OUT_OF_MEMORY;
    }

    strcpy(track.track_name,track_name);

    if(linkedListInsertLast(tracks_db->list, &track) != LIST_SUCCESS){
       
        free(track.track_name);
        return RDB_OUT_OF_MEMORY;
    }

    free(track.track_name);

    tracks_db->num_of_tracks++;

    return RDB_SUCCESS;
}

RecordsResult tracksDbRemoveTrack(TracksDB tracks_db, char *track_name){
    
    if(tracks_db == NULL){
        return RDB_NULL_ARGUMENT;
    }
    linkedListGoToHead(tracks_db->list);
   
    if(linkedListFind(tracks_db->list, track_name, matchTrackByName) == LIST_SUCCESS){
        if(linkedListRemoveCurrent(tracks_db->list) != LIST_SUCCESS){
            return RDB_NULL_ARGUMENT;
        }
    } else {
        return RDB_TRACK_DOESNT_EXIST;
    }

    tracks_db->num_of_tracks--;

    return RDB_SUCCESS;
}

RecordsResult tracksDbReportTracks(TracksDB tracks_db, FILE *out){

    if(tracks_db == NULL) return RDB_NULL_ARGUMENT;

    if(tracks_db->num_of_tracks == 0) return RDB_NO_TRACKS;
   
    if(linkedListPrint(tracks_db->list ,out ,tracks_db->num_of_tracks) != LIST_SUCCESS){
        return RDB_NULL_ARGUMENT;
    }

    return RDB_SUCCESS;
}

int findTrackInRecord(TracksDB tracks_db, char *track_name){
    
    if(tracks_db == NULL) return RDB_NULL_ARGUMENT;

    if(tracks_db->num_of_tracks == 0) return RDB_NO_TRACKS;

    linkedListGoToHead(tracks_db->list);

    if(linkedListFind(tracks_db->list,track_name,matchTrackByName) != LIST_SUCCESS){
        return 0;
    }

    return 1;
}

TracksDB tracksDbTracksCopy(TracksDB tracks_db){

    if(tracks_db == NULL) return NULL;
    
    TracksDB new_tracks = (TracksDB)malloc(sizeof(struct tracks_db));
    if(new_tracks == NULL){
        return NULL;
    }

    if(linkedListFilterElements(tracks_db->list,&(new_tracks->list),copyFuncForFilter, 0) != LIST_SUCCESS){
        free(new_tracks);
        return NULL;
    }
    new_tracks->num_of_tracks = tracks_db->num_of_tracks;

    return new_tracks;
}

