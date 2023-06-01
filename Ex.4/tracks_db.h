#ifndef __TRACKS_DB_H__
#define __TRACKS_DB_H__

typedef struct tracks_db *TracksDB;

TracksDB tracksDbCreate();

void tracksDbDestroy(TracksDB tracks_db);

RecordsResult tracksDbAddTrack(TracksDB tracks_db, char *track_name, int track_length);

RecordsResult tracksDbRemoveTrack(TracksDB tracks_db, char *track_name);

RecordsResult tracksDbReportTracks(TracksDB tracks_db, FILE *out);

int findTrackInRecord(TracksDB tracks_db, char *track_name);

#endif // __TRACKS_DB_H__
