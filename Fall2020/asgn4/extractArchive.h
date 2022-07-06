#ifndef EXTRACT_ARCHIVE
#define EXTRACT ARCHIVE


void extractArchive(Settings *settings, int numPaths);
void extractEntry(char *header, int verbose, char **matches, int numPaths);

void createParentPath(char *oName);

#endif
