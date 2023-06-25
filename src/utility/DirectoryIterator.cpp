#include "DirectoryIterator.h"
#include "Utility.h"
#include <string.h>

DirectoryIterator::DirectoryIterator(const string &path)
{
    fDir = opendir(path.c_str());
    fBasePath = path;
    fSkipsDir = false;
    fMatchsExtension = false;
    if(fDir != NULL)
    {
        processNext();
    }
}

DirectoryIterator::DirectoryIterator(const string &path, const string &extension)
{
    fExtension = extension;
    fDir = opendir(path.c_str());
    fBasePath = path;
    fSkipsDir = false;
    fMatchsExtension = true;
    if(fDir != NULL)
    {
        processNext();
    }
}

DirectoryIterator::~DirectoryIterator()
{
    if(fDir != NULL)
    {
        closedir(fDir);
    }
}


void DirectoryIterator::setSkipsDirectories(bool skipsDir)
{
    fSkipsDir = skipsDir;
    if(isDir())
    {
        processNext();
    }
}

bool DirectoryIterator::hasNext() const
{
    return fNextPath.size() > 0;
}

string DirectoryIterator::next()
{
    string	currentPath = fNextPath;
    
    processNext();
    return currentPath;
}

bool DirectoryIterator::isDir() const
{
    return S_ISDIR(fFileInfo.st_mode);
}

bool DirectoryIterator::isFile() const
{
    return S_ISREG(fFileInfo.st_mode);
}

void DirectoryIterator::processNext()
{
    bool			done = false;
    struct dirent	*entry;

    do
    {
        entry = readdir(fDir);

        if(entry == NULL || entry->d_ino == 0)
        {
            fNextPath = "";
            done = true;
        }
        else
        {
            fNextPath = fBasePath + "/" + entry->d_name;
            stat(fNextPath.c_str(), &fFileInfo);

            if(isDir() && !fSkipsDir)
            {
                if((fNextPath == "." || fNextPath == ".."))
                {
                    done = true;
                }
            }
            else if(isFile())
            {
                if(fMatchsExtension)
                {
                    if(pathHasExtension(fNextPath, fExtension))
                    {
                        done = true;
                    }
                }
                else
                {
                    done = true;
                }
            }
        }
    } while(!done);
}

