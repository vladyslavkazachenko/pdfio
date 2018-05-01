#pragma once

#include <string>
#include <vector>

#include "pdfio/pdf1_4/file_structure.h"
#include "integer.h"
#include "dictionary.h"
#include "indirect_reference.h"
#include "array.h"
#include "hexstring.h"
#include "dictionary.h"
#include "stream.h"
#include "name.h"

namespace pdfio
{
   
namespace pdf1_7
{

/*! \brief PDF File Structure.*/
struct FileStructure
{
   /*! \brief PDF File Header.*/
   class Header
   {
   public:
      /*! \brief Constructs the Header by initializing the version_ by the 
       version.
       */
      inline Header(const std::string &version = "")
      : version_(version)
      {
         
      }
      /*! \brief Converts the Header to std::string by returning the version_.*/
      inline operator std::string() const
      {
         return version_;
      }
      /*! \brief Assigns the version to the version_.*/
      inline Header &operator=(const std::string &version)
      {
         version_ = version;
         return *this;
      }
      /*! \brief Compares the version to the version_.*/
      inline bool operator==(const std::string &version) const
      {
         return version_ == version;
      }
      
   private:
      std::string version_;
   };
   typedef std::tuple<Integer, Integer, Integer> XrefEntryLayout;
   /*! \brief PDF File Cross-Reference Subsection Entry.*/
   enum class XrefEntryType: Integer
   {
      kFree = 0,
      kUncompressed = 1,
      kCompressed = 2,
   };
   typedef std::tuple<XrefEntryLayout, XrefEntryType, Integer, Integer> XrefEntry;
   /*! \brief PDF File Cross-Reference Subsection.*/
   struct XrefSubsection
   {
      Integer firstObjectNumber_ = 0;
      std::vector<XrefEntry> entries_;
   };
   
   /*! \brief PDF File Cross-Reference Section.*/
   struct XrefSection
   {
      std::vector<XrefSubsection> subsections_;
   };

   /*! \brief PDF File Trailer.*/
   class Trailer : public pdf1_4::FileStructure::Trailer
   {
   public:
      /*! \brief Assigns the other to the Trailer.*/
      Trailer &operator=(const Trailer &other);
      /*! \brief Adds optional entries into the parent Dictionary.*/
      void prepare4Reading();
   };
   
   /*! \brief PDF Cross-Reference Stream.*/
   class XrefStream: public Stream, public Trailer
   {
   public:
      XrefStream();
      /*! \brief Checks whether the parent Dictionary contains entry with key 
       "Index".
       */
      bool hasIndex() const;
      /*! \brief Returns value by key "Index".*/
      const Array<Integer> &index() const;
      /*! \brief Returns value by key "Index".*/
      Array<Integer> &index();
      /*! \brief Returns value by key "W".*/
      const Array<Integer> &w() const;
      /*! \brief Returns value by key "W".*/
      Array<Integer> &w();
      /*! \brief Adds optional entries into the parent Dictionary.*/
      void prepare4Reading();
      
      static const Name kTypeValue;
   };
   /*! \brief PDF File Version.*/
   struct Version
   {
      pdf1_4::FileStructure::XrefSection xrefSection_;
      Trailer trailer_;
   };

   std::vector<Version> versions_;
};
   
}

}
