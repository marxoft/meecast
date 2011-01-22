#ifndef SORCELIST_H
#define SORCELIST_H
////////////////////////////////////////////////////////////////////////////////
#include <vector>
#include "source.h"
#include "stationlist.h"
#include "abstractconfig.h"
////////////////////////////////////////////////////////////////////////////////
#if defined (BSD) && !_POSIX_SOURCE
    #include <sys/dir.h>
    typedef struct dirent Dirent;
#else
    #include <dirent.h>
    #include <linux/fs.h>
    typedef struct dirent Dirent;
#endif
////////////////////////////////////////////////////////////////////////////////
namespace Core {
////////////////////////////////////////////////////////////////////////////////
    class SourceList : public AbstractConfig, private std::vector<Source*>{
        StationList *_stations;
        public:
            SourceList(const std::string path = prefix + sourcesPath);
            virtual ~SourceList();
            StationList& searchStation(const std::string& station);
            Source* source(const std::string& source_name);
};
////////////////////////////////////////////////////////////////////////////////
} // namespace Core
////////////////////////////////////////////////////////////////////////////////
#endif // SORCELIST_H
