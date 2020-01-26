#ifndef DBFILE_H
#define DBFILE_H

#include <map>
#include <string>
#include <vector>

#include "GameDatabase.h"

#ifdef _WIN32
#    ifdef BUILDING_CORE_DLL
#        define _DBFILE_API_ __declspec(dllexport)
#    else
#        define _DBFILE_API_ __declspec(dllimport)
#    endif
#else
#    define _DBFILE_API_
#endif


class _DBFILE_API_ DBFile
{
public:
  explicit DBFile();
  virtual ~DBFile() {};

	virtual bool open() = 0;

  virtual bool close() = 0;

	// Iteration over database
	class Iterator
	{
	  public:
    Iterator(DBFile &f, unsigned int index) :
      file(f), recordIndex(index) {}
		  
      /// Advance (prefix only)
		  Iterator & operator++() 
      { 
        recordIndex++;
			  return *this; 
		  }	
		
      std::vector<std::string> get() const
      {
        return file.get(recordIndex);
      }
	
		  /// Comparison
		  bool operator==(const Iterator &b) const
		  {
        return recordIndex == b.recordIndex;
		  }
		
      bool operator!=(const Iterator &b) const
		  {
        return recordIndex != b.recordIndex;
		  }
	  
    private:
      DBFile &file;
      unsigned int recordIndex;
	};

	/// Get begin iterator over records
	Iterator begin();
	/// Get begin iterator over records
	Iterator end();

	/// Trivial
	size_t getRecordCount() const { return recordCount; }

  /// Set table structure for further reading
  void setTableStructure(core::TableStructure * structure) { tableStructure = structure; }

  // to be implemented in inherited classes to get actual record values (specified by recordOffset), following "structure" format
  virtual std::vector<std::string> get(unsigned int recordIndex) const = 0;

protected:
	size_t recordSize;
	size_t recordCount;
	size_t fieldCount;
	size_t stringSize;
	unsigned char *data;
	unsigned char *stringTable;
  core::TableStructure * tableStructure;

  private:
  DBFile(const DBFile &);
  void operator=(const DBFile &);
};

#endif
