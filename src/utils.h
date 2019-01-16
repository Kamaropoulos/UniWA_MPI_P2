#define execCallbackIf(statement, callback) if (statement) callback

#define ifMyRankEquals(myRank, rank, callback) executeCallbackIf(myRank == rank, callback);

#define ifRoot(callback) if (myRank == ROOT_PROCESS) callback