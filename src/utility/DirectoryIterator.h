#ifndef __DIRITERATOR__
#define __DIRITERATOR__


#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;

/*!
 * @class DirectoryIterator
 *
 * This class will iterate over a directory. It has options to filter the results
 * by file extension, and weither or not to include directories. There are also
 * methods to figure out if the entry is a file or directory.
 */
class DirectoryIterator
{
protected:
    DIR		*fDir;
    string	fNextPath;
    struct stat	fFileInfo;
    string	fBasePath;
    bool	fSkipsDir;
    string	fExtension;
    bool	fMatchsExtension;

public:
    /*!
     @function DirectoryIterator
     @abstract Creates a DirecotryIterator for a given path. If it isn't a directory, or if it doesn't
         exist, then hasNext will return false.
     @param path The path of the directory to iterate over
     */
        DirectoryIterator(const string &path);
    
    /*!
     @function DirectoryIterator
     @abstract Creates a DirecotryIterator for a given path. If it isn't a directory, or if it doesn't
         exist, then hasNext will return false. Also sets up the iterator to filter the results based on
         a file extension
     @param path The path of the directory to iterate over
     @param extension The file extension to filter the results by
     */
    DirectoryIterator(const string &path, const string &extension);
    ~DirectoryIterator();

    /*!
     @function setSkipsDirectories
     @abstract Sets the flag that controls weither or not directories are included in the results.
     @param skipsDir The new flag value
     */
    void setSkipsDirectories(bool skipsDir);

    /*!
     @function hasNext
     @abstract Checks to see if there is another entry in the directory
     @result true if there is another entry, false otherwise.
     */
    bool hasNext() const;

    /*!
     @function next
     @abstract Returns the name of the next entry.
     @resurt The file path of the next entry
     */
    string next();

    /*!
     @function isDir
     @abstract Checks to see if the next entry is a folder.
     @result true if folder, false otherwise.
     */
    bool isDir() const;
    
    /*!
     @function isFile
     @abstract Checks to see if the next entry is a file or not.
     @result true if file, false otherwise
     */
    bool isFile() const;

protected:
    /*!
     * Reads in the next directory entry.
     */
    void processNext();
};

#endif
