
#include <stdio.h>
#include "records_db.h"


int main() {

    printf("***********************************START***********************************\n");  

    RecordsDB RDB = recordsDbCreate();

    int year = 1990;

    recordsDbAddRecord(RDB, "pink floyd", year, ROCK);
    recordsDbAddRecord(RDB, "eric clapton", year, POP);
    
    recordsDbAddTrackToRecord(RDB,"pink floyd","track1", 120);
    recordsDbAddTrackToRecord(RDB,"pink floyd","With or Without You", 296);
    recordsDbAddTrackToRecord(RDB,"eric clapton","With or Without You", 29);

    recordsDbReportRecords(RDB,ROCK);
    
    printf("REMOVE RECORD - 'track1'\n");

    recordsDbRemoveTrackFromRecord(RDB,"pink floyd","track1");

    printf("REPORT CONTAINING RECORD\n");
    recordsDbReportContainingRecords(RDB, "With or Without You");

    // recordsDbReportRecords(RDB,ALL_CATEGORIES);


    recordsDbDestroy(RDB);
    printf("*************************************END***********************************\n");

    return 0;
}
